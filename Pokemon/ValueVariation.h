#pragma once

#ifndef __TWEENINGOBJECT_H__
#define __TWEENINGOBJECT_H__

class ValueVariation
{
private:

	int* target;
	float goalValue;
	float curValue;

	bool isPlaying;\
	bool decrease;

public:

	ValueVariation();

	void SetTarget(int* _target);
	void SetGoalValue(int _goalValue);
	
	bool IsPlaying();

	void _Variation(int* target, float goal);
	void Variation(int* target, float goal);
};

#endif // !__TWEENINGOBJECT_H__
