#pragma once

// Interface for computer in game

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game Data.h"

using namespace sf;
using namespace std;

namespace Interface
{
	enum class ElementsStates
	{
		Hovered,
		Focused,
		Pressed,
		None
	};

	bool IsAnyListIsHovered();
	bool IsAnyPopUpHovered();
	bool IsAnyMovableElementHovered();

	namespace InterfaceData
	{
		Vector2f interface_pos = {0,0};
		Vector2f interface_size = {738,444};
		Vector2f standart_scale = { 1,1 };
		bool ShowInterfaceBorder = false;

		vector<string>buttons_pressed = {};
		string just_pressed = "";

		bool IsButtonJustPressed(string button)
		{
			if (just_pressed == button) return true;
			return false;
		}

		bool IsButtonPressed(string button)
		{
			for (vector<string>::iterator it_buttons_pressed = InterfaceData::buttons_pressed.begin();
				it_buttons_pressed != InterfaceData::buttons_pressed.end(); ++it_buttons_pressed)
			{
				if (*it_buttons_pressed == button)
					return true;
			}
			return false;
		}
		vector<string>::iterator GetButtonPressed(string button)
		{
			for (vector<string>::iterator it_buttons_pressed = InterfaceData::buttons_pressed.begin();
				it_buttons_pressed != InterfaceData::buttons_pressed.end(); ++it_buttons_pressed)
			{
				if (*it_buttons_pressed == button)
					return it_buttons_pressed;
			}
			return InterfaceData::buttons_pressed.end();
		}

//////// SETTERS

		//void SetStandartScale(const Vector2f& scale)
		//{
		//	standart_scale = scale;
		//}
	}
	struct UIblank
	{
		Vector2f position;
		Vector2f size;
		Vector2f scale;
		string image_path;
		IntRect texture_rect;

	};
	struct UIElement : UIblank
	{
		int frames_for_pressing = 20;
		int pressed_frames = frames_for_pressing;
		bool button_just_pressed = false;
		bool pressed = false;
		bool hovered = false;
		
