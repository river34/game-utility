//
//  InputLoader.h
//  GameUtility
//
//  Created by River Liu on 5/2/2018.
//  Copyright © 2018 River Liu. All rights reserved.
// 

#ifndef InputLoader_h
#define InputLoader_h

#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "Utility.h"
#include "UtilityParams.h"
#include "Input.h"
#include "InputFactory.h"
#include "../rapidxml//rapidxml.hpp"

using namespace rapidxml;

namespace GameUtility
{
	class InputLoader
	{
	public:
		void loadInput(const std::string& _file, Utility* _utility, InputFactory* _inputFactory, std::vector<Input*>& _inputPool, const bool _isFilepath)
		{
			std::vector<char> buffer;
			
			if (_isFilepath == true)
			{
				std::ifstream theFile(_file);
				buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
				std::cout << "[InputLoader] Read filepath" << std::endl;
			}
			else
			{
				buffer = std::vector<char>(_file.begin(), _file.end());
				std::cout << "[InputLoader] Read file as string" << std::endl;
			}

			buffer.push_back('\0');

			std::cout << "[InputLoader] File size: " << buffer.size() << std::endl;

			// parse the buffer using the xml file parsing library into doc
			xml_document<> doc;
			doc.parse<0>(&buffer[0]);

			std::cout << "[InputLoader] Name of my first node is: " << doc.first_node()->name() << std::endl;

			// find the root node
			xml_node<>* root_node = doc.first_node("UtilityInput");

			// iterate over inputs
			for (xml_node<>* input_node = root_node->first_node("Input"); input_node; input_node = input_node->next_sibling("Input"))
			{
				Input* newInput = _inputFactory->createInstance(input_node);
				assert(newInput);
				_inputPool.push_back(newInput);
				_utility->registerInputParameter(newInput);
			}
		}
	};
}

#endif /* InputLoader_h */