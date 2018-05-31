//
//  Map Maker
//  main.cpp
//  Eric Fleming
//  5/22/2018
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

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

struct TileMapBackgroundObject
{
	int id;
	double x;
	double y;
	double width;
	double height;
};

struct TileMapCollisionObject
{
	std::string name;
	double x;
	double y;
	double width;
	double height;
};

struct TileMap
{
	int width;
	int height;
	double tileWidth;
	double tileHeight;
	std::vector<int> mapIDs;

	std::vector<TileMapBackgroundObject*> backgroundObjects;
	std::vector<TileMapCollisionObject*> collisionObjects;
};

// Map functions
bool ReadInSpriteSheet(std::string filename);
bool ReadInTileAtlas(std::string filename);
bool ReadInTileMap(std::string filename);
void OutputMap(std::string filename);

// Map globals
std::vector<Sprite*> g_Sprites;
double g_SpriteSheetWidth;
double g_SpriteSheetHeight;

std::map<int, std::string> g_TileAtlas;

TileMap g_TileMap;

int main(int argc, char* argv[])
{
	// TODO: temp to speed up testing
	std::cout << "Enter sprite sheet file<xml>: ";
	std::string filename;
	std::getline(std::cin, filename);
	if (!ReadInSpriteSheet(filename))
		return 1;
	
	std::cout << "Enter tile atlas file<tsx>: ";
	std::getline(std::cin, filename);
	if (!ReadInTileAtlas(filename))
		return 1;

	std::cout << "Enter tile map file<tmx>: ";
	std::getline(std::cin, filename);
	if (!ReadInTileMap(filename))
		return 1;

	std::cout << "Enter level name<lvl>: ";
	std::getline(std::cin, filename);
	OutputMap(filename);

	return 0;
}

