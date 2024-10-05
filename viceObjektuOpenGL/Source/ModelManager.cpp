#include "ModelManager.h"

ModelManager::ModelManager() {

}

ModelManager::~ModelManager() {

}

void ModelManager::loadModel(float points[], size_t numVertices, size_t stride, std::string name) {
	m_models.push_back(std::make_unique<Model>(points, numVertices, stride, name));
}

void ModelManager::renderModel() {
		for(auto& model : m_models) {
		model->render();
	}
}