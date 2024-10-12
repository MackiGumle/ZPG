#pragma once
#include <unordered_map>
#include <memory>
#include "Model.h"


class ModelManager {
public:
    ModelManager();
    ~ModelManager();

    void loadModel(const float points[], size_t numVertices, size_t stride, std::string name);
    //bool loadModel(const std::string& path, const std::string& name);
    //void renderModel();
    //void renderModels();
    std::shared_ptr<Model> getModel(const std::string& name) const;

private:
    //std::vector<std::unique_ptr<Model>> m_models;
    std::unordered_map<std::string, std::shared_ptr<Model>> models;
    size_t index = 0;
};
