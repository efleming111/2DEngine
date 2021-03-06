//
//  2DEngine
//  ERenderable.cpp
//  Eric Fleming
//  6/11/2018
//

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lilRenderable.h"
#include "lilGLRenderer.h"
#include "lilGLWindow.h"

void lilRenderable::Create(TiXmlElement* element, float pixelsPerGameUnit)
{
	mPixelsPerGameUnit = pixelsPerGameUnit;

	name = element->Attribute("name");

	double texLeft, texRight, texTop, texBottom;

	element->Attribute("texleft", &texLeft);
	element->Attribute("texright", &texRight);
	element->Attribute("textop", &texTop);
	element->Attribute("texbottom", &texBottom);

	std::string pivotPoint = element->Attribute("pivotpoint");

	float* vertexData = 0;
	if (pivotPoint.compare("center") == 0)
	{
		float halfWidth = mPixelsPerGameUnit * .5f;
		float halfHeight = mPixelsPerGameUnit * .5f;

		float vertices[20] = {
			-halfWidth, -halfHeight, 0.0f,		(float)texLeft, (float)texTop,
			halfWidth, -halfHeight, 0.0f,		(float)texRight, (float)texTop,
			halfWidth, halfHeight, 0.0f,		(float)texRight, (float)texBottom,
			-halfWidth, halfHeight, 0.0f,		(float)texLeft, (float)texBottom
		};
		vertexData = &vertices[0];
	}

	else if (pivotPoint.compare("leftcenter") == 0)
	{
		float halfHeight = mPixelsPerGameUnit * .5f;

		float vertices[20] = {
			0.0, -halfHeight, 0.0f,		                (float)texLeft, (float)texTop,
			mPixelsPerGameUnit, -halfHeight, 0.0f,		(float)texRight, (float)texTop,
			mPixelsPerGameUnit, halfHeight, 0.0f,		(float)texRight, (float)texBottom,
			0.0, halfHeight, 0.0f,		                (float)texLeft, (float)texBottom
		};
		vertexData = &vertices[0];
	}

	unsigned short indices[6] = { 0, 1, 3, 3, 1, 2 };

	mMesh = lilGLRenderer->AddMesh(vertexData, 20, indices, 6);

	std::string textureFile = element->Attribute("texturefile");
	mTextureID = lilGLRenderer->AddTexture(textureFile.c_str());

	std::string shaderFile = element->Attribute("shaderfile");
	mShader = lilGLRenderer->AddShader(shaderFile.c_str());
}

void lilRenderable::Draw(lilSprite* sprite)
{
	if (sprite->isRendered)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, sprite->transform.position * mPixelsPerGameUnit);
		model = glm::rotate(model, glm::radians(sprite->transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, sprite->transform.scale);

		mShader->SetUniform("model", glm::value_ptr(model));

		glBindTexture(GL_TEXTURE_2D, mTextureID);

		mMesh->Draw();
	}
}

