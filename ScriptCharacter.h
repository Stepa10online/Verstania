#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

#include "DialogText.h"
#include "Peasant.h"

class ScriptCharacter
{
public:
	void setQueueTime(int queue_time) { this->queue_time = queue_time; }
	
	int getQueueTime() { return this->queue_time; }

	Peasant& GetPeasant() { return P; }
private:
	int queue_time = 0;
	Peasant P;
};