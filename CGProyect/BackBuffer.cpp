#include "stdafx.h"
#include "BackBuffer.h"

void CBackBuffer::SetPixel(int x, int y, int r, int g, int b){
	m_bmpBackData[y*BytesPerLine + x*3] = (BYTE) b;
	m_bmpBackData[y*BytesPerLine + x*3+1] = (BYTE) g;
	m_bmpBackData[y*BytesPerLine + x*3+2] = (BYTE) r;
}

void CBackBuffer::SetPixel(int x, int y, float r, float g, float b){
	m_bmpBackData[y*BytesPerLine + x*3] = (BYTE) b;
	m_bmpBackData[y*BytesPerLine + x*3+1] = (BYTE) g;
	m_bmpBackData[y*BytesPerLine + x*3+2] = (BYTE) r;
}

void CBackBuffer::SetPixel(int x, int y, CColor c){
	m_bmpBackData[y*BytesPerLine + x*3] = (BYTE) c.b;
	m_bmpBackData[y*BytesPerLine + x*3+1] = (BYTE) c.g;
	m_bmpBackData[y*BytesPerLine + x*3+2] = (BYTE) c.r;
}

void CBackBuffer::SetPixel(int x, int y, COLORREF c){
	m_bmpBackData[y*BytesPerLine + x*3] = GetBValue(c);
	m_bmpBackData[y*BytesPerLine + x*3+1] = GetGValue(c);
	m_bmpBackData[y*BytesPerLine + x*3+2] = GetRValue(c);
}

void CBackBuffer::FillLine(int x0, int y0, int x1, int y1, COLORREF c){
	if(x1 <= x0) std::swap(x0,x1);
	if(y1 <= y0) std::swap(y0,y1);

	if(x0 < 0) x0 = 0;
	if(x1 < 0) x1 = 0;
	if(x0 >=  m_iWidth) x0 = m_iWidth;
	if(x1 >=  m_iWidth) x1 = m_iWidth;

	if(y0 < 0) y0 = 0;
	if(y1 < 0) y1 = 0;
	if(y0 >=  m_iHeight) y0 = m_iHeight - 1;
	if(y1 >=  m_iHeight) y1 = m_iHeight - 1;

	if(y0 != m_iHeight && y0 >=0){
		for(;x0 < x1;++x0){
			m_bmpBackData[y0*BytesPerLine + x0*3] = GetBValue(c);
			m_bmpBackData[y0*BytesPerLine + x0*3+1] = GetGValue(c);
			m_bmpBackData[y0*BytesPerLine + x0*3+2] = GetRValue(c);
		}
	}
}

void CBackBuffer::Rectangle(int x0, int y0, int x1, int y1, COLORREF c){
	for(;y0<=y1;++y0)
		FillLine(x0,y0,x1,y0,c);
}

void CBackBuffer::SetPixelSecured(int x, int y, int r, int g, int b){
	if(0 <= x && x < m_iWidth && 0 <= y && y < m_iHeight){
		m_bmpBackData[y*BytesPerLine + x*3] = (BYTE) b;
		m_bmpBackData[y*BytesPerLine + x*3+1] = (BYTE) g;
		m_bmpBackData[y*BytesPerLine + x*3+2] = (BYTE) r;
	}
}

void CBackBuffer::SetPixelSecured(int x, int y, float r, float g, float b){
	if(0 <= x && x < m_iWidth && 0 <= y && y < m_iHeight){
		m_bmpBackData[y*BytesPerLine + x*3] = (BYTE) b;
		m_bmpBackData[y*BytesPerLine + x*3+1] = (BYTE) g;
		m_bmpBackData[y*BytesPerLine + x*3+2] = (BYTE) r;
	}
}

void CBackBuffer::SetPixelSecured(int x, int y, CColor c){
	if(0 <= x && x < m_iWidth && 0 <= y && y < m_iHeight){
		m_bmpBackData[y*BytesPerLine + x*3] = (BYTE) c.b;
		m_bmpBackData[y*BytesPerLine + x*3+1] = (BYTE) c.g;
		m_bmpBackData[y*BytesPerLine + x*3+2] = (BYTE) c.r;
	}
}

void CBackBuffer::SetPixelSecured(int x, int y, COLORREF c){
	if(0 <= x && x < m_iWidth && 0 <= y && y < m_iHeight){
		m_bmpBackData[y*BytesPerLine + x*3] = GetBValue(c);
		m_bmpBackData[y*BytesPerLine + x*3+1] = GetGValue(c);
		m_bmpBackData[y*BytesPerLine + x*3+2] = GetRValue(c);
	}
}

void CBackBuffer::Clear(){
	memset(m_bmpBackData,255, m_iHeight*BytesPerLine);
}


void CBackBuffer::Create () {
	HWND hwndActive = GetActiveWindow();
	if(hwndActive == NULL)
		return;
	RECT lpRect;
	GetClientRect(hwndActive, &lpRect);
	
	//ChangeSize(lpRect.right, lpRect.bottom);
}

void CBackBuffer::Destroy () {
	// if we have a bitmap destroy
	if (m_hBitmap != NULL) {
		//SelectObject(,m_hdcDestination);
		
		DeleteDC (m_hdcSource);
		DeleteObject (m_hBitmap);
		m_hBitmap = NULL;
		m_bmpBackData = NULL;
		ReleaseDC( NULL, m_hdcSource );
		DeleteDC (m_hdcDestination);
		ReleaseDC( NULL, m_hdcDestination );
	}
}

void CBackBuffer::Display(CDC* pdc) {
	
	// Display from CreateDIBSection creation
	BitBlt (pdc->GetSafeHdc(), 0, 0, m_iWidth, m_iHeight, m_hdcSource, 0, 0, SRCCOPY);
}

void CBackBuffer::ChangeSize(int x,int y, CDC* pdc){

	m_iWidth = x;
	m_iHeight = y;

	// Set up BitmapInfoHeader
	m_BitmapInfo.bmiHeader.biBitCount = 24;
	m_BitmapInfo.bmiHeader.biCompression = BI_RGB;
	m_BitmapInfo.bmiHeader.biHeight = -m_iHeight;
	m_BitmapInfo.bmiHeader.biWidth = m_iWidth;
	m_BitmapInfo.bmiHeader.biPlanes = 1;
	m_BitmapInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	

	// Create the DIB section with CreateDIBSection
	m_hdcDestination = pdc->GetSafeHdc();
	m_hdcSource      = CreateCompatibleDC(m_hdcDestination); 
	m_hBitmap        = CreateDIBSection (pdc->GetSafeHdc(), (BITMAPINFO *) &m_BitmapInfo, DIB_RGB_COLORS, (void **) &m_bmpBackData, NULL, 0);
	SelectObject (m_hdcSource, m_hBitmap);
	GetObject (m_hBitmap, sizeof (BITMAP), &m_bitmap);
	m_bmpBackData    = (BYTE*) m_bitmap.bmBits;
	

	BytesPerLine = m_iWidth * 3;
	if (BytesPerLine % 4 != 0)
		BytesPerLine += 4 - BytesPerLine % 4;

}