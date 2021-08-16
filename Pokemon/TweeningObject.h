#pragma once

#ifndef __TWEENINGOBJECT_H__
#define __TWEENINGOBJECT_H__

class TweeningObject
{
private:

	int* target;
	float goalValue;
	float curValue;
	float prevDiff;
	float diff;

	bool isPlaying;

	float timer;
	float time;

	bool decrease;

public:

	TweeningObject();

	void SetTarget(int* _target);
	void SetGoalValue(int _goalValue);
	void SetTime(float _time);
	void Update();
	void Start();
	
	bool IsPlaying();

	void _Tween(int* target, float goal);
	void Tween(int* target, float goal);
};

#endif // !__TWEENINGOBJECT_H__
