#pragma once
#include <list>
#include <glm/glm.hpp>
#include <unordered_map>

class Observer;
class Subject;

class Observer {
public:
	virtual void update() = 0;
	void setSubject(Subject* subject) {
		this->subject = subject;
	}

private:
	Subject* subject;
};

class Subject {
public:
	void addObserver(Observer* observer) {
		observers.push_back(observer);
	}

	void removeObserver(Observer* observer) {
		observers.remove(observer);
	}

	void notifyObservers() {
		for (auto observer : observers) {
			observer->update();
		}
	}
private:
	std::list<Observer*> observers;
};



class ICameraObserver {
public:
	virtual void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;
	virtual void update(glm::mat4 modelMatrix) = 0;
};

class ICameraSubject {
public:
	virtual void addObserver(ICameraObserver* observer) = 0;
	virtual void removeObserver(ICameraObserver* observer) = 0;
	virtual void notifyObservers() = 0;
};
