#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

// Checks for collisions between point and rectangle
// 
// returns "True" if point collides with rectangle
// otherwise returns "False"
bool CollisionPointRect(Vector2f point, FloatRect rect)
{
    if (point.x > rect.getPosition().x && point.x < rect.getPosition().x + rect.getSize().x && point.y > rect.getPosition().y && point.y < rect.getPosition().y + rect.getSize().y)
        return true;
    return false;
}