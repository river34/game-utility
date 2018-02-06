#pragma once

#include "../GameUtilityLib.h"
#include "../Blackboard.h"

using namespace GameUtility;

class AttackAction : public Action
{
public:
	inline AttackAction(const UtilityParams& _params) : Action(_params) { }
	void onUpdate(Blackboard* _blackboard)
	{
		float* enemyHealth = (float*)_blackboard->getEntry("enemyHealth");
		*enemyHealth -= 10.f;
	}
	inline static Action* create(const UtilityParams& _params) { return new AttackAction(_params); }
};