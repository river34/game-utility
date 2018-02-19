//
//  Target.h
//  GameUtility
//
//  Created by River Liu on 18/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef Target_h
#define Target_h

#include <string>

class Blackboard;
namespace GameUtility
{
	class Target
	{
	protected:
		std::string m_sName;
		void* m_pActor;

	public:
		inline Target(const std::string& _name, void* _actor) : m_sName(_name), m_pActor(_actor) {  }
		inline const std::string& getName() const { return m_sName; }
		inline const void* getActor() const { return m_pActor; }
	};
}

#endif /* Target_h */