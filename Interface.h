#pragma once

// Interface for computer in game

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game Data.h"

using namespace sf;
using namespace std;

namespace Interface
{
	namespace InterfaceData
	{
		Vector2f interface_pos = {0,0};
		Vector2f interface_size = {732,444};
		bool ShowInterfaceBorder = false;
	}

	struct UIElement
	{
		Vector2f position;
		Vector2f size;
		Vector2f scale;
		string image_path;
	};
	struct ComputerButton : UIElement
	{
		bool pressed = true;
		int pressed_frames = 0;
		int frames_pressing = 20;
	};
	struct List : UIElement
	{
		vector<UIElement> elements;
	};
	struct BackGround
	{
		Color color;
	};
	// Area where button will be
	// -> what button
	map<string, map<string, ComputerButton>> buttons;
	map<string, List> lists;
	vector<string> area_loaded;

	void Update()
	{
		//mouse_state = MouseState::Arrow; // better to place in main game function !!
		for (const string& area : area_loaded)
		for (map<string, ComputerButton>::iterator it_buttons = buttons[area].begin(); it_buttons != buttons[area].end(); ++it_buttons)
		{
			FloatRect button_floatRect = {
				it_buttons->second.position.x + InterfaceData::interface_pos.x,
				it_buttons->second.position.y + InterfaceData::interface_pos.y,
				it_buttons->second.size.x * it_buttons->second.scale.x,
				it_buttons->second.size.y * it_buttons->second.scale.y
			};

			

			if (CollisionPointRect({ float(mouse_pos.x), float(mouse_pos.y) }, button_floatRect))
			{
				mouse_state = MouseState::Hovering;
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					it_buttons->second.pressed = true;
					it_buttons->second.pressed_frames = 0;
				}
			}
		}
	}

	void LoadArea(string area)
	{
		area_loaded.push_back(area);
	}
	void UnLoadArea(string area)
	{
		for (vector<string>::iterator it_area = area_loaded.begin(); it_area != area_loaded.end(); ++it_area)
		{
			if (*it_area == area)
				it_area = area_loaded.erase(it_area);
		}
	}

	void DrawButton(RenderWindow&window, map<string, ComputerButton>::iterator it_buttons)
	{
		Texture button_texture;
		button_texture.loadFromFile(it_buttons->second.image_path);
		Sprite button_sprite;
		button_sprite.setTexture(button_texture);

		button_sprite.setPosition(it_buttons->second.position + InterfaceData::interface_pos);
		button_sprite.setScale(it_buttons->second.scale);
		it_buttons->second.size = Vector2f{ float(button_texture.getSize().x / 2), float(button_texture.getSize().y) };
		if (it_buttons->second.pressed_frames < it_buttons->second.frames_pressing)
		{	// pressed
			it_buttons->second.pressed_frames++;
			button_sprite.setTextureRect({
				int(it_buttons->second.size.x),	0,
				int(it_buttons->second.size.x), int(it_buttons->second.size.y)
				});
		}
		else
		{
			button_sprite.setTextureRect({
				0, 0,
				int(it_buttons->second.size.x), int(it_buttons->second.size.y)
				});
		}
		window.draw(button_sprite);
	}

	// "area" - what to show
	void Show(RenderWindow& window)
	{
		if (InterfaceData::ShowInterfaceBorder)
		{
			ConvexShape cs;
			cs.setPointCount(4);
			cs.setPoint(0, { InterfaceData::interface_pos });
			cs.setPoint(1, { InterfaceData::interface_pos + Vector2f{InterfaceData::interface_size.x, 0} });
			cs.setPoint(2, { InterfaceData::interface_pos + InterfaceData::interface_size });
			cs.setPoint(3, { InterfaceData::interface_pos + Vector2f{0, InterfaceData::interface_size.y} });
			cs.setFillColor(Color::Transparent);
			cs.setOutlineColor(Color{ 255,0,255,120 });
			cs.setOutlineThickness(4);
			window.draw(cs);
		}

		for (const string& area : area_loaded)
		for (map<string, ComputerButton>::iterator it_buttons = buttons[area].begin(); it_buttons != buttons[area].end(); ++it_buttons)
		{
			DrawButton(window, it_buttons);
		}

		for (map<string, List>::iterator it_list = lists.begin(); it_list != lists.end(); ++it_list)
		{
			Texture list_texture;
			list_texture.loadFromFile(it_list->second.image_path);
			Sprite list_sprite;
			list_sprite.setTexture(list_texture);
			list_sprite.setPosition(it_list->second.position);
			list_sprite.setScale(it_list->second.scale);
			for (vector<UIElement>::iterator it_element = it_list->second.elements.begin();it_element != it_list->second.elements.end();++it_element)
			{
				
			}
		}

	}

	void AddButton(string area, string button_name, string image_path, Vector2f position = { 0,0 }, Vector2f scale = { 1,1 })
	{
		buttons[area][button_name].image_path = image_path;
		buttons[area][button_name].position = {
		position.x * scale.x,
		position.y * scale.y };
		buttons[area][button_name].scale = scale;
	}

	void AddElementToList(string list_name, UIElement element)
	{
		lists[list_name].elements.push_back(element);
	}

	void SetInterfacePos(Vector2f position)
	{
		InterfaceData::interface_pos = position;
	}

	void PrintListOfButtons()
	{
		for (auto it_all_buttons = buttons.begin(); it_all_buttons != buttons.end(); ++it_all_buttons)
		{
			for (auto it_buttons = it_all_buttons->second.begin(); it_buttons != it_all_buttons->second.end(); ++it_buttons)
			{
				// ["Area_name"]["button_name"]
				cout << "[\"" << it_all_buttons->first << "\"] [\"" << it_buttons->first << "\"] pos: "; 
				cout << it_buttons->second.position.x << ' ' << it_buttons->second.position.y << ", scale: ";
				cout << it_buttons->second.scale.x << ' ' << it_buttons->second.scale.y << endl;
			}
		}
	}
}