#pragma once

#include "Structs.h"
#include "Enums.h"

// |    GLOBAL VARIABLE
// |    Если ошибка в дркументах присутствует, то mistake == true
bool mistake = false; 
// |    GLOBAL VARIABLE
// |    (я не знаю зачем это здесь) #DELETELATER
// |    (все док-ты будут проверяться через сканер ИЛИ все документы будут сканироваться и заноситься в компьютер)
bool qr_scanner_check = false;
// |    GLOBAL VARIABLE
// |    Описывает текущий день, месяц, год
int global_day = 28, global_month = 11, global_year = 2024;
// |    GLOBAL VARIABLE
// |	Настройки user'a
StructSettings settings{ false, 20, 20 };
// |    GLOBAL VARIABLE
// |	Текущее состояние игры (глав меню, выбор уровня, осн. игра и тд)
game_status current_game_status = game_status::game_Intro;

// DEBUG DATA
// Включает режим, где у всех документов присутствует ошибка
bool only_mistakes = false;
// DEBUG DATA
// Включает режим, где у всех документов остутствует ошибки
bool no_mistakes = false;
