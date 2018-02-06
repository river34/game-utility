#pragma once

#include "../GameUtilityLib.h"
#include "../Blackboard.h"

using namespace GameUtility;
class EnemyHealthInput : public Input
{
public:
	inline EnemyHealthInput(const UtilityParams& _params) : Input(_params) { }
	float getValue(Blackboard* _blackboard)
	{
		float* health = (float*)_blackboard->getEntry("enemyHealth");
		std::cout << "[EnemyHealthInput] value  = " << normalize(*health) << std::endl;
		return normalize(*health);
	}
	inline static Input* create(const UtilityParams& _params) { return new EnemyHealthInput(_params); }
};