//
//  ConsiderationFactory.h
//  GameUtility
//
//  Created by River Liu on 4/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef ConsiderationFactory_h
#define ConsiderationFactory_h

#include <tuple>
#include <iostream>
#include <string>
#include <map>
#include "Consideration.h"
#include "../rapidxml/rapidxml.hpp"

namespace GameUtility
{
	class ConsiderationFactory
	{
	private:
		ConsiderationFactory(const ConsiderationFactory&) {}
		ConsiderationFactory& operator=(const ConsiderationFactory&) { return *this; }
		typedef std::map<std::string, Consideration::createInstanceFn> FactoryMap;
		FactoryMap m_FactoryMap;

	public:
		ConsiderationFactory() { }
		~ConsiderationFactory() { m_FactoryMap.clear(); }
		void registerClass(const std::string& name, Consideration::createInstanceFn pfnCreate)
		{
			m_FactoryMap[name] = pfnCreate;
		}
		Consideration* createInstance(const rapidxml::xml_node<>* node)
		{
			FactoryMap::iterator it = m_FactoryMap.find(node->name());
			UtilityParams params = UtilityParams();
			for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute())
			{
				params[attr->name()] = attr->value();
			}
			if (it != m_FactoryMap.end())
			{
				return it->second(params);
			}
			return nullptr;
		}
	};
}

#endif /* ConsiderationFactory_h */