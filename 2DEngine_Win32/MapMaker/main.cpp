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

struct CollisionObject
{
	std::string name;
	std::string type;
	double x;
	double y;
	double width;
	double height;
};

struct TileMap
{
	int width;
	int height;

	std::vector<std::string> levelGOFilenames;

	std::vector<int> foregroundIds;
	std::vector<int> backgroundIds;
	std::vector<int> enemyIds;
	std::vector<int> objectIds;

	std::vector<CollisionObject*> collisionObjects;
};

// Map functions
bool ReadInSpriteSheet(const char* filename);
bool ReadInTileMap(const char* filename);
void OutputMap(const char* filename);

// Map globals
std::vector<Sprite*> gSprites;
double gSpriteSheetWidth;
double gSpriteSheetHeight;

TileMap gTileMap;

int main(int argc, char* argv[])
{
	if (!ReadInSpriteSheet(argv[1]))
		return 1;

	if (!ReadInTileMap(argv[2]))
		return 1;

	OutputMap(argv[3]);

	return 0;
}

void OutputMap(const char* filename)
{
	// Create level file
	std::string levelFilename = filename;
	levelFilename += ".lvl";

	TiXmlDocument levelDoc;
	TiXmlDeclaration* levelDec = new TiXmlDeclaration("1.0", "UTF-8", "");
	levelDoc.LinkEndChild(levelDec);

	TiXmlElement* level = new TiXmlElement("level");
	level->SetAttribute("width", gTileMap.width);
	level->SetAttribute("height", gTileMap.height);
	levelDoc.LinkEndChild(level);

	for (unsigned i = 0; i < gTileMap.levelGOFilenames.size(); ++i)
	{
		TiXmlElement* goFilename = new TiXmlElement("gofilename");
		goFilename->SetAttribute("name", gTileMap.levelGOFilenames[i].c_str());
		level->LinkEndChild(goFilename);
	}

	levelDoc.SaveFile(levelFilename.c_str());

	// Create level game object
	TiXmlDocument goDoc;
	TiXmlDeclaration* goDec = new TiXmlDeclaration("1.0", "UTF-8", "");
	goDoc.LinkEndChild(goDec);

	// Set up root element for scene game object file
	TiXmlElement* go = new TiXmlElement("go");
	goDoc.LinkEndChild(go);

//	// Set up resources
//	TiXmlElement* resources = new TiXmlElement("resources");
//	gob->LinkEndChild(resources);
//
//	// Output renderable resources
//	for (unsigned i = 0; i < g_Sprites.size(); ++i)
//	{
//		TiXmlElement* renderable = new TiXmlElement("renderable");
//		resources->LinkEndChild(renderable);
//
//		renderable->SetAttribute("type", "Renderable");
//		renderable->SetAttribute("name", g_Sprites[i]->name.c_str());
//		renderable->SetAttribute("pivotpoint", "center");
//
//		renderable->SetDoubleAttribute("texleft", g_Sprites[i]->x / g_SpriteSheetWidth);
//		renderable->SetDoubleAttribute("texright", (g_Sprites[i]->x + g_Sprites[i]->width) / g_SpriteSheetWidth);
//		renderable->SetDoubleAttribute("texbottom", g_Sprites[i]->y / g_SpriteSheetHeight);
//		renderable->SetDoubleAttribute("textop", (g_Sprites[i]->y + g_Sprites[i]->height) / g_SpriteSheetHeight);
//		std::string texfile = "data/spritesheets/";
//		texfile += g_Sprites[i]->textureFilename;
//		renderable->SetAttribute("texturefile", texfile.c_str());
//		renderable->SetAttribute("shaderfile", "data/shaders/BasicTextureShader");
//	}
//
//	// Set up scene game object
//	TiXmlElement* go = new TiXmlElement("gameobject");
//	go->SetAttribute("type", "Scene");
//	go->SetAttribute("name", "SCENE_NAME");
//	go->SetDoubleAttribute("clearcolorred", 0.0);
//	go->SetDoubleAttribute("clearcolorgreen", 0.0);
//	go->SetDoubleAttribute("clearcolorblue", 0.0);
//	gob->LinkEndChild(go);
//
//	TiXmlElement* scenes = new TiXmlElement("scenes");
//	scenes->SetAttribute("option1", "NEXT_SCENE_NAME");
//	scenes->SetAttribute("option2", "ADD_FOR_ADDITIONAL_SCENE_OPTIONS");
//	go->LinkEndChild(scenes);
//
//	TiXmlElement* playerstart = new TiXmlElement("playerstart");
//	playerstart->SetDoubleAttribute("x", g_TileMap.sceneObject.playerStartX / g_TileMap.tileWidth);
//	playerstart->SetDoubleAttribute("y", g_TileMap.sceneObject.playerStartY / g_TileMap.tileHeight);
//	go->LinkEndChild(playerstart);
//
//	TiXmlElement* trans = new TiXmlElement("transform");
//	trans->SetDoubleAttribute("x", 0);
//	trans->SetDoubleAttribute("y", 0);
//	trans->SetDoubleAttribute("z", 0);
//	trans->SetDoubleAttribute("rotation", 0.0);
//	trans->SetDoubleAttribute("sx", 1);
//	trans->SetDoubleAttribute("sy", 1);
//	trans->SetDoubleAttribute("sz", 1);
//	go->LinkEndChild(trans);
//
//	TiXmlElement* sceneComponents = new TiXmlElement("components");
//	go->LinkEndChild(sceneComponents);
//
//	TiXmlElement* sceneRigidbody = new TiXmlElement("rigidbody");
//	sceneRigidbody->SetAttribute("type", "rigidbody");
//	sceneRigidbody->SetAttribute("bodytype", "static");
//	sceneRigidbody->SetAttribute("canrotate", "false");
//	sceneComponents->LinkEndChild(sceneRigidbody);
//
//	for (unsigned i = 0; i < g_TileMap.sceneObject.collisionObjects.size(); ++i)
//	{
//		TiXmlElement* boxCollider = new TiXmlElement("boxcollider");
//		boxCollider->SetAttribute("type", "box");
//		boxCollider->SetAttribute("name", g_TileMap.sceneObject.collisionObjects[i]->name.c_str());
//		boxCollider->SetDoubleAttribute("width", g_TileMap.sceneObject.collisionObjects[i]->width / g_TileMap.tileWidth);
//		boxCollider->SetDoubleAttribute("height", g_TileMap.sceneObject.collisionObjects[i]->height / g_TileMap.tileHeight);
//
//		double xPos = (g_TileMap.sceneObject.collisionObjects[i]->x + (g_TileMap.sceneObject.collisionObjects[i]->width * .5)) / g_TileMap.tileWidth;
//		double yPos = g_TileMap.height - ((g_TileMap.sceneObject.collisionObjects[i]->y + (g_TileMap.sceneObject.collisionObjects[i]->height * .5)) / g_TileMap.tileHeight);
//		boxCollider->SetDoubleAttribute("xrel", xPos);
//		boxCollider->SetDoubleAttribute("yrel", yPos);
//		boxCollider->SetDoubleAttribute("angle", 0.0);
//		boxCollider->SetDoubleAttribute("density", 1.0);
//		boxCollider->SetDoubleAttribute("friction", 0.3);
//		boxCollider->SetAttribute("issensor", "true");
//
//		sceneRigidbody->LinkEndChild(boxCollider);
//	}
//
//	// Output tile map game objects
//	for (unsigned i = 0; i < g_TileMap.mapIDs.size(); ++i)
//	{
//		if (g_TileMap.mapIDs[i] >= 0)
//		{
//			TiXmlElement* gameobject = new TiXmlElement("gameobject");
//			gob->LinkEndChild(gameobject);
//			gameobject->SetAttribute("type", "LevelObject");
//			gameobject->SetAttribute("name", "Block");
//
//			TiXmlElement* transform = new TiXmlElement("transform");
//			transform->SetDoubleAttribute("x", (double)((int)i % g_TileMap.width) + .5);
//			transform->SetDoubleAttribute("y", (double)(g_TileMap.height - ((int)i / g_TileMap.width)) - .5);
//			transform->SetDoubleAttribute("z", 0.0);
//			transform->SetDoubleAttribute("rotation", 0.0);
//			transform->SetDoubleAttribute("sx", 1.0);
//			transform->SetDoubleAttribute("sy", 1.0);
//			transform->SetDoubleAttribute("sz", 1.0);
//			gameobject->LinkEndChild(transform);
//
//			TiXmlElement* components = new TiXmlElement("components");
//			gameobject->LinkEndChild(components);
//
//			Sprite* currentSprite = 0;
//			for (unsigned j = 0; j < g_Sprites.size(); ++j)
//			{
//				if (g_Sprites[j]->name.compare(g_TileAtlas[g_TileMap.mapIDs[i]]) == 0)
//				{
//					currentSprite = g_Sprites[j];
//					break;
//				}
//			}
//
//			TiXmlElement* sprite = new TiXmlElement("sprite");
//			sprite->SetAttribute("type", "sprite");
//			sprite->SetAttribute("name", "tile");
//			sprite->SetAttribute("renderablename", currentSprite->name.c_str());
//			sprite->SetAttribute("renderorder", 3);
//			sprite->SetAttribute("isrendered", "true");
//			sprite->SetDoubleAttribute("width", currentSprite->width / g_TileMap.tileWidth);
//			sprite->SetDoubleAttribute("height", currentSprite->height / g_TileMap.tileHeight);
//			sprite->SetDoubleAttribute("xrel", 0.0);
//			sprite->SetDoubleAttribute("yrel", 0.0);
//
//			components->LinkEndChild(sprite);
//		}
//
//	}
//
//	double mapHeight = g_TileMap.height * g_TileMap.tileHeight;
//
//	// Output background game objects
//	for (unsigned i = 0; i < g_TileMap.backgroundObjects.size(); ++i)
//	{
//		if (g_TileMap.backgroundObjects[i]->id >= 0)
//		{
//			TiXmlElement* gameobject = new TiXmlElement("gameobject");
//			gob->LinkEndChild(gameobject);
//			gameobject->SetAttribute("type", "LevelObject");
//			gameobject->SetAttribute("name", "Background");
//
//			double cenX = (g_TileMap.backgroundObjects[i]->x + (g_TileMap.backgroundObjects[i]->width * .5)) / g_TileMap.tileWidth;
//			double cenY = ((mapHeight - g_TileMap.backgroundObjects[i]->y) + (g_TileMap.backgroundObjects[i]->height * .5)) / g_TileMap.tileHeight;
//
//			TiXmlElement* transform = new TiXmlElement("transform");
//			transform->SetDoubleAttribute("x", cenX);
//			transform->SetDoubleAttribute("y", cenY);
//			transform->SetDoubleAttribute("z", 0.0);
//			transform->SetAttribute("rotation", 0);
//			transform->SetAttribute("sx", 1);
//			transform->SetAttribute("sy", 1);
//			transform->SetAttribute("sz", 1);
//			gameobject->LinkEndChild(transform);
//
//			TiXmlElement* components = new TiXmlElement("components");
//			gameobject->LinkEndChild(components);
//
//			Sprite* currentSprite = 0;
//			for (unsigned j = 0; j < g_Sprites.size(); ++j)
//			{
//				if (g_Sprites[j]->name.compare(g_TileAtlas[g_TileMap.backgroundObjects[i]->id]) == 0)
//				{
//					currentSprite = g_Sprites[j];
//					break;
//				}
//			}
//
//			TiXmlElement* sprite = new TiXmlElement("sprite");
//			sprite->SetAttribute("type", "sprite");
//			sprite->SetAttribute("name", "background");
//			sprite->SetAttribute("renderablename", currentSprite->name.c_str());
//			sprite->SetAttribute("renderorder", 2);
//			sprite->SetAttribute("isrendered", "true");
//			sprite->SetDoubleAttribute("width", g_TileMap.backgroundObjects[i]->width / g_TileMap.tileWidth);
//			sprite->SetDoubleAttribute("height", g_TileMap.backgroundObjects[i]->height / g_TileMap.tileHeight);
//			sprite->SetDoubleAttribute("xrel", 0.0);
//			sprite->SetDoubleAttribute("yrel", 0.0);
//
//			components->LinkEndChild(sprite);
//		}
//	}
//
//	// Output collision blocks game objects
//	for (unsigned i = 0; i < g_TileMap.collisionObjects.size(); ++i)
//	{
//		TiXmlElement* gameobject = new TiXmlElement("gameobject");
//		gob->LinkEndChild(gameobject);
//		gameobject->SetAttribute("type", "LevelObject");
//		gameobject->SetAttribute("name", "Collider");
//
//		double cenX = ((g_TileMap.collisionObjects[i]->x + (g_TileMap.collisionObjects[i]->width * .5)) / g_TileMap.tileWidth);
//		double cenY = ((mapHeight - g_TileMap.collisionObjects[i]->y) - (g_TileMap.collisionObjects[i]->height * .5)) / g_TileMap.tileHeight;
//
//		TiXmlElement* transform = new TiXmlElement("transform");
//		transform->SetDoubleAttribute("x", cenX);
//		transform->SetDoubleAttribute("y", cenY);
//		transform->SetDoubleAttribute("z", 0.0);
//		transform->SetAttribute("rotation", 0);
//		transform->SetAttribute("sx", 1);
//		transform->SetAttribute("sy", 1);
//		transform->SetAttribute("sz", 1);
//		gameobject->LinkEndChild(transform);
//
//		TiXmlElement* components = new TiXmlElement("components");
//		gameobject->LinkEndChild(components);
//
//		TiXmlElement* rigidbody = new TiXmlElement("rigidbody");
//		rigidbody->SetAttribute("type", "rigidbody");
//		rigidbody->SetAttribute("bodytype", "static");
//		rigidbody->SetAttribute("canrotate", "false");
//		components->LinkEndChild(rigidbody);
//
//		TiXmlElement* boxCollider = new TiXmlElement("boxcollider");
//		boxCollider->SetAttribute("type", "box");
//		boxCollider->SetAttribute("name", g_TileMap.collisionObjects[i]->name.c_str());
//		boxCollider->SetDoubleAttribute("width", g_TileMap.collisionObjects[i]->width / g_TileMap.tileWidth);
//		boxCollider->SetDoubleAttribute("height", g_TileMap.collisionObjects[i]->height / g_TileMap.tileHeight);
//		boxCollider->SetDoubleAttribute("xrel", 0.0);
//		boxCollider->SetDoubleAttribute("yrel", 0.0);
//		boxCollider->SetDoubleAttribute("angle", 0.0);
//		boxCollider->SetDoubleAttribute("density", 1.0);
//		boxCollider->SetDoubleAttribute("friction", 0.0);
//		boxCollider->SetAttribute("issensor", "false");
//
//		rigidbody->LinkEndChild(boxCollider);
//	}
//
//	// Output enemy reverse sensors
//	for (unsigned i = 0; i < g_TileMap.enemyReverse.size(); ++i)
//	{
//		TiXmlElement* gameobject = new TiXmlElement("gameobject");
//		gob->LinkEndChild(gameobject);
//		gameobject->SetAttribute("type", "LevelObject");
//		gameobject->SetAttribute("name", "enemyReverse");
//
//		double cenX = ((g_TileMap.enemyReverse[i]->x + (g_TileMap.enemyReverse[i]->width * .5)) / g_TileMap.tileWidth);
//		double cenY = ((mapHeight - g_TileMap.enemyReverse[i]->y) - (g_TileMap.enemyReverse[i]->height * .5)) / g_TileMap.tileHeight;
//
//		TiXmlElement* transform = new TiXmlElement("transform");
//		transform->SetDoubleAttribute("x", cenX);
//		transform->SetDoubleAttribute("y", cenY);
//		transform->SetDoubleAttribute("z", 0.0);
//		transform->SetAttribute("rotation", 0);
//		transform->SetAttribute("sx", 1);
//		transform->SetAttribute("sy", 1);
//		transform->SetAttribute("sz", 1);
//		gameobject->LinkEndChild(transform);
//
//		TiXmlElement* components = new TiXmlElement("components");
//		gameobject->LinkEndChild(components);
//
//		TiXmlElement* rigidbody = new TiXmlElement("rigidbody");
//		rigidbody->SetAttribute("type", "rigidbody");
//		rigidbody->SetAttribute("bodytype", "static");
//		rigidbody->SetAttribute("canrotate", "false");
//		components->LinkEndChild(rigidbody);
//
//		TiXmlElement* boxCollider = new TiXmlElement("boxcollider");
//		boxCollider->SetAttribute("type", "box");
//		boxCollider->SetAttribute("name", g_TileMap.enemyReverse[i]->name.c_str());
//		boxCollider->SetDoubleAttribute("width", g_TileMap.enemyReverse[i]->width / g_TileMap.tileWidth);
//		boxCollider->SetDoubleAttribute("height", g_TileMap.enemyReverse[i]->height / g_TileMap.tileHeight);
//		boxCollider->SetDoubleAttribute("xrel", 0.0);
//		boxCollider->SetDoubleAttribute("yrel", 0.0);
//		boxCollider->SetDoubleAttribute("angle", 0.0);
//		boxCollider->SetDoubleAttribute("density", 1.0);
//		boxCollider->SetDoubleAttribute("friction", 0.0);
//		boxCollider->SetAttribute("issensor", "true");
//
//		rigidbody->LinkEndChild(boxCollider);
//	}
//
//	// Output enemies
//	for (unsigned i = 0; i < g_TileMap.enemies.size(); ++i)
//	{
//		TiXmlElement* gameobject = new TiXmlElement("gameobject");
//		gob->LinkEndChild(gameobject);
//		gameobject->SetAttribute("type", g_TileMap.enemies[i]->type.c_str());
//		gameobject->SetAttribute("name", g_TileMap.enemies[i]->name.c_str());
//		gameobject->SetDoubleAttribute("walkacceleration", .1);
//		gameobject->SetDoubleAttribute("maxwalkspeed", 1.2);
//
//		TiXmlElement* transform = new TiXmlElement("transform");
//		transform->SetDoubleAttribute("x", g_TileMap.enemies[i]->x / g_TileMap.tileWidth);
//		transform->SetDoubleAttribute("y", g_TileMap.height - (g_TileMap.enemies[i]->y / g_TileMap.tileHeight));
//		transform->SetDoubleAttribute("z", 0.0);
//		transform->SetAttribute("rotation", 0);
//		transform->SetAttribute("sx", 1);
//		transform->SetAttribute("sy", 1);
//		transform->SetAttribute("sz", 1);
//		gameobject->LinkEndChild(transform);
//
//		TiXmlElement* components = new TiXmlElement("components");
//		gameobject->LinkEndChild(components);
//
//		TiXmlElement* rigidbody = new TiXmlElement("rigidbody");
//		rigidbody->SetAttribute("type", "rigidbody");
//		rigidbody->SetAttribute("bodytype", "dynamic");
//		rigidbody->SetAttribute("canrotate", "false");
//		components->LinkEndChild(rigidbody);
//
//		TiXmlElement* enemyBoxCollider = new TiXmlElement("boxcollider");
//		enemyBoxCollider->SetAttribute("type", "box");
//		enemyBoxCollider->SetAttribute("name", "enemy");
//		enemyBoxCollider->SetDoubleAttribute("width", .8);
//		enemyBoxCollider->SetDoubleAttribute("height", 1.35);
//		enemyBoxCollider->SetDoubleAttribute("xrel", 0.0);
//		enemyBoxCollider->SetDoubleAttribute("yrel", 0.0);
//		enemyBoxCollider->SetDoubleAttribute("angle", 0.0);
//		enemyBoxCollider->SetDoubleAttribute("density", 1.0);
//		enemyBoxCollider->SetDoubleAttribute("friction", 0.0);
//		enemyBoxCollider->SetAttribute("issensor", "false");
//		rigidbody->LinkEndChild(enemyBoxCollider);
//
//		TiXmlElement* attackBoxCollider = new TiXmlElement("boxcollider");
//		attackBoxCollider->SetAttribute("type", "box");
//		attackBoxCollider->SetAttribute("name", "attack");
//		attackBoxCollider->SetDoubleAttribute("width", 2.0);
//		attackBoxCollider->SetDoubleAttribute("height", 1.5);
//		attackBoxCollider->SetDoubleAttribute("xrel", 0.0);
//		attackBoxCollider->SetDoubleAttribute("yrel", 0.0);
//		attackBoxCollider->SetDoubleAttribute("angle", 0.0);
//		attackBoxCollider->SetDoubleAttribute("density", 1.0);
//		attackBoxCollider->SetDoubleAttribute("friction", 0.0);
//		attackBoxCollider->SetAttribute("issensor", "true");
//		rigidbody->LinkEndChild(attackBoxCollider);
//
//		TiXmlElement* animator = new TiXmlElement("animator");
//		animator->SetAttribute("type", "animator");
//		animator->SetAttribute("startinganimation", 0);
//		components->LinkEndChild(animator);
//
//		TiXmlElement* animation = new TiXmlElement("animation");
//		animation->SetAttribute("name", "NAME_OF_ANIMATION");
//		animation->SetDoubleAttribute("frameinterval", .15);
//		animation->SetAttribute("islooping", "true");
//		animator->LinkEndChild(animation);
//
//		TiXmlElement* sprite = new TiXmlElement("sprite");
//		animation->LinkEndChild(sprite);
//	}
//
//	xmlDoc.SaveFile(gobFilename.c_str());
}

