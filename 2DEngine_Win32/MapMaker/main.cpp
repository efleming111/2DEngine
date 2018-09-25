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
	std::string name;

	int width;
	int height;
	int tileWidth;
	int tileHeight;

	int red;
	int green;
	int blue;

	int playerStartX;
	int playerStartY;

	std::vector<std::string> nextLevelFilenames;
	std::vector<std::string> goFilenames;

	std::vector<int> foregroundIds;
	std::vector<int> backgroundIds;
	std::vector<int> enemyIds;
	std::vector<int> objectIds;
	std::vector<int> objectAltIds;

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

	for (unsigned i = 0; i < gTileMap.goFilenames.size(); ++i)
	{
		TiXmlElement* goFilename = new TiXmlElement("gofilename");
		goFilename->SetAttribute("name", gTileMap.goFilenames[i].c_str());
		level->LinkEndChild(goFilename);
	}

	levelDoc.SaveFile(levelFilename.c_str());

	// Create level game object
	std::string goFilename = filename;
	goFilename += ".go";

	TiXmlDocument goDoc;
	TiXmlDeclaration* goDec = new TiXmlDeclaration("1.0", "UTF-8", "");
	goDoc.LinkEndChild(goDec);

	// Set up root element for scene game object file
	TiXmlElement* go = new TiXmlElement("go");
	goDoc.LinkEndChild(go);

	// Set up resources
	TiXmlElement* resources = new TiXmlElement("resources");
	go->LinkEndChild(resources);

	// Create list of renderable items
	std::map<int, bool> renderables;
	for (unsigned i = 0; i < gTileMap.backgroundIds.size(); ++i)
		if (gTileMap.backgroundIds[i] >= 0)
			renderables[gTileMap.backgroundIds[i]] = true;

	for (unsigned i = 0; i < gTileMap.enemyIds.size(); ++i)
		if (gTileMap.enemyIds[i] >= 0)
			renderables[gTileMap.enemyIds[i]] = true;

	for (unsigned i = 0; i < gTileMap.objectIds.size(); ++i)
		if (gTileMap.objectIds[i] >= 0)
			renderables[gTileMap.objectIds[i]] = true;

	for (unsigned i = 0; i < gTileMap.objectAltIds.size(); ++i)
		if (gTileMap.objectAltIds[i] >= 0)
			renderables[gTileMap.objectAltIds[i]] = true;

	for (unsigned i = 0; i < gTileMap.foregroundIds.size(); ++i)
		if (gTileMap.foregroundIds[i] >= 0)
			renderables[gTileMap.foregroundIds[i]] = true;

	// Add alt objects to renderables
	renderables[162] = true;// CoinBoxHit
	renderables[160] = true;// ItemBoxHit
	renderables[78] = true;// CoinGold

	// Output renderable resources
	for (std::map<int, bool>::iterator it = renderables.begin(); it != renderables.end(); ++it)
	{
		TiXmlElement* renderable = new TiXmlElement("renderable");
		resources->LinkEndChild(renderable);

		renderable->SetAttribute("type", "Renderable");
		renderable->SetAttribute("name", gSprites[it->first]->name.c_str());
		renderable->SetAttribute("pivotpoint", "center");

		renderable->SetDoubleAttribute("texleft", gSprites[it->first]->x / gSpriteSheetWidth);
		renderable->SetDoubleAttribute("texright", (gSprites[it->first]->x + gSprites[it->first]->width) / gSpriteSheetWidth);
		renderable->SetDoubleAttribute("texbottom", gSprites[it->first]->y / gSpriteSheetHeight);
		renderable->SetDoubleAttribute("textop", (gSprites[it->first]->y + gSprites[it->first]->height) / gSpriteSheetHeight);
		std::string texfile = gSprites[it->first]->textureFilename;
		renderable->SetAttribute("texturefile", texfile.c_str());
		renderable->SetAttribute("shaderfile", "data/shaders/BasicTextureShader");
	}

	// Create level controller
	TiXmlElement* lcGameObject = new TiXmlElement("gameobject");
	lcGameObject->SetAttribute("type", "LevelController");
	lcGameObject->SetAttribute("name", gTileMap.name.c_str());
	lcGameObject->SetDoubleAttribute("clearcolorred", (double)gTileMap.red / 255.0);
	lcGameObject->SetDoubleAttribute("clearcolorgreen", (double)gTileMap.green / 255.0);
	lcGameObject->SetDoubleAttribute("clearcolorblue", (double)gTileMap.blue / 255.0);
	go->LinkEndChild(lcGameObject);

	TiXmlElement* levels = new TiXmlElement("levels");
	for (unsigned i = 0; i < gTileMap.nextLevelFilenames.size(); ++i)
	{
		std::ostringstream optionTag;
		optionTag << "option" << (i + 1);
		levels->SetAttribute(optionTag.str().c_str(), gTileMap.nextLevelFilenames[i].c_str());
	}
	lcGameObject->LinkEndChild(levels);

	TiXmlElement* playerstart = new TiXmlElement("playerstart");
	playerstart->SetDoubleAttribute("x", gTileMap.playerStartX);
	playerstart->SetDoubleAttribute("y", gTileMap.playerStartY);
	lcGameObject->LinkEndChild(playerstart);

	TiXmlElement* trans = new TiXmlElement("transform");
	trans->SetDoubleAttribute("x", 0);
	trans->SetDoubleAttribute("y", 0);
	trans->SetDoubleAttribute("z", 0);
	trans->SetDoubleAttribute("rotation", 0.0);
	trans->SetDoubleAttribute("sx", 1);
	trans->SetDoubleAttribute("sy", 1);
	trans->SetDoubleAttribute("sz", 1);
	lcGameObject->LinkEndChild(trans);

	TiXmlElement* sceneComponents = new TiXmlElement("components");
	lcGameObject->LinkEndChild(sceneComponents);

	// Output foreground tiles
	for (unsigned i = 0; i < gTileMap.foregroundIds.size(); ++i)
	{
		if (gTileMap.foregroundIds[i] >= 0)
		{
			TiXmlElement* gameobject = new TiXmlElement("gameobject");
			go->LinkEndChild(gameobject);
			gameobject->SetAttribute("type", "Tile");
			gameobject->SetAttribute("name", "ForegroundTile");

			TiXmlElement* transform = new TiXmlElement("transform");
			transform->SetDoubleAttribute("x", (double)((int)i % gTileMap.width) + .5);
			transform->SetDoubleAttribute("y", (double)(gTileMap.height - ((int)i / gTileMap.width)) - .5);
			transform->SetDoubleAttribute("z", 0.0);
			transform->SetDoubleAttribute("rotation", 0.0);
			transform->SetDoubleAttribute("sx", 1.0);
			transform->SetDoubleAttribute("sy", 1.0);
			transform->SetDoubleAttribute("sz", 1.0);
			gameobject->LinkEndChild(transform);

			TiXmlElement* components = new TiXmlElement("components");
			gameobject->LinkEndChild(components);

			TiXmlElement* sprite = new TiXmlElement("sprite");
			sprite->SetAttribute("type", "Sprite");
			sprite->SetAttribute("name", "Tile");
			sprite->SetAttribute("renderablename", gSprites[gTileMap.foregroundIds[i]]->name.c_str());
			sprite->SetAttribute("renderorder", 3);
			sprite->SetAttribute("isrendered", "true");
			sprite->SetDoubleAttribute("width", 1.0);
			sprite->SetDoubleAttribute("height", 1.0);
			sprite->SetDoubleAttribute("xrel", 0.0);
			sprite->SetDoubleAttribute("yrel", 0.0);

			components->LinkEndChild(sprite);
		}

	}

	// Output object tiles
	for (unsigned i = 0; i < gTileMap.objectIds.size(); ++i)
	{
		if (gTileMap.objectIds[i] >= 0)
		{
			TiXmlElement* gameobject = new TiXmlElement("gameobject");
			go->LinkEndChild(gameobject);
			gameobject->SetAttribute("type", "Tile");
			gameobject->SetAttribute("name", gSprites[gTileMap.objectIds[i]]->name.c_str());

			TiXmlElement* transform = new TiXmlElement("transform");
			transform->SetDoubleAttribute("x", (double)((int)i % gTileMap.width) + .5);
			transform->SetDoubleAttribute("y", (double)(gTileMap.height - ((int)i / gTileMap.width)) - .5);
			transform->SetDoubleAttribute("z", 0.0);
			transform->SetDoubleAttribute("rotation", 0.0);
			transform->SetDoubleAttribute("sx", 1.0);
			transform->SetDoubleAttribute("sy", 1.0);
			transform->SetDoubleAttribute("sz", 1.0);
			gameobject->LinkEndChild(transform);

			TiXmlElement* components = new TiXmlElement("components");
			gameobject->LinkEndChild(components);

			TiXmlElement* sprite = new TiXmlElement("sprite");
			sprite->SetAttribute("type", "Sprite");
			sprite->SetAttribute("name", gSprites[gTileMap.objectIds[i]]->name.c_str());
			sprite->SetAttribute("renderablename", gSprites[gTileMap.objectIds[i]]->name.c_str());
			sprite->SetAttribute("renderorder", 3);
			sprite->SetAttribute("isrendered", "true");
			sprite->SetDoubleAttribute("width", 1.0);
			sprite->SetDoubleAttribute("height", 1.0);
			sprite->SetDoubleAttribute("xrel", 0.0);
			sprite->SetDoubleAttribute("yrel", 0.0);

			components->LinkEndChild(sprite);

			if (gSprites[gTileMap.objectIds[i]]->name.compare("CoinBox") == 0)
			{
				TiXmlElement* AltSprite = new TiXmlElement("sprite");
				AltSprite->SetAttribute("type", "Sprite");
				AltSprite->SetAttribute("name", gSprites[gTileMap.objectIds[i] + 30]->name.c_str());
				AltSprite->SetAttribute("renderablename", gSprites[gTileMap.objectIds[i] + 30]->name.c_str());
				AltSprite->SetAttribute("renderorder", 3);
				AltSprite->SetAttribute("isrendered", "false");
				AltSprite->SetDoubleAttribute("width", 1.0);
				AltSprite->SetDoubleAttribute("height", 1.0);
				AltSprite->SetDoubleAttribute("xrel", 0.0);
				AltSprite->SetDoubleAttribute("yrel", 0.0);

				components->LinkEndChild(AltSprite);

				TiXmlElement* CoinSprite = new TiXmlElement("sprite");
				CoinSprite->SetAttribute("type", "Sprite");
				CoinSprite->SetAttribute("name", "CoinGold");
				CoinSprite->SetAttribute("renderablename", "CoinGold");
				CoinSprite->SetAttribute("renderorder", 2);
				CoinSprite->SetAttribute("isrendered", "false");
				CoinSprite->SetDoubleAttribute("width", 1.0);
				CoinSprite->SetDoubleAttribute("height", 1.0);
				CoinSprite->SetDoubleAttribute("xrel", 0.0);
				CoinSprite->SetDoubleAttribute("yrel", 0.0);

				components->LinkEndChild(CoinSprite);
			}

			if (gSprites[gTileMap.objectIds[i]]->name.compare("ItemBox") == 0)
			{
				TiXmlElement* AltSprite = new TiXmlElement("sprite");
				AltSprite->SetAttribute("type", "Sprite");
				AltSprite->SetAttribute("name", gSprites[gTileMap.objectIds[i] + 30]->name.c_str());
				AltSprite->SetAttribute("renderablename", gSprites[gTileMap.objectIds[i] + 30]->name.c_str());
				AltSprite->SetAttribute("renderorder", 3);
				AltSprite->SetAttribute("isrendered", "false");
				AltSprite->SetDoubleAttribute("width", 1.0);
				AltSprite->SetDoubleAttribute("height", 1.0);
				AltSprite->SetDoubleAttribute("xrel", 0.0);
				AltSprite->SetDoubleAttribute("yrel", 0.0);

				components->LinkEndChild(AltSprite);

				TiXmlElement* CoinSprite = new TiXmlElement("sprite");
				CoinSprite->SetAttribute("type", "Sprite");
				CoinSprite->SetAttribute("name", gSprites[gTileMap.objectAltIds[i]]->name.c_str());
				CoinSprite->SetAttribute("renderablename", gSprites[gTileMap.objectAltIds[i]]->name.c_str());
				CoinSprite->SetAttribute("renderorder", 2);
				CoinSprite->SetAttribute("isrendered", "false");
				CoinSprite->SetDoubleAttribute("width", 1.0);
				CoinSprite->SetDoubleAttribute("height", 1.0);
				CoinSprite->SetDoubleAttribute("xrel", 0.0);
				CoinSprite->SetDoubleAttribute("yrel", 0.0);

				components->LinkEndChild(CoinSprite);
			}

			TiXmlElement* rigidbody = new TiXmlElement("rigidbody");
			rigidbody->SetAttribute("type", "Rigidbody");
			rigidbody->SetAttribute("bodytype", "static");
			rigidbody->SetAttribute("canrotate", "false");
			components->LinkEndChild(rigidbody);

			TiXmlElement* boxCollider = new TiXmlElement("boxcollider");
			boxCollider->SetAttribute("type", "Box");
			boxCollider->SetAttribute("name", gSprites[gTileMap.objectIds[i]]->name.c_str());
			boxCollider->SetDoubleAttribute("width", 1.0);
			boxCollider->SetDoubleAttribute("height", 1.0);
			boxCollider->SetDoubleAttribute("xrel", 0.0);
			boxCollider->SetDoubleAttribute("yrel", 0.0);
			boxCollider->SetDoubleAttribute("angle", 0.0);
			boxCollider->SetDoubleAttribute("density", 1.0);
			boxCollider->SetDoubleAttribute("friction", 0.0);
			boxCollider->SetAttribute("issensor", "false");

			rigidbody->LinkEndChild(boxCollider);

			if (gSprites[gTileMap.objectIds[i]]->name.compare("ItemBox") == 0)
			{
				TiXmlElement* boxItemCollider = new TiXmlElement("boxcollider");
				boxItemCollider->SetAttribute("type", "Box");
				boxItemCollider->SetAttribute("name", gSprites[gTileMap.objectIds[i]]->name.c_str());
				boxItemCollider->SetDoubleAttribute("width", 1.0);
				boxItemCollider->SetDoubleAttribute("height", 1.0);
				boxItemCollider->SetDoubleAttribute("xrel", 0.0);
				boxItemCollider->SetDoubleAttribute("yrel", 1.0);
				boxItemCollider->SetDoubleAttribute("angle", 0.0);
				boxItemCollider->SetDoubleAttribute("density", 1.0);
				boxItemCollider->SetDoubleAttribute("friction", 0.0);
				boxItemCollider->SetAttribute("issensor", "true");

				rigidbody->LinkEndChild(boxItemCollider);
			}
		}

	}

	// Output background tiles
	for (unsigned i = 0; i < gTileMap.backgroundIds.size(); ++i)
	{
		if (gTileMap.backgroundIds[i] >= 0)
		{
			TiXmlElement* gameobject = new TiXmlElement("gameobject");
			go->LinkEndChild(gameobject);
			gameobject->SetAttribute("type", "Tile");
			gameobject->SetAttribute("name", "BackgroundTile");

			TiXmlElement* transform = new TiXmlElement("transform");
			transform->SetDoubleAttribute("x", (double)((int)i % gTileMap.width) + .5);
			transform->SetDoubleAttribute("y", (double)(gTileMap.height - ((int)i / gTileMap.width)) - .5);
			transform->SetDoubleAttribute("z", 0.0);
			transform->SetDoubleAttribute("rotation", 0.0);
			transform->SetDoubleAttribute("sx", 1.0);
			transform->SetDoubleAttribute("sy", 1.0);
			transform->SetDoubleAttribute("sz", 1.0);
			gameobject->LinkEndChild(transform);

			TiXmlElement* components = new TiXmlElement("components");
			gameobject->LinkEndChild(components);

			TiXmlElement* sprite = new TiXmlElement("sprite");
			sprite->SetAttribute("type", "Sprite");
			sprite->SetAttribute("name", "Tile");
			sprite->SetAttribute("renderablename", gSprites[gTileMap.backgroundIds[i]]->name.c_str());
			sprite->SetAttribute("renderorder", 2);
			sprite->SetAttribute("isrendered", "true");
			sprite->SetDoubleAttribute("width", 1.0);
			sprite->SetDoubleAttribute("height", 1.0);
			sprite->SetDoubleAttribute("xrel", 0.0);
			sprite->SetDoubleAttribute("yrel", 0.0);

			components->LinkEndChild(sprite);
		}

	}

	// Output level collision game objects
	double mapHeight = gTileMap.height * gTileMap.tileHeight;
	for (unsigned i = 0; i < gTileMap.collisionObjects.size(); ++i)
	{
		TiXmlElement* gameobject = new TiXmlElement("gameobject");
		go->LinkEndChild(gameobject);
		gameobject->SetAttribute("type", "Tile");
		gameobject->SetAttribute("name", "Collider");

		double cenX = ((gTileMap.collisionObjects[i]->x + (gTileMap.collisionObjects[i]->width * .5)) / gTileMap.tileWidth);
		double cenY = ((mapHeight - gTileMap.collisionObjects[i]->y) - (gTileMap.collisionObjects[i]->height * .5)) / gTileMap.tileHeight;

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
		rigidbody->SetAttribute("type", "Rigidbody");
		rigidbody->SetAttribute("bodytype", "static");
		rigidbody->SetAttribute("canrotate", "false");
		components->LinkEndChild(rigidbody);

		TiXmlElement* boxCollider = new TiXmlElement("boxcollider");
		boxCollider->SetAttribute("type", gTileMap.collisionObjects[i]->type.c_str());
		boxCollider->SetAttribute("name", gTileMap.collisionObjects[i]->name.c_str());
		boxCollider->SetDoubleAttribute("width", gTileMap.collisionObjects[i]->width / gTileMap.tileWidth);
		boxCollider->SetDoubleAttribute("height", gTileMap.collisionObjects[i]->height / gTileMap.tileHeight);
		boxCollider->SetDoubleAttribute("xrel", 0.0);
		boxCollider->SetDoubleAttribute("yrel", 0.0);
		boxCollider->SetDoubleAttribute("angle", 0.0);
		boxCollider->SetDoubleAttribute("density", 1.0);
		boxCollider->SetDoubleAttribute("friction", 0.0);
		boxCollider->SetAttribute("issensor", "false");

		rigidbody->LinkEndChild(boxCollider);
	}

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

	goDoc.SaveFile(goFilename.c_str());
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
	map->Attribute("tilewidth", &gTileMap.tileWidth);
	map->Attribute("tileheight", &gTileMap.tileHeight);

	std::string rgb = map->Attribute("backgroundcolor");
	std::string redStr = rgb.substr(1, 2);
	std::string greenStr = rgb.substr(3, 2);
	std::string blueStr = rgb.substr(5);
	gTileMap.red = std::stoi(redStr, nullptr, 16);
	gTileMap.green = std::stoi(greenStr, nullptr, 16);
	gTileMap.blue = std::stoi(blueStr, nullptr, 16);

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
					gTileMap.goFilenames.push_back(goFilename);
				}

				else if (propertyName.find("levelname") != std::string::npos)
				{
					gTileMap.name = property->Attribute("value");
				}

				else if (propertyName.find("nextlevel") != std::string::npos)
				{
					std::string nextLevelFilename = "data/levels/";
					nextLevelFilename += property->Attribute("value");
					gTileMap.nextLevelFilenames.push_back(nextLevelFilename);
				}

				else if (propertyName.find("playerstartx") != std::string::npos)
				{
					property->Attribute("value", &gTileMap.playerStartX);
				}

				else if (propertyName.find("playerstarty") != std::string::npos)
				{
					property->Attribute("value", &gTileMap.playerStartY);
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

			else if (layerName.compare("TilesObjectAlt") == 0)
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
					gTileMap.objectAltIds.push_back(id);
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





