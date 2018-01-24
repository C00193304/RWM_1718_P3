#pragma once

/**Used as an interface for the event dispatcher*/
/*Objects wanting to receive events must inherit from this*/

class EventListener
{
public:

	//list of possible events
	//add your own events here
	enum Event 
	{
		STARSCENE,
		LEVEL1,
		LEVEL2,
		LEVEL3,
		LEVEL4,
		ENDSCENE,
		REVERSE,
		PAUSE,
		QUIT,
		QUITEND,
		RIGHT,
		RIGHTR,
		LEFT,
		LEFTR,
		AnyKey,
		SPACE,
		SPACER,
		RESET,
		POWERUP,
		POWERDOWN,
		AMOUNTPARTICLES
	};


	virtual void onEvent(Event)=0;
};

