//
//  Consideration.h
//  GameUtility
//
//  Created by River Liu on 4/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef Consideration_h
#define Consideration_h

#include <string>
#include <vector>
#include <iostream>
#include "UtilityParams.h"
#include "ResponseCurve.h"
#include "Input.h"
#include "Target.h"

class Blackboard;
namespace GameUtility
{
	class Consideration
	{
	private:
		std::string m_sName;
		ResponseCurve* m_pCurve;
		Input* m_pInput;

	public:
		typedef Consideration* (*createInstanceFn) (const UtilityParams&);

	public:
		inline Consideration() : m_sName("Consideration") { }
		inline Consideration(const std::string& _name) : m_sName(_name) { }
		inline Consideration(const std::string& _name, ResponseCurve* _curve) : m_sName(_name), m_pCurve(_curve) { }
		Consideration(const UtilityParams& _params)
		{
			m_sName = "Consideration";
			auto it = _params.find("name");
			if (it != _params.end())
			{
				m_sName = it->second;
			}
		}
		inline void setCurve(ResponseCurve* _curve) { m_pCurve = _curve; }
		inline void setInput(Input* _input) { m_pInput = _input; }
		inline const std::string& getName() { return m_sName; }
		inline const std::string& getInputName() { return m_pInput->getName(); }
		inline const float getScore(const Blackboard* _blackboard, const Target* _target, const Action* _action) const
		{
			float output = m_pCurve->getScore(m_pInput->getValue(_blackboard, _target, _action));
			//std::cout << "[Consideration] " << getName() << " output = " << output << std::endl; 
			return output;
		}
		inline static Consideration* create(const UtilityParams& _params) { return new Consideration(_params); }
	};
}

#endif