// Author: SIS0049 - Oliver Siskan
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
	void createTestTriangle(std::vector<std::shared_ptr<Scene>>& Scenes, ShaderManager& shaderManager, ModelManager& modelManager);
	void create4Balls(std::vector<std::shared_ptr<Scene>>& Scenes, ShaderManager& shaderManager, ModelManager& modelManager, TextureManager& textureManager);
	void createForrest(std::vector<std::shared_ptr<Scene>>& Scenes, ShaderManager& shaderManager, ModelManager& modelManager, TextureManager& textureManager);

};

