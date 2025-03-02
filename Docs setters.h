#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include "functions.h"
#include "Structs.h"
#include "Variables.h"
#include "all_docs.h"

const static int& foo(const vector<int&>& arr)
{

}


// Возвращает Индекс указанной страны
wstring CountryIndexSetter(Countries country)
{
    /* verstaina */ // fromat: { sim, num } ...-...
    /*   orban   */ // fromat: { sim }		sssss
    /*   mpdr    */ // fromat: { sim, num } (num)s -> 100P
    /*  righter  */ // fromat: { sim }      sssssss
    /*    usr    */ // fromat: { sim, num } U..S..R.
    /*  neitral  */ // fromat: { num }		nnnn
    wchar_t wletters[27] = L"ABCDEFGHIJKLMNOPQRSTUYWXYZ";
    wchar_t wnumbers[11] = L"0123456789";
    char letters[27] = "ABCDEFGHIJKLMNOPQRSTUYWXYZ";
    char numbers[11] = "0123456789";
    switch (country)
    {
    case VERSTANIA:
    {
        // ...-...
        wstring windex = L"";
        string index = "";
        for (int i = 0; i < 6; i++)
        {
            srand(i + time(NULL));
            if (i == 3)
            {
                windex += L'-';
            }
            if(rand()%2==0)
            {
                windex += wletters[rand() % 26];
            }
            else
            {
                windex += wnumbers[rand() % 10];
            }
        }
        cout << "[DEBUG] Index for verstania set: ";
        wprintf(L"%s\n", windex);
        return windex;
    }
    case ORBAN:
    {
        wstring windex = L"";
        for (int i = 0; i < 6; i++)
        {
            srand(i + time(NULL));
            windex += wletters[rand() % 26];
        }
        cout << "[DEBUG] Index for orban set: ";
        wprintf(L"%s\n", windex);
        return windex;
    }
    case RIGHTER:
        break;
    case MPDR:
        break;
    case USR:
        break;
    case NEITRAL:
        break;
    default:
        break;
    }
}

wstring getTown(Countries country, bool random = false)
{
    switch (country)
    {
    case VERSTANIA:
    {
        break;
    }
    case ORBAN:
        break;
    case RIGHTER:
        break;
    case MPDR:
        break;
    case USR:
        break;
    case NEITRAL:
        break;
    default:
        break;
    }
    return L"";
}

wstring getRandomTown(int index, Countries country)
{
    switch (country)
    {
    case VERSTANIA: return Towns::Verstania[index];
    case ORBAN: return Towns::Orban[index];
    case RIGHTER: return Towns::Righter[index];
    case MPDR: return Towns::MPDR[index];
    case USR: return Towns::USR[index];
    case NEITRAL: return Towns::Neitral[index];
    }
}
wstring getRandomTown(int index, wstring exclude_town, Countries country)
{
    wstring town = L"";
    switch (country)
    {
    case VERSTANIA: 
        town = Towns::Verstania[index];
        index-- > 0 ? index-- : index++;
        return town == exclude_town ? town : Towns::Verstania[index];
    case ORBAN:     
        town = Towns::Orban[index];
        index-- > 0 ? index-- : index++;
        return town == exclude_town ? town : Towns::Orban[index];
    case RIGHTER:   
        town = Towns::Righter[index];
        index-- > 0 ? index-- : index++;
        return town == exclude_town ? town : Towns::Righter[index];
    case MPDR:      
        town = Towns::MPDR[index];
        index-- > 0 ? index-- : index++;
        return town == exclude_town ? town : Towns::MPDR[index];
    case USR:       
        town = Towns::USR[index];
        index-- > 0 ? index-- : index++;
        return town == exclude_town ? town : Towns::USR[index];
    case NEITRAL:   
        town = Towns::Neitral[index];
        index-- > 0 ? index-- : index++;
        return town == exclude_town ? town : Towns::Neitral[index];
    }
}

Countries getRandomCountry()
{
    switch (rand()%6)
    {
    case 0: return Countries::VERSTANIA;
    case 1: return Countries::ORBAN;
    case 2: return Countries::RIGHTER;
    case 3: return Countries::MPDR;
    case 4: return Countries::USR;
    case 5: return Countries::NEITRAL;
    default: break;
    }
}

