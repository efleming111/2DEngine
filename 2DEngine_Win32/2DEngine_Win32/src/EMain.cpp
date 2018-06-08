//
//  2DEngine
//  EMain.cpp
//  Eric Fleming
//  4/2/2018
//

//#include "engine\core\ECore.h"

#include <SDL.h>
#include "engine\input\EInput.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "engine\components\subcomponents\ETexture.h"
#include "engine\components\subcomponents\EShader.h"
#include "engine\components\subcomponents\EMeshManager.h"
#include "engine\renderer\EGLWindow.h"

// TODO: Merge mesh texture and shader managers with renderer

int main(int argc, char* argv[])
{
	lilGLWindow->Initialize();
	lilInput->Initialize();

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		SDL_Log("ERROR: Failed To Initialize GLAD Library, %s %d", __FILE__, __LINE__);
		return 1;
	}

	glViewport(0, 0, lilGLWindow->Width(), lilGLWindow->Height());

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.8f, 0.2f, 0.2f, 1.0f);

	float halfWidth = 250.0f;
	float halfHeight = 250.0f;

	float vertexData[20] = {
		-halfWidth, -halfHeight, 0.0f,		0.0f, 0.0f,
		halfWidth, -halfHeight, 0.0f,		1.0f, 0.0f,
		halfWidth, halfHeight, 0.0f,		1.0f, 1.0f,
		-halfWidth, halfHeight, 0.0f,		0.0f, 1.0f
	};

	unsigned short indices[6] = { 0, 1, 3, 3, 1, 2 };

	EMesh mesh;
	mesh.Create(vertexData, 20, indices, 6);

	/*unsigned vao;
	unsigned vbo;
	unsigned ebo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 6, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	ETexture texture;
	texture.Create("data/spritesheets/knight.png");
	EShader shader;
	shader.Create("data/shaders/BasicTextureShader");

	glm::vec3 camPosition(0.0f, 0.0f, 1.0f);
	glm::mat4 view = glm::lookAt(camPosition, camPosition + glm::vec3(0.0f, 0.0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::ortho(lilGLWindow->Width() * -.5f, lilGLWindow->Width() * .5f, lilGLWindow->Height() * -.5f, lilGLWindow->Height() * .5f, 1.0f, -1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	shader.SetUniform("model", glm::value_ptr(model));
	shader.SetUniform("camera", glm::value_ptr(view));
	shader.SetUniform("projection", glm::value_ptr(projection));

	bool running = true;
	while (running)
	{
		lilInput->Update();
#ifdef _WIN32
		if (lilKeyboard->GetKeyDown(KC_ESCAPE))
			running = false;
#endif

#ifdef __ANDROID__
		Finger* fingers = lilTouch->GetTouches();
		for (int i = 0; i < MAX_FINGER_TOUCHES && fingers[i].isTouching; ++i)
		{
			SDL_Log("Start Touch, %s %d", __FILE__, __LINE__);
			if (fingers[i].xNormalized > .75f && fingers[i].yNormalized < .25f)
			{
				running = false;
				break;
			}
		}
#endif

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.SetAsCurrent();
		mesh.Draw();

		lilGLWindow->SwapBuffers();
	}

	lilInput->Shutdown();
	lilGLWindow->Shutdown();

	return 0;


	//// TODO: Original Main Code
	//lilEngine->HandleCommandArgs(argc, argv);

	//if (lilEngine->Initialize())
	//{
	//	lilEngine->Run();
	//	lilEngine->ShutDown();
	//}

	//return 0;
}

