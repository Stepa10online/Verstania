#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <locale>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#define DEBUG false
//#define MOUSE_CHECK_POS

using namespace sf;
using namespace std;

#include "Game Data.h"

#include "Update_funcs.h"
#include "Game Functions.h"
#include "functions.h"
#include "Interface.h"
#include "Interface Updater.h"
#include "Interactions.h"
#include "Interaction handler.h"
#include "Selection.h"
#include "ScriptCharacter.h"

#include "Update Documents.h"

#include "Selection handler.h"

Vector2f offset = {0,0};
bool mouse_colliding = false;

float day_time = 240; // seconds

//global variables
Music mus;
SoundBuffer sound_buff;
Sound sound_eff_click;

map<string,Animation> animations;

game_status Game(int day, int level_choosed, RenderWindow& window);
game_status MainMenu(RenderWindow& window);
bool Settings(RenderWindow& window);
int DayChoosing(RenderWindow& window);

void SetButtons()
{
    float main_top_scale = 2;
    Interface::Add_Button("Load screen", "Log in", "sprites\\ui\\Computer Interface\\Log in.png", 
        { 170,80 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Load screen", "Exit system", "sprites\\ui\\Computer Interface\\Exit system.png", 
        { 155,105 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Main top", "Select Workspace", "sprites\\ui\\Computer Interface\\empty.png",
        { 0, 0 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Main top", "Database", "sprites\\ui\\Computer Interface\\Database.png", 
        { 63,0 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Main top", "Open", "sprites\\ui\\Computer Interface\\Open.png", 
        { 119,0 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Main top", "About", "sprites\\ui\\Computer Interface\\About.png",
        { 157,0 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Main top", "Exit", "sprites\\ui\\Computer Interface\\Exit.png", 
        { 203,0 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Documents page", "Passport", "sprites\\ui\\Computer Interface\\Passport.png", 
        { 5,36 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Documents page", "Pass", "sprites\\ui\\Computer Interface\\Pass.png", 
        { 5,55 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Documents page", "Right", "sprites\\ui\\Computer Interface\\Right.png", 
        { 5,74 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Documents page", "QR-code", "sprites\\ui\\Computer Interface\\QR-doc.png", 
        { 5,93 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Map page", "Load", "sprites\\ui\\Computer Interface\\Load.png", 
        { 6,22 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Map page", "Show", "sprites\\ui\\Computer Interface\\Show.png", 
        { 44,22 }, { main_top_scale,main_top_scale });
    Interface::Add_Button("Map page", "Scale", "sprites\\ui\\Computer Interface\\Scale.png", 
        { 84,22}, { main_top_scale,main_top_scale });

    Interface::PrintListOfButtons();
}

void SetCheckboxes()
{
    Interface::CheckBoxes::AddCheckBox("Load screen", "test", { 50,50 });
}

void SetLists()
{
    using namespace Interface;
    float main_top_scale = 2;
// Adding lists
    List_functions::AddList("List Workspace area", "List WorkspaceSelector", "sprites\\ui\\Computer Interface\\Workspace-list.png",
        { 0, 19 }, { 72, 47 }, { main_top_scale, main_top_scale });
    List_functions::AddList("List Open area", "List Open", "sprites\\ui\\Computer Interface\\Open-list.png", 
        { 119,19 }, {72,61}, { main_top_scale,main_top_scale });
    List_functions::AddList("List About area", "List About", "sprites\\ui\\Computer Interface\\About-list.png", 
        { 157,19 }, {71,46}, { main_top_scale,main_top_scale });
    List_functions::AddList("List Passport country area", "Passport country list", "sprites\\ui\\Computer Interface\\Countries for passport-list.png", 
        { 59,36 }, {58,91}, { main_top_scale,main_top_scale });
    List_functions::AddList("List Scale area", "Scale list", "sprites\\ui\\Computer Interface\\Scale-list.png",
        { 84,41 }, {40,34}, { main_top_scale,main_top_scale });
// List Workspace
    List_functions::AddButtonToList("List Workspace area", "List WorkspaceSelector", "Work", "sprites\\ui\\Computer Interface\\list-work.png",
        { 0,0 }, { 50, 10 }, { main_top_scale, main_top_scale });
    List_functions::AddButtonToList("List Workspace area", "List WorkspaceSelector", "Internet", "sprites\\ui\\Computer Interface\\list-internet.png",
        { 0,12 }, {50, 10}, { main_top_scale, main_top_scale });
// List Open
    List_functions::AddButtonToList("List Open area", "List Open", "Documents", "sprites\\ui\\Computer Interface\\list-documents.png",
        { 0,0 }, { 66,13 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Open area", "List Open", "Map", "sprites\\ui\\Computer Interface\\list-map.png",
        { 0,13 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Open area", "List Open", "Tasks", "sprites\\ui\\Computer Interface\\list-Tasks.png",
        { 0,26 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Open area", "List Open", "Scan", "sprites\\ui\\Computer Interface\\list-Scan.png",
        { 0,39 }, { 50,10 }, { main_top_scale,main_top_scale });
// List About
    List_functions::AddButtonToList("List About area", "List About", "Computer", "sprites\\ui\\Computer Interface\\list-Computer.png",
        { 0,0 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List About area", "List About", "Stamps", "sprites\\ui\\Computer Interface\\list-Stamps.png",
        { 0,13 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List About area", "List About", "Arrest", "sprites\\ui\\Computer Interface\\list-Arrest.png",
        { 0,26 }, { 50,10 }, { main_top_scale,main_top_scale });
// List Passport countries
    List_functions::AddButtonToList("List Passport country area", "List Passport country", "Verstania", "sprites\\ui\\Computer Interface\\list-Verstania.png",
        { 0,13*0 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Passport country area", "List Passport country", "MPDR", "sprites\\ui\\Computer Interface\\list-MPDR.png",
        { 0,13*1 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Passport country area", "List Passport country", "Righter", "sprites\\ui\\Computer Interface\\list-Righter.png",
        { 0,13*2 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Passport country area", "List Passport country", "Alpha-Sity", "sprites\\ui\\Computer Interface\\list-Alpha-Sity.png",
        { 0,13*3 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Passport country area", "List Passport country", "Orban", "sprites\\ui\\Computer Interface\\list-Orban.png",
        { 0,13*4 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Passport country area", "List Passport country", "Neitral", "sprites\\ui\\Computer Interface\\list-Neitral.png",
        { 0,13*5 }, { 50,10 }, { main_top_scale,main_top_scale });
// List Scale 
    List_functions::AddButtonToList("List Scale area", "List Scale", "50%", "sprites\\ui\\Computer Interface\\list-50%.png",
        { -1,9*0-2 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Scale area", "List Scale", "100%", "sprites\\ui\\Computer Interface\\list-100%.png",
        { -1,9*1-2 }, { 50,10 }, { main_top_scale,main_top_scale });
    List_functions::AddButtonToList("List Scale area", "List Scale", "200%", "sprites\\ui\\Computer Interface\\list-200%.png",
        { -1,9*2-2 }, { 50,10 }, { main_top_scale,main_top_scale });

    List_functions::PrintListsLoaded();
}

void SetDecors()
{
    float main_top_scale = 2;
    Interface::UIDecor::AddDecor("Main top", "Top bar", "sprites\\ui\\Computer Interface\\Decor\\Top Bar.png",
        { 168,0 }, { main_top_scale, main_top_scale });
    Interface::UIDecor::AddDecor("Main top", "Select Workspace", "sprites\\ui\\Computer Interface\\Decor\\Select Workspace.png",
        { 0,0 }, { main_top_scale,main_top_scale });
    Interface::UIDecor::AddDecor("Documents page", "Document page", "sprites\\ui\\Computer Interface\\Decor\\Documents page.png",
        { 0,19 }, { main_top_scale, main_top_scale });
    Interface::UIDecor::AddDecor("Map page", "Map page", "sprites\\ui\\Computer Interface\\Decor\\Map page.png",
        { 0,19 }, { main_top_scale, main_top_scale });
    Interface::UIDecor::AddDecor("Tasks page", "Tasks", "sprites\\ui\\Computer Interface\\Decor\\Tasks page.png",
        { 0,19 }, { main_top_scale,main_top_scale });
    
}

void SetInteractions()
{
    // Computer interface
    /*Interaction::AddElement(Interaction::Data::Area{ "list_select_workspace", 72,30,126,38,true,{255,0,255,75} });*/

    //Interaction::EditElement("list_select_workspace").CursorChanging = true;

   //Passport IE
    Interaction::AddElement(Interaction::Data::Area{ "passport-name&surname", 14,241,290,29,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-birth", 14,278,192,24,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-sex", 14,308,192,24,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-town", 14,340,192,24,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-till", 14,370,192,24,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-index", 212,401,92,32,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-photo", 212,284,92,116,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-country", 10,238,300,198,false });
    //Interaction::AddElement(Interaction::Data::Area{ "passport-bottom_part", 10,238,300,198,false });
    // PC
    //Interaction::AddElement(Interaction::Data::Area{ "PC-monitor", 0,0,300,500,true, Color{0,255,0,25} });
    //Interaction::AddElement(Interaction::Data::Area{ "PC-passport-name&surname", 14,241,290,29,false, Color{0,255,0,75} });
    //Interaction::AddElement(Interaction::Data::Area{ "PC-passport-birth", 14,278,192,24,false, Color{0,255,0,75} });
    //Interaction::AddElement(Interaction::Data::Area{ "PC-passport-sex", 14,308,192,24,false, Color{0,255,0,75} });
    //Interaction::AddElement(Interaction::Data::Area{ "PC-passport-town", 14,340,192,24,false, Color{0,255,0,75} });
    //Interaction::AddElement(Interaction::Data::Area{ "PC-passport-till", 14,370,192,24,false, Color{0,255,0,75} });
    //Interaction::AddElement(Interaction::Data::Area{ "PC-passport-index", 212,401,92,32,false, Color{0,255,0,75} });
    //Interaction::AddElement(Interaction::Data::Area{ "PC-passport-photo", 212,284,92,116,false, Color{0,255,0,75} });
    //Interaction::AddElement(Interaction::Data::Area{ "PC-passport-country", 10,238,300,198,false, Color{0,255,0,75} });

    //Interaction::Settings::CoutInteractionInfoString = true;
}

int main()
{
    vector<StructDay> days = { StructDay{},StructDay{},StructDay{},StructDay{},StructDay{},StructDay{},StructDay{} };
    cout << "Game started" << endl;
    FileManager::FillSettings("saves\\settings.txt", settings);
    cout << "Setting set" << endl;
    FileManager::FillDays("saves\\save.txt", days);

    // Setting Computer Interface
    Interface::SetInterfacePos({ 72,30 });
    Interface::InterfaceData::standart_scale = { 4,4 };
    SetButtons();
    SetCheckboxes();
    SetLists();
    SetDecors();
    Interface::MoveEl::AddMoveEl("1", { 100,100 }, "",
        Interface::PopUps::PopUpImagePath(Interface::PopUps::PopUp_class::Message),
        { {"ok", true}, {"close", false}, {"cancel", true}}, {2,2});
    Interface::Sliders::AddSlider("task-right_slider", { 710,92 }, 122, 1, { 2,2 });
    Interface::Sliders::AddSlider("task-left_slider", { 8,98 }, 122, 1, { 2,2 });
    // Loading first screen
    Interface::Load_Area("Load screen");

    // Setting Interactions
    SetInteractions();

    int style = settings.fullscreen == 1 ? Style::Fullscreen : 0;
    RenderWindow window(VideoMode(1920, 1080), "Welcome to VERSTANIA!",style);
    window.setFramerateLimit(75);
    ImGui::SFML::Init(window);
    

    

    if (settings.intro_played) current_game_status = game_status::game_Main_Menu;
    Clock ImGuiClock;
    Clock clock_timer_popup;

    float timer_popup = 0;

    int level_choosed = -1;

    sound_buff.loadFromFile("sounds\\click.wav");
    sound_eff_click.setBuffer(sound_buff);
    sound_eff_click.setVolume(settings.sfx_vol);

    mus.openFromFile("Papers please.mp3");
    mus.play();
    mus.setLoop(true);
    mus.setVolume(settings.mus_vol);


    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, ImGuiClock.restart());


        if (Interaction::GetElement(2).LastOperation == Interaction::Data::AreaState::Mouse_Left_Click)
            Interaction::EditElement(3, Interaction::Data::Params::Enabled, "1");
        if (Interaction::GetElement(2).LastOperation == Interaction::Data::AreaState::Mouse_Right_Click)
            Interaction::EditElement(3, Interaction::Data::Params::Enabled, "0");

        if (current_game_status == game_status::game_Main_Menu)
        {
            MainMenu(window);
            //cout << "MM" << endl;
        }
        else if (current_game_status == game_status::game_Day_choosing)
        {
            level_choosed = DayChoosing(window);
            //cout << "DC" << endl;
            cout << "LEVEL CHOOSED: " << level_choosed << endl;
            continue;
        }
        else if (current_game_status == game_status::game_Game)
        {
            int day = global_day + level_choosed > 31 ? global_day + level_choosed - 30 : global_day + level_choosed;
            Game(day,level_choosed, window);
            //cout << "Gm" << endl;
            continue;
        }


        window.clear();
#if DEBUG true
        Interaction::DrawAllElements(window);
#endif // Debug true
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
game_status MainMenu(RenderWindow& window)
{
    static bool settings_open = false;


    Animation anim;

    Color verst_sprite_color = { 255,255,255,0 };

    Texture t;
    Texture beta_scn_texture;

    Sprite s;
    Sprite beta_screen;


    Clock MoveClock;

    float move_timer = MoveClock.getElapsedTime().asSeconds();

    mus.setVolume(settings.mus_vol);

    anim.setTexture("sprites\\devices\\stamp accept pressed one.png");
    anim.setFrame({ 0,0,85,59 });
    anim.setFrameTime(0.08);
    anim.setAnimationStart(0);
    anim.setPosition({ 1751 - 170, 497 });
    anim.setScale({ 4, 4 });
    anim.setAnimationStep(1);

    animations["stamp_approving"] = anim;

    anim.setPosition({ 1751 - 170, 690 });
    anim.setTexture("sprites\\devices\\stamp denied pressed one.png");
    animations["stamp_denying"] = anim;

    t.loadFromFile("Verstania LOGO FF.png");

    s.setTexture(t);
    s.setScale(3, 3);
    s.setPosition(62, 30);
    s.setColor(verst_sprite_color);

    beta_scn_texture.loadFromFile("beta-screen-orig.png");
    beta_screen.setTexture(beta_scn_texture);
    beta_screen.setOrigin(beta_scn_texture.getSize().x / 2, beta_scn_texture.getSize().y / 2);
    beta_screen.setPosition(1920 / 2, 1080 / 2);
    beta_screen.setScale(4, 4);

    //mus.openFromFile("Glory To Verstania!.mp3");



    if (ImGui::Button("Start"))
            current_game_status = game_status::game_Day_choosing;

    if (ImGui::Button("Settings"))
    {
        settings_open = true;
        current_game_status = game_status::game_Day_choosing;
    }
    if (ImGui::Button("Exit"))
        window.close();
    if (settings_open)
        settings_open = Settings(window);

    ////////
    window.setMouseCursorVisible(true);
    window.draw(s);
    ////////
    return game_status::game_NULL;  
}

bool Settings(RenderWindow& window)
{
    static bool settings_changed = false;
    ImGui::SetNextWindowSize(ImVec2{ 400,400 });
    ImGui::Begin("Settings");
    for (int i = 0; i < 30; i++) { ImGui::Spacing(); ImGui::SameLine(); }
    if (ImGui::Button("[X]")) return false;
    if(ImGui::Checkbox("FullScreen", &settings.fullscreen)) settings_changed = true;
    if (ImGui::Button("640x480"))
        window.setSize(Vector2u{ 640,480 });
    ImGui::SameLine();
    if (ImGui::Button("1920x1080"))
        window.setSize(Vector2u{ 1920,1080 });
    int vol = settings.mus_vol;
    if (ImGui::SliderInt("Music volume", &vol, 0, 100)) settings_changed = true;
    settings.mus_vol = vol;
    vol = settings.sfx_vol;
    if(ImGui::SliderInt("Sound Effects volume", &vol, 0, 100))  settings_changed = true;
    settings.sfx_vol = vol;
    if(settings_changed == true)
        if (ImGui::Button("Save settings*"))
        {
            FileManager::SaveSettings("saves\\settings.txt", settings);
            settings_changed = false;
        }
    if (settings_changed == false)
        if (ImGui::Button("Save settings"))
            FileManager::SaveSettings("saves\\settings.txt", settings);

    ImGui::End();
    return true;
}
Passport passport;
Papers Right("sprites\\papers\\Right for arriving.png");
Pass pass(L"0.00.000");
vector<Document> docs;
vector<ScriptCharacter> script_characters;

game_status Game(int day, int level_choosed, RenderWindow& window)
{

    // when the game updates we need to update mouse state
    mouse_state = MouseState::Arrow;

    //// Static vars
    static bool docs_vector_setted = false;
    static bool day_setted = false;

    // make into function
    if (!docs_vector_setted)
    {
        cout << "[DEBUG]-document vector setted" << endl;

        //docs.push_back(Document({ 150,100 }, { 500,100 }, "rules", "", "", Color::Cyan));
        docs.push_back(
            Document(
                { 328, 419 }, 
                { 500,100 }, 
                Document::Document_ID::Internet_rules, 
                { "Internet rules fixed.png" },
                {},
                Color::Magenta));

        docs_vector_setted = true;
    }

    // make into function
    if (!day_setted)
    {
        days_setter(day, script_characters);
        for (int i = 0; i < script_characters.size(); i++)
        {
            wcout << L">| " << script_characters[i].GetPeasant().getName() << L"," << endl;
        }
        cout << "[DEBUG]-setting level [" << level_choosed << "] & script characters[" << script_characters.size() << ']' << endl;

        day_setted = true;
    }

    // SFML Variables
    
    Cursor cursor;
    static Vector2i mouse_offset = { 0,0 }, OLDmouse_offset = { 0,0 };
    Clock ImGuiClock;
    Clock FPS_Clock;
    Clock game_clock;
    Clock AnimClock;
    Clock dialog_clock;
    Image image_main;
    Font pass_font;
    Text text(L"", pass_font, 25);
    Texture cursor_texture;
    Sprite sprite_cursor;
    Image img;
    static Text small_interface_text;
    static int small_interface_str_index = 0;
    static vector<string> small_interface_str = {
        "SCANNER",
        "MONITOR",
        "DEPART",
    };


    small_interface_text.setFillColor(Color::Green);
    small_interface_text.setFont(pass_font);
    small_interface_text.setPosition({ 32 + 25,409 });
    small_interface_text.setString(small_interface_str[small_interface_str_index]);


    // temp vars

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        sound_eff_click.play();

    //Interface::Sliders::AddSlider("test1", { 300,50 }, 100, 1, { 2,2 });

    // other variables

    float x_offset = 65;
    int people_counter;
    bool newspaper_checked = false, day_animation_ended = false;
    static float fps = 1;
    vector<vector<Document>>all_documents;

    // setting variables

    pass_font.loadFromFile("pixelplay.ttf");

    img.loadFromFile("Jorji Costava_.png");


    //if (!newspaper_checked) {newspaper_checked = show_newspaper(day, game_clock, window);}

#ifdef MOUSE_CHECK_POS
    cout << Mouse::getPosition(window).x << ' ' << Mouse::getPosition(window).y << endl;
#endif // MOUSE_CHECK_POS


    //////////////////////////////
    //                          //
    //      Game cycle          //
    //                          //
    //////////////////////////////
    
    static Clock clock_timer_popup;
    float timer_popup = clock_timer_popup.getElapsedTime().asSeconds();

    if (!popup_certificate && timer_popup > 1)
    {
        Interface::PopUps::AddPopUp(Interface::PopUps::PopUp_class::Information, "cert popup",
            "New certificate\nN: Kurskoy S: Unresive\nA: 28 C: Uryp\nI: 100/019/827",
            { 0,0 }, { 2, 2 }, { {"ok", true},{"close", false} } );
        popup_certificate = true;
    }

    if (Interface::PopUps::getPopUpButtonPressed("cert popup").button_pressed == "ok")
    {
        popup_certificate = false;
        clock_timer_popup.restart();
    }



// Выдавание новых документов
    if (Document::getGiveNewDocs())
    {
        // Порядок:
        // 0. записываем в кол-во ошибок +1
        // 0.1. выдаем штраф
        // 0.2. [DEBUG] Выводим ошибки
        // 1. смортим на текущий день
        // 2. выдаем нужные док-ты в соответствии с днем
        // 3. [DEBUG] ...
        // 4. 
        //

        cout << "[DEBUG] Mistake:";
        // Если ошибка присутствует
        if (mistake)
            if (Stamp::getAccepted())   // Если въезд принят при ошибке
                cout << " -money" << endl;
            else                        // Если въезд был отказан при ошибке
                cout << " +money" << endl;
        else
            if (Stamp::getAccepted())   // Если въезд принят без ошибки
                cout << " +money" << endl;
            else                        // Если въезд был отказан без ошибки
                cout << " -money" << endl;

        Papers_setter(day, global_month, global_year, level_choosed, docs);
        //name, surname, country, birth, town, id, sex, till

        // Make into function "check_papers_against_day()"
      //{
        // passport 
        if (level_choosed != 3)
        {
            docs.push_back(
                Document(
                    { 128,160 },
                    { 870,460 }, 
                    Document::Document_ID::Passport, 
                    { "placeholder.png", "placeholder.png" },
                    {"closed"},
                    Color::Green
                )
            );

            passport.setPassportData(
                {
                    Peasant::getData().name,
                    Peasant::getData().surname,
                    Peasant::getData().country,
                    Peasant::getData().birth,
                    Peasant::getData().town,
                    Peasant::getData().index,
                    Peasant::getData().sex,
                    Peasant::getData().till
                });

            docs[-1].setTexture(0, "passport-" + passport.getPassportData().country + ".png");
            docs[-1].setTexture(1, "passport-" + passport.getPassportData().country + "-opened.png");
            docs[-1].setAdditionalData("standart passport");
        }
        else
        {
            docs.push_back(
                Document(
                    { 53 * 4,65 * 4 }, 
                    { 870,460 }, 
                    Document::Document_ID::Passport, 
                    { "placeholder.png", "placeholder.png" },
                    {},
                    Color::Green));
            docs[-1].setAdditionalData("temporary passport");
            docs[-1].setTexture(0, "sprites\\papers\\temp visa x.png");
        }
        // pass
        if (level_choosed == 1)
        {
            for (int i = 0; i < 1; i++)
            {
                Vector2f pos = { 870, 460 };
                pass.setText(Peasant::getData().pass_till);
                docs.push_back(Document({ 154,77 }, pos, Document::Document_ID::Pass));
                docs[docs.size() - 1].setElement({ 13,50 }, { 100,25 }, false); // 13 46 83 13
            }
        }
        // right
        if (level_choosed > 1)
        {
            Right.getTexts().clear();
            Right.appendText(Peasant::getData().right_surname + L" " + Peasant::getData().right_name, { 80,298 });
            Right.appendText(Peasant::getData().right_purpose, { 155,342 });
            Right.appendText(Peasant::getData().right_duration, { 155,380 });
            Right.appendText(Peasant::getData().right_till, { 155,418 });
            Right.appendText(Peasant::getData().right_id, { 243,190 });
            docs.push_back(
                Document(
                    { 96 * 4,128 * 4 },
                    { 500,100 },
                    Document::Document_ID::Right,
                    { "","" },
                    {},
                    Color::White));
        }
        // qr code
        if (level_choosed > 2)
        {
            // set doc index
            // set "Действителен с "текущая дата"
            docs.push_back(
                Document(
                    { 252,329 }, 
                    { 500,100 }, 
                    Document::Document_ID::QR, 
                    {"", ""},
                    {},
                    Color::Black));
        }
        //}
        if (script_characters.size() > 0)
        {
            cout << "time before next script character: " << script_characters[0].getQueueTime() - game_clock.getElapsedTime().asSeconds() << endl;
            if (script_characters[0].getQueueTime() <= game_clock.getElapsedTime().asSeconds())
            {
                // set passport data
                // code body
                //name
                //surname
                //country
                //birth
                //town
                //id
                //sex
                //till
                passport.setPassportData({
                    script_characters[0].GetPeasant().getName(),
                    script_characters[0].GetPeasant().getSurname(),
                    script_characters[0].GetPeasant().getCountry(),
                    script_characters[0].GetPeasant().getBirth(),
                    script_characters[0].GetPeasant().getTown(),
                    Peasant::getData().index,
                    script_characters[0].GetPeasant().getSex(),
                    Peasant::getData().till });
                for (auto doc : docs)
                {
                    if (doc.getDocID() == Document::Document_ID::Passport) {
                        doc.setTexture(0, "passport-" + passport.getPassportData().country + ".png");
                        doc.setTexture(1, "passport-" + passport.getPassportData().country + "-opened.png");
                    }
                }
                /*Right.setString(0, passport.getPassportData().name + L" " + passport.getPassportData().surname);*/

                ///
                script_characters.erase(script_characters.cbegin());
                cout << "Script characters left: " << script_characters.size() << endl;

            }
        }
        else
            cout << "No script characters left" << endl;

        /* Процесс исправления ошибок */
        Document::setGiveNewDocs(false);
    }

    mouse_pos = Mouse::getPosition(window);
    ImGui::Begin("Debug info");
    ImGui::Text("FPS:%f", 1/fps);
    if (no_mistakes)
        ImGui::Text("no_mistakes: %i", no_mistakes);
    if (only_mistakes)
        ImGui::Text("only_mistakes: %i", only_mistakes);
    ImGui::End();

    ImGui::Begin("Debug data changer");

    if (ImGui::Checkbox("Only mistakes", &only_mistakes))
        no_mistakes = false;
    if (ImGui::Checkbox("No mistakes", &no_mistakes))
        only_mistakes = false;

    ImGui::End();

// 
    Interaction::CheckInteraction();
// Checking everything
    handler_Interactions();
    handler_InterfaceElements();
    handler_Selection(docs, mouse_pos);


    Texture tt;
    tt.loadFromFile("sprites\\ui\\workspace_updated1 640x360.png");
    Sprite workspace;

    Texture texture;
    Sprite sprite;
    workspace.setTexture(tt);

// If not selected -> update all, else not update stamps, computer, doc_states and etc.
    if (!Selection::Data::SELECTED)
    {

        update_Stamps(window, Stamp::getPressed(), animations);
        update_Documents(docs, mouse_pos, OLDmouse_offset, passport, pass, window);
        update_Interface(window, mouse_pos);
        update_Document_State(window, docs);
    }

    Update_DragNDrop(docs);

//////////////////////////////////////////////////////// DRAWING ////////////////////////////////////////////////////////
    workspace.setScale({ float(window.getSize().x / workspace.getGlobalBounds().width),float(window.getSize().y / workspace.getGlobalBounds().height) });
    window.clear();
    Interface::Show(window);

    window.draw(workspace);

    DrawDocuments(window, docs, pass_font, text, passport, pass, Right, image_main);

// Displaying all Interaction elements
#if DEBUG true
                Interaction::DrawAllElements(window); 
#endif

/// Cursor updating (DrawCursor(RenderWindow& window))

    {
                window.setMouseCursorVisible(false);

                // needed for moving docs and etc.
                mouse_pos_old = OLDmouse_offset = mouse_pos;
                
                // changing the mouse texture to match what is happening
                if (mouse_state == MouseState::Arrow) {
                    cursor_texture.loadFromFile("sprites\\ui\\Computer Interface\\computer arrow.png");
                    sprite_cursor.setTextureRect({ 0,0,20,30 });
                }
                if (mouse_state == MouseState::Hovering) {
                    cursor_texture.loadFromFile("sprites\\ui\\Computer Interface\\computer point.png");
                    sprite_cursor.setTextureRect({ 0,0,20,31 });
                }
                // setters for mouse sprite
                sprite_cursor.setScale(2, 2);
                sprite_cursor.setTexture(cursor_texture);
                sprite_cursor.setPosition(Vector2f{ mouse_pos });
                
                window.draw(sprite_cursor);
    }

// For Debug porpouses 
    if (Keyboard::isKeyPressed(Keyboard::E))
    {
        Selection::Deselect();
        cout << "[Selection]: Deselect()" << endl;
    }
    if (Selection::Data::SELECTED)
    {
        RectangleShape rect(Vector2f{ float(window.getSize().x),float(window.getSize().y) });
        rect.setFillColor({ 0,0,0,100 });
        window.draw(rect);
        Selection::DrawSelection(window);
        Selection::DrawLine(window);
    }
// .

    ImGui::SFML::Render(window);
    window.display();

// earlier there was that abomination: "fps = fps = ..." that was scary. (*~*)
    fps = FPS_Clock.restart().asSeconds();
    
    
    return game_status::game_Game;
}