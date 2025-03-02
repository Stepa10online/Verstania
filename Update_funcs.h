#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

#include "all_docs.h"
#include "Docs Funcs.h"
#include "eMath.h"
#include "Animation.h"
#include "Variables.h"
#include "Interactions.h"
#include "Selection.h"

void Update(vector<Document>&docs, const Vector2i& m_pos, Vector2i OLDmouse_offset, Passport& passport, Pass& pass, RenderWindow& window)
{
    bool dragging = ImGui::IsMouseDragging(ImGuiMouseButton_Left);
    bool enable_to_close = !Interaction::IsAnyElement(Interaction::Data::Mouse_Left_DoubleClick);
    Vector2i mouse_offset = m_pos - OLDmouse_offset;

    for (auto& doc : docs)
    {
        if (doc.getDocID() == "qr")
        {
            if (CollisionPointRect(doc.getPosition(), { 100,100,50,50 }))
            {
                qr_scanner_check = true;
                continue;
            }
            else
                qr_scanner_check = false;
        }
        if (doc.getPosition().y <= 400 && !doc.getSelected())
            doc.move(0, 20);
    }

    // check if mouse colliding and pressed
    for (int i = docs.size() - 1; i >= 0; i--)
    {
        if(CollisionPointRect({ float(m_pos.x),float(m_pos.y) }, { docs[i].getPosition(),docs[i].getSize() })
            )
        {
            if (Interaction::IsAnyElement(Interaction::Data::Mouse_Left_DoubleClick) 
                && docs[i].getDocID() == "passport" && Stamp::getColliding() == false)
            {
                break;
            }
            // double clicked
            if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && docs[i].getDocID() == "passport" && Stamp::getColliding()==false)
            {
                docs[i].setSelected(true);
                if (Passport::getStatus() == Passport::TEMP_VISA)
                {
                    cout << "[DEBUG] temp visa" << endl;
                    Passport::setOpened(true);
                }
                else
                    if(!Passport::getOpened())
                    {
                        docs[i].setSize({ 320,448 });
                        Passport::setOpened(true);
                    }
                    else 
                    {
                        docs[i].setSize({ 128,docs[i].getSize().y });
                        Passport::setOpened(false);
                    }
                
                break;
            }
            // drag
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && Stamp::getColliding() == false)
            {
                docs[i].setSelected(true);
                //// additional data for debug
                //for (int i = 0; i < docs.size(); i++)
                //{
                //    cout << i << "-----------" << endl;
                //    cout << docs[i].getPosition().x << ' ' << docs[i].getPosition().y << endl;
                //    cout << docs[i].getSize().x << ' ' << docs[i].getSize().y << endl;
                //    if(docs[i].getSelected()) cout << "Selected" << endl;
                //    cout << "doc id: " << docs[i].getDocID() << endl;
                //    cout << "OpenedTexture: " << docs[i].getOpenedTextureName() << endl;
                //}
                //cout << endl;
                break;
            }

            //cout << docs[i].getPosition().x + rules.getInterElem(i).pos.x << ' ' << docs[i].getPosition().y + rules.getInterElem(i).pos.y << ' ' << rules.getInterElem(i).size.x << ' ' << rules.getInterElem(i).size.y << endl;
            
            // printer
            if (ImGui::IsKeyPressed(ImGuiKey_Enter))
                for (int n = 0; n < docs.size(); n++)
                {
                    if (docs[n].getDocID() == "passport")
                    {
                        //Passport::setStampOffset({ docs[n].getPosition().x, docs[n].getPosition().y });
                        passport.setStampOffset({ (float(m_pos.x) - docs[n].getPosition().x - 50) / 2, (float(m_pos.y) - docs[n].getPosition().y-25) / 2 });
                        passport.setStampTexture("DENIED.png");
                        //Passport::setStampOffset({ float(m_pos.x) - docs[n].getPosition().x, float(m_pos.y) - docs[n].getPosition().y });
                        Passport::setStamped(true);
                        cout << passport.getStampOffset().x << ' ' << passport.getStampOffset().y << endl;
                    }
                }
        }
    }
    // move and change docs order
    for (int i = 0; i < docs.size(); i++)
    {
        if (docs[i].getSelected())
        {
            //cout << mouse_offset.x << ' ' << mouse_offset.y << endl;
            docs[i].move(mouse_offset.x, mouse_offset.y);
            change_order(docs, i);
            break;
        }
    }
    // check if mouse released
    for (int i = 0; i < docs.size(); i++)
    {
        if (docs[i].getSelected() == true)
            if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
            {
                docs[i].setSelected(false);
                break;
            }
    }
    // scanner
    for (int i = 0; i < docs.size(); i++)
    {
        if (docs[i].getDocID() == "passport")
        {
            if (CollisionPointRect(docs[i].getPosition(), { 700-12.5,500-12.5,25,25}))
            {
                Passport p;
                if (Keyboard::isKeyPressed(Keyboard::Space))
                    cout << '-';//AddImage();
                DrawImage(window, "passport-" + p.getPassportData().country + ".png");
            }
            //if (docs[i].getSelected() && CollisionPointRect({ float(m_pos.x),float(m_pos.y) }, { 560,0,747,396 }))
            //{
            //    if (m_pos.x - docs[i].getPosition().x > 64 * 2)
            //        docs[i].move({ 64 * 2,0 });
            //    Passport::setOpened(false);
            //    if (Passport::getStamped())
            //    {
            //        Text text;
            //        Font font;
            //        font.loadFromFile("pixelplay.ttf");
            //        text.setFont(font);
            //        text.setCharacterSize(35);
            //        text.setOutlineThickness(4);
            //        text.setOutlineColor(Color::Black);
            //        text.setString(L"Отдать");
            //        text.setPosition(m_pos.x + 30, m_pos.y + 30);
            //        window.draw(text);
            //    }
            //}
        }

    }
    // rules
    //for (int i = 0; i < docs.size(); i++)
    //{
    //    if (docs[i].getDocID() == "rules" && CollisionPointRect({float(m_pos.x),float(m_pos.y)}, {docs[i].getPosition(), docs[i].getSize()}))
    //    {
    //        for (int j = 0; j < rules.getIEAmount(); j++)
    //        {
    //            if (CollisionPointRect({ float(m_pos.x),float(m_pos.y) }, { docs[i].getPosition()+rules.getInterElem(j).pos,rules.getInterElem(j).size }))
    //            {
    //                cursor = "hand";
    //                if (!dragging && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
    //                {
    //                    cout << rules.getInterElem(j).id;
    //                    rules.setPressed(j, true);
    //                    cursor = "arrow";
    //                }
    //                else
    //                    rules.setPressed(j, false);
    //            }
    //        }
    //    }
    //}
    // pass
    for (int i = 0; i < docs.size(); i++)
    {
        for (int j = 0; j < docs[i].getElementsAmount(); j++)
        {
            FloatRect fr = { docs[i].getPosition() + Vector2f{ docs[i].getElement(j).x, docs[i].getElement(j).y }, {docs[i].getElement(j).w, docs[i].getElement(j).h} };
            if (CollisionPointRect({ float(m_pos.x),float(m_pos.y) }, fr))
            {
                if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    wcout << pass.getText() << " | " << fr.left << ' ' << fr.top << ' ' << fr.width << ' ' << fr.height << " | " << docs[i].getElement(j).validity << endl;
                }
            }

        }
    }

    // stamps update
    /// ACCEPT
    if (CollisionPointRect({ float(m_pos.x),float(m_pos.y) }, { 1618,506,192,148 }))
    {
        mouse_state = MouseState::Hovering;
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            for (int n = 0; n < docs.size(); n++)
            {
                if (docs[n].getDocID() == "passport")
                {

                    if (FloatRect{docs[n].getPosition(),docs[n].getSize()}.intersects(FloatRect{ 1618,506,192,148 }) && Passport::getOpened())
                    {
                        //Passport::setStampOffset({ docs[n].getPosition().x, docs[n].getPosition().y });
                        passport.setStampOffset({ (1618 - docs[n].getPosition().x), (506 - docs[n].getPosition().y+50) });
                        Stamp::setTexture("sprites\\tempname\\ACCEPTED(ru).png");
                        //Passport::setStampOffset({ float(m_pos.x) - docs[n].getPosition().x, float(m_pos.y) - docs[n].getPosition().y });
                        Passport::setStamped(true);
                        Stamp::setAccepted(true);
                    }
                    Stamp::setPressed(1);
                }
            }
        }
    }
    /// DENIED
    if (CollisionPointRect({ float(m_pos.x),float(m_pos.y) }, { 1618,699,192,148 }))
    {
        mouse_state = MouseState::Hovering;
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            for (int n = 0; n < docs.size(); n++)
            {
                if (docs[n].getDocID() == "passport")
                {
                    if (FloatRect{docs[n].getPosition(),docs[n].getSize()}.intersects(FloatRect{ 1618,699,192,148 }) && Passport::getOpened())
                    {
                        //Passport::setStampOffset({ docs[n].getPosition().x, docs[n].getPosition().y });
                        passport.setStampOffset({ (1618 - docs[n].getPosition().x), (699 - docs[n].getPosition().y+50) });
                        Stamp::setTexture("sprites\\tempname\\DENIED(ru).png");
                        //Passport::setStampOffset({ float(m_pos.x) - docs[n].getPosition().x, float(m_pos.y) - docs[n].getPosition().y });
                        Passport::setStamped(true);
                        Stamp::setAccepted(false);
                    }
                    Stamp::setPressed(2);
                }
            }
        }
    }

    if (CollisionPointRect({ float(m_pos.x),float(m_pos.y) }, { 1618,497,384,196 }))
        Stamp::setColliding(true);
    else
        Stamp::setColliding(false);

    for (auto doc : docs)
    {
        if (doc.getDocID() != "passport") continue;

        if (Passport::getOpened())
        {
            Interaction::EditElement("passport-name&surname", Interaction::Data::Enabled, "1");
            Interaction::EditElement("passport-birth", Interaction::Data::Enabled, "1");
            Interaction::EditElement("passport-sex", Interaction::Data::Enabled, "1");
            Interaction::EditElement("passport-town", Interaction::Data::Enabled, "1");
            Interaction::EditElement("passport-till", Interaction::Data::Enabled, "1");
            Interaction::EditElement("passport-index", Interaction::Data::Enabled, "1");
            Interaction::EditElement("passport-photo", Interaction::Data::Enabled, "1");
            Interaction::EditElement("passport-bottom_part", Interaction::Data::Enabled, "1");

            Interaction::EditElement("passport-name&surname",Interaction::Data::Params::Xpos, 
                to_string(doc.getPosition().x + 14));
            Interaction::EditElement("passport-name&surname",Interaction::Data::Params::Ypos,
                to_string(doc.getPosition().y + 241));
            Interaction::EditElement("passport-birth",Interaction::Data::Params::Xpos,
                to_string(doc.getPosition().x + 14));
            Interaction::EditElement("passport-birth",Interaction::Data::Params::Ypos,
                to_string(doc.getPosition().y + 278));
            Interaction::EditElement("passport-sex",Interaction::Data::Params::Xpos,
                to_string(doc.getPosition().x + 14));
            Interaction::EditElement("passport-sex",Interaction::Data::Params::Ypos,
                to_string(doc.getPosition().y + 308));
            Interaction::EditElement("passport-town",Interaction::Data::Params::Xpos,
                to_string(doc.getPosition().x + 14));
            Interaction::EditElement("passport-town",Interaction::Data::Params::Ypos,
                to_string(doc.getPosition().y + 340));
            Interaction::EditElement("passport-till",Interaction::Data::Params::Xpos,
                to_string(doc.getPosition().x + 14));
            Interaction::EditElement("passport-till",Interaction::Data::Params::Ypos,
                to_string(doc.getPosition().y + 370));
            Interaction::EditElement("passport-index",Interaction::Data::Params::Xpos,
                to_string(doc.getPosition().x + 212));
            Interaction::EditElement("passport-index",Interaction::Data::Params::Ypos,
                to_string(doc.getPosition().y + 401));
            Interaction::EditElement("passport-photo",Interaction::Data::Params::Xpos,
                to_string(doc.getPosition().x + 212));
            Interaction::EditElement("passport-photo",Interaction::Data::Params::Ypos,
                to_string(doc.getPosition().y + 284));
            Interaction::EditElement("passport-bottom_part",Interaction::Data::Params::Xpos,
                to_string(doc.getPosition().x + 10));
            Interaction::EditElement("passport-bottom_part",Interaction::Data::Params::Ypos,
                to_string(doc.getPosition().y + 238));

        }
        else
        {

            Interaction::EditElement("passport-name&surname", Interaction::Data::Enabled, "0");
            Interaction::EditElement("passport-birth", Interaction::Data::Enabled, "0");
            Interaction::EditElement("passport-sex", Interaction::Data::Enabled, "0");
            Interaction::EditElement("passport-town", Interaction::Data::Enabled, "0");
            Interaction::EditElement("passport-till", Interaction::Data::Enabled, "0");
            Interaction::EditElement("passport-index", Interaction::Data::Enabled, "0");
            Interaction::EditElement("passport-photo", Interaction::Data::Enabled, "0");
            Interaction::EditElement("passport-bottom_part", Interaction::Data::Enabled, "0");
        }
    }

}

