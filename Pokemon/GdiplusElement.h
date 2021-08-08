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

		void DeleteElements();

	private:

		PrivateFontCollection *collection;
		FontFamily* fm;

		Font* fontS;
		Font* fontM;
		Font* fontB;
	};

private:

	static Element e;

public:

	static void Init();
	static void Delete();

	static Font* GetFontS();
	static Font* GetFontM();
	static Font* GetFontB();
};

#define GE			GdiplusElement

#define FONT_SMALL  GdiplusElement::GetFontS()
#define FONT_MEDIUM GdiplusElement::GetFontM()
#define FONT_BIG    GdiplusElement::GetFontB()

#endif