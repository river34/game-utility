//
//  ResponseCurveFactory.h
//  GameUtility
//
//  Created by River Liu on 5/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef ResponseCurveFactory_h
#define ResponseCurveFactory_h

#include <tuple>
#include <iostream>
#include <string>
#include <map>
#include "ResponseCurve.h"
#include "../rapidxml/rapidxml.hpp"

namespace GameUtility
{
	class ResponseCurveFactory
	{
	private:
		ResponseCurveFactory(const ResponseCurveFactory&) {}
		ResponseCurveFactory& operator=(const ResponseCurveFactory&) { return *this; }
		typedef std::map<std::string, ResponseCurve::createInstanceFn> FactoryMap;
		FactoryMap m_FactoryMap;

	public:
		ResponseCurveFactory() { }
		~ResponseCurveFactory() { m_FactoryMap.clear(); }
		void registerClass(const std::string& name, ResponseCurve::createInstanceFn pfnCreate)
		{
			m_FactoryMap[name] = pfnCreate;
		}
		ResponseCurve* createInstance(const rapidxml::xml_node<>* node)
		{
			FactoryMap::iterator it = m_FactoryMap.find("ResponseCurve");
			UtilityParams params = UtilityParams();
			for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute())
			{
				params[attr->name()] = attr->value();
				std::cout << "[ResponseCurveFactory] param " << attr->name() << " = " << attr->value() << std::endl;
			}
			if (it != m_FactoryMap.end())
			{
				return it->second(params);
			}
			return nullptr;
		}
	};
}

#endif /* ResponseCurveFactory_h */
