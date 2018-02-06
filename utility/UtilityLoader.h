//
//  UtilityLoader.h
//  GameUtility
//
//  Created by River Liu on 4/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef UtilityLoader_h
#define UtilityLoader_h

#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "Utility.h"
#include "UtilityParams.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Consideration.h"
#include "ConsiderationFactory.h"
#include "Input.h"
#include "ResponseCurve.h"
#include "ResponseCurveFactory.h"
#include "../rapidxml//rapidxml.hpp"

using namespace rapidxml;

namespace GameUtility
{
	class UtilityLoader
	{
	public:
		void loadUtility(const std::string& _file, Utility* _utility, ResponseCurveFactory* _curveFactory, ConsiderationFactory* _consideratioNFactory, ActionFactory* _actionFactory, std::vector<Input*>& _inputPool, const bool _isFilepath)
		{
			std::vector<char> buffer;

			if (_isFilepath == true)
			{
				std::ifstream theFile(_file);
				buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
				std::cout << "[UtilityLoader] Read filepath" << std::endl;
			}
			else
			{
				buffer = std::vector<char>(_file.begin(), _file.end());
				std::cout << "[UtilityLoader] Read file as string" << std::endl;
			}
			buffer.push_back('\0');

			std::cout << "[UtilityLoader] File size: " << buffer.size() << "\n";

			// parse the buffer using the xml file parsing library into doc
			xml_document<> doc;
			doc.parse<0>(&buffer[0]);

			std::cout << "[UtilityLoader] Name of my first node is: " << doc.first_node()->name() << "\n";

			// find the root node
			xml_node<>* root_node = doc.first_node("Utility");

			// iterate over actions
			for (xml_node<>* action_node = root_node->first_node("Action"); action_node; action_node = action_node->next_sibling("Action"))
			{
				// create action
				auto newAction = _actionFactory->createInstance(action_node);
				assert(newAction);
				std::cout << "[UtilityLoader] addAction " << newAction->getName() << std::endl;
				_utility->addAction(newAction);
				
				// iterate over considerations
				for (xml_node<>* consideration_node = action_node->first_node("Consideration"); consideration_node; consideration_node = consideration_node->next_sibling("Consideration"))
				{
					// create consideration
					auto newConsideration = _consideratioNFactory->createInstance(consideration_node);
					assert(newConsideration);
					newAction->AddConsideration(newConsideration);

					// create curve
					xml_node<>* curve_node = consideration_node->first_node("ResponseCurve");
					auto newCurve = _curveFactory->createInstance(curve_node);
					assert(newCurve);
					newConsideration->setCurve(newCurve);

					// register input
					xml_node<>* input_node = consideration_node->first_node("Input");
					for (Input* input : _inputPool)
					{
						if (input->getName() == input_node->first_attribute("id")->value())
						{
							newConsideration->setInput(input);
							break;
						}
					}
				}
			}
		}
	};
}

#endif