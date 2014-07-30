#include "stdafx.h"
#include "Image.h"
#include "Line.h"
#include "Filters.h"
#include <iostream>
#include <fstream>

CMyImage::CMyImage()
{
	m_p1.x = m_p1.y = 0;
	m_p2.x = m_p2.y = 0;
	m_id = IM_IMAGE;
	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
	m_ImageData = NULL;
	m_Original = NULL;
	m_Base = Eyes();
}

CMyImage::~CMyImage(){
	if(m_ImageData != NULL) delete [] m_ImageData;
	if(m_Original != NULL) delete [] m_Original;
}

CMatrix3 CMyImage::GetModelView(){
	return m_Traslate * m_Rotate * m_Scale * m_Base;
}

/*
	p1-----p2
	|      |
	|      |
	p4_____p3

*/
void CMyImage::OnDraw(CBackBuffer *pDC, POINT WindowsSize)
{
	//Transform points
	m_Model = GetModelView();
	CPOINT2F	p0 = m_Model * m_p1,
				p1 = m_Model * m_p2,
				p2 = m_Model * m_p3,
				p3 = m_Model * m_p4;

	

	POINT pp0, pp1;
	pp0.x = int(p0.x + 0.5);
	pp0.y = int(p0.y + 0.5);
	pp1.x = int(p2.x + 0.5);
	pp1.y = int(p2.y + 0.5);
	

	int draw = 2;

	CMatrix3 inv = Invert(m_Model);
	ScanLine(pDC,1,p0, p1, p2, inv);
	ScanLine(pDC,1,p0, p2, p3, inv);
}