		void Draw(){}
	};
	struct ComputerButton : UIElement
	{
		void update()
		{
			if (pressed_frames < frames_for_pressing)
			{
				pressed = true;
			}
			else
			{
				pressed = false;
			}

			FloatRect button_floatRect = {
				position.x + InterfaceData::interface_pos.x,
				position.y + InterfaceData::interface_pos.y,
				size.x * scale.x,
				size.y * scale.y
			};

			if (!(IsAnyListIsHovered() || IsAnyPopUpHovered() || IsAnyMovableElementHovered() /*|| IsPopUpActive()*/) &&
				CollisionPointRect({ float(mouse_pos.x), float(mouse_pos.y) }, button_floatRect))
			{
				if (pressed_frames < 10)
					mouse_state = MouseState::Arrow;
				else
					mouse_state = MouseState::Hovering;
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					button_just_pressed = true;
					pressed_frames = 0;
				}
			}
		}
		
	};
	struct CheckBox : UIElement
	{
		bool checked = false;

		void update()
		{
			if (pressed_frames < frames_for_pressing)
			{
				pressed = true;
			}
			else
			{
				pressed = false;
			}

			FloatRect button_floatRect = {
				position.x + InterfaceData::interface_pos.x,
				position.y + InterfaceData::interface_pos.y,
				size.x * scale.x,
				size.y * scale.y
			};

			if (!(IsAnyListIsHovered() || IsAnyPopUpHovered() || IsAnyMovableElementHovered() /*|| IsPopUpActive()*/) &&
				CollisionPointRect({ float(mouse_pos.x), float(mouse_pos.y) }, button_floatRect))
			{
				if (pressed_frames < 10)
					mouse_state = MouseState::Arrow;
				else
					mouse_state = MouseState::Hovering;
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					pressed_frames = 0;
					if (checked == true)
					{
						checked = false;
						return;
					}
					if (checked == false)
					{
						checked = true;
						return;
					}
				}
			}
			
		}
	};
	struct ListButton : UIElement
	{
		string button_name = "";
		bool active = true;

		ListButton(string button_name = "", bool active = true)
		{
			this->button_name = button_name;
			this->active = active;
		}

		void update()
		{
			if (pressed_frames < frames_for_pressing)
			{
				pressed = true;
			}
			else
			{
				pressed = false;
			}

			FloatRect button_floatRect = {
				position.x + InterfaceData::interface_pos.x,
				position.y + InterfaceData::interface_pos.y,
				size.x * scale.x,
				size.y * scale.y
			};

			button_just_pressed = false;

			if (!(IsAnyPopUpHovered() || IsAnyMovableElementHovered()) &&
				CollisionPointRect({ float(mouse_pos.x), float(mouse_pos.y) }, button_floatRect))
			{
				if (pressed_frames < 10)
					mouse_state = MouseState::Arrow;
				else
					mouse_state = MouseState::Hovering;
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					button_just_pressed = true;
					pressed_frames = 0;
				}
			}
		}
	};
	struct List : UIElement
	{
		//// #List_structs
		

		//// #List_Data
		vector<ListButton> elements;
		ElementsStates list_state = ElementsStates::None;
	};
	struct UIMEBTNSettings {
		string setting_name = "";
		string text = "";
		bool active = true;

		UIMEBTNSettings(string setting_name = "", string text = "")
		{
			this->setting_name = setting_name;
			this->text = text;
		}
		UIMEBTNSettings(string setting_name = "", bool active = "")
		{
			this->setting_name = setting_name;
			this->active = active;
		}
	};
	struct UIMEButton :UIElement {
		string button_name = "";
		bool active = true;
		Vector2f button_offset = { 0,0 };

		void update()
		{
			if (pressed_frames < frames_for_pressing)
			{
				pressed = true;
			}
			else
			{
				pressed = false;
			}

			FloatRect button_floatRect = {
				position.x + InterfaceData::interface_pos.x,
				position.y + InterfaceData::interface_pos.y,
				size.x * scale.x,
				size.y * scale.y
			};

			button_just_pressed = false;

			if (!IsAnyPopUpHovered() &&
				CollisionPointRect({ float(mouse_pos.x), float(mouse_pos.y) }, button_floatRect))
			{
				if (pressed_frames < 10)
					mouse_state = MouseState::Arrow;
				else
					mouse_state = MouseState::Hovering;
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					button_just_pressed = true;
					pressed_frames = 0;
				}
			}
		}
	};
	struct UIMovableElement : UIblank {
	  // Various FloatRect
		struct Vfr {
			Vector2f pos;
			Vector2f size;
		};
	   //header for title, moving around
		Vfr head;
	   //mouse offset
		Vector2f m_offset;
	   //buttons
		vector<UIMEButton> buttons;
	   // message
		string text;
	   //if mouse clicked
		bool clicked;
	   //if mouse clicked and draged
		bool drag;
	   //if mouse hovered
		bool hovered;
	};
	struct Slider : UIElement {
	   // slider height
		float slider_height;
	   // position of movable element (+top border)
		float slider_pos;
	   // bottom border = slider_pos + element_slider_height
		float element_slider_height;
	   // how much will be traanslated for (position - slider_pos)
		float translation_koef;
	   // coord Y where user clicked
		float clicked_pos;
	   // is clider was clicked (set false)
		bool clicked = false;
	   // is enabled and drawn
		bool loaded = true;
		
		string image_path = "sprites\\ui\\Computer Interface\\slider.png";

		void update()
		{
			button_just_pressed = false;
			pressed = false;


			FloatRect button_floatRect = {
				position.x + InterfaceData::interface_pos.x,
				slider_pos + InterfaceData::interface_pos.y,
				size.x * scale.x,
				size.y * scale.y
			};

			if(pressed_frames < frames_for_pressing)
				pressed_frames++;
			if (!IsAnyPopUpHovered() &&
				CollisionPointRect({ float(mouse_pos.x), float(mouse_pos.y) }, button_floatRect))
			{
				if(pressed_frames <= 10)
					mouse_state = MouseState::Arrow;
				else
					mouse_state = MouseState::Hovering;

				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
					clicked = true;

			}

			if( clicked == true && ImGui::IsMouseDown(ImGuiMouseButton_Left))
			{
				if (clicked_pos == 0)
					clicked_pos = (float)mouse_pos.y - slider_pos;
				button_just_pressed = true;
				pressed_frames = 0;
				pressed = true;
				mouse_state = MouseState::Hovering;
			}
			else
			{
				clicked_pos = 0;
				clicked = false;
			}
		}

	};

	namespace BackGround
	{
		//Color color = Color{153,153,153,255};
		Color color = Color{73,83,123,255};
	};

   // strung1->Area, string2->button_name
	map<string, map<string, ComputerButton>> buttons;
   // strung1->Area, string2->checkbox_name
	map<string, map<string, CheckBox>> checkboxes;
   // List_name, list itself
	map<string, map<string, List>> lists;
   // Movable Elements
	map<string, UIMovableElement> movls;
	
	map<string, Slider> sliders;
	
	// Contains only loaded areas for interface decorations
	vector<string> areas_loaded;
	// Contains only loaded areas for list update
	// Means, that some lists can be related to areas 
	// that not actually loaded.
	// lists's area must be loaded to draw & update them
	vector<string> lists_areas_loaded;
	// Contains only loaded areas for buttons update
	// Means, that some buttons can be related to areas 
	// that not actually loaded.
	// Buttons's area must be loaded to draw & update them
	vector<string> buttons_areas_loaded;



	namespace UIDecor
	{
		struct Decor
		{
			string image_path;
			Vector2f position;
			Vector2f size;
			Vector2f scale;
			bool show = true;
		};
		// Decor shows as other elements only when it's area is
		// loaded
		map<string, map<string, Decor>> decors;
		void DrawDecor(RenderWindow& window, const Decor& decor)
		{

			Texture button_texture;
			button_texture.loadFromFile(decor.image_path);
			Sprite button_sprite;
			button_sprite.setTexture(button_texture);

			button_sprite.setPosition(decor.position + InterfaceData::interface_pos);
			button_sprite.setScale(decor.scale);

			window.draw(button_sprite);
		}
		void DrawDecors(RenderWindow& window)
		{

			for (const string& area : areas_loaded)
			for (map<string, Decor>::iterator it_decor = decors[area].begin();
				it_decor != decors[area].end(); ++it_decor)
			{
				if(it_decor->second.show)
					DrawDecor(window, it_decor->second);
			}
		}

		void AddDecor(string area, string decor_name, string image_path, 
			Vector2f position = { 0,0 }, Vector2f scale = { 1,1 })
		{
			decors[area][decor_name].image_path = image_path;
			decors[area][decor_name].position = {
								position.x * scale.x,
								position.y * scale.y };
			decors[area][decor_name].scale = scale;
		}
		void Show(string decor_element_name) {
			for (const auto& area : areas_loaded)
				decors[area][decor_element_name].show = true;
		}
		void Hide(string decor_element_name) {
			for (const auto& area : areas_loaded)
				decors[area][decor_element_name].show = false;
		}
	}

	namespace ComputerButtons
	{
		void Update()
		{
			for (const string& area : areas_loaded)
			for (int i = 0; i < InterfaceData::buttons_pressed.size(); i++)
			{
				if(buttons[area].find(InterfaceData::buttons_pressed[i]) != buttons[area].end())
					cout << i << " pressed rn: [\"" << area << "\"] " << InterfaceData::buttons_pressed[i] << endl;
			}
			//if(InterfaceData::just_pressed!="")
			//	cout << "Just pressed: " << InterfaceData::just_pressed << endl;

			for (const string& area : areas_loaded)
			for (map<string, ComputerButton>::iterator it_buttons = buttons[area].begin(); 
				it_buttons != buttons[area].end(); ++it_buttons)
			{
				it_buttons->second.update();

				if (it_buttons->second.button_just_pressed)
				{
					InterfaceData::just_pressed = it_buttons->first;
				}
				else InterfaceData::just_pressed = "";

				// Если прошла половина всех кадров, то добавлять в вектор
				if (it_buttons->second.pressed &&
					it_buttons->second.pressed_frames > it_buttons->second.frames_for_pressing/2)
				{	
					bool button_found = false;
					// finding is there already button in the vector, if not so -> add that button to the vector
					for (vector<string>::iterator it_buttons_pressed = InterfaceData::buttons_pressed.begin();
						it_buttons_pressed != InterfaceData::buttons_pressed.end(); ++it_buttons_pressed)
						if (*it_buttons_pressed == it_buttons->first) button_found = true;
					if(!button_found)InterfaceData::buttons_pressed.push_back(it_buttons->first);
				}
				else
					// finding is there button in the vector, if so -> erase that button from the vector
					for(vector<string>::iterator it_buttons_pressed = InterfaceData::buttons_pressed.begin(); 
						it_buttons_pressed!= InterfaceData::buttons_pressed.end(); ++it_buttons_pressed)
						if (*it_buttons_pressed == it_buttons->first) { InterfaceData::buttons_pressed.erase(it_buttons_pressed); break; }
			}
		}

		void Draw_Button(RenderWindow& window, UIElement& element)
		{
			Texture button_texture;
			button_texture.loadFromFile(element.image_path);
			Sprite button_sprite;
			button_sprite.setTexture(button_texture);

			button_sprite.setPosition(element.position + InterfaceData::interface_pos);
			button_sprite.setScale(element.scale);

			// press handler
			element.size = Vector2f{ float(button_texture.getSize().x / 2), float(button_texture.getSize().y) };
			if (element.pressed){	
				element.pressed_frames++;
				button_sprite.setTextureRect({
					int(element.size.x),	0, // x y
					int(element.size.x), int(element.size.y) // w h
					});}
			else{
				button_sprite.setTextureRect({
					0, 0, // x y
					int(element.size.x), int(element.size.y) // w h
					});}
			if (element.hovered)
				button_sprite.setColor(Color{ 200,200,200 });
			else
				button_sprite.setColor(Color::White);
			window.draw(button_sprite);
		}
	}

	// General_Checkers
	bool IsAnyListIsHovered()
	{
		for (const string& list_area : lists_areas_loaded)
			for (map<string, List>::iterator it_lists = lists[list_area].begin();
				it_lists != lists[list_area].end(); ++it_lists)
		{
			if (it_lists->second.list_state == ElementsStates::Hovered)
			{
				return true;
			}
		}
		return false;
	}
	


