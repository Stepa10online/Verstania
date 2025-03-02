#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

#include "Collision.h"

namespace Interaction
{
	namespace Data
	{
		enum AreaState
		{
			Mouse_Out,
			Mouse_Entered,
			Mouse_Left_Click,
			Mouse_Right_Click,
			Mouse_Middle_Click,
			Mouse_Left_DoubleClick,
			Mouse_Right_DoubleClick,
			Mouse_Middle_DoubleClick,
			Mouse_Exited,
			Mouse_In,
			Not_Enabled,
		};
		struct Area
		{
			string index = "NULL";
			float x = 0;
			float y = 0;
			float w = 0;
			float h = 0;
			bool enabled = true;
			sf::Color color = Color::Transparent;
			Data::AreaState Mouse_condition;
			AreaState LastOperation = Not_Enabled;
		};
		enum Params
		{
			Xpos,
			Ypos,
			Width,
			Height,
			Color,
			Enabled,
		};


	}
	namespace Settings
	{
		bool CoutInteractionInfoIndex = false;
		bool CoutInteractionInfoString = false;
		bool CoutFullInteractionInfoIndex = false;
		bool CoutFullInteractionInfoString = false;
		bool SaveLastClickedData = true;
		// TODO
		// bool ChangeColorIfClick = false
		// bool ChangeColorIfColliding = false
		// bool ChangeColorIfDoubleClick = false
		// Color MainyColor = { 255,50,25,75 }
		// Color SecondaryColor = { 255,75,50,75 } //Brighter
		//
	}

	vector<Data::Area> all_elements;

	Data::AreaState check(int);

	void AddElement(Data::Area element)
	{
		all_elements.push_back(element);
	}

	Data::Area GetElement(int i)
	{
		return all_elements[i];
	}
	Data::Area GetElement(string index)
	{
		for (auto element : all_elements)
			if (element.index == index) return element;

	}

	Data::Area& EditElement(int i)
	{
		if (i < all_elements.size())
			return all_elements[i];
		else
			cout << "[DEBUG ERROR] out of range in function \"EditElement\"!" << endl;
	}

	Data::Area& EditElement(string s_index)
	{
		int index = -1;
		for (int i = 0; i < all_elements.size(); i++)
		{
			if (all_elements[i].index == s_index)
				index = i;
		}
		if (index != -1)
			return all_elements[index];
		else
			cout << "[DEBUG ERROR] out of range in function \"EditElement\"!" << endl;
	}
	// Да, Я не знаю как заставить эту штуку нормально работать потому использую костыль и не стыжусь этого
	bool EditElement(int i, Data::Params parameters, string data)
	{
		switch (parameters)
		{
		case Interaction::Data::Xpos:
			all_elements[i].x = stoi(data);
			break;
		case Interaction::Data::Ypos:
			all_elements[i].y = stoi(data);
			break;
		case Interaction::Data::Width:
			all_elements[i].w = stoi(data);
			break;
		case Interaction::Data::Height:
			all_elements[i].h = stoi(data);
			break;
		case Interaction::Data::Color:
			cout << "[DEBUG] [Interaction] operation edit color didnt complete" << endl;
			break;
		case Interaction::Data::Enabled:
			all_elements[i].enabled = stoi(data);
			break;
		default:
			cout << "[DEBUG ERROR] [Interaction] out of range in function \"EditElement\"!" << endl;
			break;
		}
		return true;
	}
	bool EditElement(string s_index, Data::Params parameters, string data)
	{
		int index = -1;
		for (int i = 0; i < all_elements.size(); i++)
		{
			if (all_elements[i].index == s_index)
				index = i;
		}
		if (index == -1)
		{
			cout << "[DEBUG ERROR] [Interaction] out of range in function \"EditElement\"!" << endl;
			return false;
		}
		switch (parameters)
		{
		case Interaction::Data::Xpos:
			all_elements[index].x = stoi(data);
			break;
		case Interaction::Data::Ypos:
			all_elements[index].y = stoi(data);
			break;
		case Interaction::Data::Width:
			all_elements[index].w = stoi(data);
			break;
		case Interaction::Data::Height:
			all_elements[index].h = stoi(data);
			break;
		case Interaction::Data::Color:
			cout << "[DEBUG] [Interaction] operation edit color didnt complete" << endl;
			break;
		case Interaction::Data::Enabled:
			all_elements[index].enabled = stoi(data);
			break;
		}
		return true;
	}

