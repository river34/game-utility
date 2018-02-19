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
#include <list>
#include <map>
#include "Action.h"
#include "Input.h"
#include "Target.h"

class Blackboard;
namespace GameUtility
{
#ifndef MAX_INPUTS
#define MAX_INPUTS 64
#endif
	class Utility
	{
	private:
		std::vector<Action*> m_ActionList;
		std::vector<Action*> m_CurrentActionList;
		std::list<Target*> m_TargetList;
		std::map<std::string, Input*> m_InputMap;

	public:
		inline ~Utility() { m_ActionList.clear(); m_CurrentActionList.clear(); m_TargetList.clear(); m_InputMap.clear(); }
		inline void addAction(Action* _action) { m_ActionList.push_back(_action); }
		inline void addTarget(Target* _target) { m_TargetList.push_back(_target); }
		inline void removeTarget(const std::string& _name) 
		{ 
			for (auto t : m_TargetList) 
			{
				std::cout << "t->getName()" << t->getName() << " _name" << _name << std::endl;
				if (t->getName() == _name)
				{
					m_TargetList.remove(t);
					std:: cout << "[Utility] remove from target list" << std::endl;
					break;
				}
			} 
		}
		inline void registerInputParameter(Input* _input) { m_InputMap[_input->getName()] = _input; }
		inline Input* getInputParameter(const std::string& _key) { auto it = m_InputMap.find(_key); if (it != m_InputMap.end()) return it->second; return nullptr; }
		void tick(Blackboard* _blackboard)
		{
			std::cout << "[Utility] tick Utility" << std::endl;
			float score = 0.f;
			auto max_action = m_ActionList.begin();
			auto max_target = m_TargetList.begin();
			for (auto it_action = m_ActionList.begin(); it_action != m_ActionList.end(); it_action++)
			{
				for (auto it_target = m_TargetList.begin(); it_target != m_TargetList.end(); it_target++)
				{
					float newScore = (*it_action)->getScore(_blackboard, *it_target);
					//std::cout << "[Utility] calculate action = " << (*it_action)->getName() << " target = " << (*it_target)->getName() <<  " score = " << newScore << std::endl;
					if (newScore > score)
					{
						score = newScore;
						max_action = it_action;
						max_target = it_target;
					}
				}
			}
			std::cout << "[Utility] choose action = " << (*max_action)->getName() << " target = " << (*max_target)->getName() << std::endl;
			(*max_action)->onUpdate(_blackboard, *max_target);
		}
	};
}

#endif /* GameUtility_h */