//
//  Renderable Parser
//  main.cpp
//  Eric Fleming
//  9/13/2018
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

#include "tinyxml\tinyxml.h"


struct Sprite
{
	std::string name;
	double x;
	double y;
	double width;
	double height;
	std::string textureFilename;
};

bool ReadInSpriteSheet(char* argv[]);
void OutputRenderables(char* argv[], int numOfArgs);

// Map globals
std::vector<Sprite*> gSprites;
double gSpriteSheetWidth;
double gSpriteSheetHeight;

int main(int argc, char* argv[])
{
	if (!ReadInSpriteSheet(argv))
		return 1;

	OutputRenderables(argv, argc);

	return 0;
}

void OutputRenderables(char* argv[], int numOfArgs)
{
	// Create files
	std::string goFilename = argv[numOfArgs - 1];

	TiXmlDocument goDoc;
	TiXmlDeclaration* goDec = new TiXmlDeclaration("1.0", "UTF-8", "");
	goDoc.LinkEndChild(goDec);

	// Set up root element for scene game object file
	TiXmlElement* go = new TiXmlElement("go");
	goDoc.LinkEndChild(go);

	// Set up resources
	TiXmlElement* resources = new TiXmlElement("resources");
	go->LinkEndChild(resources);

	// Output renderable resources
	for (int i = 2; i < numOfArgs; ++i)
	{
		for (unsigned j = 0; j < gSprites.size(); ++j)
		{
			if (gSprites[j]->name.compare(argv[i]) == 0)
			{
				TiXmlElement* renderable = new TiXmlElement("renderable");
				resources->LinkEndChild(renderable);

				renderable->SetAttribute("type", "Renderable");
				renderable->SetAttribute("name", gSprites[j]->name.c_str());
				renderable->SetAttribute("pivotpoint", "center");

				renderable->SetDoubleAttribute("texleft", gSprites[j]->x / gSpriteSheetWidth);
				renderable->SetDoubleAttribute("texright", (gSprites[j]->x + gSprites[j]->width) / gSpriteSheetWidth);
				renderable->SetDoubleAttribute("texbottom", gSprites[j]->y / gSpriteSheetHeight);
				renderable->SetDoubleAttribute("textop", (gSprites[j]->y + gSprites[j]->height) / gSpriteSheetHeight);
				std::string texfile = gSprites[j]->textureFilename;
				renderable->SetAttribute("texturefile", texfile.c_str());
				renderable->SetAttribute("shaderfile", "data/shaders/BasicTextureShader");
			}
		}
	}

	goDoc.SaveFile(goFilename.c_str());
}

bool ReadInSpriteSheet(char* argv[])
{
	TiXmlDocument xmlDoc;
	xmlDoc.LoadFile(argv[1]);

	TiXmlElement* sprites = xmlDoc.RootElement();
	if (!sprites)
	{
		std::cout << "Error finding sprite sheet root element\n" << std::endl;
		std::cin.get();
		return false;
	}

	std::string spriteSheetFilename = sprites->Attribute("gamepath");
	sprites->Attribute("width", &gSpriteSheetWidth);
	sprites->Attribute("height", &gSpriteSheetHeight);

	for (TiXmlElement* sprite = sprites->FirstChildElement(); sprite; sprite = sprite->NextSiblingElement())
	{
		Sprite* newSprite = new Sprite();
		newSprite->name = sprite->Attribute("n");
		sprite->Attribute("x", &newSprite->x);
		sprite->Attribute("y", &newSprite->y);
		sprite->Attribute("w", &newSprite->width);
		sprite->Attribute("h", &newSprite->height);
		newSprite->textureFilename = spriteSheetFilename;

		gSprites.push_back(newSprite);
	}

	return true;
}