void CMyImage::ScanLine(CBackBuffer *pDC, int draw, CPOINT2F p0, CPOINT2F p1, CPOINT2F p2, CMatrix3 inv){
	CPOINT2F sampl;

	int y, xmin, xmax, x, coord00, coord01, coord10, coord11, r, g, b;
	float tx, ty, epsilon = 0.000001f;
	float m1 = 0.0f, m2 = 0.0f, cy, cx;
	bool mb1 = false, mb2 = false;

	//Sort the points
	if(p2.y < p1.y) std::swap(p2,p1);
	if(p1.y < p0.y) std::swap(p0,p1);
	if(p2.y < p1.y) std::swap(p1,p2);


	//Break the larger line in two and interpolate its color
	cy = (p2.y - p0.y == 0)?0.5f:((float)(p1.y - p0.y)/(p2.y - p0.y));
	cy = (p1.y - p0.y == 0)?0.5f:(1.0f/(p1.y - p0.y));

	//Paint first half
	//Calculate the slope of p0 and p1
	if(abs(p0.x - p1.x) <= epsilon) mb1 = true;
	else m1 = float(p0.y - p1.y)/(p0.x - p1.x);

	//Calculate the slope of p0 and p2
	if(abs(p0.x - p2.x) <= epsilon) mb2 = true;
	else m2 = float(p0.y - p2.y)/(p0.x - p2.x);
	

	//Go throught every y
	for(y = int(p0.y + 0.5); y < p1.y; ++y){

		xmin = (int)((!mb1 && abs(m1) >= epsilon?( float(y - p0.y) / m1):0) + p0.x);
		xmax = (int)((!mb2 && abs(m2) >= epsilon?( float(y - p0.y) / m2):0) + p0.x);

		if(xmax < xmin) std::swap(xmin, xmax);

		cx = (xmax - xmin == 0)? 0.5f:(1.0f/(xmax - xmin));

		//Go throught every x
		for(x = xmin; x <= xmax; ++x){
			//Bilinear interpolation
			sampl = inv * CPOINT2F(x,y);
			if(0 <= sampl.x && sampl.x < m_iWidth && 0 <= sampl.y && sampl.y < m_iHeight ){
				sampl.x = min(sampl.x, m_iWidth - 2);
				sampl.y = min(sampl.y, m_iHeight - 2);
				coord00 = int(sampl.y) * m_iWidth * 3 + int(sampl.x) * 3;
				coord01 = int(sampl.y + 0.5) * m_iWidth * 3 + int(sampl.x) * 3;
				coord10 = int(sampl.y) * m_iWidth * 3 + int(sampl.x + 0.5) * 3;
				coord11 = int(sampl.y + 0.5) * m_iWidth * 3 + int(sampl.x + 0.5) * 3;

				tx = sampl.x - int(sampl.x);
				ty = sampl.y - int(sampl.y);

				r = int(((m_ImageData[coord00]) * (1.0f - tx) + (m_ImageData[coord10]) * tx) * (1.0f - ty) + ((m_ImageData[01]) * (1.0f - tx) + (m_ImageData[coord11]) * tx) * ty);
				g = int(((m_ImageData[coord00 + 1]) * (1.0f - tx) + (m_ImageData[coord10 + 1]) * tx) * (1.0f - ty) + ((m_ImageData[coord01 + 1]) * (1.0f - tx) + (m_ImageData[coord11 + 1]) * tx) * ty);
				b = int(((m_ImageData[coord00 + 2]) * (1.0f - tx) + (m_ImageData[coord10 + 2]) * tx) * (1.0f - ty) + ((m_ImageData[coord01 + 2]) * (1.0f - tx) + (m_ImageData[coord11 + 2]) * tx) * ty);

				//Interpolamos los pixeles
				if(draw == 2)	pDC->SetPixel(x, y, r, g, b);
				else			pDC->SetPixelSecured(x, y, r, g, b);
			}
		}
	}

	//Paint second half
	cy = (p2.y - p1.y == 0)? 0.5f :(1.0f/(p2.y - p1.y));

	//Calculate the slope of p0 and p1
	if(abs(p2.x - p1.x) <= epsilon) mb1 = true;
	else m1 = (float) (p2.y - p1.y)/(p2.x - p1.x);

	//Calculate the slope of p0 and p2
	if(abs(p2.x - p0.x) <= epsilon) mb2 = true;
	else m2 = (float)  (p2.y - p0.y)/(p2.x - p0.x);

	//Go throught every y
	for(y = int(p1.y + 0.5); y < p2.y; ++y){

		xmin = (int)((!mb1 && abs(m1) >= epsilon?( float(y - p2.y) / m1):0) + p2.x);
		xmax = (int)((!mb2 && abs(m2) >= epsilon?( float(y - p2.y) / m2):0) + p2.x);

		if(xmax < xmin) std::swap(xmin, xmax);

		cx = (xmax - xmin == 0)? 0.5f: (1.0f/(xmax - xmin));

		//Go throught every x
		for(x = xmin; x <= xmax; ++x){
			//Bilinear interpolation
			sampl = inv * CPOINT2F(x,y);
			if(0 <= sampl.x && sampl.x < m_iWidth && 0 <= sampl.y && sampl.y < m_iHeight){
				sampl.x = min(sampl.x, m_iWidth - 2);
				sampl.y = min(sampl.y, m_iHeight - 2);
				coord00 = int(sampl.y) * m_iWidth * 3 + int(sampl.x) * 3;
				coord01 = int(sampl.y + 0.5) * m_iWidth * 3 + int(sampl.x) * 3;
				coord10 = int(sampl.y) * m_iWidth * 3 + int(sampl.x + 0.5) * 3;
				coord11 = int(sampl.y + 0.5) * m_iWidth * 3 + int(sampl.x + 0.5) * 3;


				tx = sampl.x - int(sampl.x);
				ty = sampl.y - int(sampl.y);

				r = int(((m_ImageData[coord00]) * (1.0f - tx) + (m_ImageData[coord10]) * tx) * (1.0f - ty) + ((m_ImageData[01]) * (1.0f - tx) + (m_ImageData[coord11]) * tx) * ty);
				g = int(((m_ImageData[coord00 + 1]) * (1.0f - tx) + (m_ImageData[coord10 + 1]) * tx) * (1.0f - ty) + ((m_ImageData[coord01 + 1]) * (1.0f - tx) + (m_ImageData[coord11 + 1]) * tx) * ty);
				b = int(((m_ImageData[coord00 + 2]) * (1.0f - tx) + (m_ImageData[coord10 + 2]) * tx) * (1.0f - ty) + ((m_ImageData[coord01 + 2]) * (1.0f - tx) + (m_ImageData[coord11 + 2]) * tx) * ty);

				//Interpolamos los pixeles
				if(draw == 2)	pDC->SetPixel(x, y, r, g, b);
				else			pDC->SetPixelSecured(x, y, r, g, b);
			}
		}
	}
}

