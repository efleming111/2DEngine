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

struct SceneObject
{
	double playerStartX;
	double playerStartY;

	std::vector<TileMapCollisionObject*> collisionObjects;
};

struct Enemy
{
	std::string type;
	std::string name;
	double x;
	double y;
};

struct EnemyReverse
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
	SceneObject sceneObject;
	std::vector<Enemy*> enemies;
	std::vector<EnemyReverse*> enemyReverse;
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

	std::cout << "Enter scene name: ";
	std::getline(std::cin, filename);
	OutputMap(filename);

	return 0;
}

void OutputMap(std::string filename)
{
	std::string scnFilename = filename + ".scn";
	std::string gobFilename = filename + ".gob";

	TiXmlDocument scnDoc;
	TiXmlDeclaration* scnDec = new TiXmlDeclaration("1.0", "UTF-8", "");
	scnDoc.LinkEndChild(scnDec);

	// Set up root element for scene object file
	TiXmlElement* scnScene = new TiXmlElement("scene");
	scnScene->SetAttribute("width", g_TileMap.width);
	scnScene->SetAttribute("height", g_TileMap.height);
	scnDoc.LinkEndChild(scnScene);

	TiXmlElement* scnGOB = new TiXmlElement("gob");
	scnGOB->SetAttribute("filename", "ADD_GOB_FILENAMES_HERE");
	scnScene->LinkEndChild(scnGOB);

	scnDoc.SaveFile(scnFilename.c_str());

	TiXmlDocument xmlDoc;
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");
	xmlDoc.LinkEndChild(dec);

	// Set up root element for scene game object file
	TiXmlElement* gob = new TiXmlElement("gob");
	xmlDoc.LinkEndChild(gob);

	// Set up resources
	TiXmlElement* resources = new TiXmlElement("resources");
	gob->LinkEndChild(resources);

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
		renderable->SetDoubleAttribute("texbottom", g_Sprites[i]->y / g_SpriteSheetHeight);
		renderable->SetDoubleAttribute("textop", (g_Sprites[i]->y + g_Sprites[i]->height) / g_SpriteSheetHeight);
		std::string texfile = "data/spritesheets/";
		texfile += g_Sprites[i]->textureFilename;
		renderable->SetAttribute("texturefile", texfile.c_str());
		renderable->SetAttribute("shaderfile", "data/shaders/BasicTextureShader");
	}

	// Set up scene game object
	TiXmlElement* go = new TiXmlElement("gameobject");
	go->SetAttribute("type", "Scene");
	go->SetAttribute("name", "SCENE_NAME");
	go->SetDoubleAttribute("clearcolorred", 0.0);
	go->SetDoubleAttribute("clearcolorgreen", 0.0);
	go->SetDoubleAttribute("clearcolorblue", 0.0);
	gob->LinkEndChild(go);

	TiXmlElement* scenes = new TiXmlElement("scenes");
	scenes->SetAttribute("option1", "NEXT_SCENE_NAME");
	scenes->SetAttribute("option2", "ADD_FOR_ADDITIONAL_SCENE_OPTIONS");
	go->LinkEndChild(scenes);

	TiXmlElement* playerstart = new TiXmlElement("playerstart");
	playerstart->SetDoubleAttribute("x", g_TileMap.sceneObject.playerStartX / g_TileMap.tileWidth);
	playerstart->SetDoubleAttribute("y", g_TileMap.sceneObject.playerStartY / g_TileMap.tileHeight);
	go->LinkEndChild(playerstart);

	TiXmlElement* trans = new TiXmlElement("transform");
	trans->SetDoubleAttribute("x", 0);
	trans->SetDoubleAttribute("y", 0);
	trans->SetDoubleAttribute("z", 0);
	trans->SetDoubleAttribute("rotation", 0.0);
	trans->SetDoubleAttribute("sx", 1);
	trans->SetDoubleAttribute("sy", 1);
	trans->SetDoubleAttribute("sz", 1);
	go->LinkEndChild(trans);
	
	TiXmlElement* sceneComponents = new TiXmlElement("components");
	go->LinkEndChild(sceneComponents);

	TiXmlElement* sceneRigidbody = new TiXmlElement("rigidbody");
	sceneRigidbody->SetAttribute("type", "rigidbody");
	sceneRigidbody->SetAttribute("bodytype", "static");
	sceneRigidbody->SetAttribute("canrotate", "false");
	sceneComponents->LinkEndChild(sceneRigidbody);

	for (unsigned i = 0; i < g_TileMap.sceneObject.collisionObjects.size(); ++i)
	{
		TiXmlElement* boxCollider = new TiXmlElement("boxcollider");
		boxCollider->SetAttribute("type", "box");
		boxCollider->SetAttribute("name", g_TileMap.sceneObject.collisionObjects[i]->name.c_str());
		boxCollider->SetDoubleAttribute("width", g_TileMap.sceneObject.collisionObjects[i]->width / g_TileMap.tileWidth);
		boxCollider->SetDoubleAttribute("height", g_TileMap.sceneObject.collisionObjects[i]->height / g_TileMap.tileHeight);

		double xPos = (g_TileMap.sceneObject.collisionObjects[i]->x + (g_TileMap.sceneObject.collisionObjects[i]->width * .5)) / g_TileMap.tileWidth;
		double yPos = g_TileMap.height - ((g_TileMap.sceneObject.collisionObjects[i]->y + (g_TileMap.sceneObject.collisionObjects[i]->height * .5)) / g_TileMap.tileHeight);
		boxCollider->SetDoubleAttribute("xrel", xPos);
		boxCollider->SetDoubleAttribute("yrel", yPos);
		boxCollider->SetDoubleAttribute("angle", 0.0);
		boxCollider->SetDoubleAttribute("density", 1.0);
		boxCollider->SetDoubleAttribute("friction", 0.3);
		boxCollider->SetAttribute("issensor", "true");

		sceneRigidbody->LinkEndChild(boxCollider);
	}

	// Output tile map game objects
	for (unsigned i = 0; i < g_TileMap.mapIDs.size(); ++i)
	{
		if (g_TileMap.mapIDs[i] >= 0)
		{
			TiXmlElement* gameobject = new TiXmlElement("gameobject");
			gob->LinkEndChild(gameobject);
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
			sprite->SetAttribute("name", "tile");
			sprite->SetAttribute("renderablename", currentSprite->name.c_str());
			sprite->SetAttribute("renderorder", 3);
			sprite->SetAttribute("isrendered", "true");
			sprite->SetDoubleAttribute("width", currentSprite->width / g_TileMap.tileWidth);
			sprite->SetDoubleAttribute("height", currentSprite->height / g_TileMap.tileHeight);
			sprite->SetDoubleAttribute("xrel", 0.0);
			sprite->SetDoubleAttribute("yrel", 0.0);

			components->LinkEndChild(sprite);
		}
		
	}

	double mapHeight = g_TileMap.height * g_TileMap.tileHeight;

	// Output background game objects
	for (unsigned i = 0; i < g_TileMap.backgroundObjects.size(); ++i)
	{
		if (g_TileMap.backgroundObjects[i]->id >= 0)
		{
			TiXmlElement* gameobject = new TiXmlElement("gameobject");
			gob->LinkEndChild(gameobject);
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
			sprite->SetAttribute("name", "background");
			sprite->SetAttribute("renderablename", currentSprite->name.c_str());
			sprite->SetAttribute("renderorder", 2);
			sprite->SetAttribute("isrendered", "true");
			sprite->SetDoubleAttribute("width", g_TileMap.backgroundObjects[i]->width / g_TileMap.tileWidth);
			sprite->SetDoubleAttribute("height", g_TileMap.backgroundObjects[i]->height / g_TileMap.tileHeight);
			sprite->SetDoubleAttribute("xrel", 0.0);
			sprite->SetDoubleAttribute("yrel", 0.0);

			components->LinkEndChild(sprite);
		}
	}

	// Output collision blocks game objects
	for (unsigned i = 0; i < g_TileMap.collisionObjects.size(); ++i)
	{
		TiXmlElement* gameobject = new TiXmlElement("gameobject");
		gob->LinkEndChild(gameobject);
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
		boxCollider->SetDoubleAttribute("friction", 0.0);
		boxCollider->SetAttribute("issensor", "false");

		rigidbody->LinkEndChild(boxCollider);
	}

	// Output enemy reverse sensors
	for (unsigned i = 0; i < g_TileMap.enemyReverse.size(); ++i)
	{
		TiXmlElement* gameobject = new TiXmlElement("gameobject");
		gob->LinkEndChild(gameobject);
		gameobject->SetAttribute("type", "LevelObject");
		gameobject->SetAttribute("name", "enemyReverse");

		double cenX = ((g_TileMap.enemyReverse[i]->x + (g_TileMap.enemyReverse[i]->width * .5)) / g_TileMap.tileWidth);
		double cenY = ((mapHeight - g_TileMap.enemyReverse[i]->y) - (g_TileMap.enemyReverse[i]->height * .5)) / g_TileMap.tileHeight;

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
		boxCollider->SetAttribute("name", g_TileMap.enemyReverse[i]->name.c_str());
		boxCollider->SetDoubleAttribute("width", g_TileMap.enemyReverse[i]->width / g_TileMap.tileWidth);
		boxCollider->SetDoubleAttribute("height", g_TileMap.enemyReverse[i]->height / g_TileMap.tileHeight);
		boxCollider->SetDoubleAttribute("xrel", 0.0);
		boxCollider->SetDoubleAttribute("yrel", 0.0);
		boxCollider->SetDoubleAttribute("angle", 0.0);
		boxCollider->SetDoubleAttribute("density", 1.0);
		boxCollider->SetDoubleAttribute("friction", 0.0);
		boxCollider->SetAttribute("issensor", "true");

		rigidbody->LinkEndChild(boxCollider);
	}

	// Output enemies
	for (unsigned i = 0; i < g_TileMap.enemies.size(); ++i)
	{
		TiXmlElement* gameobject = new TiXmlElement("gameobject");
		gob->LinkEndChild(gameobject);
		gameobject->SetAttribute("type", g_TileMap.enemies[i]->type.c_str());
		gameobject->SetAttribute("name", g_TileMap.enemies[i]->name.c_str());
		gameobject->SetDoubleAttribute("walkacceleration", .1);
		gameobject->SetDoubleAttribute("maxwalkspeed", 1.2);

		TiXmlElement* transform = new TiXmlElement("transform");
		transform->SetDoubleAttribute("x", g_TileMap.enemies[i]->x / g_TileMap.tileWidth);
		transform->SetDoubleAttribute("y", g_TileMap.height - (g_TileMap.enemies[i]->y / g_TileMap.tileHeight));
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
		rigidbody->SetAttribute("bodytype", "dynamic");
		rigidbody->SetAttribute("canrotate", "false");
		components->LinkEndChild(rigidbody);

		TiXmlElement* enemyBoxCollider = new TiXmlElement("boxcollider");
		enemyBoxCollider->SetAttribute("type", "box");
		enemyBoxCollider->SetAttribute("name", "enemy");
		enemyBoxCollider->SetDoubleAttribute("width", .8);
		enemyBoxCollider->SetDoubleAttribute("height", 1.35);
		enemyBoxCollider->SetDoubleAttribute("xrel", 0.0);
		enemyBoxCollider->SetDoubleAttribute("yrel", 0.0);
		enemyBoxCollider->SetDoubleAttribute("angle", 0.0);
		enemyBoxCollider->SetDoubleAttribute("density", 1.0);
		enemyBoxCollider->SetDoubleAttribute("friction", 0.0);
		enemyBoxCollider->SetAttribute("issensor", "false");
		rigidbody->LinkEndChild(enemyBoxCollider);

		TiXmlElement* attackBoxCollider = new TiXmlElement("boxcollider");
		attackBoxCollider->SetAttribute("type", "box");
		attackBoxCollider->SetAttribute("name", "attack");
		attackBoxCollider->SetDoubleAttribute("width", 2.0);
		attackBoxCollider->SetDoubleAttribute("height", 1.5);
		attackBoxCollider->SetDoubleAttribute("xrel", 0.0);
		attackBoxCollider->SetDoubleAttribute("yrel", 0.0);
		attackBoxCollider->SetDoubleAttribute("angle", 0.0);
		attackBoxCollider->SetDoubleAttribute("density", 1.0);
		attackBoxCollider->SetDoubleAttribute("friction", 0.0);
		attackBoxCollider->SetAttribute("issensor", "true");
		rigidbody->LinkEndChild(attackBoxCollider);

		TiXmlElement* animator = new TiXmlElement("animator");
		animator->SetAttribute("type", "animator");
		animator->SetAttribute("startinganimation", 0);
		components->LinkEndChild(animator);

		TiXmlElement* animation = new TiXmlElement("animation");
		animation->SetAttribute("name", "NAME_OF_ANIMATION");
		animation->SetDoubleAttribute("frameinterval", .15);
		animation->SetAttribute("islooping", "true");
		animator->LinkEndChild(animation);

		TiXmlElement* sprite = new TiXmlElement("sprite");
		animation->LinkEndChild(sprite);
	}

	xmlDoc.SaveFile(gobFilename.c_str());
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
