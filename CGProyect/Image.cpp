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
}

CMyImage::~CMyImage(){
	if(m_ImageData != NULL) delete [] m_ImageData;
	if(m_Original != NULL) delete [] m_Original;
}

void CMyImage::OnDraw(CBackBuffer *pDC, POINT WindowsSize)
{
	POINT p0, p1;
	p0.x = (int)min(m_p1.x, m_p3.x);
	p0.y = (int)min(m_p1.y, m_p3.y);
	p1.x = (int)max(m_p1.x, m_p3.x);
	p1.y = (int)max(m_p1.y, m_p3.y);

	
	

	int draw = 2;

	if(p1.x < 0 || p0.x >= WindowsSize.x || p1.y < 0 || p0.y >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;

	if(draw != 0){
		if(m_ImageData == NULL){
			for(int i = p0.y; i < p1.y ; ++i){
				for(int j = p0.x; j < p1.x ; ++j){
					pDC->SetPixelSecured(j,i,0,0,0);
				}
			}
		}else{
			int offset;

			for(int i = 0; i < m_iHeight ; ++i)
					for(int j = 0; j < m_iWidth; ++j){
						offset = i * m_iWidth * 3 + j * 3;
						//std::cout<<m_ImageData[offset]<< "   "<< m_ImageData[offset +1]<<"   "<<m_ImageData[offset+2] <<std::endl;
						pDC->SetPixelSecured(j,i, m_ImageData[offset], m_ImageData[offset + 1],m_ImageData[offset + 2]);
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
	POINT pp0, pp1;
	pp0.x = (int)m_p1.x;
	pp0.y = (int)m_p1.y;
	pp1.x = (int)m_p3.x;
	pp1.y = (int)m_p3.y;

	CColor red(255,0,0);

	POINT p0, p1;
	p0.x = pp0.x;
	p0.y = pp0.y;
	p1.x = pp1.x;
	p1.y = pp0.y;

	int draw;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = pp0.x;
	p0.y = pp0.y;
	p1.x = pp0.x;
	p1.y = pp1.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = pp0.x;
	p0.y = pp1.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = pp1.x;
	p0.y = pp0.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);


	CColor green(0, 255, 0);

	p0.x = pp0.x;
	p0.y = pp0.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());

	p0.x = pp0.x;
	p0.y = pp1.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());

	p0.x = pp1.x;
	p0.y = pp1.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());

	p0.x = pp1.x;
	p0.y = pp0.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());


	CColor other(255, 100, 0);

	p0.x = (int)m_p1.x;
	p0.y = (int)m_p1.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

	p0.x = (int)m_p2.x;
	p0.y = (int)m_p2.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

	p0.x = (int)m_p3.x;
	p0.y = (int)m_p3.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

	p0.x = (int)m_p4.x;
	p0.y = (int)m_p4.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());
}

bool CMyImage::Intersect(POINT p){

	//TODO
	POINT p0, p1;
	p0.x = (int)min(m_p1.x, m_p2.x);
	p0.y = (int)min(m_p1.y, m_p2.y);
	p1.x = (int)max(m_p1.x, m_p2.x);
	p1.y = (int)max(m_p1.y, m_p2.y);

	if(p0.x <= p.x && p.x <= p1.x && p0.y <= p.y && p.y <= p1.y) return true;
	return false;
}

CPOINT2F* CMyImage::IntersectControlPoint(POINT p){
	double epsilon = 4;

	if(abs((p.x - m_p1.x)) <= epsilon && abs((p.y - m_p1.y)) <= epsilon)
		return &m_p1;

	if(abs((p.x - m_p2.x)) <= epsilon && abs((p.y - m_p2.y)) <= epsilon)
		return &m_p2;

	if(abs((p.x - m_p3.x)) <= epsilon && abs((p.y - m_p3.y)) <= epsilon)
		return &m_p3;

	if(abs((p.x - m_p4.x)) <= epsilon && abs((p.y - m_p4.y)) <= epsilon)
		return &m_p4;

	return NULL;
}

void CMyImage::Translate(POINT p){
	m_p1.x += p.x;
	m_p1.y += p.y;
	m_p2.x += p.x;
	m_p2.y += p.y;
	m_p3.x += p.x;
	m_p3.y += p.y;
	m_p4.x += p.x;
	m_p4.y += p.y;
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

	std::ofstream off("out.txt");
    std::cout.rdbuf(off.rdbuf()); //redirect std::cout to out.txt!
	std::cout<< type<<"   "<<dim<<std::endl;


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
