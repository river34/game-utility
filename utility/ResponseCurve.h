//
//  ResponseCurve.h
//  GameUtility
//
//  Created by River Liu on 4/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef ResponseCurve_h
#define ResponseCurve_h

#include <cassert>
#include <cmath>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "UtilityParams.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace GameUtility
{
	class ResponseCurve
	{
	public:
		enum CurveType
		{
			Linear,
			Step,
			Polynomial,
			Logistic,
			Logit,
			Normal,
			Sin
		};

	private:
		CurveType m_eType;
		double m_dSlope;
		double m_dExponent;
		double m_dXShift;
		double m_dYShift;

	public:
		typedef ResponseCurve* (*createInstanceFn) (const UtilityParams&);

	public:
		inline ResponseCurve() : ResponseCurve(ResponseCurve::CurveType::Linear, 1.0, 1.0, 0.0, 0.0) { }
		inline ResponseCurve(const CurveType _type, const double _slope, const double _exponent, const double _xshift, const double _yshift) : m_eType(_type), m_dSlope(_slope), m_dExponent(_exponent), m_dXShift(_xshift), m_dYShift(_yshift) { }
		ResponseCurve(const UtilityParams& _params)
		{
			m_eType = CurveType::Linear;
			auto it = _params.find("type");
			if (it != _params.end())
			{
				m_eType = stringToType(it->second);
			}
			m_dSlope = 1;
			it = _params.find("slope");
			if (it != _params.end())
			{
				std::stringstream s(it->second);
				s >> m_dSlope;
			}
			m_dExponent = 1;
			it = _params.find("exponent");
			if (it != _params.end())
			{
				std::stringstream s(it->second);
				s >> m_dExponent;
			}
			m_dXShift = 0;
			it = _params.find("xshift");
			if (it != _params.end())
			{
				std::stringstream s(it->second);
				s >> m_dXShift;
			}
			m_dYShift = 0;
			it = _params.find("yshift");
			if (it != _params.end())
			{
				std::stringstream s(it->second);
				s >> m_dYShift;
			}
			std::cout << "[ResponseCurve] create ResponseCurve " << m_eType << std::endl;
		}
		inline ResponseCurve(const ResponseCurve& _other) : m_eType(_other.m_eType), m_dSlope(_other.m_dSlope), m_dExponent(_other.m_dExponent), m_dXShift(_other.m_dXShift), m_dYShift(_other.m_dYShift) { }

		CurveType stringToType(const std::string& _type)
		{
			if (_type == "Linear")
			{
				return CurveType::Linear;
			}
			if (_type == "Step")
			{
				return CurveType::Step;
			}
			if (_type == "Polynomial")
			{
				return CurveType::Polynomial;
			}
			if (_type == "Logistic")
			{
				return CurveType::Logistic;
			}
			if (_type == "Logit")
			{
				return CurveType::Logit;
			}
			if (_type == "Normal")
			{
				return CurveType::Normal;
			}
			if (_type == "Sin")
			{
				return CurveType::Sin;
			}
			return CurveType::Linear;
		}
		float getScore(const float _input)
		{
			std::cout << "[ResponseCurve] input " << _input << std::endl;
			float output = 0.f;
			switch (m_eType)
			{
			case CurveType::Step:
				output = (_input - m_dXShift < 0.5) ? m_dYShift : m_dSlope + m_dYShift; break;
			case CurveType::Linear:
				output = (m_dSlope * (_input - m_dXShift)) + m_dYShift; break;
			case CurveType::Polynomial:
				output = (m_dSlope * pow(_input - m_dXShift, m_dExponent)) + m_dYShift; break;
			case CurveType::Logistic:
				output = (m_dSlope / (1 + exp(-10.0 * m_dExponent * (_input - 0.5 - m_dXShift)))) + m_dYShift; break;
			case CurveType::Logit:
				output = m_dSlope * log((_input - m_dXShift) / (1.0 - (_input - m_dXShift))) / 5.0 + 0.5 + m_dYShift; break;
			case CurveType::Normal:
				output = m_dSlope * exp(-30.0 * m_dExponent * (_input - m_dXShift - 0.5) * (_input - m_dXShift - 0.5)) + m_dYShift; break;
			case CurveType::Sin:
				output = 0.5 * m_dSlope * sin(2.0 * M_PI * (_input - m_dXShift)) + 0.5 + m_dYShift; break;
			}
			std::cout << "[ResponseCurve] output = " << output << std::endl;
			std::cout << "[ResponseCurve] sanitize = " << sanitize(output) << std::endl;

			return sanitize(output);
		}
		inline static ResponseCurve* create(const UtilityParams& _params) { return new ResponseCurve(_params); }

	private:
		double sanitize(double _y)
		{
			if (_y < 0.0) return 0.0;
			if (_y > 1.0) return 1.0;
			return _y;
		}
	};
}

#endif /* ResponseCurve_h */