#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <locale>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#define DEBUG true
//#define MOUSE_CHECK_POS

using namespace sf;
using namespace std;

#include "Game Data.h"

#include "Update_funcs.h"
#include "Game Functions.h"
#include "functions.h"
#include "Interface.h"
#include "Interactions.h"
#include "Selection.h"
#include "ScriptCharacter.h"

Vector2f offset = {0,0};
bool mouse_colliding = false;

float day_time = 240; // seconds

//global variables
Music mus;

map<string,Animation> animations;

void drawFragmentShader(sf::RenderWindow& window, const std::string& fragmentShaderFile,
    const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
{
    const std::string fragmentShader = \
        "varying out vec4 FragColor; // Цвет фрагмента"\
        "uniform sampler2D texture;"\
        "void main()"\
        "{"\
        "    vec4 color = texture(texture, gl_FragCoord.xy / vec2(800.0, 600.0));"\
        "    if (color.r > 0.9 && color.g > 0.9 && color.b > 0.9)"\
        "        FragColor = vec4(1.0, 0.0, 1.0, 1.0); // Фиолетовый цвет"\
        "    else"\
        "        FragColor = color;"\
        "}";


    setlocale(LC_ALL, "");
    // Создаем фрагментный шейдер
    sf::Shader shader;
    shader.loadFromMemory(fragmentShader, sf::Shader::Fragment);
    Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);
    shader.setUniform("texture", texture);
    //shader.setUniform("texture", sf::Shader::CurrentTexture);
    //{
    //    std::cerr << "Ошибка загрузки фрагментного шейдера!" << std::endl;
    //    return;
    //}

    // Устанавливаем uniform-переменные для прямоугольников
    //shader.setUniform("rect1Position", sf::Glsl::Vec2(rect1.getPosition().x / window.getSize().x, rect1.getPosition().y / window.getSize().y));
    //shader.setUniform("rect1Size", sf::Glsl::Vec2(rect1.getSize().x / window.getSize().x, rect1.getSize().y / window.getSize().y));
    //shader.setUniform("rect2Position", sf::Glsl::Vec2(rect2.getPosition().x / window.getSize().x, rect2.getPosition().y / window.getSize().y));
    //shader.setUniform("rect2Size", sf::Glsl::Vec2(rect2.getSize().x / window.getSize().x, rect2.getSize().y / window.getSize().y));

    // Создаем прямоугольники для отрисовки
    RectangleShape fullScreenRect(Vector2f{ float(window.getSize().x), float(window.getSize().y)});
    fullScreenRect.setPosition(0, 0);

    // Применяем шейдер и отрисовываем полный экранный прямоугольник
    window.draw(fullScreenRect, &shader);
}

game_status Game(int day, int level_choosed, RenderWindow& window);
game_status MainMenu(RenderWindow& window);
bool Settings(RenderWindow& window);
int DayChoosing(RenderWindow& window);

void SetButtons()
{
    Interface::SetInterfacePos({78,30});
    Interface::AddButton("Load screen", "Log in", "sprites\\ui\\Computer Interface\\Log in button.png", { 0,0 }, { 3,3 });
    Interface::AddButton("Main top", "Database", "sprites\\ui\\Computer Interface\\Database.png", { 36,0 }, { 3,3 });
    Interface::PrintListOfButtons();
}

void SetLists()
{
    using namespace Interface;

    AddElementToList("Map", buttons["Load screen"]["Log in "]);
}