// Only List functions
	namespace List_functions
	{
		//// #Structs

	//// #Data
		string active_list = "";
		// offset for elements in list from top left corner
		Vector2f element_list_offset = {5,5};
		// List_name, button only for list
		map<string, ListButton> lists_buttons;

		string pressed_button = "";

	//// #Checking
		bool IsListActive(string list_name)
		{
			return active_list == list_name;
		}

		// Переделать -> WhatListElementPressed(string list_name)
		string WhatListElementPressed()
		{
			// Пробигаемся по доступным облостям -> 
			// Пробигаемся по загруженным спискам -> 
			// Пробигаемся по элементам списка ->
			// Ищем нажатый элемент
			for (const string& list_area : lists_areas_loaded)
			for (auto it_list = lists[list_area].begin();
				it_list != lists[list_area].end(); ++it_list)
			for (auto it_button = it_list->second.elements.begin();
				it_button != it_list->second.elements.end(); ++it_button)
			{
				if (it_button->pressed &&
					it_button->pressed_frames > it_button->frames_for_pressing / 2)
				{
					cout << it_button->button_name << endl;
					return it_button->button_name;
				}
			}
			return "";
		}

		bool IsListInCollision(string area, string list_name)
		{
			FloatRect list_fr = {
					lists[area][list_name].position + InterfaceData::interface_pos,
					lists[area][list_name].size
			};

			if (IsListActive(list_name) &&
				CollisionPointRect({ float(mouse_pos.x),float(mouse_pos.y) }, list_fr))
			{
				return true;
			}
			return false;
		}

	//// #Update

		void UpdateLists()
		{

			//for (map<string, map<string, List>>::iterator it_lists = lists.begin();
			//	it_lists != lists.end(); ++it_lists)
			//{
			//	//cout << "[\"" << it_lists->first << "\"]";
			//	if (IsListActive(it_lists->first))
			//	{
			//		cout << " - active";
			//	}
			//	//cout << endl;
			//}

			for (const string& list_area : lists_areas_loaded)
			for (map<string, List>::iterator it_lists = lists[list_area].begin();
				it_lists != lists[list_area].end(); ++it_lists)
			{
				if (IsListActive(it_lists->first))
				for (ListButton& list_buttion : it_lists->second.elements)
				{
					list_buttion.update();
				}
					
			}
		}
		void UnLoadListArea(string);
		void UnLoadAllListAreas();
		void UpdateOldListActivness()
		{
			if(active_list!="")
			for (const string& area : lists_areas_loaded)
				for (map<string, List>::iterator it_lists = lists[area].begin();
					it_lists != lists[area].end(); ++it_lists)
			{
				if (it_lists->first == active_list)
				{
					if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !IsListInCollision(area, active_list))
					{
						//list_state = listState::None;
						it_lists->second.list_state = ElementsStates::None;
						UnLoadListArea(active_list);
						active_list = "";
					}
				}
			}
		}

		//
		// UpdateListsActiveness Должен проверять
		// наведен ли курсор на лист, если да, то 
		// кнопки позади нажать нельзя
		//
		void UpdateListsActiveness()
		{
			for (const string& area : lists_areas_loaded)
			for (map<string, List>::iterator it_lists = lists[area].begin();
				it_lists != lists[area].end(); ++it_lists)
			{
				if (IsListInCollision(area, it_lists->first))
					it_lists->second.list_state = ElementsStates::Hovered;
				else
				{
					it_lists->second.list_state = ElementsStates::None;
					if (IsListActive(it_lists->first) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
					{
						active_list = "";
					}
				}

				//if (IsListActive(it_lists->first) && 
				//	ImGui::IsMouseClicked(ImGuiMouseButton_Left) &&
				//	!IsListInCollision(area, it_lists->first))
				//{
				//	cout << "Doesn't colliding -> [\"" << it_lists->first << "\"]" << endl;
				//	active_list = "";
				//}
				//else if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				//{
				//	cout << "Colliding -> [\"" << it_lists->first << "\"]" << endl;
				//	//active_list = it_lists->first;
				//}
			}
		}

	//// #Setters
		void SetActiveList(string list_name)
		{
			active_list = list_name;
		}

	//// #Drawing
		void DrawList(RenderWindow& window, List& list)
		{
			Texture list_texture;
			list_texture.loadFromFile(list.image_path);
			Sprite list_sprite;
			list_sprite.setTexture(list_texture);

			list_sprite.setPosition(list.position + InterfaceData::interface_pos);
			list_sprite.setScale(list.scale);

			window.draw(list_sprite);

			for (vector<ListButton>::iterator it_buttons = list.elements.begin();
				it_buttons != list.elements.end(); ++it_buttons)
			{
				ComputerButtons::Draw_Button(window, *it_buttons);
			}
		}

		void Draw_Lists(RenderWindow& window)
		{
			for (const string& list_area : lists_areas_loaded)
			for (map<string, List>::iterator it_lists = lists[list_area].begin();
				it_lists != lists[list_area].end(); ++it_lists)
			{
				//cout << list_area << ": " << it_lists->second.elements.size() << endl;
				if (IsListActive(it_lists->first))
					DrawList(window, it_lists->second);
			}
		}

	//// #Addition
		void AddButtonToList(string area, string list_element_name, string button_name, 
			string image_path, Vector2f position = {0,0},Vector2f size = {10,10},
			Vector2f scale = {1,1})
		{
			ListButton* temp_lbutton = new(ListButton);
			temp_lbutton->position = {
				6 + position.x * scale.x + lists[area][list_element_name].position.x,
				6 + position.y * scale.y + lists[area][list_element_name].position.y + 2* lists[area][list_element_name].elements.size()};
			temp_lbutton->size = {
								size.x * scale.x,
								size.y * scale.y };
			temp_lbutton->scale = scale;
			temp_lbutton->image_path = image_path;
			temp_lbutton->button_name = button_name;
			lists[area][list_element_name].elements.push_back(*temp_lbutton);
			delete temp_lbutton;
		}

		void AddList(string area, string list_areas, string image_path, 
			Vector2f position = { 0,0 }, Vector2f size = {10,10},
			Vector2f scale = { 1,1 })
		{
			lists[area][list_areas].image_path = image_path;
			lists[area][list_areas].position = {
								position.x * scale.x,
								position.y * scale.y };
			lists[area][list_areas].size = {
								size.x * scale.x,
								size.y * scale.y };
			lists[area][list_areas].scale = scale;
		}
	//// Loaders
		void PrintListsLoaded();
		void LoadListArea(string list_area)
		{
			cout << "Load list area: ";
			bool found_area = false;
			for (vector<string>::iterator it_area = lists_areas_loaded.begin(); it_area != lists_areas_loaded.end(); ++it_area)
			{
				if (*it_area == list_area)
					found_area = true;
			}
			if (!found_area)
			{
				cout << list_area << endl;
				lists_areas_loaded.push_back(list_area);
			}
			else cout << "None" << endl;

			PrintListsLoaded();
		}
		void UnLoadListArea(string area)
		{
			cout << "Unload list area: " << area << endl;
			for (vector<string>::iterator it_area = lists_areas_loaded.begin(); it_area != lists_areas_loaded.end(); ++it_area)
			{
				if (*it_area == area)
				{
					cout << "List \"" << *it_area << "\" was unloaded" << endl;
					lists_areas_loaded.erase(it_area);
					PrintListsLoaded();
					return;
				}
			}
			cout << "Not a single list was unloaded" << endl;
			//PrintListsLoaded();
		}
		void UnLoadAllListAreas()
		{
			for (const string& list_area : lists_areas_loaded)
			{
				UnLoadListArea(list_area);
			}
		}
	//// #Debug code
		void PrintListsLoaded()
		{
			cout << "Lists Loaded:" << endl;

			//for (const string& area : lists_areas_loaded)
			for (map<string, map<string, List>>::iterator it_lists = lists.begin();
				it_lists != lists.end(); ++it_lists)
			{
				cout << "[\"" << it_lists->first << "\"]";
				if (IsListActive(it_lists->first))
				{
					cout << " - active";
				}
				cout << endl;
			}
		}
	}

