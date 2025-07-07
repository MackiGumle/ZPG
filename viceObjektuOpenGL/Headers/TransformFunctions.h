#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <functional>
#include <cmath>
#include <chrono>
#include <random>


glm::vec3 timeBasedScale();

glm::vec3 sineWaveTranslation();

glm::vec3 sineWaveTranslationRandom(float offset);

float backAndForthRotation();