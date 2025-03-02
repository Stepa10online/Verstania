#pragma once

//
// Mini functions that play a secondary role. (time translation, etc.)
//


#include "Collision.h"
#define _CRT_SECURE_NO_WARNINGS
#include "Peasant.h"
#define _CRT_SECURE_NO_WARNINGS
#include "SFML/Audio.hpp"

#define _CRT_SECURE_NO_WARNINGS

Clock pass_clock;
string getCurrentTime()
{
    time_t result = time(NULL);
    char str[26];
    ctime_s(str, sizeof str, &result);
    return str;
}
int translate(string month)
{
    const char* month_s[] = {
     "Jan","Feb", "Mar","Apr",
     "May","Jun","Jul","Aug",
     "Sep","Oct","Nov","Dec"
    };
    for (int i = 0; i < 12; i++)
    {
        if (month == month_s[i])
        {
            cout << month_s[i] << endl;
            return i + 1;
        }
    }

    return -1;
}



string setRandomPassData()
{
    string date = getCurrentTime();
    int current_day = stoi(date.substr(8, 2));

    //cout << date.substr(4, 3) << endl;
    int current_month = translate(date.substr(4, 3));
    int current_year = stoi(date.substr(20, 4));

    srand(pass_clock.getElapsedTime().asSeconds());
    int rd = rand() % 6;
    int rm = rand() % 20;
    int ry = rand() % 100;

    if (rd >= 3) current_day -= rd % 2 * (-1);
    if (rm >= 15) current_month -= rm % 2 * (-1);
    if (ry > 70) { current_year -= rd % 2 * (-1); cout << "{!}" << current_year << endl; }
    int day = current_day;
    int month = current_month;
    int year = current_year;
    string s = to_string(current_day) + '.' + to_string(current_month) + '.' + to_string(current_year);

    return s;
}
bool show_newspaper(int day, Clock& anim_clock, RenderWindow& window)
{
    srand(time(NULL));
    float time = anim_clock.getElapsedTime().asSeconds();
    static Clock temp_clock;
    float temp_time = temp_clock.getElapsedTime().asSeconds();
    bool start_temp_clock = false;
    window.clear();
    //newspaper
    Texture texture;
    Texture texture_overlay;
    Sprite newspaper;
    Sprite overlay;
    SoundBuffer soundbuff;
    Sound sound;
    soundbuff.loadFromFile("sounds\\lamp turn on.mp3");
    sound.setBuffer(soundbuff);
    sound.setVolume(settings.sfx_vol);
    texture_overlay.loadFromFile("sprites\\ui\\newspaper overlay.png");
    if (temp_time < 2)
        texture_overlay.loadFromFile("sprites\\ui\\newspaper overlay dark.png");
    if (temp_time > 2 && temp_time < 2.5)
        sound.play();
    if(Keyboard::isKeyPressed(Keyboard::Enter))
        sound.play();
    overlay.setScale(4, 4);
    overlay.setTexture(texture_overlay);

    //button
    Vector2f btn_size = { 200, 110 };
    Vector2f btn_pos = { 1700, 870 };

    float x = smootherstep(0, 1.35, time);

    newspaper.setPosition((1 - x) * (-2000) + 400, 60);
    texture.loadFromFile("sprites\\newspapers\\VerstaniaTruth1.png");
    switch (day)
    {
    case 1:
        texture.loadFromFile("sprites\\newspapers\\VerstaniaTruth1.png");
        break;
    case 2:
        texture.loadFromFile("sprites\\newspapers\\VerstaniaTruth2.png");
        break;
    case 3:
        texture.loadFromFile("sprites\\newspapers\\VerstaniaTruth3.png");
        break;
    case 4:
        texture.loadFromFile("sprites\\newspapers\\VerstaniaTruth4.png");
        break;
    case 5:
        texture.loadFromFile("sprites\\newspapers\\VerstaniaTruth5.png");
        break;
    case 6:
        texture.loadFromFile("sprites\\newspapers\\VerstaniaTruth6.png");
        break;
    case 7:
        texture.loadFromFile("sprites\\newspapers\\VerstaniaTruth7.png");
        break;
    default:
        break;
    }
    newspaper.setTexture(texture);
    newspaper.setScale(4.5, 4.5);
    window.draw(newspaper);
    window.draw(overlay);
    if (time >= 1.35)
    {
        float black_time = time - 1.35;

        static Color color = { Uint8(0),Uint8(0),Uint8(0),255 };
        if (color.r >= 255)
            color = Color::White;
        else
            if (int(black_time * 100) % 2 == 0)
                color += Color{ Uint8(3),Uint8(3),Uint8(3),0 };
        float color_multiplier = smootherstep(0, 2, black_time);
        //cout << int(255*color_multiplier) << endl;
        static bool blacking = false;
        static bool blacked = false;
        if(MyButton(btn_pos, btn_size, L"Дальше", window, {25,24}, { Uint8(150 * color_multiplier), Uint8(150 * color_multiplier), Uint8(150 * color_multiplier),255 }) == 2)
                blacking = true;
        
        if (blacking)
        {
            static int a_color = 0;
            RectangleShape black_screen(Vector2f{ 1920,1080 });
            black_screen.setFillColor({ 0,0,0,Uint8(a_color) });
            a_color += 10;
            window.draw(black_screen);
            if (a_color > 255)
                blacked = true;
        }
        if (blacked)
        {
            anim_clock.restart();
            blacked = false;
            return true;
        }
    }
    window.display();
    return false;
}

enum Countries {
    VERSTANIA,
    ORBAN,
    RIGHTER,
    MPDR,
    USR,
    NEITRAL
};
Countries getEnumCountry(wstring country)
{
    if (country == L"verstania")
        return Countries::VERSTANIA;
    if (country == L"orban")
        return Countries::ORBAN;
    if (country == L"mpdr")
        return Countries::MPDR;
    if (country == L"righter")
        return Countries::RIGHTER;
    if (country == L"usr")
        return Countries::USR;
    if (country == L"neitral")
        return Countries::NEITRAL;
    //if(country == L"")
    //    return Countries::

    cout << "[ERROR] <getEnumCountry> No such country found: ";
    printf("%ls\n", country);

}