// Author: SIS0049 - Oliver Siskan
#include "SkyBox.h"
#include "ShaderProgram.h"

SkyBox::SkyBox(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Texture> texture, Camera* camera) 
	: DrawableObject(model, shaderProgram, Material(), texture), camera(camera)
{
	selectable = false;
	addTransformation(std::make_unique<DynamicTranslation>(
		[this]() { 
			return this->moveWithCamera ? this->camera->getPosition() : this->getPosition();
		}
	));
}

SkyBox::~SkyBox()
{
}

void SkyBox::render()
{

	//glDepthMask(GL_FALSE);
	DrawableObject::render();
	//glDepthMask(GL_TRUE);

	glClear(GL_DEPTH_BUFFER_BIT);
}
