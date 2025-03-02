#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <windows.h>
#include <shellapi.h>
using namespace sf;
using namespace std;
#include "ScriptCharacter.h"
#include "Collision.h"
#include "Peasant.h"
#include "Days.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

////////////////////////////////////////////////////////////// INTERACTION ELEMENTS

#include "UI elements.h"

////////////////////////////////////////////////////////////// SETTERS

#include "Docs setters.h"

////////////////////////////////////////////////////////////// INTERFACE

void Intro(RenderWindow& window)
{

    Clock ImGuiClock;
    bool opened = true;


    int screen_number = 0;
    bool Next_screen = false;
    while (opened)
    {
        Event game_event;
        while (window.pollEvent(game_event))
        {
            ImGui::SFML::ProcessEvent(game_event);
        }
        ImGui::SFML::Update(window, ImGuiClock.restart());

        if (Next_screen) { screen_number++; Next_screen = false; }

        window.clear();
        switch (screen_number)
        {
        case 0:
            MyText({ 450,400 }, L"                  Добро пожаловать.\nПрошу, перед началом игры настройте все параметры.", window, 50);
            break;
        case 1:
            MyText({ 450,400 }, L"Громкость", window, 50);
            MyButton({ 400,500 }, { 90, 70 }, L"-5", window);
            MyButton({ 600,500 }, { 90, 70 }, L"+5", window);
        default:
            break;
        }
        
        if (MyButton({ 1700,900 }, { 200, 70 }, L"Дальше " +to_wstring(screen_number), window) == 2)
        {
            Next_screen = true;
            if(screen_number >= 3)
            {
                settings.intro_played = true;
                FileManager::SaveSettings("saves\\settings.txt", settings);
                return;
            }
        }
        ImGui::SFML::Render(window);
        window.display();
    }
}
int DayChoosing(RenderWindow& window)
{
    Clock ImGuiClock;
    bool opened = true;
    //int days_enabled = Day::getEnabledDays();
    int days_enabled = 5;

    if (Keyboard::isKeyPressed(Keyboard::Escape) || (Keyboard::isKeyPressed(Keyboard::LAlt) && Keyboard::isKeyPressed(Keyboard::F4))){
        current_game_status = game_status::game_Main_Menu;
        return -1;
    }
        

///////////// Общий фон
    Texture t;
    Sprite s;
    t.loadFromFile("day choose.png");
    s.setTexture(t);
    s.setScale(4, 4);

///////////// Кнопки
    Vector2f btn_size = { 150, 80 };
    Vector2f btn_pos = { -10, 400 };
    wstring day_label = L"Day ";
    float interval = 50;

    window.clear();
    for (int i = 0; i < 8; i++)
    {
        if (i >= days_enabled)
            break;
            
        /// Задавание кнопок

        btn_pos.x += btn_size.x + 47;

        if (i == 6) // Последний уровень
        {
            day_label = L"Продолжение следует...";
            btn_size.x = 460;
        }
        else
            day_label = L"Day " + to_wstring(i+1);
            

        if (MyButton(btn_pos, btn_size, day_label, window, {0,5}) == 2)
        {
            if(i == 6)
            {
                ShellExecute(0, 0, L"https://t.me/OnlineRecycleBin", 0, 0, SW_SHOW);
            }
            else
            {
                current_game_status = game_status::game_Game;
                return (i + 1);
            }
        }

        if (i < days_enabled-1)
            for (int j = 0; j < 10; j++)
            {
                RectangleShape rect;
                rect.setSize(Vector2f{ 2.5, 2.5 });
                rect.setPosition(btn_pos + Vector2f{ btn_size.x, btn_size.y / 2 - rect.getSize().y } + Vector2f{ rect.getSize().x * 2 * j, 0 });
                window.draw(rect);
            }
    }

    window.draw(s);
    ImGui::SFML::Render(window);
    window.display();

    return -1;
}

////////////////// SETTERS

void days_setter(int day, vector<ScriptCharacter>& script_characters)
{
    cout << "[DEBUG function] days_setter. day: " << day << endl;
    switch (day)
    {
    case 0:
        cout << "INFINIT MODE";
        break;
    case 1:
    {
        wcout << L"Нео Гвардовски" << endl;
        ScriptCharacter sc;
        sc.GetPeasant().setName(L"Нео");
        sc.GetPeasant().setSurname(L"Гвардовски");
        sc.GetPeasant().setCountry(L"verstania");
        sc.GetPeasant().setBirth(L"1964.06.24");
        sc.GetPeasant().setSex(L"M");
        sc.GetPeasant().setTown(L"Юж.Верстанск");
        sc.setQueueTime(10);
        script_characters.push_back(sc);
        for (int i = 0; i < script_characters.size(); i++)
        {
            wcout << ">| " << script_characters[i].GetPeasant().getName() << endl;
        }

        break;
    }
    case 2:
    {

        wcout << L"Степан Джонат" << endl;
        ScriptCharacter sc;
        sc.GetPeasant().setName(L"Степан");
        sc.GetPeasant().setSurname(L"Джонат");
        sc.setQueueTime(30);
        script_characters.push_back(sc);

        wcout << L"Алекс Костав" << endl;
        sc.GetPeasant().setName(L"Алекс");
        sc.GetPeasant().setSurname(L"Костав");
        sc.setQueueTime(60);
        script_characters.push_back(sc);
        for (int i = 0; i < script_characters.size(); i++)
        {
            wcout << ">| " << script_characters[i].GetPeasant().getName() << endl;
        }
        break;
    }
    case 3:
    {
        cout << "3 day" << endl;
        break;
    }
    default:
        cout << "default" << endl;
        break;
    }

}