void OutputMap(std::string filename)
{
	std::string levelData;

	TiXmlDocument xmlDoc;
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");
	xmlDoc.LinkEndChild(dec);

	TiXmlElement* level = new TiXmlElement("scene");
	level->SetAttribute("width", g_TileMap.width);
	level->SetAttribute("height", g_TileMap.height);
	xmlDoc.LinkEndChild(level);

	// Output tile map
	for (unsigned i = 0; i < g_TileMap.mapIDs.size(); ++i)
	{
		if (g_TileMap.mapIDs[i] >= 0)
		{
			TiXmlElement* gameobject = new TiXmlElement("gameobject");
			level->LinkEndChild(gameobject);
			gameobject->SetAttribute("type", "LevelObject");
			gameobject->SetAttribute("name", "Block");

			TiXmlElement* transform = new TiXmlElement("transform");
			transform->SetDoubleAttribute("x", (double)((int)i % g_TileMap.width) + .5);
			transform->SetDoubleAttribute("y", (double)(g_TileMap.height - ((int)i / g_TileMap.width)) - .5);
			transform->SetDoubleAttribute("z", 0.0);
			transform->SetDoubleAttribute("rotation", 0.0);
			transform->SetDoubleAttribute("sx", 1.0);
			transform->SetDoubleAttribute("sy", 1.0);
			transform->SetDoubleAttribute("sz", 1.0);
			gameobject->LinkEndChild(transform);

			TiXmlElement* components = new TiXmlElement("components");
			gameobject->LinkEndChild(components);

			Sprite* currentSprite = 0;
			for (unsigned j = 0; j < g_Sprites.size(); ++j)
			{
				if (g_Sprites[j]->name.compare(g_TileAtlas[g_TileMap.mapIDs[i]]) == 0)
				{
					currentSprite = g_Sprites[j];
					break;
				}
			}

			TiXmlElement* sprite = new TiXmlElement("sprite");
			sprite->SetAttribute("type", "sprite");
			sprite->SetAttribute("isrendered", "true");
			sprite->SetDoubleAttribute("width", currentSprite->width / g_TileMap.tileWidth);
			sprite->SetDoubleAttribute("height", currentSprite->height / g_TileMap.tileHeight);
			sprite->SetDoubleAttribute("xrel", 0.0);
			sprite->SetDoubleAttribute("yrel", 0.0);
			sprite->SetDoubleAttribute("texleft", currentSprite->x / g_SpriteSheetWidth);
			sprite->SetDoubleAttribute("texright", (currentSprite->x + currentSprite->width) / g_SpriteSheetWidth);
			sprite->SetDoubleAttribute("texbottom", currentSprite->y / g_SpriteSheetHeight);
			sprite->SetDoubleAttribute("textop", (currentSprite->y + currentSprite->height) / g_SpriteSheetHeight);
			std::string texfile = "data/spritesheets/";
			texfile += currentSprite->textureFilename;
			sprite->SetAttribute("texturefile", texfile.c_str());
			sprite->SetAttribute("shaderfile", "data/shaders/BasicTextureShader");


			components->LinkEndChild(sprite);
		}
		
	}

	double mapHeight = g_TileMap.height * g_TileMap.tileHeight;

	// Output background
	for (unsigned i = 0; i < g_TileMap.backgroundObjects.size(); ++i)
	{
		if (g_TileMap.backgroundObjects[i]->id >= 0)
		{
			TiXmlElement* gameobject = new TiXmlElement("gameobject");
			level->LinkEndChild(gameobject);
			gameobject->SetAttribute("type", "LevelObject");
			gameobject->SetAttribute("name", "Background");

			double cenX = (g_TileMap.backgroundObjects[i]->x + (g_TileMap.backgroundObjects[i]->width * .5)) / g_TileMap.tileWidth;
			double cenY = ((mapHeight - g_TileMap.backgroundObjects[i]->y) + (g_TileMap.backgroundObjects[i]->height * .5)) / g_TileMap.tileHeight;

			TiXmlElement* transform = new TiXmlElement("transform");
			transform->SetDoubleAttribute("x", cenX);
			transform->SetDoubleAttribute("y", cenY);
			transform->SetDoubleAttribute("z", 0.0);
			transform->SetAttribute("rotation", 0);
			transform->SetAttribute("sx", 1);
			transform->SetAttribute("sy", 1);
			transform->SetAttribute("sz", 1);
			gameobject->LinkEndChild(transform);

			TiXmlElement* components = new TiXmlElement("components");
			gameobject->LinkEndChild(components);

			Sprite* currentSprite = 0;
			for (unsigned j = 0; j < g_Sprites.size(); ++j)
			{
				if (g_Sprites[j]->name.compare(g_TileAtlas[g_TileMap.backgroundObjects[i]->id]) == 0)
				{
					currentSprite = g_Sprites[j];
					break;
				}
			}

			TiXmlElement* sprite = new TiXmlElement("sprite");
			sprite->SetAttribute("type", "sprite");
			sprite->SetAttribute("isrendered", "true");
			sprite->SetDoubleAttribute("width", g_TileMap.backgroundObjects[i]->width / g_TileMap.tileWidth);
			sprite->SetDoubleAttribute("height", g_TileMap.backgroundObjects[i]->height / g_TileMap.tileHeight);
			sprite->SetDoubleAttribute("xrel", 0.0);
			sprite->SetDoubleAttribute("yrel", 0.0);
			sprite->SetDoubleAttribute("texleft", currentSprite->x / g_SpriteSheetWidth);
			sprite->SetDoubleAttribute("texright", (currentSprite->x + currentSprite->width) / g_SpriteSheetWidth);
			sprite->SetDoubleAttribute("texbottom", currentSprite->y / g_SpriteSheetHeight);
			sprite->SetDoubleAttribute("textop", (currentSprite->y + currentSprite->height) / g_SpriteSheetHeight);
			std::string texfile = "data/spritesheets/";
			texfile += currentSprite->textureFilename;
			sprite->SetAttribute("texturefile", texfile.c_str());
			sprite->SetAttribute("shaderfile", "data/shaders/BasicTextureShader");


			components->LinkEndChild(sprite);
		}
	}

	// Output collision blocks
	for (unsigned i = 0; i < g_TileMap.collisionObjects.size(); ++i)
	{
		TiXmlElement* gameobject = new TiXmlElement("gameobject");
		level->LinkEndChild(gameobject);
		gameobject->SetAttribute("type", "LevelObject");
		gameobject->SetAttribute("name", "Collider");

		double cenX = ((g_TileMap.collisionObjects[i]->x + (g_TileMap.collisionObjects[i]->width * .5)) / g_TileMap.tileWidth);
		double cenY = ((mapHeight - g_TileMap.collisionObjects[i]->y) - (g_TileMap.collisionObjects[i]->height * .5)) / g_TileMap.tileHeight;

		TiXmlElement* transform = new TiXmlElement("transform");
		transform->SetDoubleAttribute("x", cenX);
		transform->SetDoubleAttribute("y", cenY);
		transform->SetDoubleAttribute("z", 0.0);
		transform->SetAttribute("rotation", 0);
		transform->SetAttribute("sx", 1);
		transform->SetAttribute("sy", 1);
		transform->SetAttribute("sz", 1);
		gameobject->LinkEndChild(transform);

		TiXmlElement* components = new TiXmlElement("components");
		gameobject->LinkEndChild(components);

		TiXmlElement* rigidbody = new TiXmlElement("rigidbody");
		rigidbody->SetAttribute("type", "rigidbody");
		rigidbody->SetAttribute("bodytype", "static");
		rigidbody->SetAttribute("canrotate", "false");
		components->LinkEndChild(rigidbody);

		TiXmlElement* boxCollider = new TiXmlElement("boxcollider");
		boxCollider->SetAttribute("type", "box");
		boxCollider->SetAttribute("name", g_TileMap.collisionObjects[i]->name.c_str());
		boxCollider->SetDoubleAttribute("width", g_TileMap.collisionObjects[i]->width / g_TileMap.tileWidth);
		boxCollider->SetDoubleAttribute("height", g_TileMap.collisionObjects[i]->height / g_TileMap.tileHeight);
		boxCollider->SetDoubleAttribute("xrel", 0.0);
		boxCollider->SetDoubleAttribute("yrel", 0.0);
		boxCollider->SetDoubleAttribute("angle", 0.0);
		boxCollider->SetDoubleAttribute("density", 1.0);
		boxCollider->SetDoubleAttribute("friction", 0.3);
		boxCollider->SetAttribute("issensor", "false");

		rigidbody->LinkEndChild(boxCollider);

	}

	xmlDoc.SaveFile(filename.c_str());
}

