//
//  Map Maker
//  spritesheet.h
//  Eric Fleming
//  6/19/2018
//

#pragma once

#include <string>
#include <iostream>
#include <list>

#include "tinyxml\tinyxml.h"

struct Renderable
{
	std::string type;
	std::string name;
	std::string pivotPoint;
	double texRight;
	double texLeft;
	double texBottom;
	double texTop;
	std::string textureFilename;
	std::string shaderFilename;
};

bool ReadInSpriteSheet(std::string filename, std::list<Renderable*>& renderables)
{
	TiXmlDocument xmlDoc;
	xmlDoc.LoadFile(filename.c_str());

	TiXmlElement* rootElement = xmlDoc.RootElement();
	if (!rootElement)
	{
		std::cout << "Error finding sprite sheet root element\n" << std::endl;
		std::cin.get();
		return false;
	}

	std::string textureFilename = rootElement->Attribute("imagePath");

	double ssWidth, ssHeight;
	rootElement->Attribute("width", &ssWidth);
	rootElement->Attribute("height", &ssHeight);

	for (TiXmlElement* spriteElement = rootElement->FirstChildElement(); spriteElement; spriteElement = spriteElement->NextSiblingElement())
	{
		Renderable* renderable = new Renderable();

		renderable->type = "Renderable";
		renderable->name = spriteElement->Attribute("n");
		renderable->pivotPoint = "center";

		double x, y, w, h;
		spriteElement->Attribute("x", &x);
		spriteElement->Attribute("y", &y);
		spriteElement->Attribute("w", &w);
		spriteElement->Attribute("h", &h);

		renderable->texLeft = x / ssWidth;
		renderable->texRight = (x + w) / ssWidth;
		renderable->texBottom = y / ssHeight;
		renderable->texTop = (y + h) / ssHeight;

		renderable->textureFilename = "data/spritesheets/";
		renderable->textureFilename += textureFilename;

		renderable->shaderFilename = "data/shaders/BasicTextureShader";

		renderables.push_back(renderable);
	}

	return true;
}