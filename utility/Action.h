//
//  Action.h
//  GameUtility
//
//  Created by River Liu on 4/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef Action_h
#define Action_h

#include <string>
#include <vector>
#include "UtilityParams.h"
#include "Consideration.h"

class Blackboard;
namespace GameUtility
{
	class Action
	{
	protected:
		std::string m_sName;
		std::vector<Consideration*> m_Considerations;
		float m_fWeight;

	public:
		typedef Action* (*createInstanceFn) (const UtilityParams&);

	public:
		inline Action() : m_sName("Action"), m_fWeight(1.f) { }
		inline Action(const std::string& _name) : m_sName(_name), m_fWeight(1.f) {  }
		inline Action(const std::string& _name, const float _weight) : m_sName(_name), m_fWeight(_weight) { }
		Action(const UtilityParams& _params)
		{
			m_sName = "Action";
			auto it = _params.find("name");
			if (it != _params.end())
			{
				m_sName = it->second;
			}
			m_fWeight = 1.f;
			it = _params.find("weight");
			if (it != _params.end())
			{
				std::stringstream s(it->second);
				s >> m_fWeight;
			}
		}
		void AddConsideration(Consideration* _consideration)
		{
			m_Considerations.push_back(_consideration);
		}
		float getScore(Blackboard* _blackboard)
		{
			float finalScore = m_fWeight;
			for (Consideration* c : m_Considerations)
			{
				finalScore *= c->getScore(_blackboard);
			}
			std::cout << "[Action] finalScore = " << finalScore << std::endl;
			return finalScore;
		}
		inline std::string getName() { return m_sName; }
		inline virtual void onUpdate(Blackboard* _blackboard) { }
		inline static Action* create(const UtilityParams& _params) { return new Action(_params); }
	};
}

#endif /* Action_h */