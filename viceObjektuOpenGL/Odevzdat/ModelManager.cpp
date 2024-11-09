#include "ModelManager.h"

ModelManager::ModelManager() {

}

ModelManager::~ModelManager() {

}

void ModelManager::loadModel(const float points[], size_t numBytes, size_t stride, std::string name) {
	//models.push_back(std::make_unique<Model>(points, numVertices, stride, name));
	if(models.find(name) != models.end()) {
		std::cout << "[x] Model with name " + name + " already exists\n";
		//throw std::runtime_error("Model with name " + name + " already exists");
		return;
	}

	models[name] = std::make_shared<Model>(points, numBytes, stride, name);
	std::cout << "[i] Loaded model ->\t" << "name: " << name << "\tnumVertices: " << models.at(name)->getNumVertices() << "\n";
}

std::shared_ptr<Model> ModelManager::getModel(const std::string& name) const {
	if(models.find(name) == models.end()) {
		std::cerr << "[x] Model with name " + name + " not found\n";
		throw std::runtime_error("Model with name " + name + " not found");
	}

	return models.at(name);
}