int main()
{
    vector<StructDay> days = { StructDay{},StructDay{},StructDay{},StructDay{},StructDay{},StructDay{},StructDay{} };
    cout << "Game started" << endl;
    FileManager::FillSettings("saves\\settings.txt", settings);
    cout << "Setting set" << endl;
    FileManager::FillDays("saves\\save.txt", days);

    // Setting Buttons
    SetButtons();
    Interface::LoadArea("Load screen");
    Interface::LoadArea("Main top");

    int style = settings.fullscreen == 1 ? Style::Fullscreen : 0;
    RenderWindow window(VideoMode(1920, 1080), "Welcome to VERSTANIA!",style);
    window.setFramerateLimit(75);
    ImGui::SFML::Init(window);
    
    
    //Test IE
    Interaction::AddElement(Interaction::Data::Area{ "test-index-0", 1581,497,267,416, true }); // Область печатей
    Interaction::AddElement(Interaction::Data::Area{ "test-index-1", 525,525,50,50, true }); // Область левой панели
    Interaction::AddElement(Interaction::Data::Area{ "test-index-2", 650,500,100,100, true, {25,255,50,75} }); // Область стекла
    Interaction::AddElement(Interaction::Data::Area{ "test-index-3", 800,500,100,100, true, {25,50,255,75} }); // Область вторичных печатей
    //Passport IE
    Interaction::AddElement(Interaction::Data::Area{ "passport-name&surname", 14,241,290,29,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-birth", 14,278,192,24,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-sex", 14,308,192,24,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-town", 14,340,192,24,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-till", 14,370,192,24,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-index", 212,401,92,32,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-photo", 212,284,92,116,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-country", 10,238,300,198,false });
    Interaction::AddElement(Interaction::Data::Area{ "passport-bottom_part", 10,238,300,198,false });
    // Interface IE
    Interaction::AddElement(Interaction::Data::Area{ "left-green-arrow", 20,412,33,40.5,false, {0,255,0,75} });
    Interaction::AddElement(Interaction::Data::Area{ "right-green-arrow", 290,412,33,40.5,false,{0,255,0,75} });
    Interaction::AddElement(Interaction::Data::Area{ "green-enter", 328,412,33,40.5,false,{0,255,0,75} });
    // PC
    Interaction::AddElement(Interaction::Data::Area{ "PC-monitor", 0,0,300,500,true, Color{0,255,0,25} });
    Interaction::AddElement(Interaction::Data::Area{ "PC-passport-name&surname", 14,241,290,29,false, Color{0,255,0,75} });
    Interaction::AddElement(Interaction::Data::Area{ "PC-passport-birth", 14,278,192,24,false, Color{0,255,0,75} });
    Interaction::AddElement(Interaction::Data::Area{ "PC-passport-sex", 14,308,192,24,false, Color{0,255,0,75} });
    Interaction::AddElement(Interaction::Data::Area{ "PC-passport-town", 14,340,192,24,false, Color{0,255,0,75} });
    Interaction::AddElement(Interaction::Data::Area{ "PC-passport-till", 14,370,192,24,false, Color{0,255,0,75} });
    Interaction::AddElement(Interaction::Data::Area{ "PC-passport-index", 212,401,92,32,false, Color{0,255,0,75} });
    Interaction::AddElement(Interaction::Data::Area{ "PC-passport-photo", 212,284,92,116,false, Color{0,255,0,75} });
    Interaction::AddElement(Interaction::Data::Area{ "PC-passport-country", 10,238,300,198,false, Color{0,255,0,75} });

    Interaction::Settings::CoutInteractionInfoString = false;

    mus.openFromFile("Papers please.mp3");
    mus.play();
    mus.setLoop(true);
    mus.setVolume(settings.mus_vol);

    int level_choosed = -1;

    if (settings.intro_played) current_game_status = game_status::game_Main_Menu;
    Clock ImGuiClock;
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

        Interaction::CheckInteraction();


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

    Interaction::EditElement("left-green-arrow", Interaction::Data::Enabled, "1");
    Interaction::EditElement("right-green-arrow", Interaction::Data::Enabled, "1");
    Interaction::EditElement("green-enter", Interaction::Data::Enabled, "1");

    //// Static vars
    static bool docs_vector_setted = false;
    static bool day_setted = false;


    Right.setTextureName("sprites\\papers\\Right for arriving.png");

    //Rules rules;
    //rules.addInterElem(0, { 0,0 }, { 50,50 }, "main_page");
    //rules.addInterElem(1, { 100,25 }, { 50,50 }, "back_to_main_page");



// TODO:
// -   make code more readable (bruh...)
// -   get rid of useless couts
// -   
// -   
//


    // make into function
    if (!docs_vector_setted)
    {
        cout << "[DEBUG] doc vector setted" << endl;

        docs.push_back(Document({ 150,100 }, { 500,100 }, "rules", "", "", Color::Cyan));
        docs.push_back(Document({ 328, 419 }, { 500,100 }, "internet rules", "Internet rules fixed.png", "", Color::Magenta));

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
        cout << "[DEBUG] setting day[" << day << "] & script characters[" << script_characters.size() << ']' << endl;

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

    SoundBuffer sound_buff;
    Sound sound_eff_click;
    sound_buff.loadFromFile("sounds\\click.wav");
    sound_eff_click.setBuffer(sound_buff);
    sound_eff_click.setVolume(settings.sfx_vol);
    // temp vars

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        sound_eff_click.play();


    // other variables

    float x_offset = 65;
    int people_counter;
    bool newspaper_checked = false, day_animation_ended = false;
    float fps = FPS_Clock.restart().asSeconds();
    vector<vector<Document>>all_documents;

    // setting variables

    pass_font.loadFromFile("pixelplay.ttf");

    img.loadFromFile("Jorji Costava_.png");


    if (Keyboard::isKeyPressed(Keyboard::Escape) || (Keyboard::isKeyPressed(Keyboard::LAlt) && Keyboard::isKeyPressed(Keyboard::F4)))
    {
        Document::setGiveNewDocs(true); current_game_status = game_status::game_Main_Menu;
        Interaction::EditElement("left-green-arrow", Interaction::Data::Enabled, "0");
        Interaction::EditElement("right-green-arrow", Interaction::Data::Enabled, "0");
        Interaction::EditElement("green-enter", Interaction::Data::Enabled, "0");
        docs.clear();
    }

    //if (!newspaper_checked) {newspaper_checked = show_newspaper(day, game_clock, window);}

#ifdef MOUSE_CHECK_POS
    cout << Mouse::getPosition(window).x << ' ' << Mouse::getPosition(window).y << endl;
#endif // MOUSE_CHECK_POS


    //////////////////////////////
    //                          //
    //      Game cycle          //
    //                          //
    //////////////////////////////
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
            docs.push_back(Document({ 128,160 }, { 870,460 }, "passport", "placeholder.png", "placeholder.png", Color::Green));

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

            passport.setOpenedTextureName("passport-" + passport.getPassportData().country + "-opened.png");
            passport.setTexture("passport-" + passport.getPassportData().country + ".png");
            passport.setStatus(Passport::USUAL);
        }
        else
        {
            docs.push_back(Document({ 53 * 4,65 * 4 }, { 870,460 }, "passport", "placeholder.png", "", Color::Green));
            Passport::setStatus(Passport::TEMP_VISA);
            passport.setTexture("sprites\\papers\\temp visa x.png");
            passport.setOpenedTextureName("sprites\\papers\\temp visa x.png");
        }
        // pass
        if (level_choosed == 1)
        {
            for (int i = 0; i < 1; i++)
            {
                Vector2f pos = { 870, 460 };
                pass.setText(Peasant::getData().pass_till);
                docs.push_back(Document({ 154,77 }, pos, "pass"));
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
            docs.push_back(Document({ 96 * 4,128 * 4 }, { 500,100 }, "right", "", "", Color::White));
        }
        // qr code
        if (level_choosed > 2)
        {
            // set doc index
            // set "Действителен с "текущая дата"
            docs.push_back(Document({ 252,329 }, { 500,100 }, "qr", "", "", Color::Black));
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
                    if (doc.getDocID() == "passport") {
                        passport.setOpenedTextureName("passport-" + passport.getPassportData().country + "-opened.png");
                        passport.setTextureName("passport-" + passport.getPassportData().country + ".png");
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
    ImGui::Text("FPS:%f", 1 / fps);
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


    Interaction::CheckInteraction();
    Interface::Update();

    Texture tt;
    tt.loadFromFile("sprites\\ui\\workspace_updated1 640x360.png");
    Sprite workspace;

    Texture texture;
    Sprite sprite;
    workspace.setTexture(tt);

    //////////////////////////////////////////////////////// DRAWING ////////////////////////////////////////////////////////
    workspace.setScale({ float(window.getSize().x / workspace.getGlobalBounds().width),float(window.getSize().y / workspace.getGlobalBounds().height) });
    window.clear();

    if (Keyboard::isKeyPressed(Keyboard::BackSlash))
        Imigrant_gone(img);
    if (Keyboard::isKeyPressed(Keyboard::RShift))
        Imigrant_came(img);
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    sprite.setPosition(740, 30);
    sprite.setScale(3, 3);
    window.draw(sprite);
    texture.loadFromFile("sprites\\ui\\green_ui.png");
    sprite.setTexture(texture);
    sprite.setScale({ 1.5,1.5 });
    if (Interaction::GetElement("left-green-arrow").Mouse_condition == Interaction::Data::Mouse_In)
        sprite.setTextureRect({ 22,0,22,27 });
    else if (Interaction::GetElement("left-green-arrow").Mouse_condition == Interaction::Data::Mouse_Left_Click ||
        Interaction::GetElement("left-green-arrow").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
    {
        sprite.setTextureRect({ 44,0,22,27 });
        if (small_interface_str_index > 0)
            small_interface_str_index--;
    }
    else
        sprite.setTextureRect({ 0,0,22,27 });
    sprite.setPosition({ 20,412 });
    window.draw(small_interface_text);
    window.draw(sprite);
    if (Interaction::GetElement("right-green-arrow").Mouse_condition == Interaction::Data::Mouse_In)
    {
        sprite.setTextureRect({ 44,0,-22,27 });

    }
    else if (Interaction::GetElement("right-green-arrow").Mouse_condition == Interaction::Data::Mouse_Left_Click ||
        Interaction::GetElement("right-green-arrow").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
    {
        sprite.setTextureRect({ 66,0,-22,27 });
        if (small_interface_str_index < small_interface_str.size() - 1)
            small_interface_str_index++;
    }
    else
        sprite.setTextureRect({ 22,0,-22,27 });


    sprite.setPosition({ 290,412 });
    window.draw(sprite);

    if (Interaction::GetElement("green-enter").Mouse_condition == Interaction::Data::Mouse_In)
    {
        sprite.setTextureRect({ 22,27,22,27 });
        
    }
    else if (Interaction::GetElement("green-enter").Mouse_condition == Interaction::Data::Mouse_Left_Click || 
        Interaction::GetElement("green-enter").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
    {
        sprite.setTextureRect({ 44,27,22,27 });

        if (small_interface_str[small_interface_str_index] == "MONITOR")
        {
            Interaction::EditElement("PC-passport-name&surname", Interaction::Data::Enabled, "1");
            Interaction::EditElement("PC-passport-birth", Interaction::Data::Enabled, "1");
            Interaction::EditElement("PC-passport-sex", Interaction::Data::Enabled, "1");
            Interaction::EditElement("PC-passport-town", Interaction::Data::Enabled, "1");
            Interaction::EditElement("PC-passport-till", Interaction::Data::Enabled, "1");
            Interaction::EditElement("PC-passport-index", Interaction::Data::Enabled, "1");
            Interaction::EditElement("PC-passport-photo", Interaction::Data::Enabled, "1");
            Interaction::EditElement("PC-passport-country", Interaction::Data::Enabled, "1");
        }
    }
    else
        sprite.setTextureRect({ 0,27,22,27 });
    sprite.setPosition({ 328,412 });
    window.draw(sprite);
    window.draw(workspace);


    RectangleShape h;
    //tt.loadFromImage(passport.getImage("passport-righther.png"));
    h.setTexture(&tt);
    h.setPosition(float(300), float(800));
    window.draw(h);

    RectangleShape SCANNER;
    SCANNER.setFillColor({ 100,100,100,255 });
    SCANNER.setSize({ float(64 * 2.1), float(10) });



    DrawDocuments(window, docs, pass_font, text, passport, pass, Right, image_main);

    //cout << "[DEBUG] " << m_pos.x << ' ' << m_pos.y << endl;
    if (!Selection::Data::SELECTED)
    {
        Update_Stamps(window, Stamp::getPressed(), animations);
        Update(docs, mouse_pos, OLDmouse_offset, passport, pass, window);
        Update_Interface(window, mouse_pos);
        Update_Document_State(window, docs);
    }
        //if(Selection::Data::first_selected && Selection::Data::second_selected)
    UpdateSelection(docs, mouse_pos);


#if DEBUG true
    Interaction::DrawAllElements(window);
#endif // Debug true

    ///----Mouse cursor----///
    if (mouse_state == MouseState::Arrow)
    {
        cursor_texture.loadFromFile("cursor.png");
        sprite_cursor.setTextureRect({ 0,0,20,30 });
    }
    if (mouse_state == MouseState::Hovering)
    {
        cursor_texture.loadFromFile("cursor point.png");
        sprite_cursor.setTextureRect({ 0,0,20,31 });
    }
    sprite_cursor.setScale(2, 2);
    sprite_cursor.setTexture(cursor_texture);
    sprite_cursor.setPosition(Vector2f{ mouse_pos });
    window.setMouseCursorVisible(false);
    OLDmouse_offset = mouse_pos;


    Interface::Show(window);
    window.draw(sprite_cursor);

    if (Keyboard::isKeyPressed(Keyboard::E))
    {
        Selection::Deselect();
        cout << 2 << endl;
    }
    if (Selection::Data::SELECTED)
    {
        RectangleShape rect(Vector2f{ float(window.getSize().x),float(window.getSize().y) });
        rect.setFillColor({ 0,0,0,100 });
        window.draw(rect);
        Selection::DrawSelection(window);
        Selection::DrawLine(window);
    }

    ImGui::SFML::Render(window);
    window.display();

    return game_status::game_Game;
}