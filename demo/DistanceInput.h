#pragma once

#include <iostream>
#include "../GameUtilityLib.h"
#include "../Blackboard.h"

using namespace GameUtility;
class DistanceInput : public Input
{
public:
	inline DistanceInput(const UtilityParams& _params) : Input(_params) { }
	float getValue(Blackboard* _blackboard)
	{
		float* position = (float*)_blackboard->getEntry("position");
		float* enemyPosition = (float*)_blackboard->getEntry("enemyPosition");
		float distance = (*position > *enemyPosition) ? *position - *enemyPosition : *enemyPosition > *position;
		std::cout << "[DistanceInput] value  = " << normalize(distance) << std::endl;
		return normalize(distance);
	}
	inline static Input* create(const UtilityParams& _params) { return new DistanceInput(_params); }
};