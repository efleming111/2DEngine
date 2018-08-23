//
//  2DEngine
//  and_GLWindow.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <string>

#include <SDL.h>

#define lilGLWindow laGLWindow::Instance()

class laGLWindow
{
public:
	// Returns only instance of class
	static laGLWindow* Instance();

	// Creates window, returns true on success
	bool Initialize();

	// Shuts down and cleans up window
	void Shutdown();

	// Returns width of window
	int Width() const { return m_Width; }

	// Returns height of window
	int Height() const { return m_Height; }

	// Swaps the front and back buffers
	void SwapBuffers();

	void ShowCursor(bool value) {}

private:
	static laGLWindow* s_Instance;

	SDL_Window* m_Window;
	SDL_GLContext m_GLContext;

	std::string m_Title;
	bool m_Fullscreen;
	int m_Width;
	int m_Height;

	int m_VSync;

private:
	bool LoadData();

	// Only one instance of class and no copying
	laGLWindow() { m_Window = 0; }
	~laGLWindow() {}
	laGLWindow(const laGLWindow& window) {}
	void operator=(const laGLWindow& window) {}
};

