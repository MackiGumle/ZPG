// Author: SIS0049 - Oliver Siskan
#pragma once
#include <unordered_map>
#include <vector>
/*
#include "DrawableObject.h"
#include "ShaderProgram.h"*/
#include "Lights.h"
#include "Camera.h"
#include "ObserverPattern.h"


class DrawableObject;
class ShaderProgram;
class SkyBox;

class Scene
{
public:
	Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms,
		std::vector<std::shared_ptr<DrawableObject>> drawableObjects);

	Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms,
		std::vector<std::shared_ptr<DrawableObject>> drawableObjects,
		std::vector<std::shared_ptr<BaseLight>> lights);

	~Scene();

	void addDrawableObject(std::shared_ptr<DrawableObject> drawableObject);
	void addLight(std::shared_ptr<BaseLight> light);
	void addShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);
	void setSkyBox(std::unique_ptr<SkyBox> skybox);
	
	Camera* getCamera();
	void rotateCamera(float xoffset, float yoffset);
	void stopSkyboxMovement();

	void selectObject(int index);
	void setControlPoint(glm::vec3 controlPoint);

	void render();

private:
	struct ControlPoint {
		float t;
		float delta;
		glm::mat4x3 controlPoints;
	};

	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms;
	std::vector<std::shared_ptr<DrawableObject>> drawableObjects;
	std::vector<std::shared_ptr<BaseLight>> lights;
	Camera camera;
	std::unique_ptr<SkyBox> skybox;
	int selectedObject = 0;
	glm::mat4x3 controlPoints;
	std::unordered_map<int, ControlPoint> controlPointsMap;
};