void CMyImage::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_id;
		ar << m_bgcolor;
		ar << m_linecolor;
		ar << m_filled;
		ar << m_p1.x;
		ar << m_p1.y;
		ar << m_p2.x;
		ar << m_p2.y;
	}
	else
	{
		ar >> m_bgcolor;
		ar >> m_linecolor;
		ar >> m_filled;
		ar >> m_p1.x;
		ar >> m_p1.y;
		ar >> m_p2.x;
		ar >> m_p2.y;
	}
}

void CMyImage::DrawSelected(CBackBuffer *pDC, POINT WindowsSize){

	m_Model = GetModelView();
	CPOINT2F	pp1 = m_Model * m_p1,
				pp2 = m_Model * m_p2,
				pp3 = m_Model * m_p3,
				pp4 = m_Model * m_p4;


	CColor red(255,0,0);

	POINT p1, p2, p3, p4;
	p1.x = int(pp1.x + 0.5);
	p1.y = int(pp1.y + 0.5);
	p2.x = int(pp2.x + 0.5);
	p2.y = int(pp2.y + 0.5);
	p3.x = int(pp3.x + 0.5);
	p3.y = int(pp3.y + 0.5);
	p4.x = int(pp4.x + 0.5);
	p4.y = int(pp4.y + 0.5);

	int draw;

	//Check if the figure is inside the drawing area
	if(max(p1.x, p2.x) < 0 && min(p1.x, p2.x) >= WindowsSize.x && max(p1.y, p2.y) < 0 && min(p1.y, p2.y) >= WindowsSize.y) draw = 0;
	else if(p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y && p2.x >= 0 && p2.x < WindowsSize.x && p2.y >= 0 && p2.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p1, p2, pDC, red.ToCOLORREF(), draw);

	//Check if the figure is inside the drawing area
	if(max(p2.x, p3.x) < 0 && min(p2.x, p3.x) >= WindowsSize.x && max(p2.y, p3.y) < 0 && min(p2.y, p3.y) >= WindowsSize.y) draw = 0;
	else if(p2.x >= 0 && p2.x < WindowsSize.x && p2.y >= 0 && p2.y < WindowsSize.y && p3.x >= 0 && p3.x < WindowsSize.x && p3.y >= 0 && p3.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p2, p3, pDC, red.ToCOLORREF(), draw);

	//Check if the figure is inside the drawing area
	if(max(p3.x, p4.x) < 0 && min(p3.x, p4.x) >= WindowsSize.x && max(p3.y, p4.y) < 0 && min(p3.y, p4.y) >= WindowsSize.y) draw = 0;
	else if(p3.x >= 0 && p3.x < WindowsSize.x && p3.y >= 0 && p3.y < WindowsSize.y && p4.x >= 0 && p4.x < WindowsSize.x && p4.y >= 0 && p4.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p3, p4, pDC, red.ToCOLORREF(), draw);

	//Check if the figure is inside the drawing area
	if(max(p1.x, p1.x) < 0 && min(p1.x, p4.x) >= WindowsSize.x && max(p1.y, p4.y) < 0 && min(p1.y, p4.y) >= WindowsSize.y) draw = 0;
	else if(p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y && p4.x >= 0 && p4.x < WindowsSize.x && p4.y >= 0 && p4.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p1, p4, pDC, red.ToCOLORREF(), draw);


	/*CColor green(0, 255, 0);

	pDC->Rectangle(p1.x - 5, p1.y - 5, p1.x + 5, p1.y + 5,green.ToCOLORREF());
	pDC->Rectangle(p2.x - 5, p2.y - 5, p2.x + 5, p2.y + 5,green.ToCOLORREF());
	pDC->Rectangle(p3.x - 5, p3.y - 5, p3.x + 5, p3.y + 5,green.ToCOLORREF());
	pDC->Rectangle(p4.x - 5, p4.y - 5, p4.x + 5, p4.y + 5,green.ToCOLORREF());*/


	CColor other(255, 100, 0);

	pDC->Rectangle(p1.x - 5, p1.y - 5, p1.x + 5, p1.y + 5,other.ToCOLORREF());
	pDC->Rectangle(p2.x - 5, p2.y - 5, p2.x + 5, p2.y + 5,other.ToCOLORREF());
	pDC->Rectangle(p3.x - 5, p3.y - 5, p3.x + 5, p3.y + 5,other.ToCOLORREF());
	pDC->Rectangle(p4.x - 5, p4.y - 5, p4.x + 5, p4.y + 5,other.ToCOLORREF());
}

