#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Structs.h"
using namespace std;
namespace FileManager
{

    /////////////////////////////
    // When returns:
    // -1  - file isn't open
    //  0  - file ended
    //  1  - smth went wrong
    ////////////////////////////
    int wFillDays(vector<StructDay>& days)
    {
        wifstream file(L"TEST.txt");

        if (!file.is_open()) return -1;

        wstring data;
        while (1)
        {
            file >> data;
            if (file.eof()) return 1;
        }

        file.close();
    }

    void readdata(ifstream file, bool& face)
    {
        string data;
        file >> data;
        if (file.eof()) return;
        face = stoi(data);
    }
    int FillSettings(string file_name, StructSettings& sett)
    {

        ifstream file(file_name);

        if (!file.is_open()) return -1;

        string data = "";

        for (int i = 0; 1; i++)
        {
            file >> data;
            if (file.eof()) { file.close();  return 1; }

            if (data == "<intro_played>")
            {
                file >> data;
                sett.intro_played = stoi(data);
            }
            if (data == "<tutorial_passed>")
            {
                file >> data;
                sett.tutorial_passed = stoi(data);
            }
            if (data == "<mus_vol>")
            {
                file >> data;
                sett.mus_vol = stoi(data);
            }
            if (data == "<sfx_vol>")
            {
                file >> data;
                sett.sfx_vol = stoi(data);
            }
            if (data == "<easy_mode>")
            {
                file >> data;
                sett.easy_mode = stoi(data);
            }
            if (data == "<fullscreen>")
            {
                file >> data;
                sett.fullscreen = stoi(data);
            }
        }
        file.close();
    }
    int FillDays(string file_name, vector<StructDay>& days)
    {
        StructDay d;
        days[0] = d;

        ifstream file(file_name);

        if (!file.is_open()) return -1;

        string data;
        for (int i = 0; 1; i++)
        {
            file >> data;
            if (file.eof()) { file.close();  return 1; }

            if (data == "<new_day>")
                for (int j = 0; 1; j++)
                {
                    file >> data;
                    if (data == "<new_day>") break;
                    if (file.eof()) { file.close();  return 1; }

                    if (data == "<enabled>")
                    {
                        file >> data;
                        days[i].enabled = stoi(data);
                    }
                    if (data == "<gov_rep>")
                    {
                        file >> data;
                        days[i].all_parametrs.Gov_rep = stoi(data);
                    }
                    if (data == "<usr_rep>")
                    {
                        file >> data;
                        days[i].all_parametrs.USR_rep = stoi(data);
                    }
                    if (data == "<ter_arr>")
                    {
                        file >> data;
                        days[i].all_parametrs.terrorist_arrested = stoi(data);
                    }
                    if (data == "<mak_arr>")
                    {
                        file >> data;
                        days[i].all_parametrs.Maktrahen_arrested = stoi(data);
                    }
                }
        }

        file.close();
    }
    int SaveSettings(string file_name, StructSettings& sett)
    {
        ofstream out_file(file_name);
        
        if (!out_file.is_open()) return -1;
        
        out_file << "<intro_played> " << to_string(sett.intro_played) << endl;
        out_file << "<tutorial_passed> " << to_string(sett.tutorial_passed) << endl;
        out_file << "<mus_vol> " << to_string(sett.mus_vol) << endl;
        out_file << "<sfx_vol> " << to_string(sett.sfx_vol) << endl;
        out_file << "<easy_mode> " << to_string(sett.easy_mode) << endl;
        out_file << "<fullscreen> " << to_string(sett.fullscreen) << endl;
        
        out_file.close();
        return 0;
    }
    int SaveDays(string file_name, const vector<StructDay>& days, int days_enabled = 7)
    {
        ofstream file(file_name, ios_base::app);
        if (!file.is_open()) return -1;
        for (int i = 0; i < days_enabled; i++)
        {
            if (i >= days.size())
            {
                file << "<new_day>" << endl;
                file << "<enabled> " << to_string(0) << endl;
                file << "<gov_rep> " << to_string(0) << endl;
                file << "<usr_rep> " << to_string(0) << endl;
                file << "<ter_arr> " << to_string(0) << endl;
                file << "<mak_arr> " << to_string(0) << endl;
                continue;
            }
            file << "<new_day>" << endl;
            file << "<enabled> " << to_string(days[i].enabled) << endl;
            if (days[i].all_parametrs.Gov_rep != 0)
                file << "<gov_rep> " << to_string(days[i].all_parametrs.Gov_rep) << endl;
            if (days[i].all_parametrs.USR_rep != 0)
                file << "<usr_rep> " << to_string(days[i].all_parametrs.USR_rep) << endl;
            if (days[i].all_parametrs.terrorist_arrested != 0)
                file << "<ter_arr> " << to_string(days[i].all_parametrs.terrorist_arrested) << endl;
            if (days[i].all_parametrs.Maktrahen_arrested != 0)
                file << "<mak_arr> " << to_string(days[i].all_parametrs.Maktrahen_arrested) << endl;
            // ... etc
        }
        file.close();
        return 0;
    }
    int Save(string file_name, const vector<StructDay>& days, StructSettings& sett, int days_enabled = 7)
    {
        ofstream file(file_name);
        if (!file.is_open()) return -1;
        file << "<intro_played> " << to_string(sett.intro_played) << endl;
        file << "<tutorial_passed> " << to_string(sett.tutorial_passed) << endl;
        file << "<mus_vol> " << to_string(sett.mus_vol) << endl;
        file << "<sfx_vol> " << to_string(sett.sfx_vol) << endl;
        for (int i = 0; i < days_enabled; i++)
        {
            if (i >= days.size())
            {
                file << "<new_day>" << endl;
                file << "<enabled> " << to_string(0) << endl;
                file << "<gov_rep> " << to_string(0) << endl;
                file << "<usr_rep> " << to_string(0) << endl;
                file << "<ter_arr> " << to_string(0) << endl;
                file << "<mak_arr> " << to_string(0) << endl;
                continue;
            }
            file << "<new_day>" << endl;
            file << "<enabled> " << to_string(days[i].enabled) << endl;
            if (days[i].all_parametrs.Gov_rep != 0)
                file << "<gov_rep> " << to_string(days[i].all_parametrs.Gov_rep) << endl;
            if (days[i].all_parametrs.USR_rep != 0)
                file << "<usr_rep> " << to_string(days[i].all_parametrs.USR_rep) << endl;
            if (days[i].all_parametrs.terrorist_arrested != 0)
                file << "<ter_arr> " << to_string(days[i].all_parametrs.terrorist_arrested) << endl;
            if (days[i].all_parametrs.Maktrahen_arrested != 0)
                file << "<mak_arr> " << to_string(days[i].all_parametrs.Maktrahen_arrested) << endl;
            // ... etc
        }


        file.close();
        return 0;
    }

}