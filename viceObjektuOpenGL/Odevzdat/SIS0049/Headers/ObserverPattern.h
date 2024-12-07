// Author: SIS0049 - Oliver Siskan
#pragma once
#include <list>

class Observer;
class Subject;

class Observer {
public:
	virtual void update() = 0;
};

class Subject {
public:
	virtual ~Subject() = default;

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
protected:
	std::list<Observer*> observers;
};
