//
//  2DEngine
//  lilGLWindow.h
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
	int Width() const { return mWidth; }

	// Returns height of window
	int Height() const { return mHeight; }

	// Swaps the front and back buffers
	void SwapBuffers();

	// Set weather or not to show mouse cursor
	// @ value - true shows cursor, false  hides cursor
	void ShowCursor(bool value);


private:
	static laGLWindow* sInstance;

	SDL_Window* mWindow;
	SDL_GLContext mGLContext;

	std::string mTitle;
	bool mFullscreen;
	int mWidth;
	int mHeight;

	int mVSync;

private:
	bool LoadData();

	// Only one instance of class and no copying
	laGLWindow() { mWindow = 0; }
	~laGLWindow() {}
	laGLWindow(const laGLWindow& window) {}
	void operator=(const laGLWindow& window) {}
};

