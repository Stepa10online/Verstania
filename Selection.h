#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

namespace Selection
{
	namespace Data {
		bool SELECTED = false;

		enum last_selection
		{
			// Ставится когда первое выделение было последним выбранным
			first,
			// Ставится когда второе выделение было последним выбранным
			second,
			// Для заглушки, типа NULL
			none
		};

		last_selection last_selected = last_selection::none;

		Vector2f first_selection_pos = { 0,0 };
		Vector2f first_selection_size = { 0,0 };
	
		Vector2f second_selection_pos = { 0,0 };
		Vector2f second_selection_size = { 0,0 };
	}

	void AutoSelect(Vector2f pos, Vector2f size)
	{
		cout << Data::first_selection_pos.y << ' ';
		cout << Data::first_selection_size.y / 2 << ' ';
		cout << Data::first_selection_pos.y + Data::first_selection_size.y / 2 << ' ';
		cout << Data::second_selection_pos.y << ' ';
		cout << Data::second_selection_size.y << ' ';
		cout << Data::second_selection_pos.y + Data::second_selection_size.y << endl;
		if ((Data::last_selected == Data::last_selection::none && Data::SELECTED == false) || Data::last_selected == Data::last_selection::second)
		{
			Data::first_selection_pos = pos;
			Data::first_selection_size = size;

			Data::SELECTED = true;
			Data::last_selected = Data::last_selection::first;
			return;
		}
		if (Data::last_selected == Data::last_selection::first)
		{
			Data::second_selection_pos = pos;
			Data::second_selection_size = size;

			Data::SELECTED = true;
			Data::last_selected = Data::last_selection::second;
			return;
		}

	}

	void Deselect()
	{
		Data::last_selected = Data::last_selection::none;
		Data::SELECTED = false;
		Data::first_selection_pos = { 0,0 };
		Data::first_selection_size = { 0,0 };
		Data::second_selection_pos = { 0,0 };
		Data::second_selection_size = { 0,0 };
	}

	void DrawSelection(RenderWindow &window)
	{
		if (!Data::SELECTED) return;
		ConvexShape rect(4);
		rect.setOutlineColor(Color::White);
		rect.setOutlineThickness(5);
		rect.setFillColor(Color::Transparent);
		Vector2f pos;
		Vector2f size;
		pos = Data::first_selection_pos;
		size = Data::first_selection_size;
		rect.setPoint(0, pos);
		rect.setPoint(1, { pos.x + size.x, pos.y });
		rect.setPoint(2, { pos.x + size.x, pos.y + size.y });
		rect.setPoint(3, { pos.x, pos.y + size.y });
		window.draw(rect);
		pos = Data::second_selection_pos;
		size = Data::second_selection_size;
		rect.setPoint(0, pos);
		rect.setPoint(1, { pos.x + size.x, pos.y });
		rect.setPoint(2, { pos.x + size.x, pos.y + size.y });
		rect.setPoint(3, { pos.x, pos.y + size.y });
		window.draw(rect);
	}


