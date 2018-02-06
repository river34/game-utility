//
//  Input.h
//  GameUtility
//
//  Created by River Liu on 4/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef Input_h
#define Input_h

#include <string>
#include <sstream>
#include "UtilityParams.h"

class Blackboard;
namespace GameUtility
{
	class Input
	{
	protected:
		std::string m_sName;
		float m_fMinValue;
		float m_fMaxValue;

	public:
		typedef Input* (*createInstanceFn) (const UtilityParams&);

	public:
		inline Input() : m_sName("InputParameter"), m_fMinValue(0.f), m_fMaxValue(1.f) { }
		inline Input(const std::string& _name, const float _minValue, const float _maxValue) : m_sName(_name), m_fMinValue(_minValue), m_fMaxValue(_maxValue) { }
		inline Input(const Input& _other) : m_sName(_other.m_sName), m_fMinValue(_other.m_fMinValue), m_fMaxValue(_other.m_fMaxValue) { }
		Input(const UtilityParams& _params)
		{
			m_sName = "Input";
			auto it = _params.find("id");
			if (it != _params.end())
			{
				m_sName = it->second;
			}
			m_fMinValue = 0.f;
			it = _params.find("min");
			if (it != _params.end())
			{
				std::stringstream s(it->second);
				s >> m_fMinValue;
			}
			m_fMaxValue = 1.f;
			it = _params.find("max");
			if (it != _params.end())
			{
				std::stringstream s(it->second);
				s >> m_fMaxValue;
			}
			std::cout << "[Input] created " << getName() << " min = " << getMin() << " max = " << getMax() << std::endl;
		}
		inline std::string getName() { return m_sName; }
		inline float getMin() { return m_fMinValue; }
		inline float getMax() { return m_fMaxValue; }
		inline virtual float getValue(Blackboard* _blackboard) { return 0.f; }
		float normalize(float _value)
		{
			assert(m_fMaxValue - m_fMinValue > 0);
			if (_value < m_fMinValue) return m_fMinValue;
			if (_value > m_fMaxValue) return m_fMaxValue;
			return m_fMinValue + (_value - m_fMinValue) / (m_fMaxValue - m_fMinValue);
		}
		inline static Input* create(const UtilityParams& _params) { return new Input(_params); }
	};
}

#endif /* Input */