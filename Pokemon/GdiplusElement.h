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
		~Element() = default;

		void LoadMyFont();
		void CreateMyFont();
		void CreateStrFormat();
		void CreateBrush();

		void Init();
		void Reset();

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

	GdiplusElement() = delete;
	~GdiplusElement() = delete;

public:

	static void Init() { e.Init(); }
	static void Reset() { e.Reset(); }

	static Font* GetFontS() { return e.fontS; }
	static Font* GetFontM() { return e.fontM; }
	static Font* GetFontB() { return e.fontB; }

	static StringFormat* GetLeftAlign() { return e.leftAlign; }
	static StringFormat* GetCenterAlign() { return e.centerAlign; }
	static StringFormat* GetRightAlign() { return e.rightAlign; }

	static SolidBrush* GetBlack() { return e.black; }
	static SolidBrush* GetWhite() { return e.white; }
};

#define GE			GdiplusElement

#define FONT_SMALL  GdiplusElement::GetFontS()
#define FONT_MEDIUM GdiplusElement::GetFontM()
#define FONT_BIG    GdiplusElement::GetFontB()

#define LEFT_ALIGN   GdiplusElement::GetLeftAlign()
#define CENTER_ALIGN GdiplusElement::GetCenterAlign()
#define RIGHT_ALIGN  GdiplusElement::GetRightAlign()

#define BLACK GdiplusElement::GetBlack()
#define WHITE GdiplusElement::GetWhite()

#endif