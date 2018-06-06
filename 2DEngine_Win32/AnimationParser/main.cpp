//
//  Animation Parser
//  main.cpp
//  Eric Fleming
//  6/6/2018/2018
//

#include <iostream>
#include <string>
#include <vector>

#include "tinyxml\tinyxml.h"

// Map objects
struct Sprite
{
	std::string name;
	double x;
	double y;
	double width;
	double height;
	std::string textureFilename;
};

// Map functions
bool ReadInSpriteSheet(std::string name);
void OutputData(std::string name);

// Map globals
std::vector<Sprite*> g_Sprites;
double g_SpriteSheetWidth;
double g_SpriteSheetHeight;

int main(int argc, char* argv[])
{
	// TODO: temp to speed up testing
	std::cout << "Enter sprite sheet name: ";
	std::string name;
	std::getline(std::cin, name);
	if (!ReadInSpriteSheet(name))
		return 1;

	OutputData(name);

	// C:\2DEngine\assetcreation\unsorted\knight

	return 0;
}

void OutputData(std::string name)
{
	std::string filename = name + ".gobdata";

	TiXmlDocument xmlDoc;
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");
	xmlDoc.LinkEndChild(dec);

	// Set up root element
	TiXmlElement* gobData = new TiXmlElement("gobdata");
	xmlDoc.LinkEndChild(gobData);

	// Set up resources
	TiXmlElement* resources = new TiXmlElement("resources");
	gobData->LinkEndChild(resources);

	// Output renderable resources
	for (unsigned i = 0; i < g_Sprites.size(); ++i)
	{
		TiXmlElement* renderable = new TiXmlElement("renderable");
		resources->LinkEndChild(renderable);

		renderable->SetAttribute("type", "Renderable");
		renderable->SetAttribute("name", g_Sprites[i]->name.c_str());
		renderable->SetAttribute("pivotpoint", "center");

		renderable->SetDoubleAttribute("texleft", g_Sprites[i]->x / g_SpriteSheetWidth);
		renderable->SetDoubleAttribute("texright", (g_Sprites[i]->x + g_Sprites[i]->width) / g_SpriteSheetWidth);
		renderable->SetDoubleAttribute("texbottom", (g_Sprites[i]->y + g_Sprites[i]->height) / g_SpriteSheetHeight);
		renderable->SetDoubleAttribute("textop", g_Sprites[i]->y / g_SpriteSheetHeight);
		std::string texfile = "data/spritesheets/";
		texfile += g_Sprites[i]->textureFilename;
		renderable->SetAttribute("texturefile", texfile.c_str());
		renderable->SetAttribute("shaderfile", "data/shaders/BasicTextureShader");
	}

	// Set up resources
	TiXmlElement* sprites = new TiXmlElement("sprites");
	gobData->LinkEndChild(sprites);

	// Output sprite object for each renderable
	for (unsigned i = 0; i < g_Sprites.size(); ++i)
	{
		TiXmlElement* sprite = new TiXmlElement("sprite");
		sprites->LinkEndChild(sprite);

		sprite->SetAttribute("type", "sprite");
		sprite->SetAttribute("name", g_Sprites[i]->name.c_str());
		sprite->SetAttribute("renderablename", g_Sprites[i]->name.c_str());
		sprite->SetAttribute("renderorder", 4);
		sprite->SetAttribute("isrendered", "false");
		sprite->SetDoubleAttribute("width", 1.0);
		sprite->SetDoubleAttribute("height", 1.35);
		sprite->SetDoubleAttribute("xrel", 0.0);
		sprite->SetDoubleAttribute("yrel", 0.0);
	}
	
	xmlDoc.SaveFile(filename.c_str());
}

bool ReadInSpriteSheet(std::string name)
{
	std::string filename = name + ".xml";

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
	rootElement->Attribute("width", &g_SpriteSheetWidth);
	rootElement->Attribute("height", &g_SpriteSheetHeight);

	for (TiXmlElement* spriteElement = rootElement->FirstChildElement(); spriteElement; spriteElement = spriteElement->NextSiblingElement())
	{
		Sprite* sprite = new Sprite();
		sprite->name = spriteElement->Attribute("n");
		spriteElement->Attribute("x", &sprite->x);
		spriteElement->Attribute("y", &sprite->y);
		spriteElement->Attribute("w", &sprite->width);
		spriteElement->Attribute("h", &sprite->height);
		sprite->textureFilename = textureFilename;

		g_Sprites.push_back(sprite);
	}

	return true;
}

