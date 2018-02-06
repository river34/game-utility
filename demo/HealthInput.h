#pragma once

#include "../GameUtilityLib.h"
#include "../Blackboard.h"

using namespace GameUtility;
class HealthInput : public Input
{
public:
	inline HealthInput(const UtilityParams& _params) : Input(_params) { }
	float getValue(Blackboard* _blackboard)
	{
		float* health = (float*)_blackboard->getEntry("health");
		std::cout << "[HealthInput] value  = " << normalize(*health) << std::endl;
		return normalize(*health);
	}
	inline static Input* create(const UtilityParams& _params) { return new HealthInput(_params); }
};