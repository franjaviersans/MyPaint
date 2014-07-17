#include "stdafx.h"
#include "Image.h"
#include "Line.h"
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
	m_bmpBackData = NULL;
	m_ImageData = NULL;
}

CMyImage::~CMyImage(){
	// if we have a bitmap destroy
	if (m_bmpBitmap.DeleteObject())
		m_bmpBitmap.Detach(); // If there was a bitmap, detach it

	if(m_ImageData != NULL) delete [] m_ImageData;
}

void CMyImage::OnDraw(CBackBuffer *pDC, POINT WindowsSize)
{
	POINT p0, p1;
	p0.x = min(m_p1.x, m_p2.x);
	p0.y = min(m_p1.y, m_p2.y);
	p1.x = max(m_p1.x, m_p2.x);
	p1.y = max(m_p1.y, m_p2.y);

	
	

	int draw = 2;

	if(p1.x < 0 || p0.x >= WindowsSize.x || p1.y < 0 || p0.y >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;

	if(draw != 0){
		if(m_bmpBackData == NULL){
			for(int i = p0.y; i < p1.y ; ++i){
				for(int j = p0.x; j < p1.x ; ++j){
					pDC->SetPixelSecured(j,i,1,0,0);
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
	pp1.x = (int)m_p2.x;
	pp1.y = (int)m_p2.y;

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
}

bool CMyImage::Intersect(POINT p){

	POINT p0, p1;
	p0.x = min(m_p1.x, m_p2.x);
	p0.y = min(m_p1.y, m_p2.y);
	p1.x = max(m_p1.x, m_p2.x);
	p1.y = max(m_p1.y, m_p2.y);

	if(p0.x <= p.x && p.x <= p1.x && p0.y <= p.y && p.y <= p1.y) return true;
	return false;
}

CPOINT2F* CMyImage::IntersectControlPoint(POINT p){
	double epsilon = 4;

	if(abs((p.x - m_p1.x)) <= epsilon && abs((p.y - m_p1.y)) <= epsilon)
		return &m_p1;

	if(abs((p.x - m_p2.x)) <= epsilon && abs((p.y - m_p2.y)) <= epsilon)
		return &m_p2;

	return NULL;
}

void CMyImage::Translate(POINT p){
	m_p1.x += p.x;
	m_p1.y += p.y;
	m_p2.x += p.x;
	m_p2.y += p.y;
}



void CMyImage::ChangeFillColor(COLORREF c){
}

void CMyImage::ChangeLineColor(COLORREF c){
}

void CMyImage::ChangeFilled(){
}

void CMyImage::SetBitmap(CString strBitmap)
{
	m_sBitmap = strBitmap;

	HBITMAP hBitmap = (HBITMAP) ::LoadImage(AfxGetInstanceHandle(),
						m_sBitmap, IMAGE_BITMAP, 0, 0, 
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
		
		m_p1.x = 0;
		m_p1.y = 0;
		m_p2.x = m_iWidth;
		m_p2.y = m_iHeight;

		

		m_bmpBackData    = (BYTE*) bm.bmBits;

		m_ImageData = new float[m_iWidth * m_iHeight * 3];

		int offset1, offset2;


		if(bm.bmBitsPixel == 32){
				for(int i = 0, k=m_iHeight - 1; i < m_iHeight ; ++i,--k)
					for(int j = 0, l=0; j < m_iWidth; ++j,++l){
						offset1 = k * m_iBytesPerLine + l * 4;
						offset2 = i * m_iWidth * 3 + j * 3;
						
						m_ImageData[offset2]			= (int)m_bmpBackData[offset1];
						m_ImageData[offset2 + 1]		= (int)m_bmpBackData[offset1 + 1];
						m_ImageData[offset2 + 2]		= (int)m_bmpBackData[offset1 + 2];
					}
		}else if(bm.bmBitsPixel == 24){
			for(int i = 0, k=m_iHeight - 1; i < m_iHeight ; ++i,--k)
				for(int j = 0, l=0; j < m_iWidth; ++j,++l){
					offset1 = k * m_iBytesPerLine + l * 3;
					offset2 = i * m_iWidth * 3 + j * 3;
					m_ImageData[offset2]			= (int)m_bmpBackData[offset1];
					m_ImageData[offset2 + 1]		= (int)m_bmpBackData[offset1 + 1];
					m_ImageData[offset2 + 2]		= (int)m_bmpBackData[offset1 + 2];
				}
		}else if(bm.bmBitsPixel == 8){
			/*for(int i = p0.y, k=m_iHeight - 1; i < p1.y ; ++i,--k)
				for(int j = p0.x, l=0; j < p1.x ; ++j,++l){
					int offset = k*m_iBytesPerLine + l*1;
					pDC->SetPixelSecured(j,i, m_bmpBackData[offset], m_bmpBackData[offset],m_bmpBackData[offset]);
				}*/
		}
	}
}