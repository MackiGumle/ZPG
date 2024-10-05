#pragma once
#include <vector>
#include <memory>
#include "Model.h"


class ModelManager {
public:
    ModelManager();
    ~ModelManager();

    void loadModel(float points[], size_t numVertices, size_t stride, std::string name);
    bool loadModel(const std::string& path, const std::string& name);
    void renderModel();

private:
    std::vector<std::unique_ptr<Model>> m_models;
};