// Only PopUps functions
	namespace PopUps
	{

		// PopUp classification
		enum class PopUp_class
		{
			Message,
			Success,
			Error,
			Information,
			Warning
		};
		struct PopUp_Button : UIElement
		{
		public:
			string button_name = "";
			bool active = true;
		public:
			PopUp_Button(string button_name="", bool active=true)
			{
				this->button_name = button_name;
				this->active = active;
			}
			void update()
			{
				if (pressed_frames < frames_for_pressing)
				{
					pressed = true;
				}
				else
				{
					pressed = false;
				}

				FloatRect button_floatRect = {
					position.x + InterfaceData::interface_pos.x,
					position.y + InterfaceData::interface_pos.y,
					size.x * scale.x,
					size.y * scale.y
				};

				button_just_pressed = false;

				if (CollisionPointRect({ float(mouse_pos.x), float(mouse_pos.y) }, button_floatRect))
				{
					if (pressed_frames < 20)
						mouse_state = MouseState::Arrow;
					else
						mouse_state = MouseState::Hovering;
					if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
					{
						button_just_pressed = true;
						pressed_frames = 0;
					}
				}
			}
		};
		struct PopUpText : UIblank
		{
			string message = "";
			Vector2f offset = { 0,0 };
		};
		struct PopUpButtonSettings
		{
			string button_name;
			bool active;
		};
		struct PopUp : UIblank
		{
			Font font;
			PopUp_class popup_class = PopUp_class::Message;
			ElementsStates popup_state = ElementsStates::None;
			
			vector<PopUpButtonSettings> popup_buttons_settings;
			vector<PopUp_Button> popup_buttons = {};
			
			string id = "";
			string message = "";
		};
		
		vector<PopUp> popups;

		string PopUpImagePath(const PopUp_class& );

		bool IsPopUpHovered(PopUp& popup)
		{
			FloatRect popup_fr = {popup.position, popup.size};
			if (CollisionPointRect(Vector2f{ float(mouse_pos.x),float(mouse_pos.y) }, popup_fr))
			{
				popup.popup_state = ElementsStates::Hovered;
				return true;
			}
			popup.popup_state = ElementsStates::None;
			return false;
		}

		void PopUpsUpdate()
		{
			for (vector<PopUp>::iterator it_popup = popups.begin(); 
				it_popup != popups.end(); ++it_popup)
			{
				IsPopUpHovered(*it_popup);
				/*
				it_popup = --popups.end();
				for (vector<PopUp_Button>::iterator it_popup_buttons = it_popup->popup_buttons.begin();
					it_popup_buttons != it_popup->popup_buttons.end(); ++it_popup_buttons)
				{
					it_popup_buttons->update();
					if (it_popup_buttons->pressed && it_popup_buttons->pressed_frames > it_popup_buttons->frames_for_pressing/2 &&
						(it_popup_buttons->button_name == "closing" || it_popup_buttons->button_name == "ok"))
					{
						popups.erase(it_popup);
						return;
					}
				}*/
			}

			if(popups.size()>0)
				for (vector<PopUp_Button>::iterator it_popup_buttons = (popups.end()-1)->popup_buttons.begin();
				it_popup_buttons != (popups.end()-1)->popup_buttons.end(); ++it_popup_buttons)
			{
				it_popup_buttons->update();
				if (it_popup_buttons->pressed && it_popup_buttons->pressed_frames > it_popup_buttons->frames_for_pressing / 2 &&
					(it_popup_buttons->button_name == "close" || it_popup_buttons->button_name == "ok"))
				{
					popups.erase(popups.end()-1);
					break;
				}
			}
		}

		void AddPopUp(PopUp_class popup_class, string id, string message, 
			Vector2f position = { 0, 0 }, Vector2f scale = { 1,1 },
			vector<PopUpButtonSettings> popup_buttons_settings = { {"ok",true},{"close",true}})
		{
		  //needed vars
			PopUp temp_popup;
			PopUp_Button popup_button;
			Vector2f popup_offset = position;

		  //Setting popup's data
			temp_popup.scale = scale;
			temp_popup.id = id;
			temp_popup.message = message;
			if (popups.size() > 0)
			{
				if (popups[popups.size() - 1].position.x + 8 * scale.x < 500)
					popup_offset.x = popups[popups.size() - 1].position.x;
				else
					popup_offset.x = 30;

				if (popups[popups.size() - 1].position.y + 8 * scale.y < 500)
					popup_offset.y = popups[popups.size() - 1].position.y;
				else
					popup_offset.y = 30;
			}
			temp_popup.image_path = PopUpImagePath(popup_class);
			temp_popup.position = {
								popup_offset.x + 8 * scale.x + Interface::InterfaceData::interface_pos.x,
								popup_offset.y + 6 * scale.y + Interface::InterfaceData::interface_pos.y };

		  //Setting popup's buttons
			popup_button.scale = scale;
		
			for (int i = 0; i < popup_buttons_settings.size(); i++)
			{
				string button_settings_name = popup_buttons_settings[i].button_name;
				popup_button.button_name = button_settings_name;

			  //Setting buttons activness
				for (int c = 0; c < temp_popup.popup_buttons.size(); c++)
					if (button_settings_name == temp_popup.popup_buttons[c].button_name)
						temp_popup.popup_buttons[c].active = popup_buttons_settings[i].active;

			  //Setting buttons params
				if (button_settings_name == "ok")
				{
					popup_button.position = temp_popup.position + Vector2f{ 200,100 };
					popup_button.image_path = "sprites\\ui\\Computer Interface\\ok.png";
					popup_button.size = { 28,15 };
					temp_popup.popup_buttons.push_back(popup_button);
				}
				if (button_settings_name == "close")
				{
					popup_button.position = temp_popup.position + Vector2f{ 224,-20 };
					popup_button.image_path = "sprites\\ui\\Computer Interface\\X.png";
					popup_button.size = { 15,15 };
					temp_popup.popup_buttons.push_back(popup_button);
				}

			}
		  //adding new popup to vector
			popups.push_back(temp_popup);
		}

		struct PopUp_return {
			string button_pressed = "";
		};
	  // returns pressed button
		PopUp_return getPopUpButtonPressed(string id)
		{
			PopUp_return ppr;
			for(int i=0; i<popups.size();i++)
			{
				if (popups[i].id == id)
				{
					for(int j=0; j<popups[i].popup_buttons.size();j++)
					{
						if (popups[i].popup_buttons[j].pressed)
							ppr.button_pressed = popups[i].popup_buttons[j].button_name;
					}
				}
			}
			return ppr;
		}

		void Draw_PopUps(RenderWindow& window)
		{
			Texture texture;
			Sprite sprite;
			Font font;
			Text text;

			font.loadFromFile("pixelplay.ttf");
			text.setFont(font);
			text.setCharacterSize(15);
			text.setFillColor(Color{ 25,25,25 });

			for (vector<PopUp>::iterator it_popup = popups.begin();
				it_popup != popups.end(); ++it_popup)
			{
				// draw sprite
				texture.loadFromFile(it_popup->image_path);
				sprite.setTexture(texture);
				it_popup->size = {
					(float)texture.getSize().x * it_popup->scale.x,
					(float)texture.getSize().y * it_popup->scale.y };
				sprite.setPosition(it_popup->position);
				sprite.setScale(it_popup->scale);
				window.draw(sprite);
				// draw text
				text.setPosition(it_popup->position + Vector2f{ 60,50 });
				text.setString(it_popup->message);
				window.draw(text);
				// draw buttons
				for (vector<PopUp_Button>::iterator it_popup_buttons = it_popup->popup_buttons.begin();
					it_popup_buttons != it_popup->popup_buttons.end(); ++it_popup_buttons)
				{
					ComputerButtons::Draw_Button(window, *it_popup_buttons);
				}
			}
		}

		string PopUpImagePath(const PopUp_class& popup_class)
		{
			switch (popup_class)
			{
			case Interface::PopUps::PopUp_class::Message:
				return "sprites\\ui\\Computer Interface\\popup-System message.png";
			case Interface::PopUps::PopUp_class::Success:
				return "sprites\\ui\\Computer Interface\\popup-Success.png";
			case Interface::PopUps::PopUp_class::Error:
				return "sprites\\ui\\Computer Interface\\popup-Fatal Error.png";
			case Interface::PopUps::PopUp_class::Information:
				return "sprites\\ui\\Computer Interface\\popup-Informaition.png";
			case Interface::PopUps::PopUp_class::Warning:
				return "sprites\\ui\\Computer Interface\\popup-Warning.png";
			default:
				return "sprites\\ui\\Computer Interface\\popup-System message.png";
			}
		}
	}

