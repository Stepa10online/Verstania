#pragma once

#include "Structs.h"
#include "Enums.h"

// |    GLOBAL VARIABLE
// |    Если ошибка в дркументах присутствует, то mistake == true
bool mistake = false; 
// |    GLOBAL VARIABLE
bool qr_scanner_check = false;
// |    GLOBAL VARIABLE
int global_day = 28, global_month = 11, global_year = 2024;
// |    GLOBAL VARIABLE
StructSettings settings{ false, 20, 20 };
// |    GLOBAL VARIABLE
game_status current_game_status = game_status::game_Intro;

// DEBUG DATA
bool only_mistakes = false;
// DEBUG DATA
bool no_mistakes = false;
