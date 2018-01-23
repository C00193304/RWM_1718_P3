#pragma once

class EventListener
{
public:

	//list of possible events
	//add your own events here
	enum Event {
		QUIT,
		FUEL
	};


	virtual void onEvent(Event) = 0;
};