bool CMyImage::Intersect(POINT p){

	m_Model = GetModelView();
	CPOINT2F pp = p;
	pp = Invert(m_Model) *pp;

	POINT p0, p1;
	p0.x = (int)min(m_p1.x, min(m_p2.x, min(m_p3.x,m_p4.x)));
	p0.y = (int)min(m_p1.y, min(m_p2.y, min(m_p3.y,m_p4.y)));
	p1.x = (int)max(m_p1.x, max(m_p2.x, max(m_p3.x,m_p4.x)));
	p1.y = (int)max(m_p1.y, max(m_p2.y, max(m_p3.y,m_p4.y)));

	if(p0.x <= pp.x && pp.x <= p1.x && p0.y <= pp.y && pp.y <= p1.y) return true;
	return false;
}

CPOINT2F* CMyImage::IntersectControlPoint(POINT p){
	double epsilon = 4;
	m_Model = GetModelView();
	CPOINT2F	pp1 = m_Model * m_p1,
				pp2 = m_Model * m_p2,
				pp3 = m_Model * m_p3,
				pp4 = m_Model * m_p4;



	if(abs((p.x - pp1.x)) <= epsilon && abs((p.y - pp1.y)) <= epsilon)
		return &m_p1;

	if(abs((p.x - pp2.x)) <= epsilon && abs((p.y - pp2.y)) <= epsilon)
		return &m_p2;

	if(abs((p.x - pp3.x)) <= epsilon && abs((p.y - pp3.y)) <= epsilon)
		return &m_p3;

	if(abs((p.x - pp4.x)) <= epsilon && abs((p.y - pp4.y)) <= epsilon)
		return &m_p4;

	return NULL;
}


//Scale the mage
void CMyImage::ModifyPoint(POINT p, CPOINT2F * initial, bool shift){
	
	m_Model = GetModelView();

	CMatrix3 scal;
	CPOINT2F pp1, pp3, proyected;
	pp1 = m_Model * m_p1;
	pp3 = m_Model * m_p3;
	proyected = m_Model * (*initial);

	//Calculate the midpoint
	float factor = 0.0001f, midx, midy;
	midx = abs((pp1.x + pp3.x)/2.0f);
	midy = abs((pp1.y + pp3.y)/2.0f);

	scal = Scale2D(abs(midx - p.x)/abs(midx - proyected.x), abs(midy - p.y)/abs(midy - proyected.y));
	
	//Shift to maintain the aspect ratio
	if(shift){
		float ma = max(scal.mat[0][0], scal.mat[1][1]);
		scal.mat[0][0] = scal.mat[1][1] = ma;
	}
	
	scal = scal * m_Scale;

	//Set limits to the scale factor
	scal.mat[0][0] = min(2.0f, max(0.1f, scal.mat[0][0]));
	scal.mat[1][1] = min(2.0f, max(0.1f, scal.mat[1][1]));

	m_Scale = scal;
}

