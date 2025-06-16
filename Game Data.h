#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// For changing cursor sprite
enum class MouseState
{
	Arrow,
	Hovering,
	Waiting,
	Cancel
};

Vector2i mouse_pos;
Vector2i mouse_pos_old;
MouseState mouse_state;

bool popup_certificate = false;