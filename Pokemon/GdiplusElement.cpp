#include "GdiplusElement.h"

using namespace Gdiplus;

GdiplusElement::Element GdiplusElement::e = GdiplusElement::Element();

GdiplusElement::Element::Element()
	: collection(NULL), fm(NULL), fontS(NULL), fontM(NULL), fontB(NULL), leftAlign(NULL), centerAlign(NULL), rightAlign(NULL),
	  black(NULL), white(NULL)
{ }

GdiplusElement::Element::~Element()
{ }


//https://m.blog.naver.com/codbs7/221441864531
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

void GdiplusElement::Element::CreateStrFormat()
{
	leftAlign = new StringFormat;
	centerAlign = new StringFormat;
	rightAlign = new StringFormat;

	leftAlign->SetAlignment(StringAlignmentNear);
	leftAlign->SetLineAlignment(StringAlignmentCenter);

	centerAlign->SetAlignment(StringAlignmentCenter);
	centerAlign->SetLineAlignment(StringAlignmentCenter);

	rightAlign->SetAlignment(StringAlignmentFar);
	rightAlign->SetLineAlignment(StringAlignmentCenter);
}

void GdiplusElement::Element::CreateBrush()
{
	black = new SolidBrush(Color(0, 0, 0));
	white = new SolidBrush(Color(248, 248, 248));
}

void GdiplusElement::Element::DeleteElements()
{
	delete fontS;
	delete fontM;
	delete fontB;

	delete[] fm;

	delete collection;

	delete leftAlign;
	delete centerAlign;
	delete rightAlign;

	delete white;
	delete black;
}

void GdiplusElement::Init()
{
	e.LoadMyFont();
	e.CreateMyFont();

	e.CreateStrFormat();
	e.CreateBrush();
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

StringFormat * GdiplusElement::GetLeftAlign()
{
	return e.leftAlign;
}

StringFormat * GdiplusElement::GetCenterAlign()
{
	return e.centerAlign;
}

StringFormat * GdiplusElement::GetRightAlign()
{
	return e.rightAlign;
}

SolidBrush * GdiplusElement::GetBlack()
{
	return e.black;
}

SolidBrush * GdiplusElement::GetWhite()
{
	return e.white;
}