int getTownsAmount(Countries country)
{
    switch (country)
    {
    case VERSTANIA: return Towns::Verstania.size();
    case ORBAN: return Towns::Orban.size();
    case RIGHTER: return Towns::Righter.size();
    case MPDR: return Towns::MPDR.size();
    case USR: return Towns::USR.size();
    case NEITRAL: return Towns::Neitral.size();
    }
}
void setPass(int, int, int, bool);
void setRight(int,int,int,bool);

void Papers_setter(int day, int month, int year,int level_choosed, vector<Document>& docs)
{
    int seed = time(NULL);
    int day_in_papers = (global_day + day) > 30 ? day : (global_day + day);
    int month_in_papers = (global_day + day) > 30 ? global_month + 1 : global_month;
    int year_in_papers = year;
    int list_index = rand() % 23;
    int purpose_list_index = rand() % 3;
    int duration_list_index = rand() % 10;

    wstring wrong_index = L"!!!!!!";
    wstring name = Peasant::getNameList()[list_index].name;
    wstring surname = Peasant::getNameList()[list_index].surname;
    wstring sex = Peasant::getNameList()[list_index].sex;

    if (rand() % 2) Peasant::setData(Peasant::Country, L"verstania");
    else Peasant::setData(Peasant::Country, L"orban");
    int random_town_index = getTownsAmount(getEnumCountry(Peasant::getData().country));
    wstring town = getRandomTown(rand() % random_town_index, getEnumCountry(Peasant::getData().country));
    wstring index = CountryIndexSetter(getEnumCountry(Peasant::getData().country));


    cout << "[DEBUG] Setting right papers" << endl;

    srand(seed + 68127124874);

    Peasant::setData(Peasant::Name, name);
    Peasant::setData(Peasant::Surname, surname);
    Peasant::setData(Peasant::RightName, name);
    Peasant::setData(Peasant::RightSurname, surname);
    Peasant::setData(Peasant::Sex, sex);
    Peasant::setData(Peasant::Town, town);
    Peasant::setData(Peasant::Till, to_wstring(day_in_papers) + L"." + to_wstring(month_in_papers) + L"." + to_wstring(year_in_papers));
    Peasant::setData(Peasant::PassTill, to_wstring(day_in_papers) + L"." + to_wstring(month_in_papers) + L"." + to_wstring(year_in_papers));
    Peasant::setData(Peasant::RightPurpose, Peasant::getPurposeList()[purpose_list_index]);
    Peasant::setData(Peasant::RightDuration, Peasant::getDurationList()[duration_list_index]);
    Peasant::setData(Peasant::Index, index);
    Peasant::setData(Peasant::RightIndex, index);

    if (duration_list_index == 0) Peasant::setData(Peasant::RightPurpose, L"ПМЖ");
    setPass(day_in_papers, month_in_papers, year_in_papers, 0);
    setRight(day_in_papers, month_in_papers, year_in_papers, 0);

    // Допуск ошибки

    int r_is_mistake = rand() % 2;
    if(only_mistakes)
        r_is_mistake = 1;
    if(no_mistakes)
        r_is_mistake = 0;
    //cout << r_is_mistake << endl;
    if (r_is_mistake == 1)
    {
        mistake = true;
        int r_paper = rand() % 5;
        if (level_choosed < 2) if (r_paper == 2) r_paper = rand() % 2;       // если право до 2го дня
        if (level_choosed < 3) if (r_paper == 3) r_paper = rand() % 2;       // если qr код до 3го дня
        if (level_choosed > 1) if (r_paper == 1) r_paper += rand() % 2 - 1;  // если пропуск после 1го дня
        if (level_choosed == 3) if (r_paper == 0) r_paper = rand() % 4 + 1;   // если паспорт в 3й день
        cout << "[DEBUG] Mistake " << r_paper << " lvl: " << level_choosed << endl;

        switch (r_paper)
        {
        // passport
        case 0:
        {
            cout << "[DEBUG] passport mark" << endl;

            // updating random for different results
            srand(seed + 27384126583457);

            // getting what graph will contain mistake
            int r_graph = -1;
            if(day == 1) r_graph = rand() % 4;
            else r_graph = rand() % 7;
            switch (0 /*r_graph*/)
            {
            // До 1го дня
                // town
            case 0:
                cout << "[DEBUG] town mistake" << endl;
                if (rand() % 2)
                {
                        // берем случайную страну, которая может совпадать с предыдущей
                    Countries country = getRandomCountry(); 
                        // получаем количество городов в этой стране
                    int towns_amount = getTownsAmount(country);
                    cout << "towns_amount: " << towns_amount << endl;
                        // берем случайный город который НЕ будет совпадать с первоначальным городом "town"
                    wstring wrong_town = getRandomTown(rand()%towns_amount, town, country);
                    Peasant::setData(Peasant::Town, wrong_town);
                    cout << "Wrong town setted" << endl;

                }
                break;
                // till
            case 1:
                cout << "[DEBUG] till mistake" << endl;
                Peasant::setData(Peasant::Till,
                    to_wstring(abs(day_in_papers - rand() % 5)) + "." +
                    to_wstring(month_in_papers - rand() % 2 + 1) + "." +
                    to_wstring(year_in_papers - int((rand() % 10) / 10))
                );
                break;
                // photo
            case 2:
                cout << "[DEBUG] photo mistake" << endl;
                break;
                // sex
            case 3:
                cout << "[DEBUG] sex mistake" << endl;
                if(Peasant::getData().sex == L"M")
                    Peasant::setData(Peasant::Sex, L"W");
                else
                    Peasant::setData(Peasant::Sex, L"M");
                break;
            // После 1го дня
                // name&surname
            case 4: 
                cout << "[DEBUG] name&surname mistake" << endl;
                Peasant::setData(Peasant::Name, Peasant::getFalseNameList()[list_index].name);
                Peasant::setData(Peasant::Surname, Peasant::getFalseNameList()[list_index].surname);
                break;
                // index
            case 5: 
            {
                cout << "[DEBUG] index mistake" << endl;

                const wchar_t wletters[27] = L"ABCDEFGHIJKLMNOPQRSTUYWXYZ";
                const wchar_t wnumbers[11] = L"0123456789";
                wchar_t wsimbol = '!';
                if (rand() % 2)
                    wsimbol = wletters[rand() % 27];
                else
                    wsimbol = wnumbers[rand() % 11];
                int rand_num_for_index = -1;
                switch (getEnumCountry(Peasant::getData().country))
                {
                case VERSTANIA:
                    rand_num_for_index = rand() % 7;
                    break;
                case ORBAN:
                    rand_num_for_index = rand() % 6;
                    break;
                case RIGHTER:
                    rand_num_for_index = rand() % 8;
                    rand_num_for_index = 0;
                    break;
                case MPDR:
                    rand_num_for_index = rand() % 4;
                    rand_num_for_index = 0;
                    break;
                case USR:
                    rand_num_for_index = rand() % 9;
                    rand_num_for_index = 0;
                    break;
                case NEITRAL:
                    rand_num_for_index = rand() % 5;
                    rand_num_for_index = 0;
                    break;
                default:
                    cout << "[ERROR] (Passport > index > \"Country not found\")" << endl;
                    rand_num_for_index = 0;
                    break;
                }
                wrong_index = Peasant::getData().index;
                wrong_index[rand_num_for_index] = wsimbol;
                Peasant::setData(Peasant::Index, wrong_index);
                break;
            }
                // validation
            case 6:
                cout << "[DEBUG] validation mistake" << endl;
                break;
            default:
                break;
            }
            break;
        }
        // pass
        case 1:
        {
            cout << "[DEBUG] pass mark ";
            setPass(day_in_papers, month_in_papers, year_in_papers, 1);
        }   
        // right
        case 2:
        {
            cout << "[DEBUG] right mark" << endl;
            srand(seed + 6718435278651272);
            int r_graph = rand() % 6;
            r_graph = 4;
            switch (r_graph)
            {
            case 0: // name&surname
                cout << "[DEBUG] name&surname mistake" << endl;
                Peasant::setData(Peasant::RightName, Peasant::getFalseNameList()[list_index].name);
                Peasant::setData(Peasant::RightSurname, Peasant::getFalseNameList()[list_index].surname);
                break;
            case 1: // purpose
                cout << "[DEBUG] purpose mistake" << endl;
                break;
            case 2: // index
                cout << "[DEBUG] index mistake" << endl;

                break;
            case 3: // duration
                cout << "[DEBUG] duration mistake" << endl;
                break;
            case 4: // till
            {
                cout << "[DEBUG] till mistake " << endl;
                setRight(day_in_papers, month_in_papers, year_in_papers, 1);
                break;
            }
            case 5: // stamp
                cout << "[DEBUG] stamp mistake" << endl;
                break;
            default:
                break;
            }
            break;
        }
        // qr
        case 3:
        {
            cout << "[DEBUG] qrcode mark" << endl;
            srand(seed + 6718435278651272);
            int r_graph = rand() % 2;
            switch (r_graph)
            {
            case 0: // index
                cout << "[DEBUG] index mistake" << endl;
                break;
            case 1: // qr code
                cout << "[DEBUG] qr-code mistake" << endl;
                break;
            default:
                break;
            }
            break;
        }
        // etc
        case 4:
        {
            cout << "[DEBUG] etc... mark" << endl;
            break;
        }
        default:
            cout << "[DEBUG] Wrong mistake index " << r_paper << endl;
            break;
        }
    }
    else
    {
        cout << "[DEBUG] no mistakes" << endl;
        mistake = false;
    }
}

