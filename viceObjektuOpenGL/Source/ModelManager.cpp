#include "ModelManager.h"

ModelManager::ModelManager() {

}

ModelManager::~ModelManager() {

}

void ModelManager::loadModel(const float points[], size_t numVertices, size_t stride, std::string name) {
	m_models.push_back(std::make_unique<Model>(points, numVertices, stride, name));
}

void ModelManager::renderModel() {
		m_models[m_index]->render();
		++m_index;
		m_index %= m_models.size();
}

void ModelManager::renderModels() {
	for(auto& model : m_models) {
		model->render();
	}
}