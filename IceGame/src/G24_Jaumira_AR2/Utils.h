#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Type.h"


inline std::string FloatToString(float _num, int _decimals)
{
	std::stringstream stream;

	stream << std::fixed << std::setprecision(_decimals) << _num;

	return static_cast<std::string>(stream.str());
}

inline std::string FillDigits(int _num, int _digits)
{
	std::stringstream stream;

	stream << std::setw(_digits) << std::setfill('0') << _num;

	return stream.str();
}

inline int RandomNum(int min, int max)
{
	return (int)(rand()%(max - min) + min);
}

namespace Collision
{
	inline bool ObjectCollision(Rect o1, Rect o2)
	{
		Vec2 ob1 = Vec2(o1.x + o1.w / 2, o1.y + o1.h / 2);
		Vec2 ob2 = Vec2(o2.x + o2.w / 2, o2.y + o2.h / 2);

		float tmp1 = sqrt(pow(ob2.x - ob1.x, 2) + pow(ob2.y - ob1.y, 2));
		float tmp2 = sqrt(pow(o1.w / 2 + o2.w / 2, 2) + pow(o1.h / 2 + o2.h / 2, 2));

		return sqrt(pow(ob2.x - ob1.x, 2)) < (o1.w + o2.w) * 0.5 && sqrt(pow(ob2.y - ob1.y, 2)) < (o1.h + o2.h) * 0.5;
	};
}