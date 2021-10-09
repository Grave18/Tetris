#pragma once

#include <iostream>
#include <vector>

enum class Events
{
	PLAYER_FELL_EVENT
};

class Observer
{
public:
	virtual ~Observer() = default;

	virtual void on_notify(void* entity, Events event) = 0;
};

class Subject
{
private:
	std::vector<Observer*> observers_ {};

public:
	void add_observer(Observer* observer)
	{
		observers_.push_back(observer);
	}

	void remove_observer(Observer* observer)
	{
		// Save new end and remove elements from vector
		const auto new_end = std::remove(
			observers_.begin(),
			observers_.end(), 
			observer);
		// Finally erase unused tail from vector
		observers_.erase(new_end, observers_.end());
	}
	
	void notify(void* entity, Events event)
	{
		for(const auto& observer: observers_)
		{
			observer->on_notify(entity, event);
		}
	}
};