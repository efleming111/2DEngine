//
//  2DEngine
//  and_GLWindow.cpp
//  Eric Fleming
//  4/2/2018
//

#include "../renderer/lilGLWindow.h"
#include "../utilities/lilFileIO.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"

laGLWindow* laGLWindow::s_Instance = 0;

laGLWindow* laGLWindow::Instance()
{
	if (!s_Instance)
		s_Instance = new laGLWindow();

	return s_Instance;
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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_DisplayMode dm;
	if (SDL_GetDisplayMode(0, 0, &dm))
	{
		SDL_Log("ERROR: %s %s %d", SDL_GetError(), __FILE__, __LINE__);
		return false;
	}

	m_Width = dm.w;
	m_Height = dm.h;

	m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, flags);
	if (!m_Window)
	{
		SDL_Log("ERROR: %s %s %d", SDL_GetError(), __FILE__, __LINE__);
		SDL_Quit();
		return false;
	}

	m_GLContext = SDL_GL_CreateContext(m_Window);
	SDL_GL_SetSwapInterval(m_VSync);

	return true;
}

void laGLWindow::Shutdown()
{
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void laGLWindow::SwapBuffers()
{
	SDL_GL_SwapWindow(m_Window);
}

void laGLWindow::ShowCursor(bool value)
{
	// Empty
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
	m_Width = widthElement->FirstAttribute()->IntValue();

	TiXmlElement* heightElement = rootElement->FirstChildElement("height");
	m_Height = heightElement->FirstAttribute()->IntValue();

	TiXmlElement* fullscreenElement = rootElement->FirstChildElement("fullscreen");
	std::string isFullscreen = fullscreenElement->FirstAttribute()->Value();
	if (isFullscreen.compare("true") == 0)
		m_Fullscreen = true;
	else
		m_Fullscreen = false;

	TiXmlElement* titleElement = rootElement->FirstChildElement("title");
	m_Title = titleElement->FirstAttribute()->Value();

	TiXmlElement* vsyncElement = rootElement->FirstChildElement("vsync");
	std::string isVSync = vsyncElement->FirstAttribute()->Value();
	if (isVSync.compare("true") == 0)
		m_VSync = 1;
	else
		m_VSync = 0;

	return true;
}