bool ReadInTileMap(std::string filename)
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

	rootElement->Attribute("width", &g_TileMap.width);
	rootElement->Attribute("height", &g_TileMap.height);
	rootElement->Attribute("tilewidth", &g_TileMap.tileWidth);
	rootElement->Attribute("tileheight", &g_TileMap.tileHeight);

	for (TiXmlElement* child = rootElement->FirstChildElement(); child; child = child->NextSiblingElement())
	{
		std::string elementName = child->Value();
		if (elementName.compare("layer") == 0)
		{
			TiXmlElement* dataElement = child->FirstChildElement();
			std::string data = dataElement->GetText();
			std::stringstream tileData(data, std::ios_base::in);

			int id;
			char discard;
			for (int i = 0; i < (g_TileMap.width * g_TileMap.height); ++i)
			{
				tileData >> id;
				tileData >> discard;
				id--;
				g_TileMap.mapIDs.push_back(id);
			}
		}

		else if (elementName.compare("objectgroup") == 0)
		{
			std::string groupName = child->Attribute("name");
			if (groupName.compare("background") == 0)
			{
				for (TiXmlElement* grandChild = child->FirstChildElement(); grandChild; grandChild = grandChild->NextSiblingElement())
				{
					TileMapBackgroundObject* bg = new TileMapBackgroundObject();

					grandChild->Attribute("gid", &bg->id);
					bg->id--;
					grandChild->Attribute("x", &bg->x);
					grandChild->Attribute("y", &bg->y);
					grandChild->Attribute("width", &bg->width);
					grandChild->Attribute("height", &bg->height);

					g_TileMap.backgroundObjects.push_back(bg);
				}
			}

			else if (groupName.compare("collision") == 0)
			{
				for (TiXmlElement* grandChild = child->FirstChildElement(); grandChild; grandChild = grandChild->NextSiblingElement())
				{
					TileMapCollisionObject* col = new TileMapCollisionObject();

					col->name = grandChild->Attribute("name");
					grandChild->Attribute("x", &col->x);
					grandChild->Attribute("y", &col->y);
					grandChild->Attribute("width", &col->width);
					grandChild->Attribute("height", &col->height);

					g_TileMap.collisionObjects.push_back(col);
				}
			}
		}
	}

	return true;
}

bool ReadInTileAtlas(std::string filename)
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

	TiXmlElement* firstChild = rootElement->FirstChildElement();

	for (TiXmlElement* tileElement = firstChild->NextSiblingElement(); tileElement; tileElement = tileElement->NextSiblingElement())
	{
		int id;
		tileElement->Attribute("id", &id);

		TiXmlElement* imageElement = tileElement->FirstChildElement();
		std::string name = imageElement->Attribute("source");

		int slashIndex = name.find_last_of("/", name.length() - 2);
		g_TileAtlas[id] = name.substr(slashIndex + 1, name.length() - 2);
	}

	return true;
}

bool ReadInSpriteSheet(std::string filename)
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
