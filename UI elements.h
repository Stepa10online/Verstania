#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
#include "Collision.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

namespace InteractionElements
{
    float outline_thickness = 2.4;
    Color outline_color = Color{ 150,150,150,255 };
    bool enable_button_oultine = true;
    bool enable_text_oultine = true;

    void setEnabeButtonOutline(bool state) { InteractionElements::enable_button_oultine = state; }
    void setEnabeTextOutline(bool state) { InteractionElements::enable_text_oultine = state; }
}


// regular game button
// returns 0 when ignored
// returns 1 when hovered
// returns 2 when pressed
int MyButton(Vector2f pos, Vector2f size, wstring str, RenderWindow& window, Vector2f text_offset = { 0,0 }, Color color = Color::White)
{
    ConvexShape cs(4);
    cs.setPoint(0, pos);
    cs.setPoint(1, pos + Vector2f{ size.x,0 });
    cs.setPoint(2, pos + size);
    cs.setPoint(3, pos + Vector2f{ 0,size.y });
    //cs.move((btn_size.x + interval) * i, 0);
    cs.setFillColor(Color::Black);
    cs.setOutlineThickness(2.4);

    Font font;
    Text text;

    font.loadFromFile("pixelplay.ttf");
    text.setFont(font);
    text.setCharacterSize(50);
    text.setString(str);
    text.setPosition(cs.getPosition() + pos + Vector2f{ 25,0 }+text_offset);
    if (CollisionPointRect(Vector2f{ Mouse::getPosition(window) }, { cs.getPosition() + pos, size }))
    {
        if (InteractionElements::enable_button_oultine)
            cs.setOutlineColor(color);
        if (InteractionElements::enable_text_oultine)
            text.setOutlineColor(color);
        text.setFillColor(color);

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            // pressed
            return 2;
        }
        // hovered
        window.draw(cs);
        window.draw(text);
        return 1;
    }
    else
    {
        if (InteractionElements::enable_button_oultine)
            cs.setOutlineColor({ 150,150,150,255 });
        if (InteractionElements::enable_text_oultine)
            text.setOutlineColor({ 150,150,150,255 });
        text.setFillColor({ 150,150,150,255 });
    }
    window.draw(cs);
    window.draw(text);
    return 0;
}
//
// Image path requirements:
//   image path must contain ".png"
// Image parametrs:
//   IntRect: X, Y, Width, Height
//
int MyImageButton(Vector2f pos, Vector2f size, wstring str, RenderWindow& window, string image_path, IntRect image_par, Vector2f text_offset = { 0,0 })
{
    ConvexShape cs(4);
    cs.setPoint(0, pos);
    cs.setPoint(1, pos + Vector2f{ size.x,0 });
    cs.setPoint(2, pos + size);
    cs.setPoint(3, pos + Vector2f{ 0,size.y });
    //cs.move((btn_size.x + interval) * i, 0);
    cs.setFillColor(Color::White);
    //cs.setOutlineThickness(2.4);
    Texture texture;
    texture.loadFromFile(image_path);
    cs.setTexture(&texture);
    cs.setTextureRect(image_par);
    Font font;
    Text text;

    font.loadFromFile("pixelplay.ttf");
    text.setFont(font);
    text.setCharacterSize(50);
    text.setString(str);
    text.setPosition(cs.getPosition() + pos + Vector2f{ 25,0 } + text_offset);
    if (CollisionPointRect(Vector2f{ Mouse::getPosition(window) }, { cs.getPosition() + pos, size }))
    {
        if (InteractionElements::enable_button_oultine)
            cs.setOutlineColor(Color::White);
        if (InteractionElements::enable_text_oultine)
            text.setOutlineColor(Color::White);
        text.setFillColor(Color::White);

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            // pressed
            return 2;
        }
        // hovered
        window.draw(cs);
        window.draw(text);
        return 1;
    }
    else
    {
        if (InteractionElements::enable_button_oultine)
            cs.setOutlineColor({ 150,150,150,255 });
        if (InteractionElements::enable_text_oultine)
            text.setOutlineColor({ 150,150,150,255 });
        text.setFillColor({ 150,150,150,255 });
    }
    window.draw(cs);
    window.draw(text);
    return 0;
}

void MyText(Vector2f pos, wstring str, RenderWindow& window, float char_size = 25, Color color = Color::White)
{
    Font font;
    font.loadFromFile("pixelplay.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(char_size);
    text.setPosition(pos);
    text.setFillColor(color);
    text.setString(str);
    window.draw(text);
}
void MyText(string font_name, Vector2f pos, wstring str, RenderWindow& window, float char_size = 25, Color color = Color::White)
{
    Font font;
    font.loadFromFile(font_name);
    Text text;
    text.setFont(font);
    text.setCharacterSize(char_size);
    text.setPosition(pos);
    text.setFillColor(color);
    text.setString(str);
    window.draw(text);
}