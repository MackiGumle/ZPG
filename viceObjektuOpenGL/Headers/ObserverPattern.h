#pragma once
#include <list>
#include <glm/glm.hpp>
#include <unordered_map>

class ICameraObserver {
public:
	virtual void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;
	virtual void update(glm::mat4 modelMatrix) = 0;
};

class IApplicationObserver {
public:
	virtual void update(std::unordered_map<int, bool>& keys) = 0;
};



class ICameraSubject {
public:
	virtual void addObserver(ICameraObserver* observer) = 0;
	virtual void removeObserver(ICameraObserver* observer) = 0;
	virtual void notifyObservers() = 0;
};

class IApplicationSubject {
public:
	virtual void addObserver(IApplicationObserver* observer) = 0;
	virtual void removeObserver(IApplicationObserver* observer) = 0;
	virtual void notifyObservers() = 0;
};