#pragma once
#include <vector>
#include <memory>
#include "Model.h"


class ModelManager {
public:
    ModelManager();
    ~ModelManager();

    void loadModel(const float points[], size_t numVertices, size_t stride, std::string name);
    bool loadModel(const std::string& path, const std::string& name);
    void renderModel();
    void renderModels();

private:
    std::vector<std::unique_ptr<Model>> m_models;
    size_t m_index = 0;
};
