#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

#include "Peasant.h"
#include "Variables.h"
#include "SaveManager.h"


class Day
{
public:
	static unsigned int getEnabledDays() { return days_enabled; }
	static void setEnabledDays(const unsigned int& enabled_days ) { days_enabled = enabled_days; }

private:


	static vector<StructDay> days;
	static unsigned int days_enabled;
};
vector<StructDay> Day::days = {};
unsigned int Day::days_enabled = -1;