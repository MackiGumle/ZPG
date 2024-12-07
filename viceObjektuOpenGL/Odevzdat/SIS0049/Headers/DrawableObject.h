// Author: SIS0049 - Oliver Siskan
#pragma once
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Material.h"
#include "ObserverPattern.h"
#include "Texture.h"
#include "Model.h"


// Subject of Light
class DrawableObject : public Subject
{
public:
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material);
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material, std::shared_ptr<Texture> texture);
	~DrawableObject();

	void addTransformation(std::unique_ptr<Transformation> transformation, bool continuous = false);
	void clearTransformations() { transformationComposite.clear(); }
	void clearTranslation() { transformationComposite.clearTranslation(); }
	virtual void render();

	glm::vec3 getPosition() const { return position; }

	bool selectable = true;

protected:
	bool firstRender = true;
	std::shared_ptr<Model> model;
	std::shared_ptr<ShaderProgram> shaderProgram;
	
	TransformationComposite transformationComposite;

	glm::vec3 position;
	
	Material material;
	std::shared_ptr<Texture> texture;
};