// Only CheckBoxes functions
	namespace CheckBoxes
	{
		void CheckBoxesUpdate()
		{
			for (const string& area : areas_loaded)
				for (map<string,CheckBox>::iterator it_checkbox = checkboxes[area].begin();
				it_checkbox != checkboxes[area].end(); ++it_checkbox)
			{
				it_checkbox->second.update();

				if (it_checkbox->second.pressed)
				{
					it_checkbox->second.pressed_frames++;
				}

				//if (it_checkbox->second.checked == true)
				//	cout << it_checkbox->first << " - true" << endl;
				//if (it_checkbox->second.checked == false)
				//	cout << it_checkbox->first << " - false" << endl;

			}
		}

		void Draw_CheckBoxes(RenderWindow& window)
		{
			Sprite sprite;
			Texture texture;
			texture.loadFromFile("sprites\\ui\\Computer Interface\\check box.png");
			sprite.setTexture(texture);
			sprite.setScale(InterfaceData::standart_scale);
			sprite.setTextureRect({ 0,0,9,9 });
			for (const string& area : areas_loaded)
			for (map<string, CheckBox>::iterator it_checkbox = checkboxes[area].begin();
				it_checkbox != checkboxes[area].end(); ++it_checkbox)
			{
				if (it_checkbox->second.pressed)
				{
					if (it_checkbox->second.checked == false)
						sprite.setTextureRect({9,0,9,9});
					if (it_checkbox->second.checked == true)
						sprite.setTextureRect({27,0,9,9});
				}
				else
				{
					if (it_checkbox->second.checked == false)
						sprite.setTextureRect({ 0,0,9,9 });
					if (it_checkbox->second.checked == true)
						sprite.setTextureRect({ 18,0,9,9 });
				}
				sprite.setPosition(it_checkbox->second.position+InterfaceData::interface_pos);
				window.draw(sprite);
			}
		}
		
		void AddCheckBox(const string& area, const string& checkbox_name, const Vector2f& pos)
		{
			checkboxes[area][checkbox_name].checked = false;
			checkboxes[area][checkbox_name].size = { 9, 9 };
			checkboxes[area][checkbox_name].position = pos;
			// InterfaceData::standart_scale ЗАДАЕТСЯ В Draw checkboxes[area][checkbox_name].scale не используется в Draw
			checkboxes[area][checkbox_name].scale = InterfaceData::standart_scale;
		}
	}

