#include "SceneCreator.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "DrawableObject.h"
#include "TransformFunctions.h"
#include "Scene.h"


void SceneCreator::createTestTriangle(std::vector<std::shared_ptr<Scene>>& Scenes, ShaderManager& shaderManager, ModelManager& modelManager)
{
	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms = {
		shaderManager.getShaderProgram("SC0_Green"),
	};

	std::vector<std::shared_ptr<DrawableObject>> objects = {
		std::make_shared<DrawableObject>(modelManager.getModel("Triangle"), shaderManager.getShaderProgram("SC0_Green")),
	};

	objects[0]->addTransformation(std::make_unique<Translation>(glm::vec3(0, 0, -3)));

	Scenes.push_back(std::make_shared<Scene>(shaderPrograms, objects));
}

void SceneCreator::create4Balls(std::vector<std::shared_ptr<Scene>>& Scenes, ShaderManager& shaderManager, ModelManager& modelManager)
{
	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms = {
		shaderManager.getShaderProgram("SC2_Green"),
		/*shaderManager.getShaderProgram("SC2_LambertLight"),
		shaderManager.getShaderProgram("SC2_PhongLight"),
		shaderManager.getShaderProgram("SC2_BlinnLight"),*/
		shaderManager.getShaderProgram("SC2_multiple"),
	};

	std::vector<std::shared_ptr<BaseLight>> lights = {
		std::make_shared<PointLight>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 1, 0.25f), 1),
		//std::make_shared<PointLight>(glm::vec3(2.0f, 0.0f, -2.0f), glm::vec3(0, 1.0f, 0), 1),
		//std::make_shared<SpotLight>(15.5f, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0, 10, 10), glm::vec3(1,0,1), 1),
	};

	std::vector<std::shared_ptr<DrawableObject>> objects = {
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC2_multiple")),
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC2_Green")),
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC2_multiple")),
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC2_multiple")),
	};


	objects[1]->addTransformation(std::make_unique<Scale>(0.25f));
	objects[0]->addTransformation(std::make_unique<DynamicScale>(timeBasedScale));
	objects[1]->addTransformation(std::make_unique<DynamicTranslation>(sineWaveTranslation));
	objects[1]->addObserver(lights[0].get());
	lights[0]->setObject(objects[1].get());
	

	int i = 0;
	for (auto& object : objects) {
		object->addTransformation(std::make_unique<Translation>(glm::vec3(0, 2, -2.5f)));
		object->addTransformation(std::make_unique<Rotation>(90 * i++, glm::vec3(0, 0, 1)));
	}

	Scenes.push_back(std::make_shared<Scene>(shaderPrograms, objects, lights));
}