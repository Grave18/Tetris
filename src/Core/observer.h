#pragma once

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
		auto a = std::remove(
			observers_.begin(),
			observers_.end(), 
			observer);
	}
	
	void notify(void* entity, Events event)
	{
		for(const auto& observer: observers_)
		{
			observer->on_notify(entity, event);
		}
	}
};