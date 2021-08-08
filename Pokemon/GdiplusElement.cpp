#include "GdiplusElement.h"

using namespace Gdiplus;

GdiplusElement::Element GdiplusElement::e = GdiplusElement::Element();

GdiplusElement::Element::Element()
	: collection(NULL), fm(NULL), fontS(NULL), fontM(NULL), fontB(NULL)
{ }

GdiplusElement::Element::~Element()
{ }

void GdiplusElement::Element::LoadMyFont()
{
	collection = new PrivateFontCollection;
	collection->AddFontFile(L"data/font/Dot.ttf");
}

void GdiplusElement::Element::CreateMyFont()
{
	WCHAR familyName[LF_FACESIZE];
	int count, found;

	count = collection->GetFamilyCount();
	fm = new FontFamily[count];
	collection->GetFamilies(count, fm, &found);

	fm[0].GetFamilyName(familyName);

	fontS = new Font(familyName, 4 * SCREEN_MUL, FontStyleBold, UnitPoint, collection);
	fontM = new Font(familyName, 6 * SCREEN_MUL, FontStyleBold, UnitPoint, collection);
	fontB = new Font(familyName, 8 * SCREEN_MUL, FontStyleBold, UnitPoint, collection);
}

void GdiplusElement::Element::DeleteElements()
{
	delete fontS;
	delete fontM;
	delete fontB;

	delete[] fm;

	delete collection;
}

void GdiplusElement::Init()
{
	e.LoadMyFont();
	e.CreateMyFont();
}

void GdiplusElement::Delete()
{
	e.DeleteElements();
}

Font * GdiplusElement::GetFontS()
{
	return e.fontS;
}

Font * GdiplusElement::GetFontM()
{
	return e.fontM;
}

Font * GdiplusElement::GetFontB()
{
	return e.fontB;
}