bool ReadInTileMap(const char* filename)
{
	TiXmlDocument tmxDoc;
	tmxDoc.LoadFile(filename);

	TiXmlElement* map = tmxDoc.RootElement();
	if (!map)
	{
		std::cout << "Error finding tile atlas root element\n" << std::endl;
		std::cin.get();
		return false;
	}

	map->Attribute("width", &gTileMap.width);
	map->Attribute("height", &gTileMap.height);

	for (TiXmlElement* childElement = map->FirstChildElement(); childElement; childElement = childElement->NextSiblingElement())
	{
		std::string elementName = childElement->Value();

		if (elementName.compare("properties") == 0)
		{
			for (TiXmlElement* property = childElement->FirstChildElement(); property; property = property->NextSiblingElement())
			{
				std::string propertyName = property->Attribute("name");
				
				if (propertyName.find("filename") != std::string::npos)
				{
					std::string goFilename = property->Attribute("value");
					gTileMap.levelGOFilenames.push_back(goFilename);
				}
			}
		}

		else if (elementName.compare("layer") == 0)
		{
			std::string layerName = childElement->Attribute("name");

			if (layerName.compare("TilesFG") == 0)
			{
				TiXmlElement* dataElement = childElement->FirstChildElement();
				std::string data = dataElement->GetText();
				std::stringstream tileData(data, std::ios_base::in);

				int id;
				char discard;
				for (int i = 0; i < (gTileMap.width * gTileMap.height); ++i)
				{
					tileData >> id;
					tileData >> discard;
					id--;
					gTileMap.foregroundIds.push_back(id);
				}
			}
			
			else if (layerName.compare("TilesBG") == 0)
			{
				TiXmlElement* dataElement = childElement->FirstChildElement();
				std::string data = dataElement->GetText();
				std::stringstream tileData(data, std::ios_base::in);

				int id;
				char discard;
				for (int i = 0; i < (gTileMap.width * gTileMap.height); ++i)
				{
					tileData >> id;
					tileData >> discard;
					id--;
					gTileMap.backgroundIds.push_back(id);
				}
			}

			else if (layerName.compare("Enemy") == 0)
			{
				TiXmlElement* dataElement = childElement->FirstChildElement();
				std::string data = dataElement->GetText();
				std::stringstream tileData(data, std::ios_base::in);

				int id;
				char discard;
				for (int i = 0; i < (gTileMap.width * gTileMap.height); ++i)
				{
					tileData >> id;
					tileData >> discard;
					id--;
					gTileMap.enemyIds.push_back(id);
				}
			}

			else if (layerName.compare("TilesObject") == 0)
			{
				TiXmlElement* dataElement = childElement->FirstChildElement();
				std::string data = dataElement->GetText();
				std::stringstream tileData(data, std::ios_base::in);

				int id;
				char discard;
				for (int i = 0; i < (gTileMap.width * gTileMap.height); ++i)
				{
					tileData >> id;
					tileData >> discard;
					id--;
					gTileMap.objectIds.push_back(id);
				}
			}
		}

		else if (elementName.compare("objectgroup") == 0)
		{
			std::string groupName = childElement->Attribute("name");

			if (groupName.compare("Collision") == 0)
			{
				for (TiXmlElement* collisionObject = childElement->FirstChildElement(); collisionObject; collisionObject = collisionObject->NextSiblingElement())
				{
					CollisionObject* object = new CollisionObject();

					object->name = collisionObject->Attribute("name");
					object->type = collisionObject->Attribute("type");
					collisionObject->Attribute("x", &object->x);
					collisionObject->Attribute("y", &object->y);
					collisionObject->Attribute("width", &object->width);
					collisionObject->Attribute("height", &object->height);

					gTileMap.collisionObjects.push_back(object);
				}
			}

			else if (groupName.compare("Misc") == 0)
			{
				// Nothing here yet
			}
		}
	}

	return true;
}

bool ReadInSpriteSheet(const char* filename)
{
	TiXmlDocument xmlDoc;
	xmlDoc.LoadFile(filename);

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





