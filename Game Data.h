#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

enum class MouseState
{
	Arrow,
	Hovering,
	Waiting,
	Cancel
};

Vector2i mouse_pos;
MouseState mouse_state;