//Rotate the image
void CMyImage::RotateFigure(POINT p1, POINT p2){
	m_Model = GetModelView();

	CMatrix3 rot;
	CPOINT2F pp1, pp3, proyected;
	pp1 = m_Model * m_p1;
	pp3 = m_Model * m_p3;

	//Calculate the midpoint
	float factor = 0.0001f, midx, midy;
	midx = abs((pp1.x + pp3.x)/2.0f);
	midy = abs((pp1.y + pp3.y)/2.0f);

	double	alpha1 = atan2(p1.x - midx, p1.y - midy),
			alpha2 = atan2(p2.x - midx, p2.y - midy);
	rot = Rotate2D(alpha2 - alpha1);
	
	m_Rotate = rot * m_Rotate;
}

//Trasnlate the image
void CMyImage::Translate(POINT p){
	m_Traslate = Translate2D(float(p.x), float(p.y)) * m_Traslate;
}



void CMyImage::ChangeFillColor(COLORREF c){
}

void CMyImage::ChangeLineColor(COLORREF c){
}

void CMyImage::ChangeFilled(){
}

bool CMyImage::SetBitmap(CString strBitmap)
{
    CBitmap m_bmpBitmap;
    BITMAP bm;
	BYTE* m_bmpBackData;
	HBITMAP hBitmap = (HBITMAP) ::LoadImage(AfxGetInstanceHandle(),
						strBitmap, IMAGE_BITMAP, 0, 0, 
						LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	// Do we have a valid handle for the loaded image?
	if (hBitmap)
	{
		// Delete the current bitmap
		if (m_bmpBitmap.DeleteObject())
		m_bmpBitmap.Detach(); // If there was a bitmap, detach it
		// Attach the currently loaded bitmap to the bitmap object
		m_bmpBitmap.Attach(hBitmap);

		m_bmpBitmap.GetBitmap(&bm);  //Get Bitmap Structure
		m_iWidth = bm.bmWidth;
		m_iHeight = bm.bmHeight;

		if(bm.bmBitsPixel == 32)		m_iBytesPerLine = m_iWidth * 4;
		else if(bm.bmBitsPixel == 24)	m_iBytesPerLine = m_iWidth * 3;
		else if(bm.bmBitsPixel == 8)	m_iBytesPerLine = m_iWidth * 1;


		if (m_iBytesPerLine % 4 != 0) m_iBytesPerLine += 4 - m_iBytesPerLine % 4;
		
		//Set the BB
		m_p1.x = 0;
		m_p1.y = 0;
		m_p2.x = (float)m_iWidth;
		m_p2.y = (float)0;
		m_p3.x = (float)m_iWidth;
		m_p3.y = (float)m_iHeight;
		m_p4.x = (float)0;
		m_p4.y = (float)m_iHeight;

		m_Base = Eyes();
		m_Base = Translate2D(-float(m_iWidth)/2.0f,-float(m_iHeight)/2.0f) * m_Base;
		m_Rotate = Rotate2D(0);
		m_Scale = Scale2D(1,1);
		m_Traslate = Translate2D(float(m_iWidth)/2.0f,float(m_iHeight)/2.0f);


		//Get a pointer to the information
		m_bmpBackData    = (BYTE*) bm.bmBits;

		//Transform the image
		m_ImageData = new float[m_iWidth * m_iHeight * 3];
		m_Original = new float[m_iWidth * m_iHeight * 3];


		int offset1, offset2;

		//Transform bitmap to 24 bits
		if(bm.bmBitsPixel == 32){

				for(int i = 0, k=m_iHeight - 1; i < m_iHeight ; ++i,--k)
					for(int j = 0; j < m_iWidth; ++j){
						offset1 = k * m_iBytesPerLine + j * 4;
						offset2 = i * m_iWidth * 3 + j * 3;
						
						m_ImageData[offset2]			= (float)m_bmpBackData[offset1];
						m_ImageData[offset2 + 1]		= (float)m_bmpBackData[offset1 + 1];
						m_ImageData[offset2 + 2]		= (float)m_bmpBackData[offset1 + 2];
					}
		}else if(bm.bmBitsPixel == 24){
			for(int i = 0, k=m_iHeight - 1; i < m_iHeight ; ++i,--k)
				for(int j = 0; j < m_iWidth; ++j){
					offset1 = k * m_iBytesPerLine + j * 3;
					offset2 = i * m_iWidth * 3 + j * 3;
					m_ImageData[offset2]			= (float)m_bmpBackData[offset1];
					m_ImageData[offset2 + 1]		= (float)m_bmpBackData[offset1 + 1];
					m_ImageData[offset2 + 2]		= (float)m_bmpBackData[offset1 + 2];
				}
		}else if(bm.bmBitsPixel == 8){

			//Get the number of pallete colors
			DWORD bufferSize = sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD));
			LPBITMAPINFO pBmi;
			pBmi = (LPBITMAPINFO) new BYTE[bufferSize];
			memset(pBmi, 0, bufferSize);
			pBmi->bmiHeader.biSize = sizeof(pBmi->bmiHeader);

			//Copy the image info
			GetDIBits(GetDC(NULL), hBitmap, 0, 0, NULL, pBmi, DIB_RGB_COLORS);
			//Copy the image color palette
			GetDIBits(GetDC(NULL), hBitmap, 0, 0, NULL, pBmi, DIB_RGB_COLORS);

			//The number of colors in the pal
			UINT nColors = (pBmi->bmiHeader.biBitCount)? pBmi->bmiHeader.biBitCount : 1 << pBmi->bmiHeader.biBitCount;

			//Get the palette colors
			if( nColors <= 256 ) {
				for(int i = 0, k=m_iHeight - 1; i < m_iHeight ; ++i,--k)
					for(int j = 0; j < m_iWidth; ++j){
						offset1 = k * m_iBytesPerLine + j;
						offset1 = m_bmpBackData[offset1];
						offset2 = i * m_iWidth * 3 + j * 3;

						//Palette is stored in BGR
						m_ImageData[offset2]			= (float)pBmi->bmiColors[offset1].rgbBlue;
						m_ImageData[offset2 + 1]		= (float)pBmi->bmiColors[offset1].rgbGreen;
						m_ImageData[offset2 + 2]		= (float)pBmi->bmiColors[offset1].rgbRed;
					}

					
			}		
		}else{
			AfxMessageBox("The program only support BMP with 8, 24 and 32 bits", MB_OK | MB_ICONSTOP);

			if(m_ImageData != NULL) delete [] m_ImageData;
			if(m_Original != NULL) delete [] m_Original;
			m_ImageData = NULL;
			m_Original = NULL;
			return false;
		}

		memcpy(m_Original,m_ImageData, m_iWidth * m_iHeight * 3 * sizeof(float));

		DeleteObject(m_bmpBitmap);
		// if we have a bitmap destroy
		if (m_bmpBitmap.DeleteObject())
			m_bmpBitmap.Detach(); // If there was a bitmap, detach it

		return true;

	}else{
		AfxMessageBox("The image is not a BMP image.", MB_OK | MB_ICONSTOP);
		return false;
	}
}


