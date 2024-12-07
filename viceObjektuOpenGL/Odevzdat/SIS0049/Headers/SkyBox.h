// Author: SIS0049 - Oliver Siskan
#pragma once
#include "DrawableObject.h"


class SkyBox : public DrawableObject
{
public:
	SkyBox(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Texture> texture, Camera* camera);
	~SkyBox();
	void render() override;

	bool moveWithCamera = true;

private:
	Camera* camera = nullptr;
};

