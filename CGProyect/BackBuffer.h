#ifndef CBackBuffer_H
#define CBackBuffer_H

#pragma once



#include "stdafx.h"
#include <fstream>
#include "Color.h"
#define WIDTHBYTES(bits) ((((bits) + 31) / 32) * 4)


class CBackBuffer
{
public:
	// own user defined functions	
	CBackBuffer() {};  // over ride default constructor
	~CBackBuffer() {}; // over ride default destructor
	void Create();
	void Destroy();
	void Display(CDC*);
	void ChangeSize(int,int,CDC*);
	void SetPixel(int, int, int, int ,int);
	void SetPixel(int, int, float, float ,float);
	void SetPixel(int, int, CColor);
	void SetPixel(int, int, COLORREF);
	void FillLine(int, int, int, int, COLORREF);
	void Rectangle(int, int, int, int, COLORREF);
	void SetPixelSecured(int, int, int, int ,int);
	void SetPixelSecured(int, int, float, float ,float);
	void SetPixelSecured(int, int, CColor);
	void SetPixelSecured(int, int, COLORREF);
	void Clear();
	// simple accessors
	int Height(void) const
	{ return m_iHeight; };
	int Width(void) const
	{ return m_iWidth; };

private:
	// generic back buffer info
	BYTE* m_bmpBackData;
	int m_iHeight;
	int m_iWidth;
	int BytesPerLine;

	// MS Windows specific data
	BITMAP m_bitmap;            // The BITMAP structure defines the type, width, height, color format, and bit values of a bitmap
	BITMAPINFO m_BitmapInfo;    // The BITMAPINFO structure defines the dimensions and color information for a Win32 DIB
	HBITMAP m_hBitmap;
	HDC m_hdcSource;
	HDC m_hdcDestination;
};

#endif