// Only Text functions
	namespace TextBoxes 
	{

	}

   // Only Sliders functions
	namespace Sliders
	{
		// TODO: Add slider loader and slider unloader to enable and disable slider, when needed
		void Update_Sliders()
		{
			for (map<string, Slider>::iterator it_slider = sliders.begin();
				it_slider != sliders.end(); it_slider++)
			{
				if (!it_slider->second.loaded)continue;
				it_slider->second.update();

			   // moving slider
				if (it_slider->second.pressed)
				{
				   // setting position
					it_slider->second.slider_pos = int(((float)mouse_pos.y - it_slider->second.clicked_pos)/2)*2;

				   // limiting slider by an upper bound
					if (it_slider->second.slider_pos < it_slider->second.position.y)
						it_slider->second.slider_pos = it_slider->second.position.y;
					
				   // limiting slider by a bottom bound
				   //TODO: replace (it_slider->second.slider_height/2) by mesured slider's height
					if (it_slider->second.slider_pos + it_slider->second.size.y * it_slider->second.scale.y + 8 >
						it_slider->second.position.y + it_slider->second.slider_height*it_slider->second.scale.y)
						it_slider->second.slider_pos = it_slider->second.position.y    + 
													   it_slider->second.slider_height *
													   it_slider->second.scale.y       - 8 -
													   it_slider->second.size.y * it_slider->second.scale.y;
					cout << it_slider->second.slider_pos - it_slider->second.position.y << ' ' << it_slider->second.position.y <<
						' ' << it_slider->second.slider_height << endl;
				}
			}
		}

		void Draw_Slider_Background(RenderWindow& window, const Slider& slider)
		{
		   // background image
			Image img;
		   // backround texture & sprite
			Texture txtr;
			Sprite spr;

			img.create(11, slider.slider_height, { 111, 111, 111 });

			txtr.loadFromImage(img);

			spr.setTexture(txtr);
			spr.setPosition(slider.position + Interface::InterfaceData::interface_pos);
			spr.setScale(slider.scale);

			window.draw(spr);
		}

		void Draw_Slider(RenderWindow& window, const Slider& slider)
		{
		   // image-donor
			Image img;
		   // completed image
			Image img_slider;
		   // slider's texture & sprite
			Texture txtr;
			Sprite spr;
		   // counter of img's Y pixels 
			int y = 0;
		   // temp var for easier code
			float slider_height = slider.size.y;

		   // setting image-donor
			img.loadFromFile(slider.image_path);
		   // setting img_slider temporary image
			img_slider.create(11, 4 + slider_height);

		   // making completed image
			for (int img_x = 0;
				 y < slider_height+4; img_x++)
			{
				if (img_x > img.getSize().x / 2)
				{
					img_x = 0;
					y++;
				}
				if(y < 2 || y > slider_height+1)
				{
					img_slider.setPixel(img_x, y, 
						img.getPixel(img_x + (img.getSize().x / 2) * slider.pressed, 
							         y > slider_height + 1 ? y - slider_height+1 : y));
				}
				else
				{
					img_slider.setPixel(img_x, y, 
						img.getPixel(img_x + (img.getSize().x / 2) * slider.pressed, 2));
				}
			}

			txtr.loadFromImage(img_slider);
			spr.setTexture(txtr);

			spr.setPosition(Vector2f{ slider.position.x, slider.slider_pos } + Interface::InterfaceData::interface_pos);
			spr.setScale(slider.scale);

			window.draw(spr);
			
		}
	   // translate depending on the coefficient
		void Translate(float& obj_pos)
		{

		}

		void Draw_Sliders(RenderWindow& window)
		{
			for (map<string, Slider>::iterator it_slider = sliders.begin();
				it_slider != sliders.end(); it_slider++)
			{
				if (!it_slider->second.loaded)continue;
				Draw_Slider_Background(window, it_slider->second);
				Draw_Slider(window, it_slider->second);
			}
		}
		
		void AddSlider(string index, Vector2f pos, float slider_height, float slider_koef,
			Vector2f scale)
		{
			Slider slider;
			slider.position = pos;
			slider.slider_height = slider_height;
			slider.translation_koef = slider_koef;
			slider.scale = scale;
		   // slider size (movable element)
		   // TODO: remove size param, the size will be calculated depending on the page size.
			slider.size = Vector2f{ 11, 51 };
			
			sliders[index] = slider;
		}
	}

