//
//  2DEngine
//  EGLWindow.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <string>

#include <SDL.h>

#define lilGLWindow EGLWindow::Instance()

class EGLWindow
{
public:
	// Returns only instance of class
	static EGLWindow* Instance();

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

#ifdef _WIN32
	// Set weather or not to show mouse cursor
	// @ value - true shows cursor, false  hides cursor
	void ShowCursor(bool value);
#endif

private:
	static EGLWindow* s_Instance;

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
	EGLWindow() { m_Window = 0; }
	~EGLWindow() {}
	EGLWindow(const EGLWindow& window) {}
	void operator=(const EGLWindow& window) {}
};