void CMyImage::ApplyFilter(int type, int dim){

	


	/*CFilters f;
		f.Min(m_Original, m_ImageData, m_iWidth, m_iHeight, 7);*/

	switch(type){
		case(IM_BOX):
		{
			m_Filter.Box(m_Original, m_ImageData, m_iWidth, m_iHeight, dim);
			break;
		}
		case(IM_MIN):
		{
			m_Filter.Min(m_Original, m_ImageData, m_iWidth, m_iHeight, dim);
			break;
		}
		case(IM_MAX):
		{
			m_Filter.Max(m_Original, m_ImageData, m_iWidth, m_iHeight, dim);
			break;			 
		}
		case(IM_GAUSSIAN):
		{
			m_Filter.Gaussian(m_Original, m_ImageData, m_iWidth, m_iHeight, dim);
			break;			 
		}
		case(IM_MEDIAN):
		{
			m_Filter.Median(m_Original, m_ImageData, m_iWidth, m_iHeight, dim);
			break;			 
		}
		case(IM_LAPLACE):
		{
			m_Filter.Laplace(m_Original, m_ImageData, m_iWidth, m_iHeight);
			break;			 
		}
		case(IM_SHARPEN):
		{
			m_Filter.Sharpen(m_Original, m_ImageData, m_iWidth, m_iHeight);
			break;			 
		}
	
	}	
}