	void DrawLine(RenderWindow& window)
	{
		Vertex line[] = {
			Vertex{{0,0},Color::White}, // left
			Vertex{{0,0},Color::White}, // right
		};
		Vector2f first_selection_pos = Data::first_selection_pos;
		Vector2f second_selection_pos = Data::second_selection_pos;
		Vector2f first_selection_size = Data::first_selection_size;
		Vector2f second_selection_size = Data::second_selection_size;

		if (Vector2f{ first_selection_pos + first_selection_size }.x <
			Vector2f{ second_selection_pos + second_selection_size }.x)
		{
			Vector2f temp_data = second_selection_pos;
			second_selection_pos = first_selection_pos;
			first_selection_pos = temp_data;
			temp_data = second_selection_size;
			second_selection_size = first_selection_size;
			first_selection_size = temp_data;
		}
		if (Vector2f{ first_selection_pos + first_selection_size }.y >
			Vector2f{ second_selection_pos + second_selection_size }.y)
		{
			Vector2f temp_data = second_selection_pos;
			second_selection_pos = first_selection_pos;
			first_selection_pos = temp_data;
			temp_data = second_selection_size;
			second_selection_size = first_selection_size;
			first_selection_size = temp_data;
		}
		
		// down
		if (first_selection_pos.y + first_selection_size.y / 2 > second_selection_pos.y &&
			first_selection_pos.y + first_selection_size.y / 2 < second_selection_pos.y + second_selection_size.y)
		{
			line[0].position = {
				first_selection_pos.x + first_selection_size.x/2,
				first_selection_pos.y + first_selection_size.y,
			};
			line[1].position = {
				first_selection_pos.x + first_selection_size.x / 2,
				second_selection_pos.y + second_selection_size.y + 20,
			};
			window.draw(line, 2, Lines);
			line[0].position = {
				second_selection_pos.x + second_selection_size.x/2,
				second_selection_pos.y + second_selection_size.y,
			};
			line[1].position = {
				second_selection_pos.x + second_selection_size.x / 2,
				second_selection_pos.y + second_selection_size.y + 20,
			};
			window.draw(line, 2, Lines);
			line[0].position = {
				first_selection_pos.x + first_selection_size.x / 2,
				second_selection_pos.y + second_selection_size.y + 20,
			};
			line[1].position = {
				second_selection_pos.x + second_selection_size.x / 2,
				second_selection_pos.y + second_selection_size.y + 20,
			};
			window.draw(line, 2, Lines);

			return;
		}
		
		// left
		if (first_selection_pos.x > 960)
		{
			if ( first_selection_pos.x <= second_selection_pos.x )
			{
				line[0].position = {
					first_selection_pos.x,
					first_selection_pos.y + first_selection_size.y / 2,
				};
				line[1].position = {
					first_selection_pos.x - 20, // 20 - some number
					first_selection_pos.y + first_selection_size.y / 2,
				};
				window.draw(line, 2, Lines);
				line[0].position = {
					second_selection_pos.x,
					second_selection_pos.y + second_selection_size.y / 2,
				};
				line[1].position = {
					first_selection_pos.x - 20,
					second_selection_pos.y + second_selection_size.y / 2,
				};
				window.draw(line, 2, Lines);
				line[0].position = {
					first_selection_pos.x - 20,
					first_selection_pos.y + first_selection_size.y / 2,
				};
				line[1].position = {
					first_selection_pos.x - 20,
					second_selection_pos.y + second_selection_size.y / 2,
				};
				window.draw(line, 2, Lines);
			}
			else
			{

			}

			return;
		}

		// right
		if(first_selection_pos.x + first_selection_size.x + 0 < // 0 - some number 
		   second_selection_pos.x)
		{
			line[0].position = {
				first_selection_pos.x + first_selection_size.x,
				first_selection_pos.y + first_selection_size.y / 2,
			};
			line[1].position = {
				second_selection_pos.x + second_selection_size.x + 20, // 20 - some number
				first_selection_pos.y + first_selection_size.y / 2,
			};
			window.draw(line, 2, Lines);
			line[0].position = {
				second_selection_pos.x + second_selection_size.x,
				second_selection_pos.y + second_selection_size.y / 2,
			};
			line[1].position = {
				second_selection_pos.x + second_selection_size.x + 20,
				second_selection_pos.y + second_selection_size.y / 2,
			};
			window.draw(line, 2, Lines);
			line[0].position = {
				second_selection_pos.x + second_selection_size.x + 20,
				first_selection_pos.y + first_selection_size.y / 2
			};
			line[1].position = {
				second_selection_pos.x + second_selection_size.x + 20,
				second_selection_pos.y + second_selection_size.y / 2,
			};
			window.draw(line, 2, Lines);
		}
		else if (
			first_selection_pos.x + first_selection_size.x + 0 >= // 0 - some number 
			second_selection_pos.x
			)
		{
			line[0].position = {
				first_selection_pos.x + first_selection_size.x,
				first_selection_pos.y + first_selection_size.y / 2,
			};
			line[1].position = {
				first_selection_pos.x + first_selection_size.x + 20, // 20 - some number
				first_selection_pos.y + first_selection_size.y / 2,
			};
			window.draw(line, 2, Lines);
			line[0].position = {
				second_selection_pos.x + second_selection_size.x,
				second_selection_pos.y + second_selection_size.y / 2,
			};
			line[1].position = {
				first_selection_pos.x + first_selection_size.x + 20,
				second_selection_pos.y + second_selection_size.y / 2,
			};
			window.draw(line, 2, Lines);
			line[0].position = {
				first_selection_pos.x + first_selection_size.x + 20,
				first_selection_pos.y + first_selection_size.y / 2
			};
			line[1].position = {
				first_selection_pos.x + first_selection_size.x + 20,
				second_selection_pos.y + second_selection_size.y / 2,
			};
			window.draw(line, 2, Lines);
			return;
		}

	}
}