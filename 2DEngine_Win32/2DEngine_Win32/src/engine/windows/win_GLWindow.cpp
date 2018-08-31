//
//  2DEngine
//  win_GLWindow.cpp
//  Eric Fleming
//  4/2/2018
//

#include "../renderer/lilGLWindow.h"
#include "../utilities/lilFileIO.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"

laGLWindow* laGLWindow::sInstance = 0;

laGLWindow* laGLWindow::Instance()
{
	if (!sInstance)
		sInstance = new laGLWindow();

	return sInstance;
}

bool laGLWindow::Initialize()
{
	if (!LoadData())
	{
		SDL_Log("ERROR: Failed To Load Window Data, %s %d", __FILE__, __LINE__);
		return false;
	}

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("ERROR: %s %s %d", SDL_GetError(), __FILE__, __LINE__);
		return false;
	}

	int flags = 0;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (mFullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
		SDL_DisplayMode dm;
		if (SDL_GetDisplayMode(0, 0, &dm))
		{
			SDL_Log("ERROR: %s %s %d", SDL_GetError(), __FILE__, __LINE__);
			mFullscreen = false;
		}

		else
		{
			mWidth = dm.w;
			mHeight = dm.h;
		}
	}

	if (!mFullscreen)
	{
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	}

	mWindow = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, flags);
	if (!mWindow)
	{
		SDL_Log("ERROR: %s %s %d", SDL_GetError(), __FILE__, __LINE__);
		SDL_Quit();
		return false;
	}

	mGLContext = SDL_GL_CreateContext(mWindow);
	SDL_GL_SetSwapInterval(mVSync);

	return true;
}

void laGLWindow::Shutdown()
{
	SDL_GL_DeleteContext(mGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void laGLWindow::SwapBuffers()
{
	SDL_GL_SwapWindow(mWindow);
}

void laGLWindow::ShowCursor(bool value)
{
	if (value)
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);
}

bool laGLWindow::LoadData()
{
	char* xmlFile = lilFileIO::ReadFile("data/WindowParams.xml", "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* rootElement = xmlDoc.RootElement();
	if (!rootElement)
		return false;

	TiXmlElement* widthElement = rootElement->FirstChildElement("width");
	mWidth = widthElement->FirstAttribute()->IntValue();

	TiXmlElement* heightElement = rootElement->FirstChildElement("height");
	mHeight = heightElement->FirstAttribute()->IntValue();

	TiXmlElement* fullscreenElement = rootElement->FirstChildElement("fullscreen");
	std::string isFullscreen = fullscreenElement->FirstAttribute()->Value();
	if (isFullscreen.compare("true") == 0)
		mFullscreen = true;
	else
		mFullscreen = false;

	TiXmlElement* titleElement = rootElement->FirstChildElement("title");
	mTitle = titleElement->FirstAttribute()->Value();

	TiXmlElement* vsyncElement = rootElement->FirstChildElement("vsync");
	std::string isVSync = vsyncElement->FirstAttribute()->Value();
	if (isVSync.compare("true") == 0)
		mVSync = 1;
	else
		mVSync = 0;

	return true;
}

