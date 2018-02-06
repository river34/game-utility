//
//  InputFactory.h
//  GameUtility
//
//  Created by River Liu on 5/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef InputFactory_h
#define InputFactory_h

#include <tuple>
#include <iostream>
#include <string>
#include <map>
#include "Input.h"
#include "../rapidxml/rapidxml.hpp"

namespace GameUtility
{
	class InputFactory
	{
	private:
		InputFactory(const InputFactory&) {}
		InputFactory& operator=(const InputFactory&) { return *this; }
		typedef std::map<std::string, Input::createInstanceFn> FactoryMap;
		FactoryMap m_FactoryMap;

	public:
		InputFactory() { }
		~InputFactory() { m_FactoryMap.clear(); }
		void registerClass(const std::string& name, Input::createInstanceFn pfnCreate)
		{
			m_FactoryMap[name] = pfnCreate;
		}
		Input* createInstance(const rapidxml::xml_node<>* node)
		{
			std::string id = (node->first_attribute("id") == nullptr) ? "" : node->first_attribute("id")->value();
			std::string name = node->name();
			FactoryMap::iterator it = m_FactoryMap.find(id + name);
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

#endif /* InputFactory_h */