void UpdateSelection(vector<Document>& docs, const Vector2i& m_pos )
{
    for (int i = docs.size() - 1; i >= 0; i--)
    {
        if (CollisionPointRect({ float(m_pos.x),float(m_pos.y) }, { docs[i].getPosition(),docs[i].getSize() }))
        {
            if (Interaction::IsAnyElement(Interaction::Data::Mouse_Left_DoubleClick)
                && docs[i].getDocID() == "passport" && Stamp::getColliding() == false)
            {
                if (Interaction::GetElement("passport-name&surname").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
                {
                    setlocale(LC_ALL, "ru");
                    Interaction::Data::Area element = Interaction::GetElement("passport-name&surname");
                    Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
                    printf("[DEBUG] passport data: name & surname: [%ls] [%ls]\n", Passport::getPassportData().name.c_str(), Passport::getPassportData().surname.c_str());
                }
                if (Interaction::GetElement("passport-birth").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
                {
                    setlocale(LC_ALL, "ru");
                    Interaction::Data::Area element = Interaction::GetElement("passport-birth");
                    Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
                    printf("[DEBUG] passport data: birth: [%ls] \n", Passport::getPassportData().birth);
                }
                if (Interaction::GetElement("passport-sex").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
                {
                    setlocale(LC_ALL, "ru");
                    Interaction::Data::Area element = Interaction::GetElement("passport-sex");
                    Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
                    printf("[DEBUG] passport data: sex: [%ls] \n", Passport::getPassportData().sex);
                }
                if (Interaction::GetElement("passport-town").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
                {
                    setlocale(LC_ALL, "ru");
                    Interaction::Data::Area element = Interaction::GetElement("passport-town");
                    Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
                    printf("[DEBUG] passport data: town: [%ls] \n", Passport::getPassportData().town.c_str());
                }
                if (Interaction::GetElement("passport-till").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
                {
                    setlocale(LC_ALL, "ru");
                    Interaction::Data::Area element = Interaction::GetElement("passport-till");
                    Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
                    printf("[DEBUG] passport data: till: [%ls] \n", Passport::getPassportData().till.c_str());
                }
                if (Interaction::GetElement("passport-index").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
                {
                    setlocale(LC_ALL, "ru");
                    Interaction::Data::Area element = Interaction::GetElement("passport-index");
                    Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
                    printf("[DEBUG] passport data: index: [%ls] \n", Passport::getPassportData().id);
                }
                if (Interaction::GetElement("passport-photo").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
                {
                    setlocale(LC_ALL, "ru");
                    Interaction::Data::Area element = Interaction::GetElement("passport-photo");
                    Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
                    printf("[DEBUG] passport data: till: [commentary:<NOT FOUND>] \n");
                }

                break;
            }
        }
    }
    if (Interaction::IsAnyElement(Interaction::Data::Mouse_Left_DoubleClick))
    {
        if (Interaction::GetElement("PC-passport-name&surname").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
        {
            setlocale(LC_ALL, "ru");
            Interaction::Data::Area element = Interaction::GetElement("PC-passport-name&surname");
            Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
            printf("[DEBUG] PC passport data: name & surname: [%ls] [%ls]\n", Passport::getPassportData().name.c_str(), Passport::getPassportData().surname.c_str());
        }
        if (Interaction::GetElement("PC-passport-birth").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
        {
            setlocale(LC_ALL, "ru");
            Interaction::Data::Area element = Interaction::GetElement("PC-passport-birth");
            Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
        }
        if (Interaction::GetElement("PC-passport-sex").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
        {
            setlocale(LC_ALL, "ru");
            Interaction::Data::Area element = Interaction::GetElement("PC-passport-sex");
            Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
        }
        if (Interaction::GetElement("PC-passport-town").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
        {
            setlocale(LC_ALL, "ru");
            Interaction::Data::Area element = Interaction::GetElement("PC-passport-town");
            Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
        }
        if (Interaction::GetElement("PC-passport-till").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
        {
            setlocale(LC_ALL, "ru");
            Interaction::Data::Area element = Interaction::GetElement("PC-passport-till");
            Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
        }
        if (Interaction::GetElement("PC-passport-photo").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
        {
            setlocale(LC_ALL, "ru");
            Interaction::Data::Area element = Interaction::GetElement("PC-passport-photo");
            Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
        }
        if (Interaction::GetElement("PC-passport-index").Mouse_condition == Interaction::Data::Mouse_Left_DoubleClick)
        {
            setlocale(LC_ALL, "ru");
            Interaction::Data::Area element = Interaction::GetElement("PC-passport-index");
            Selection::AutoSelect({ element.x,element.y }, { element.w,element.h });
        }
    }
}

void Update_Interface(RenderWindow& window, const Vector2i& m_pos)
{
    Texture texture, btn_texture;
    Sprite sprite;
    vector<Sprite> btn_sprites;
    static Clock anim_clock;

    texture.loadFromFile("workspace_updated_left.png");
    sprite.setTexture(texture);
    sprite.setScale(4, 4);
    sprite.setPosition(-428, 496);
    
    btn_texture.loadFromFile("workspace_updated_button.png");
    for (int i = 0; i < 2; i++)
    {
        Sprite temp;
        temp.setTexture(btn_texture);
        temp.setScale(4, 4);
        temp.setPosition(-428,512+124*i);
        btn_sprites.push_back(temp);
    }

    /* ещё 3 попытки */






    static bool entered = false;
    static bool animation_played = false;
    if (CollisionPointRect(Vector2f{ m_pos }, { 0,496,288,428 }))
    {
        if (!entered)
        {
            entered = true;
            anim_clock.restart();
        }
        float time = anim_clock.getElapsedTime().asSeconds();
        float x = smootherstep(0, 0.3, time);
        if (x == 1) animation_played = true;
        else animation_played = false;
        sprite.setPosition((1 - x) * (-428), 496);

        for (int i = 0; i < btn_sprites.size(); i++)
        {
            btn_sprites[i].setPosition((1 - x) * (-428), 512 + 124 * i);
        }
    }
    else
    {
        if (entered)
        {
            entered = false;
            anim_clock.restart();
        }
        float time = anim_clock.getElapsedTime().asSeconds();
        float x = smootherstep(0, 0.3, time);
        if (x == 1) animation_played = true;
        else animation_played = false;
        sprite.setPosition((x) * (sprite.getPosition().x), 496);
        for (int i = 0; i < btn_sprites.size(); i++)
        {
            btn_sprites[i].setPosition((x) * (btn_sprites[i].getPosition().x), 512 + 124 * i);
        }
    }

    window.draw(sprite);
    for (const auto& btn : btn_sprites)
        window.draw(btn);
}

void Update_Stamps(RenderWindow& window, unsigned int& pressed_state, map<string, Animation>& animations)
{

    if (pressed_state == 1)
    {
        animations["stamp_approving"].play(window);
        if (animations["stamp_approving"].getPlayed())
            Stamp::setPressed(0);
    }
    else
        animations["stamp_approving"].play(window, 0);
    if (pressed_state == 2)
    {
        animations["stamp_denying"].play(window);
        if (animations["stamp_denying"].getPlayed())
            Stamp::setPressed(0);
    }
    else
        animations["stamp_denying"].play(window, 0);
    
}

void Imigrant_gone(Image& image)
{
    for (unsigned int x = 0; x < image.getSize().x; x++)
    {
        for (unsigned int y = 0; y < image.getSize().y; y++)
        {
            Color NewColor = image.getPixel(x, y);
            NewColor.r /= 1.1;
            NewColor.g /= 1.1;
            NewColor.b /= 1.1;
            image.setPixel(x, y, NewColor);
        }
    }
}
void Imigrant_came(Image& image)
{
    for (unsigned int x = 0; x < image.getSize().x; x++)
    {
        for (unsigned int y = 0; y < image.getSize().y; y++)
        {
            Color NewColor = image.getPixel(x, y);
            NewColor.r *= 1.1;
            NewColor.g *= 1.1;
            NewColor.b *= 1.1;
            image.setPixel(x, y, NewColor);
        }
    }
}
bool checkWithBaseData(Passport p)
{
    return true;
}
void Update_Document_State(RenderWindow& window, vector<Document>&docs)
{
    Vector2i m_pos = Mouse::getPosition(window);
    for (int i = 0; i < docs.size(); i++)
    {
        bool give_away = false;
        if(docs[i].getDocID() == "passport" || docs[i].getDocID() == "pass" || docs[i].getDocID() == "right"
            || docs[i].getDocID() == "qr")
        if ( docs[i].getSelected() && CollisionPointRect({float(m_pos.x),float(m_pos.y)}, {560,0,747,396}))
        {
            if(docs[i].getDocID() == "passport")
            {
                if (m_pos.x - docs[i].getPosition().x > 64 * 2)
                    docs[i].move({ 64 * 2,0 });
                if (Passport::getStatus() != Passport::TEMP_VISA)
                    Passport::setOpened(false);
            }
            if (Passport::getStamped())
            {
                Text text;
                Font font;
                font.loadFromFile("pixelplay.ttf");
                text.setFont(font);
                text.setCharacterSize(35);
                text.setOutlineThickness(4);
                text.setOutlineColor(Color::Black);
                text.setString(L"Отдать");
                text.setPosition(m_pos.x + 30, m_pos.y + 30);
                window.draw(text);
                if (!Mouse::isButtonPressed(Mouse::Left))
                {
                    give_away = true;
                }
            }

            if (give_away)
            {
                docs.erase(docs.begin() + i);
                cout << "Remained documents: " << docs.size() << endl;
                bool all_docs_given = true;

                for (auto& doc : docs)
                {
                    if (doc.getDocID() == "passport" || doc.getDocID() == "pass" || doc.getDocID() == "right"
                        || doc.getDocID() == "qr")
                    {
                        all_docs_given = false;
                        //checkWithBaseData();
                    }
                }

                give_away = false;
                if(all_docs_given)
                {
                    cout << "all_docs_given" << endl;
                    
                    Document::setGiveNewDocs(true);
                    Passport::setStamped(false);
                }

            }
        }
        //else //if(docs[i].getSelected())
        //    Passport::setOpened(true);

    }
}

void MoveAnimation(Vector2f& pos, const float& time, Vector2f start_pos,
    const float& a, const float& b, const float& c, const float& d)
{
    Vector2f new_pos = pos;
    double koef = abs(sin(time * a)) / (time*b);
    //double koef = sqrt( abs( cos(time*a)*c/(time*d+b) ) ) ;

    new_pos.x *= koef;
    new_pos.x = pos.x + new_pos.x;
    cout << time << '\t' << koef << '\t' << new_pos.x << endl;
    pos = new_pos;

}

bool ANIMATION_day_started(int day, RenderWindow& window, Clock& anim_clock)
{
    RectangleShape black_screen(Vector2f{1920,1080});
    black_screen.setFillColor(Color::Black);
    static float a_color = 255;
    //cout << "[DEBUG] day starting " << int(a_color) << ' ' << smootherstep(0, 1, anim_clock.getElapsedTime().asSeconds()) << ' ' << anim_clock.getElapsedTime().asSeconds() << endl;

    a_color = (1 - smootherstep(0, 5, anim_clock.getElapsedTime().asSeconds())) * 255;
    cout << "Alpha color: " << a_color << ' '<< smootherstep(0, 5, 1) << endl;
    black_screen.setFillColor({0,0,0,Uint8(a_color)});

    window.draw(black_screen);

    if (int(a_color) <= 0)
    {
        anim_clock.restart();
        return 1;
    }
    return 0;
}