//
//  XML Sprite Sheet Creator
//  main.cpp
//  Eric Fleming
//  9/7/2018
//

#include <iostream>
#include <sstream>
#include <string>

#include "tinyxml/tinyxml.h"

int main(int argc, char* argv[])
{
	std::string filename = "spritesheet.xml";
	int width = 692;
	int height = 692;
	int borderPadding = 1;
	int spritePadding = 1;
	int spriteSize = 21;

	TiXmlDocument doc;
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(dec);

	TiXmlElement* sprites = new TiXmlElement("sprites");
	sprites->SetAttribute("width", width);
	sprites->SetAttribute("height", height);
	doc.LinkEndChild(sprites);

	// <sprite n="Sprite###" x="#" y="#" w="21" h="21"/>
	int spriteCount = 1;
	int currentX;
	int currentY;
	for (int y = 0; y < 30; ++y)
	{
		currentY = borderPadding + spritePadding + (y * (spriteSize + spritePadding + spritePadding));
		for (int x = 0; x < 30; ++x)
		{
			currentX = borderPadding + spritePadding + (x * (spriteSize + spritePadding + spritePadding));

			TiXmlElement* sprite = new TiXmlElement("sprite");

			std::ostringstream spriteName;
			spriteName << "Sprite" << spriteCount;
			std::string name = spriteName.str();

			sprite->SetAttribute("n", name.c_str());
			sprite->SetAttribute("x", currentX);
			sprite->SetAttribute("y", currentY);
			sprite->SetAttribute("w", spriteSize);
			sprite->SetAttribute("h", spriteSize);
			sprites->LinkEndChild(sprite);

			spriteCount++;
		}
	}

	doc.SaveFile(filename.c_str());

	return 0;
}