	void DrawAllElements(RenderWindow& window)
	{
		Data::Area element;
		for (int i = 0; i < all_elements.size(); i++)
		{
			element = all_elements[i];
			RectangleShape rect(Vector2f{ element.w,element.h });
			rect.setPosition(element.x, element.y);
			if(element.color == Color::Transparent)
				rect.setFillColor({ 255,50,25,75 });
			else
				rect.setFillColor(element.color);

			if (element.color == Color::Transparent && !element.enabled)
				rect.setFillColor({ 125,0,0,75 });
			else if(!element.enabled)
				rect.setFillColor(Color{ Uint8(element.color.r *= 0.5),Uint8(element.color.g *= 0.5) ,Uint8(element.color.b *= 0.5),element.color.a});
			window.draw(rect);
		}
	}

	Data::AreaState CheckInteraction(int i)
	{
		if (all_elements[i].enabled)
			return check(i);
		else
			return Data::AreaState::Not_Enabled;
	}
	vector<Data::AreaState> CheckInteraction()
	{
		vector<Data::AreaState> area_states;
		for (int i = 0; i < all_elements.size(); i++)
		{
			if(all_elements[i].enabled)
				area_states.push_back(check(i));
			else
				area_states.push_back(Data::AreaState::Not_Enabled);
		}
		return area_states;
	}
	// Maybe not but maybe yes
	// Если вводить, то потребуется много чего ещё редактировать.
	// Вводить логику с update, чтобы все вызванные функции только
	// 
	//static enum Settings
	//{
	//	DrawAllElements = false,
	//};

	bool IsAnyElementEnabled()
	{
		for (auto element : all_elements)
			if (element.enabled) return true;
		return false;
	}
	bool AreAllElementsEnabled()
	{
		for (auto element : all_elements)
			if (!element.enabled) return false;
		return true;
	}

	bool IsAnyElement(Data::AreaState state)
	{
		for (auto element : all_elements)
			if (element.Mouse_condition == state) return true;
		return false;
	}

