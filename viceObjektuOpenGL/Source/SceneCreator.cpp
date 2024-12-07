#include "SceneCreator.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "DrawableObject.h"
#include "TransformFunctions.h"
#include "Scene.h"
#include "TextureManager.h"
#include "SkyBox.h"

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

void SceneCreator::create4Balls(std::vector<std::shared_ptr<Scene>>& Scenes, ShaderManager& shaderManager, ModelManager& modelManager, TextureManager& textureManager)
{
	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms = {
		shaderManager.getShaderProgram("SC1_LambertLight"),
		shaderManager.getShaderProgram("SC1_PhongLight"),
		shaderManager.getShaderProgram("SC1_BlinnLight"),
		shaderManager.getShaderProgram("SC1_Green"),
	};

	std::vector<std::shared_ptr<DrawableObject>> objects = {
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC1_LambertLight"), Material(), textureManager.getTexture("Default")),
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC1_PhongLight"), Material(), textureManager.getTexture("Default")),
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC1_BlinnLight"), Material(), textureManager.getTexture("Default")),
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC1_Green"), Material(), textureManager.getTexture("Default")),
	};


	int i = 0;
	for (auto& object : objects) {
		object->addTransformation(std::make_unique<Translation>(glm::vec3(0, 2, -2.5f)));
		object->addTransformation(std::make_unique<Rotation>(90 * i++, glm::vec3(0, 0, 1)));
	}

	Scenes.push_back(std::make_shared<Scene>(shaderPrograms, objects));
}

void SceneCreator::createForrest(std::vector<std::shared_ptr<Scene>>& Scenes, ShaderManager& shaderManager, ModelManager& modelManager, TextureManager& textureManager)
{
	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms1 = {
		shaderManager.getShaderProgram("SC2_Green"),
		shaderManager.getShaderProgram("SC2_multiple"),
		shaderManager.getShaderProgram("Skybox"),
	};

	// Random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> pos(-50.0f, 50.0f);
	std::uniform_real_distribution<float> scale(0.7f, 1.7f);

	// Scene 1 Forest
	std::vector<std::shared_ptr<BaseLight>> lights1 = {
		std::make_shared<PointLight>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0.643f, 0), 1),
	};

	std::vector<std::shared_ptr<DrawableObject>> objects1 = {};


	for (size_t i = 0; i < 80; i++)
	{
		objects1.push_back(std::make_shared<DrawableObject>(modelManager.getModel("Tree"),
			shaderManager.getShaderProgram("SC2_multiple"),
			Material(),
			textureManager.getTexture("Default")
		));

		if (i % 2 == 0)
			objects1.push_back(std::make_shared<DrawableObject>(modelManager.getModel("Bushes"),
				shaderManager.getShaderProgram("SC2_multiple")));
	}

	// Create attached lights (fireflies)
	for (size_t i = 0; i < 10; i++)
	{
		lights1.push_back(
			std::make_shared<PointLight>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.50f, 0.80f, 0.10f), 0.50f, 1.0f, 0.8f));
		objects1.push_back(
			std::make_shared<DrawableObject>(modelManager.getModel("Sphere"),
				shaderManager.getShaderProgram("SC2_Green")
				//Material(0.05f, 0.1f, 0.45f, 25, glm::vec3(0.5f, 0.0f, 1.0f))
			)
		);

		objects1.back()->addTransformation(std::make_unique<Scale>(glm::vec3(0.05f)));
		objects1.back()->addTransformation(std::make_unique<Translation>(glm::vec3(0, scale(gen) + 1, 0)));
		objects1.back()->addTransformation(std::make_unique<DynamicTranslation>(
			[i]() { return sineWaveTranslationRandom(i); } 
		));
		objects1.back()->addObserver(lights1[i].get());
		lights1.back()->setObject(objects1.back().get());
	}

	// Displace objects
	size_t i = 0;
	for (auto& object : objects1) {
		object->addTransformation(std::make_unique<Scale>(glm::vec3(scale(gen))));

		float x = pos(gen);
		float z = pos(gen);
		if (i % 4 == 0)
			object->addTransformation(std::make_unique<DynamicRotation>(backAndForthRotation,
				[]() -> glm::vec3 {return glm::vec3(0.0f, 1.0f, 0.0f); }
		));

		object->addTransformation(std::make_unique<Translation>(glm::vec3(x, 0, z)));

		++i;
	}

	// Weird orange sphere
	objects1.push_back(std::make_shared<DrawableObject>(
		modelManager.getModel("Sphere"),
		shaderManager.getShaderProgram("SC2_multiple"),
		Material(1.0f, 1.0f, 0.45f, 0.25f, glm::vec3(1.0f, 0.5f, 0.3f))
	));


	objects1.back()->addTransformation(std::make_unique<DynamicTranslation>(sineWaveTranslation));
	objects1.back()->addObserver(lights1[0].get());
	lights1[0]->setObject(objects1.back().get());

	// Forrest floor
	objects1.push_back(std::make_shared<DrawableObject>(
		modelManager.getModel("TexturedPlain"),
		shaderManager.getShaderProgram("SC2_multiple"),
		//Material(0.5f, 0.1f, 0.45f, 25, glm::vec3(1.0f, 1.0f, 1.0f)),
		Material(1, 1, 1, 25, glm::vec3(1.0f, 1.0f, 1.0f)),
		textureManager.getTexture("Texture")
	));

	objects1.back()->addTransformation(std::make_unique<Scale>(1000));
	objects1.back()->selectable = false;

	objects1.push_back(std::make_shared<DrawableObject>(
		modelManager.getModel("Login"),
		shaderManager.getShaderProgram("SC2_multiple"),
		Material(1, 1, 2, 25, glm::vec3(1.0f, 1.0f, 1.0f)),
		textureManager.getTexture("Texture")
	));

	auto scene = std::make_shared<Scene>(shaderPrograms1, objects1, lights1);
	scene->setSkyBox(
		std::make_unique<SkyBox>(
			modelManager.getModel("SkyCube"),
			shaderManager.getShaderProgram("Skybox"),
			textureManager.getTexture("SkyboxSpace"),
			scene->getCamera()
		)
	);

	Scenes.push_back(scene);
}
