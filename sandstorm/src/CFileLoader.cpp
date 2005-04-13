#include "../include/Sandstorm.h"

CTexture CFileLoader::LoadTextureFromResource(HINSTANCE hInstance, int id) {
	HBITMAP bmp =LoadImageFromResource(hInstance,id);

	SIZE sz;
	if (!bmp) {
		throw "Unable to load bitmap";
	}

	BITMAP bitmap = {0};

	if(!GetObject(bmp, sizeof(bitmap), &bitmap)) {
			DeleteObject(bmp);
		throw "GetObject failed while loading bitmap";
	}

	sz.cx = bitmap.bmWidth;
	sz.cy = bitmap.bmHeight>0?bitmap.bmHeight:-bitmap.bmHeight;

	HDC dc  = CreateCompatibleDC(NULL);
	HDC bitmapDC = CreateCompatibleDC(dc); //HDC heb je vast all 
	SelectObject(bitmapDC, bmp);  
	BitBlt(dc,0,0,sz.cx,sz.cy, bitmapDC,0,0,SRCCOPY); //of what BLITTER dan ook) 


	// in HDC dc zit nu de bitmapdata, maak er maar een DIBje van
	BITMAPINFO bmi;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biClrImportant = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biHeight = sz.cy;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biWidth = sz.cx;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;

	int* data = new int[sz.cx*sz.cy];
	GetDIBits(dc,bmp, 0, sz.cy, data, &bmi, DIB_RGB_COLORS);

	CTexture t(sz.cx,sz.cy);
	t.Put(data);

	delete[] data;
	return t;
}

HBITMAP CFileLoader::LoadImageFromResource(HINSTANCE hInstance, const char* name) {
	return (HBITMAP)LoadImage (hInstance, name,IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}

HBITMAP CFileLoader::LoadImageFromResource(HINSTANCE hInst, int id) {
	return (HBITMAP)LoadImage (hInst, MAKEINTRESOURCE (id),IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}
