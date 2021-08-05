#include "BaseClass.h"

BaseClass::BaseClass() : gm(NULL) { }

BaseClass::~BaseClass() 
{ 
	delete black;
	delete white;

	delete leftAlign;
	delete centerAlign;
	delete rightAlign;
}

void BaseClass::ResourceInit()
{
	black = new SolidBrush(Color(255, 0, 0, 0));
	white = new SolidBrush(Color(255, 248, 248, 248));

	fontS = DataLoadManager::GetFontS();
	fontM = DataLoadManager::GetFontM();
	fontB = DataLoadManager::GetFontB();

	leftAlign = new StringFormat;
	leftAlign->SetAlignment(StringAlignmentNear);
	leftAlign->SetLineAlignment(StringAlignmentCenter);

	centerAlign = new StringFormat;
	centerAlign->SetAlignment(StringAlignmentCenter);
	centerAlign->SetLineAlignment(StringAlignmentCenter);

	rightAlign = new StringFormat;
	rightAlign->SetAlignment(StringAlignmentFar);
	rightAlign->SetLineAlignment(StringAlignmentCenter);
}

void BaseClass::SetManager(GameManager * _gm)
{
	gm = _gm;
}

void BaseClass::Update() { }
void BaseClass::Draw(Graphics& g) { }
