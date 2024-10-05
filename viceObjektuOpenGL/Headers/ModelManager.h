#pragma once
#include <vector>
#include <memory>
#include "Model.h"


class ModelManager {
public:
    //ModelManager(Application& app);
    ModelManager();
    ~ModelManager();

    void loadModel(const std::string& path, const std::string& name);
    void renderModel(const std::string& name);

private:
    //Application& m_app;
    std::vector<std::unique_ptr<Model>> m_models;
};