	// Checks Data::Area element for: (enum Data::AreaState) Mouse_Entering, Mouse_Click, Mouse_Exiting, Mouse_In
	// Data::Area - struct that contains: X,Y,W,H
	//
	Data::AreaState check(int i)
	{
		Data::Area *element = &all_elements[i];
		Vector2f m_pos = { ImGui::GetMousePos().x, ImGui::GetMousePos().y };
		if (CollisionPointRect(m_pos, FloatRect{ element->x,element->y,element->w,element->h }))
		{
			if (element->Mouse_condition == Data::AreaState::Mouse_Left_Click || element->Mouse_condition == Data::AreaState::Mouse_Left_DoubleClick ||
				element->Mouse_condition == Data::AreaState::Mouse_Right_Click || element->Mouse_condition == Data::AreaState::Mouse_Right_DoubleClick ||
				element->Mouse_condition == Data::AreaState::Mouse_Middle_Click || element->Mouse_condition == Data::AreaState::Mouse_Middle_DoubleClick)
				element->Mouse_condition = Data::AreaState::Mouse_In;
			if (element->Mouse_condition == Data::AreaState::Mouse_Out)
			{
				element->Mouse_condition = Data::AreaState::Mouse_Entered;
				if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_Entered" << endl;
				if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString )cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Entered" << endl;
				return Data::AreaState::Mouse_Entered;
			}
			if (element->Mouse_condition == Data::AreaState::Mouse_Entered)
			{
				element->Mouse_condition = Data::AreaState::Mouse_In;
				if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_In" << endl;
				if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString)cout << "[DEBUG] [Interaction] " << element->index << " Mouse_In" << endl;
				return Data::AreaState::Mouse_In;
			}
			if (element->Mouse_condition == Data::AreaState::Mouse_In)
			{
				// Double clicked
				if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					element->Mouse_condition = Data::AreaState::Mouse_Left_DoubleClick;
					if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_Left_DoubleClick" << endl;
					if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString)cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Left_DoubleClick" << endl;
					element->LastOperation = Data::AreaState::Mouse_Left_DoubleClick;
					return Data::AreaState::Mouse_Left_DoubleClick;
				}
				if(ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Right))
				{
					element->Mouse_condition = Data::AreaState::Mouse_Right_DoubleClick;
					if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_Right_DoubleClick" << endl;
					if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString)cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Right_DoubleClick" << endl;
					element->LastOperation = Data::AreaState::Mouse_Right_DoubleClick;
					return Data::AreaState::Mouse_Right_DoubleClick;
				}
				if(ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Middle))
				{
					element->Mouse_condition = Data::AreaState::Mouse_Middle_DoubleClick;
					if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_Middle_DoubleClick" << endl;
					if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString)cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Middle_DoubleClick" << endl;
					element->LastOperation = Data::AreaState::Mouse_Middle_DoubleClick;
					return Data::AreaState::Mouse_Middle_DoubleClick;
				}
				// Just clicked
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					element->Mouse_condition = Data::AreaState::Mouse_Left_Click;
					if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_Left_Click" << endl;
					if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString)cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Left_Click" << endl;
					element->LastOperation = Data::AreaState::Mouse_Left_Click;
					return Data::AreaState::Mouse_Left_Click;
				}
				if(ImGui::IsMouseClicked(ImGuiMouseButton_Right))
				{
					element->Mouse_condition = Data::AreaState::Mouse_Right_Click;
					if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_Right_Click" << endl;
					if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString)cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Right_Click" << endl;
					element->LastOperation = Data::AreaState::Mouse_Right_Click;
					return Data::AreaState::Mouse_Right_Click;
				}
				if(ImGui::IsMouseClicked(ImGuiMouseButton_Middle))
				{
					element->Mouse_condition = Data::AreaState::Mouse_Middle_Click;
					if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_Middle_Click" << endl;
					if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString)cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Middle_Click" << endl;
					element->LastOperation = Data::AreaState::Mouse_Middle_Click;
					return Data::AreaState::Mouse_Middle_Click;
				}
			}
		}
		else
		{
			if (element->Mouse_condition == Data::AreaState::Mouse_Left_Click || element->Mouse_condition == Data::AreaState::Mouse_Left_DoubleClick ||
				element->Mouse_condition == Data::AreaState::Mouse_Right_Click || element->Mouse_condition == Data::AreaState::Mouse_Right_DoubleClick ||
				element->Mouse_condition == Data::AreaState::Mouse_Middle_Click || element->Mouse_condition == Data::AreaState::Mouse_Middle_DoubleClick)
				element->Mouse_condition = Data::AreaState::Mouse_Out;
			if (element->Mouse_condition == Data::AreaState::Mouse_In || element->Mouse_condition == Data::AreaState::Mouse_Entered)
			{
				element->Mouse_condition = Data::AreaState::Mouse_Exited;
				if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_Exited" << endl;
				if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString)cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Exited" << endl;
				return Data::AreaState::Mouse_Exited;
			}
			if (element->Mouse_condition == Data::AreaState::Mouse_Exited)
			{
				element->Mouse_condition = Data::AreaState::Mouse_Out;
				if (Settings::CoutInteractionInfoIndex || Settings::CoutFullInteractionInfoIndex) cout << "[DEBUG] [Interaction] " << i << " Mouse_Out" << endl;
				if (Settings::CoutInteractionInfoString || Settings::CoutFullInteractionInfoString)cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Out" << endl;
				return Data::AreaState::Mouse_Out;
			}
		}

		if (Settings::CoutFullInteractionInfoIndex)
		{
			if(element->Mouse_condition == Data::AreaState::Mouse_Out)
				cout << "[DEBUG] [Interaction] " << i << " Mouse_Out" << endl;
			if(element->Mouse_condition == Data::AreaState::Mouse_In)
				cout << "[DEBUG] [Interaction] " << i << " Mouse_In" << endl;
		}
		if (Settings::CoutFullInteractionInfoString)
		{
			if(element->Mouse_condition == Data::AreaState::Mouse_Out)
				cout << "[DEBUG] [Interaction] " << element->index << " Mouse_Out" << endl;
			if(element->Mouse_condition == Data::AreaState::Mouse_In)
				cout << "[DEBUG] [Interaction] " << element->index << " Mouse_In" << endl;
		}
		return element->Mouse_condition;
	}
};