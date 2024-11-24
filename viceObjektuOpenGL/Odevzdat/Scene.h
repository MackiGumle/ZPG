#pragma once
#include <unordered_map>
#include <vector>

#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "ObserverPattern.h"
#include "Lights.h"


class Scene
{
public:
	Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms,
		std::vector<std::shared_ptr<DrawableObject>> drawableObjects);

	Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms,
		std::vector<std::shared_ptr<DrawableObject>> drawableObjects,
		std::vector<std::shared_ptr<BaseLight>> PointLights);

	Scene(std::vector<std::shared_ptr<ShaderProgram>>&& shaderPrograms,
		std::vector<std::shared_ptr<DrawableObject>>&& drawableObjects);


	void addDrawableObject(std::shared_ptr<DrawableObject> drawableObject);
	
	Camera* getCamera();
	void rotateCamera(float xoffset, float yoffset);

	void render();

private:
	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms;
	std::vector<std::shared_ptr<DrawableObject>> drawableObjects;
	std::vector<std::shared_ptr<BaseLight>> lights;
	Camera camera;
};