void setPass(int day_in_papers, int month_in_papers, int year_in_papers,  bool mistake)
{
    if (!mistake) // При ошибке будет < сегодняшней даты
    {
        wstring date = to_wstring(day_in_papers) + L":" + to_wstring(month_in_papers) + L":" + to_wstring(year_in_papers);
        Peasant::setData(Peasant::PassTill, date);
    }
    else
    {
        int r_day=0, r_month=0, r_year=0;
        switch (rand() % 3)
        {
        case 0:
            r_day = rand() % 10 - 4;
            if (r_day == 0) r_day--;
            break;
        case 1:
            r_month = rand() % 2 - 1;
            if (r_month == 0) r_month--;
            break;
        case 2:
            r_year = rand() % 3 - 2;
            if (r_year == 0) r_day--;
            break;
        }
        cout << r_day << ' ' << r_month << ' ' << r_year << endl;
        wstring date = to_wstring(day_in_papers + r_day) + L"." + to_wstring(month_in_papers + r_month) + L"." + to_wstring(year_in_papers + r_year);
        Peasant::setData(Peasant::PassTill, date);
    }
    
}
void setRight(int day_in_papers, int month_in_papers, int year_in_papers, bool mistake)
{
    if (!mistake) // При ошибке будет < сегодняшней даты
    {
        Peasant::setData(Peasant::RightTill, to_wstring(day_in_papers) + L"-" + to_wstring(month_in_papers) + L"-" + to_wstring(year_in_papers));
        return;
    }
    cout << "[DEBUG] right date: " << day_in_papers << ' ' << month_in_papers << ' ' << year_in_papers << endl;
    int r_day = rand() % 20 + 1;
    int r_month = rand() % 5 + 1;
    int r_year = rand() % 2 + 1;
    
    // 0 - только день
    // 1 - день и месяц
    // 2 - год
    int r_choose = rand() % 3;
    if(r_choose < 2)
    {
        if (day_in_papers - r_day < 0)
        {
            day_in_papers = 30 - r_day;
            month_in_papers--;
        }
        else
            day_in_papers -= r_day;
        if (r_choose == 1)
        {
            if (month_in_papers - r_month < 0)
            {
                month_in_papers = 12 - r_month;
                year_in_papers--;
            }
        }

    }
    else if(r_choose == 3)
        year_in_papers -= r_year;

    int design_mistake = rand() % 3;
    if (design_mistake > 0) // Ошибка в дате и/или ошибка в оформлении
    {
        if(design_mistake == 1) Peasant::setData(Peasant::RightTill, to_wstring(day_in_papers) + L"~" + to_wstring(month_in_papers) + L"-" + to_wstring(year_in_papers));
        if(design_mistake == 2) Peasant::setData(Peasant::RightTill, to_wstring(day_in_papers) + L"." + to_wstring(month_in_papers) + L"." + to_wstring(year_in_papers));
    }
    else
        Peasant::setData(Peasant::RightTill, to_wstring(day_in_papers) + L"-" + to_wstring(month_in_papers) + L"-" + to_wstring(year_in_papers));
}