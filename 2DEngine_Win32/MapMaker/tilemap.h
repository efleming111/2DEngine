//
//  Map Maker
//  tilemap.h
//  Eric Fleming
//  6/19/2018
//

#pragma once

#include <string>
#include <sstream>
#include <list>
#include <iostream>

#include "tinyxml\tinyxml.h"

struct Tile
{
	std::string name;
	float x;
	float y;
};

struct TileMap
{
	int width;
	int height;

	int tileWidthInPixels;
	int tileHeightInPixels;

	std::list<Tile*> tiles;
};

void ReadInTiles(TiXmlElement* data, TileMap& tileMap);

bool ReadInTileMap(std::string filename, TileMap& tileMap)
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

	rootElement->Attribute("width", &tileMap.width);
	rootElement->Attribute("height", &tileMap.height);
	rootElement->Attribute("tilewidth", &tileMap.tileWidthInPixels);
	rootElement->Attribute("tileheight", &tileMap.tileHeightInPixels);

	for (TiXmlElement* child = rootElement->FirstChildElement(); child; child = child->NextSiblingElement())
	{
		std::string elementName = child->Value();
		if (elementName.compare("layer") == 0)
		{
			TiXmlElement* dataElement = child->FirstChildElement();
			ReadInTiles(dataElement, tileMap);
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

			else if (groupName.compare("level") == 0)
			{
				for (TiXmlElement* grandChild = child->FirstChildElement(); grandChild; grandChild = grandChild->NextSiblingElement())
				{
					std::string objectName = grandChild->Attribute("name");
					if (objectName.compare("playerstart") == 0)
					{
						grandChild->Attribute("x", &(g_TileMap.sceneObject.playerStartX));
						grandChild->Attribute("y", &(g_TileMap.sceneObject.playerStartY));
					}

					else
					{
						TileMapCollisionObject* col = new TileMapCollisionObject();

						col->name = grandChild->Attribute("name");
						grandChild->Attribute("x", &col->x);
						grandChild->Attribute("y", &col->y);
						grandChild->Attribute("width", &col->width);
						grandChild->Attribute("height", &col->height);

						g_TileMap.sceneObject.collisionObjects.push_back(col);
					}
				}
			}

			else if (groupName.compare("enemies") == 0)
			{
				for (TiXmlElement* grandChild = child->FirstChildElement(); grandChild; grandChild = grandChild->NextSiblingElement())
				{
					std::string enemyObjectName = grandChild->Attribute("name");
					if (enemyObjectName.compare("ZombieBoy") == 0)
					{
						Enemy* enemy = new Enemy();
						enemy->type = grandChild->Attribute("type");
						enemy->name = enemyObjectName;
						grandChild->Attribute("x", &enemy->x);
						grandChild->Attribute("y", &enemy->y);
						g_TileMap.enemies.push_back(enemy);
					}

					else if (enemyObjectName.compare("enemyreverse") == 0)
					{
						EnemyReverse* enemyReverse = new EnemyReverse();
						enemyReverse->name = enemyObjectName;
						grandChild->Attribute("x", &enemyReverse->x);
						grandChild->Attribute("y", &enemyReverse->y);
						grandChild->Attribute("width", &enemyReverse->width);
						grandChild->Attribute("height", &enemyReverse->height);
						g_TileMap.enemyReverse.push_back(enemyReverse);
					}
				}
			}
		}
	}

	return true;
}

void ReadInTiles(TiXmlElement* data, TileMap& tileMap)
{
	std::string strData = data->GetText();
	std::stringstream tileData(strData, std::ios_base::in);

	int id;
	char discard;
	for (int i = 0; i < (tileMap.width * tileMap.height); ++i)
	{
		tileData >> id;
		tileData >> discard;
		id--;
		g_TileMap.mapIDs.push_back(id);
	}
}


