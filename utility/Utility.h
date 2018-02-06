//
//  Utility.h
//  GameUtility
//
//  Created by River Liu on 4/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef GameUtility_h
#define GameUtility_h

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "Action.h"
#include "Input.h"

class Blackboard;
namespace GameUtility
{
	class Utility
	{
	private:
		std::vector<Action*> m_ActionList;
		std::vector<Action*> m_CurrentActionList;
		std::map<std::string, Input*> m_InputMap;

	public:
		inline void addAction(Action* _action) { m_ActionList.push_back(_action); }
		inline void registerInputParameter(Input* _input) { m_InputMap[_input->getName()] = _input; }
		inline Input* getInputParameter(const std::string& _key) { auto it = m_InputMap.find(_key); if (it != m_InputMap.end()) return it->second; return nullptr; }
		void tick(Blackboard* _blackboard)
		{
			std::cout << "[Utility] tick Utility" << std::endl;
			assert(m_ActionList.size() > 0);
			float score = 0.f;
			auto max = m_ActionList.begin();
			for (auto it = m_ActionList.begin(); it != m_ActionList.end(); it++)
			{
				float newScore = (*it)->getScore(_blackboard);
				std::cout << "[Utility] calculate " << (*it)->getName() << " score = " << newScore << std::endl;
				if (newScore > score)
				{
					score = newScore;
					max = it;
				}
			}
			std::cout << "[Utility] choose " << (*max)->getName() << std::endl;
			(*max)->onUpdate(_blackboard);
		}
	};
}

#endif /* GameUtility_h */