// Only MovaableElements functions
	namespace MoveEl
	{
	   // Click aNd Drop
		namespace CND
		{
			bool IsInHead(const UIMovableElement::Vfr head)
			{
				return CollisionPointRect({ (float)mouse_pos.x, (float)mouse_pos.y }, {head.pos,head.size});
			}

			bool Update(UIMovableElement* me)
			{

				me->hovered = false;
				Vector2f m_pos = Vector2f{ (float)mouse_pos.x,(float)mouse_pos.y };
				Vector2f m_pos_old = Vector2f{ (float)mouse_pos_old.x,(float)mouse_pos_old.y };
				if (IsInHead(me->head))
				{
					mouse_state = MouseState::Hovering;
					me->hovered = true;
					if (!me->clicked && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
						me->clicked = true;
					else if (me->clicked && ImGui::IsMouseDown(ImGuiMouseButton_Left))
					{
						me->drag = true;
						me->m_offset = m_pos - me->position;
					}
					else if (me->clicked && !ImGui::IsMouseDown(ImGuiMouseButton_Left))
					{
						me->drag = false;
						me->clicked = false;
						me->m_offset = { 0,0 };
					}
				}
				if (me->drag)
				{
					me->position = me->position + m_pos - m_pos_old;
					for (int i = 0; i < me->buttons.size(); i++)
					{
						me->buttons[i].position = me->position + me->buttons[i].button_offset;
					}
					return true;
				}

				return false;
			}
		}
		
		// general update function
		bool update_ME(UIMovableElement* me)
		{
			// move head to element position
			me->head.pos = me->position + Vector2f{0,4};
			// updating size of header
			me->head.size.y = 20 * me->scale.y;

			return CND::Update(me);
		}

		string getMEButtonPressed(string id)
		{
			for (map<string, UIMovableElement>::iterator it_mes = movls.begin();
				it_mes != movls.end(); it_mes++)
			{
				if (it_mes->first == id)
					for (int i = 0; i < it_mes->second.buttons.size(); i++)
					{
						if (it_mes->second.buttons[i].pressed)
							return it_mes->second.buttons[i].button_name;
					}
			}
			return "";
		}


		void Update_MovableElements()
		{
			for (map<string, UIMovableElement>::iterator it_mes = movls.begin();
				it_mes != movls.end(); it_mes++)
			{

				for (vector<UIMEButton>::iterator it_button = it_mes->second.buttons.begin();
					it_button != it_mes->second.buttons.end(); ++it_button)
				{
					it_button->update();

					if (it_button->active && it_button->pressed &&
						it_button->pressed_frames > it_button->frames_for_pressing / 2 &&
						(it_button->button_name == "ok" || it_button->button_name == "close" ||
							it_button->button_name == "cancel"))
					{
						movls.erase(it_mes);
						break;
					}
				}
				
				if (update_ME(&it_mes->second))break;
			}
		}

		void Draw_MoveEl(RenderWindow& window)
		{
			Texture texture;
			Sprite spr;
			
			for (map<string, UIMovableElement>::iterator it_mes = movls.begin();
				it_mes != movls.begin(); it_mes++)
			{
				texture.loadFromFile(it_mes->second.image_path);
				spr.setTexture(texture);
				spr.setTextureRect({ 0,0,(int)texture.getSize().x,(int)texture.getSize().y });
				spr.setPosition(it_mes->second.position);
				spr.setScale(it_mes->second.scale);
				it_mes->second.head.size = { 
					(float)texture.getSize().x * it_mes->second.scale.x-10,
					(float)texture.getSize().y * it_mes->second.scale.y };

				window.draw(spr);
				for (vector<UIMEButton>::iterator it_button = it_mes->second.buttons.begin();
					it_button != it_mes->second.buttons.end(); ++it_button)
				{
					ComputerButtons::Draw_Button(window, *it_button);
				}
			}

		}



		void AddMoveEl(const string index, const Vector2f pos, string text, const string image_path,
			vector<UIMEBTNSettings> buttons_settings, Vector2f scale)
		{
			UIMovableElement me;
			vector<UIMEButton> me_buttons;
			UIMEButton me_temp_button;
			float sizeX = 0, sizeY = 0;

			me_temp_button.scale = scale;

			bool ok_setting = false;

			for (int i = 0; i < buttons_settings.size(); i++)
			{
				string setting = buttons_settings[i].setting_name;
				me_temp_button.button_name = setting;
				me_temp_button.active = buttons_settings[i].active;

				//Setting buttons params
				if (setting == "ok")
				{
					me_temp_button.button_offset = Vector2f{ 200,100 };
					me_temp_button.image_path = "sprites\\ui\\Computer Interface\\ok.png";
					me_temp_button.size = { 28,15 };
					me_buttons.push_back(me_temp_button);

					ok_setting = true;
				}
				if (setting == "close")
				{
					me_temp_button.button_offset = Vector2f{ 224,-20 };
					if(me_temp_button.active)
						me_temp_button.image_path = "sprites\\ui\\Computer Interface\\X.png";
					else
						me_temp_button.image_path = "sprites\\ui\\Computer Interface\\X_unactive.png";
					me_temp_button.size = { 15,15 };
					me_buttons.push_back(me_temp_button);
				}
				if (setting == "cancel")
				{
					// updating "ok_button" if there is "cancel_button"
					if (ok_setting) for (int i = 0; i < me.buttons.size(); i++)
						if (me.buttons[i].button_name == "ok")
							me.buttons[i].position = { 180,100 };

					me_temp_button.button_offset = Vector2f{ 200, 100 };
					if (me_temp_button.active)
						me_temp_button.image_path = "sprites\\ui\\Computer Interface\\cancel.png";
					else
						me_temp_button.image_path = "sprites\\ui\\Computer Interface\\cancel_unactive.png";
					me_temp_button.size = { 37,15 };
					me_buttons.push_back(me_temp_button);
				}
			}


			me.text = text;
			me.drag = false;
			me.clicked = false;
			me.head.size = { sizeX, 50 * scale.y };
			me.position = pos;
			me.head.pos = pos;
			me.scale = scale;
			me.image_path = image_path;
			me.buttons = me_buttons;
			
			movls[index] = me;
		}
	}

// checkers

	bool IsAnyPopUpHovered()
	{
		for (vector<PopUps::PopUp>::iterator it_popup = PopUps::popups.begin();
			it_popup != PopUps::popups.end(); ++it_popup)
		{
			if (it_popup->popup_state == ElementsStates::Hovered)
			{
				return true;
			}
		}
		return false;
	}

	bool IsAnyMovableElementHovered()
	{
		for (map<string, UIMovableElement>::iterator me_it = movls.begin();
			me_it != movls.end(); me_it++)
		{
			if (me_it->second.hovered)
				return true;
		}
		return false;
	}

// Show all UI elements
	void Show(RenderWindow& window)
	{
		ConvexShape cs;
		cs.setPointCount(4);
		cs.setPoint(0, { InterfaceData::interface_pos });
		cs.setPoint(1, { InterfaceData::interface_pos + Vector2f{InterfaceData::interface_size.x, 0} });
		cs.setPoint(2, { InterfaceData::interface_pos + InterfaceData::interface_size });
		cs.setPoint(3, { InterfaceData::interface_pos + Vector2f{0, InterfaceData::interface_size.y} });
		cs.setFillColor(BackGround::color);
		if (InterfaceData::ShowInterfaceBorder)
		{ cs.setOutlineColor(Color{ 255,0,255,120 }); cs.setOutlineThickness(4); }
		window.draw(cs);

		// draw decors
		UIDecor::DrawDecors(window);

		// draw buttons
		for (const string& area : areas_loaded)
		for (map<string, ComputerButton>::iterator it_buttons = buttons[area].begin(); it_buttons != buttons[area].end(); ++it_buttons)
		{
			ComputerButtons::Draw_Button(window, it_buttons->second);
		}

		// draw checkboxes
		CheckBoxes::Draw_CheckBoxes(window);

		// draw sliders
		Sliders::Draw_Sliders(window);

		// draw movable elements
		MoveEl::Draw_MoveEl(window);

		// draw lists
		List_functions::Draw_Lists(window);

		PopUps::Draw_PopUps(window);

	}

// Other setters, loaders and etc. (usfull functions)
	void Unload_Buttons(string area)
	{
		cout << "Clean buttons:" << endl;
		for (map<string, ComputerButton>::iterator it_buttons = buttons[area].begin();
			it_buttons != buttons[area].end(); ++it_buttons)
		{
			it_buttons->second.pressed_frames = it_buttons->second.frames_for_pressing;
			auto it = InterfaceData::GetButtonPressed(it_buttons->first);
			if(it != InterfaceData::buttons_pressed.end())
			{
				cout << "-[\"" << *it << "\"]" << endl;
				InterfaceData::buttons_pressed.erase(it);
			}

		}
	}

	void Add_Button(string area, string button_name, string image_path, Vector2f position = { 0,0 }, Vector2f scale = { 1,1 })
	{
		buttons[area][button_name].image_path = image_path;
		buttons[area][button_name].position = {
										position.x * scale.x,
										position.y * scale.y };
		buttons[area][button_name].scale = scale;
	}

	void PrintListOfButtons()
	{
		cout << "Buttons Loaded:" << endl;
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

	void SetInterfacePos(Vector2f position)
	{
		InterfaceData::interface_pos = position;
	}

	void Load_Area(string area)
	{
		bool found_area = false;
		for (vector<string>::iterator it_area = areas_loaded.begin(); it_area != areas_loaded.end(); ++it_area)
		{
			if (*it_area == area)
				found_area = true;
		}
		if (!found_area)
		{
			areas_loaded.push_back(area);
			buttons_areas_loaded.push_back(area);
		}
	}
	void UnLoad_Area(string area)
	{
		for (vector<string>::iterator it_area = areas_loaded.begin(); it_area != areas_loaded.end(); ++it_area)
		{
			if (*it_area == area)
			{
				Interface::Unload_Buttons(*it_area);
				areas_loaded.erase(it_area);
				return;
			}
		}
	}
	void UnLoad_All_Areas()
	{
		for (vector<string>::iterator it_area = areas_loaded.begin(); it_area != areas_loaded.end();)
		{
			UnLoad_Area(*it_area);
		}
	}
	bool Is_Area_Loaded(string area)
	{
		for (vector<string>::iterator it_area = areas_loaded.begin(); it_area != areas_loaded.end(); ++it_area)
		{
			if (*it_area == area)
				return true;
		}
		return false;
	}
	void PrintAreasLoaded()
	{
		cout << "Areas Loaded:" << endl;
		for (vector<string>::iterator it_area = areas_loaded.begin(); it_area != areas_loaded.end(); ++it_area)
		{
			cout << "-[\"" << *it_area << "\"]" << endl;
		}
	}
}