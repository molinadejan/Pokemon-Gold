#pragma once

#ifndef __GDIPLUSELEMENT_H__
#define __GDIPLUSELEMENT_H__

#include "framework.h"

using namespace Gdiplus;

class GdiplusElement
{
private:

	class Element
	{
		friend GdiplusElement;

	private:

		Element();
		~Element();

		void LoadMyFont();
		void CreateMyFont();

		void CreateStrFormat();

		void CreateBrush();

		void DeleteElements();

	private:

		PrivateFontCollection *collection;
		FontFamily* fm;

		Font* fontS;
		Font* fontM;
		Font* fontB;

		StringFormat* leftAlign;
		StringFormat* centerAlign;
		StringFormat* rightAlign;

		SolidBrush* black;
		SolidBrush* white;
	};

private:

	static Element e;

public:

	static void Init();
	static void Delete();

	static Font* GetFontS();
	static Font* GetFontM();
	static Font* GetFontB();

	static StringFormat* GetLeftAlign();
	static StringFormat* GetCenterAlign();
	static StringFormat* GetRightAlign();

	static StringFormat* GetLeftBottomAlign();
	static StringFormat* GetCenterBott0mAlign();
	static StringFormat* GetRightBottomAlign();

	static SolidBrush* GetBlack();
	static SolidBrush* GetWhite();
};

#define GE			GdiplusElement

#define FONT_SMALL  GdiplusElement::GetFontS()
#define FONT_MEDIUM GdiplusElement::GetFontM()
#define FONT_BIG    GdiplusElement::GetFontB()

#define LEFT_ALIGN   GdiplusElement::GetLeftAlign()
#define CENTER_ALIGN GdiplusElement::GetCenterAlign()
#define RIGHT_ALIGN  GdiplusElement::GetRightAlign()

#define LEFT_BOTTOM_ALIGN   GdiplusElement::GetLeftBottomAlign()
#define CENTER_BOTTOM_ALIGN GdiplusElement::GetCenterBottomAlign()
#define RIGHT_BOTTOM_ALIGN  GdiplusElement::GetRightBottomAlign()

#define BLACK GdiplusElement::GetBlack()
#define WHITE GdiplusElement::GetWhite()

#endif