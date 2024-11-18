#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <cmath>
#include <chrono>

glm::vec3 timeBasedScale() {
	auto now = std::chrono::steady_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

	float minScale = 0.5f;
	float maxScale = 1.5f;
	float frequency = 0.005f;

	float scale = minScale + (maxScale - minScale) * (0.5f * (std::sin(frequency * time) + 1.0f));
	return glm::vec3(scale);
};

glm::vec3 sineWaveTranslation() {
	auto now = std::chrono::steady_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

	float timeInSeconds = time * 0.001f;

	float yAmplitude = 5.0f;
	float yFrequency = 1.0f;

	float yPosition = yAmplitude * std::sin(yFrequency * timeInSeconds);

	float zAmplitude = 10.0f;
	float zFrequency = 0.2f;

	float zPosition = zAmplitude * std::sin(zFrequency * timeInSeconds);

	return glm::vec3(0.0f, yPosition, zPosition);
};

float backAndForthRotation() {
	auto now = std::chrono::steady_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

	float timeInSeconds = time * 0.001f;

	float maxAngle = 45.0f;
	float frequency = 1.0f;

	return maxAngle * std::sin(frequency * timeInSeconds);
};