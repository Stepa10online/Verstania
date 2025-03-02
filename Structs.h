#pragma once
#include "vector"
#include "iostream"
using namespace std;
struct StructParametrs
{
    int money = 0;
    ///
    /// -1  - hard mode
    ///  0  - normal mode
    ///  1  - easy mode
    ///
    int Gov_rep = 0;
    int USR_rep = 0;
    bool terrorist_arrested = false;
    bool Maktrahen_arrested = false;
};

struct StructDay
{
    bool enabled = false;
    StructParametrs all_parametrs = {};
    static float days_timer[30];
};
float StructDay::days_timer[] = {
        5 * 60.0, // 5 mins
        6 * 60.0, // 6 mins
        4 * 60.0, // 4 mins
        7 * 60.0, // 7 mins
        8 * 60.0, // 8 mins
        9 * 60.0, // 9 mins
};

///
/// mus_vol
/// sfx_vol
/// easy_mode
///
struct StructSettings
{
    bool fullscreen = false;
    unsigned int mus_vol = 0;
    unsigned int sfx_vol = 0;
    bool easy_mode = false;
    bool intro_played = false;
    bool tutorial_passed = false;
};

struct Towns
{
    static vector<wstring> Verstania;
    static vector<wstring> MPDR;
    static vector<wstring> Orban;
    static vector<wstring> Righter;
    static vector<wstring> USR;
    static vector<wstring> Neitral;
};
vector<wstring> Towns::MPDR = {
       L"Западный ГНДР", L"Восточный ГНДР",
       L"Северный кратор", L"Южный кратор",
       L"Центральные области", L"Островные регионы",
};
vector<wstring> Towns::Verstania = {
       L"Юж. Верстанск", L"Сев. Печград",
       L"Вост. Сундукс", L"Зап. Компостск",
       L"Центр. Верстанск", L"Лесной регион",
       L"Внеш. Кольцо", L"Внут. Кольцо" };

vector<wstring> Towns::Orban = {
       L"Благоухальск", L"Фермонтан",
       L"Октиран", L"Мухопраснк",
       L"Культ. Центр", L"Древнеград",
       L"Струнал", L"Пладольск",
       L"Горр", L"Шлак",
       L"Критиг", L"Корак",
       L"Зодник", };
vector<wstring> Towns::USR = {
       L"U_1", L"U_2",
       L"U_3", L"U_4",
       L"U_5", L"U_6",
       L"U_7", L"U_8",
       L"U_9", L"U_10", };
vector<wstring> Towns::Righter = {
       L"Гл. Обл.", L"Мл. Обл.",
       L"Второстеп. Обл.", L"Гл. Кольцо Связи",
       L"ЖД регион",  };
vector<wstring> Towns::Neitral = {
       L"N_1", L"N_2",
       L"N_3", L"N_4",
       L"N_5", L"N_6",
       L"N_7", L"N_8",
       L"N_9", L"N_10", };