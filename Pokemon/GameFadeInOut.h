#pragma once

#ifndef __GAMEFADEINOUT_H__
#define __GAMEFADEINOUT_H__

#include "BaseClass.h"

class GameFadeInOut : public BaseClass
{
private:

	const float FADETIME = 0.4f;

private:

	float fadeTimer;

public:

	GameFadeInOut();
	~GameFadeInOut() = default;

	void Draw(Graphics& g) override;
	void Update() override;
};

#endif
