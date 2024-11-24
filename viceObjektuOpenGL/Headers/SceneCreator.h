#pragma once
#include <vector>
#include <memory>

class ShaderManager;
class ModelManager;
class TextureManager;
class Scene;


class SceneCreator
{
public:
	static void createTestTriangle(std::vector<std::shared_ptr<Scene>>& Scenes, ShaderManager& shaderManager, ModelManager& modelManager);
	static void create4Balls(std::vector<std::shared_ptr<Scene>>& Scenes, ShaderManager& shaderManager, ModelManager& modelManager, TextureManager& textureManager);

};

