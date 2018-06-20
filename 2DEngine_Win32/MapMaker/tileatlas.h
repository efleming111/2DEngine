//
//  Map Maker
//  tileatlas.h
//  Eric Fleming
//  6/19/2018
//

#pragma once

#include <string>
#include <iostream>
#include <map>

#include "tinyxml\tinyxml.h"

bool ReadInTileAtlas(std::string filename, std::map<int, std::string>& tileAtlas)
{
	TiXmlDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	TiXmlElement* rootElement = xmlDoc.RootElement();
	if (!rootElement)
	{
		std::cout << "Error finding tile atlas root element\n" << std::endl;
		std::cin.get();
		return false;
	}

	for (TiXmlElement* tileElement = rootElement->FirstChildElement("tile"); tileElement; tileElement = tileElement->NextSiblingElement())
	{
		int id;
		tileElement->Attribute("id", &id);

		TiXmlElement* imageElement = tileElement->FirstChildElement();
		std::string source = imageElement->Attribute("source");

		int slashIndex = source.find_last_of("/", source.length() - 2);
		std::string name = source.substr(slashIndex + 1, source.length() - 2);

		tileAtlas[id] = name;
	}

	return true;
}