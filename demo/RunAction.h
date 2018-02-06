#pragma once

#include "../GameUtilityLib.h"
#include "../Blackboard.h"

using namespace GameUtility;

class RunAction : public Action
{
public:
	inline RunAction(const UtilityParams& _params) : Action(_params) { }
	void onUpdate(Blackboard* _blackboard)
	{
		float* position = (float*)_blackboard->getEntry("position");
		*position += 30.f;
	}
	inline static Action* create(const UtilityParams& _params) { return new RunAction(_params); }
};