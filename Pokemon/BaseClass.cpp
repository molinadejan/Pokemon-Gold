#include "BaseClass.h"

BaseClass::BaseClass() : gm(NULL) { }
BaseClass::~BaseClass() { }

void BaseClass::SetManager(GameManager * _gm)
{
	gm = _gm;
}

void BaseClass::Update() { }
void BaseClass::Draw(Graphics& g) { }
