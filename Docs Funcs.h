#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
#include "Collision.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "UI elements.h"
#include "Document_class.h"
#include "all_docs.h"
#include "Variables.h"


////////////////////////////////////////////////////////////// CHANGE ORDER OF PAPERS

// ������ ������� ���������� � vector ��� ����������� ������ ������ ������ ������
// i - ������ ���������, ������� ����� ����������� ������
void change_order(vector<Document>& docs, int i)
{
    Document temp_doc = docs[i];
    for (int j = i; j < docs.size() - 1; j++)
    {
        docs[j] = docs[j + 1];
    }
    docs[docs.size() - 1] = temp_doc;
}

////////////////////////////////////////////////////////////// DRAWING


void DrawPassport(RenderWindow& window, Image& passport_image_stamped, const Image& stamp_img, Sprite& spr)
{
    Texture txr;
    if(Passport::getStamped())
    for (int y = 0; y < stamp_img.getSize().y; y++)
    {
        for (int x = 0; x < stamp_img.getSize().x; x++)
        {
            if (Passport::getStampOffset().x + x >= passport_image_stamped.getSize().x) continue;
            if (Passport::getStampOffset().y + y >= passport_image_stamped.getSize().y) continue;
            if (Passport::getStampOffset().x + x <= 0) continue;
            if (Passport::getStampOffset().y + y <= 0) continue;
            if (stamp_img.getPixel(x, y) == Color::Transparent) continue;

            passport_image_stamped.setPixel(Passport::getStampOffset().x + x, Passport::getStampOffset().y + y, stamp_img.getPixel(x, y));
        }
    }

    spr.setScale(1, 1);
    txr.loadFromImage(passport_image_stamped);
    spr.setTexture(txr);
    window.draw(spr);
    txr.loadFromImage(passport_image_stamped);
    spr.setTexture(txr);

    window.draw(spr);
}

void DrawPassportText(RenderWindow& window, Font font, Text text, float doc_pos_x, float doc_pos_y)
{
    
    static struct Passport::PassportData* pd = &Passport::getPassportData();
    //if (pd->country == L"verstania")
    
    {
        // name + surname
        text.setString(pd->name + L" " + pd->surname);
        text.setPosition({ doc_pos_x + 20,doc_pos_y + 243 });
        window.draw(text);
        // birth
        text.setPosition({ doc_pos_x + 64,doc_pos_y + 274 });
        text.setString(pd->birth);
        window.draw(text);
        // sex
        text.setPosition({ doc_pos_x + 64,doc_pos_y + 305 });
        text.setString(pd->sex);
        window.draw(text);
        // town
        text.setPosition({ doc_pos_x + 64,doc_pos_y + 336 });
        text.setString(pd->town);
        window.draw(text);
        // till
        text.setPosition({ doc_pos_x + 64,doc_pos_y + 367 });
        text.setString(pd->till);
        window.draw(text);
        // index
        text.setPosition({ doc_pos_x + 213, doc_pos_y + 403 });
        text.setString(pd->id);
        window.draw(text);
    }
}

void DrawDocuments(RenderWindow& window, vector<Document>& docs, Font font, Text text, 
    Passport& passport, Pass& pass, Papers Right, Image& image)
{
    Image img = image, stamp_img;
    Texture texture;
    Sprite sprite;

    stamp_img.loadFromFile(Stamp::getTexture());
    
    text.setFillColor(Color::Black);

    if (!Passport::getOpened())
    {
        img.loadFromFile(passport.getTextureName());
    }
    if (Passport::getOpened())
    {
        img.loadFromFile(passport.getOpenedTextureName());
    }

    for (auto& doc : docs)
    {
        float doc_pos_x = doc.getPosition().x;
        float doc_pos_y = doc.getPosition().y;
        if (doc.getDocID() == "passport")
        {
            sprite.setTextureRect({ 0,0,int(img.getSize().x),int(img.getSize().y) });
            sprite.setPosition(doc.getPosition());
            DrawPassport(window, img, stamp_img, sprite);
            image = img;
            if(Passport::getOpened())
                DrawPassportText(window, font, text, doc_pos_x, doc_pos_y);
        }
        if (doc.getDocID() == "pass")
        {
            Text pass_text;
            pass_text.setFont(font);
            image.loadFromFile("pass.png");
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            sprite.setTextureRect({ 0,0,(int)(texture.getSize().x),(int)(texture.getSize().y) });
            sprite.setScale(2, 2);
            sprite.setPosition(Vector2f{ doc_pos_x,doc_pos_y });
            pass_text.setFillColor(Color{ 123,123,123,255 });
            pass_text.setPosition(Vector2f{ doc_pos_x,doc_pos_y } + Vector2f{ 12 * sprite.getScale().x,42 * sprite.getScale().y });
            pass_text.setString(pass.getText());
            pass_text.setCharacterSize(100);
            pass_text.setScale(0.25, 0.25);
            window.draw(sprite);
            window.draw(pass_text);
            continue;
        }
        if (doc.getDocID() == "rules")
        {
            //for (int i = 0; i < rules.getIEAmount(); i++)
            //{
            //    RectangleShape element;
            //    if (rules.getInterElem(i).pressed) element.setFillColor(Color::Red);
            //    else element.setFillColor(Color::Green);
            //    element.setPosition(Vector2f{ doc_pos_x,doc_pos_y } + rules.getInterElem(i).pos);
            //    element.setSize(rules.getInterElem(i).size);
            //    window.draw(element);
            //}
            continue;
        }
        if (doc.getDocID() == "right")
        {
            texture.loadFromFile(Right.getTextureName());
            sprite.setTexture(texture);
            sprite.setTextureRect(IntRect{ 0,0,192,256 });
            sprite.setPosition(Vector2f{ doc_pos_x,doc_pos_y });
            sprite.setScale(2, 2);
            window.draw(sprite);
            Text text;
            font.loadFromFile("pixelplay.ttf");
            for (int i = 0; i < Right.getTexts().size(); i++)
            {
                text.setString(Right.getTexts()[i].str);
                text.setPosition(Right.getTexts()[i].pos + Vector2f{ doc_pos_x,doc_pos_y });
                text.setFillColor(Color::Black);
                text.setFont(font);
                window.draw(text);
            }
            continue;
        }
        if (doc.getDocID() == "qr")
        {
            if (qr_scanner_check)
            {
                texture.loadFromFile("sprites\\papers\\qr code little.png");
                sprite.setTextureRect({ 0,0,25,34 });
            }
            else if (doc_pos_y + 329 / 2 < 500)
            {
                texture.loadFromFile("sprites\\papers\\qr code little rotated.png");
                sprite.setTextureRect({ 0,0,32,37 });
            }
            else
            {
                texture.loadFromFile("sprites\\papers\\qr code.png");
                sprite.setTextureRect({ 0,0,36,47 });
            }
            sprite.setTexture(texture);
            sprite.setPosition(doc_pos_x, doc_pos_y);
            sprite.setScale(7, 7);
            window.draw(sprite);

            if (doc_pos_y + 329 / 2 >= 500)
            {
                Text text;
                text.setFont(font);
                text.setFillColor({ 136,149,135,255 });
                text.setPosition(Vector2f{ 30,245 } + Vector2f{ doc_pos_x,doc_pos_y });
                text.setString("INDEX\nNAME__. SURNA.");
                window.draw(text);
                text.setString(L"�������� � �������");
                text.setCharacterSize(20);
                text.setPosition(Vector2f{ 30,0 } + Vector2f{ doc_pos_x,doc_pos_y });
                window.draw(text);
            }

            continue;
        }
    }
    /*
    for (auto& document : docs)
    {
        Image image; // stamp image
        Texture texture;
        Sprite sprite;
        float doc_pos_x = document.getPosition().x;
        float doc_pos_y = document.getPosition().y;
        if (document.getDocID() == "passport")
        {

            if (Passport::getOpened() && Passport::getStamped())
                image.loadFromFile(passport.getStampTexture());
            else if (!Passport::getStamped())
                image_main.loadFromFile(passport.getOpenedTextureName());
            for (int y = 0; y < image.getSize().y; y++)
                for (int x = 0; x < image.getSize().x; x++)
                {
                    if (passport.getStampOffset().x + x >= image_main.getSize().x) continue;
                    if (passport.getStampOffset().y + y >= image_main.getSize().y) continue;
                    if (passport.getStampOffset().x + x <= 0) continue;
                    if (passport.getStampOffset().y + y <= 0) continue;
                    if (image.getPixel(x, y) == Color::Transparent) continue;
                    //if (image.getPixel(x, y) == Color{ 201, 181, 151, 255 }) continue;
                    //image_main.setPixel(x, y, image.getPixel(x,y));
                    image_main.setPixel(passport.getStampOffset().x + x, passport.getStampOffset().y + y, image.getPixel(x, y));
                }
            //if(passport.getStatus() == Passport::TEMP_VISA)
            //    texture.loadFromImage(image_main); // texture with stamp
            //else
            if (passport.getOpened())
            {
                cout << "[DEBUG] passport opened" << endl;
                texture.loadFromImage(image_main); // texture with stamp
            }
            else
            {
                texture.loadFromImage(closed_main_image); // texture without stamp
            }
            sprite.setPosition(Vector2f{ doc_pos_x,doc_pos_y });
            sprite.setTexture(texture);
            window.draw(sprite);
            if (passport.getOpened())
            {
                text.setFillColor(Color{ 154, 175, 147 });
                text.setOutlineColor(Color{ 154, 175, 147 });
                text.setFillColor(Color{ 70,70,70,255 });
                text.setOutlineColor(Color{ 70,70,70,255 });
                struct Passport::PassportData* pd = &Passport::getPassportData();

                if (pd->country == L"verstania")
                {
                    // name + surname
                    text.setString(pd->name + L" " + pd->surname);
                    text.setPosition({ doc_pos_x + 20,doc_pos_y + 243 });
                    window.draw(text);
                    // birth
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 274 });
                    text.setString(pd->birth);
                    window.draw(text);
                    // sex
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 305 });
                    text.setString(pd->sex);
                    window.draw(text);
                    // town
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 336 });
                    text.setString(pd->town);
                    window.draw(text);
                    // till
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 367 });
                    text.setString(pd->till);
                    window.draw(text);
                    // index
                    text.setPosition({ doc_pos_x + 213, doc_pos_y + 403 });
                    text.setString(pd->id);
                    window.draw(text);
                }
                if (pd->country == "orban")
                {
                    // name + surname
                    text.setString(pd->name + L" " + pd->surname);
                    //text.setString(pd->name + ' ' + pd->surname);
                    text.setPosition({ doc_pos_x + 20,doc_pos_y + 243 });
                    window.draw(text);
                    // birth
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 274 });
                    text.setString(pd->birth);
                    window.draw(text);
                    // sex
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 305 });
                    text.setString(pd->sex);
                    window.draw(text);
                    // town
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 336 });
                    text.setString(pd->town);
                    window.draw(text);
                    // till
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 367 });
                    text.setString(pd->till);
                    window.draw(text);
                    // index
                    text.setPosition({ doc_pos_x + 213, doc_pos_y + 403 });
                    text.setString(pd->id);
                    window.draw(text);
                }
                if (pd->country == "MPDR")
                {
                    // name + surname
                    text.setString(pd->name + L" " + pd->surname);
                    //text.setString(pd->name + ' ' + pd->surname);
                    text.setPosition({ doc_pos_x + 20, +243 });
                    window.draw(text);
                    // birth
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 274 });
                    text.setString(pd->birth);
                    window.draw(text);
                    // sex
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 305 });
                    text.setString(pd->sex);
                    window.draw(text);
                    // town
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 336 });
                    text.setString(pd->town);
                    window.draw(text);
                    // till
                    text.setPosition({ doc_pos_x + x_offset,doc_pos_y + 367 });
                    text.setString(pd->till);
                    window.draw(text);
                }
            }
            continue;
        }
        
        if (document.getDocID() == "internet rules")
        {

            RectangleShape doc_rect(document.getSize());
            doc_rect.setFillColor(Color::White);
            doc_rect.setPosition(Vector2f{ doc_pos_x,doc_pos_y });
            window.draw(doc_rect);
            texture.loadFromFile("rules of the internet title.png");
            sprite.setTexture(texture);
            sprite.setTextureRect({ 0,0,108,39 });
            sprite.setPosition(Vector2f{ doc_pos_x,doc_pos_y } + Vector2f{ 150,0 });
            sprite.setScale(1.1, 1.1);
            Text text;
            Font font;
            font.loadFromFile("pixelplay.ttf");
            text.setPosition(Vector2f{ doc_pos_x,doc_pos_y } + Vector2f{ 10,4 });
            static wstring s[] = {
    L"\n1. �� ������ � /b/.\n2. ������ ������� �� ������ � /b/.\n3. �� � ���� ��������.\n4. ��� ��� � ������.\n5. �� �� �������, �� �� ��������.\n6. �������� ����� ���� ��� ������ \n������, ��� � ����� ������������, \n����������� ��������.\n7. ����� � ��� �������� ��������.\n8. ������ �� ����������.\n9. ��� ����������� ������ ���� �� \n���������� � ������������� �����.\n10. ���������� �� ���� �� �������.\n11. ����� ����������� ������ ���� \n����������� �������.",
    L"12. � ��������� ���� ������ �� ����� \n�������.\n13. ������ ������� ���.\n14. �� ����� ������.\n15. ��� ���� ��������� ����������� \n��������� ����� ���� ���������������.\n16. ������� ��� ���.\n17. ����� ��� ����������.\n18. ���� ���� ������ 16-�� �� ����\n������� 17 �� ����������������.\n19. /b/ - ��� �� ���� ������ �����.\n20. ������������� ������� � ����\n��������� ������������� ��������� �\n��������.\n21. �� ����������� �������� �������.\n  22. ������, ����� � ������ ��������",
    L"������ �� � ���� ��������� ��� �\n�������.\n23.������� �����.\n24. / b / ������ ����� ������.\n25.�� � ������, ���� � ��������\n�����������.\n26.������������� ��� ���������.\n27.��������� � ����� ������.�����\n������ ���������.\n28.������� � ��� ��������� ���\n������!\n29.���� � ����������� �����\n����������, ���� �����.\n30.�� ����� �����.\n31.������ ������ ����� ���� ������.",
    L"32.� ������ � 75 % ��� ����\n������������� ����������.\n33.���� ����� �� ������ ���\n������ ������� � ��������� ���������-\n����.\n34.� ���� ���� ����. �������\n����������.\n35.���� ����� � ���� ��� � ����������\n�� ���� ���������.��������,\n�� ������, ��� � ���� ������.\n36.��� �� ��� �� ����, ��� ��������\n���� - �� �������. ��� ����������. \n37.������ � ������� ����� ���������\n�� ��.\n38.� ���� ���� ����� - �����.\n  39.������ ������������� �������-",
    L"����� � ������ ������ ���� ��������-\n���.\n40.������ ������ ����������� ������\n������� �� �����������!\n��� ����������!\n41.� ����� ��������� ���� ����.\n42.���������� ��� ������� 34\n�� ����������.��� �������� � ������\n������� 34.\n43.��������� ������� �� 95 % ��\n�������.\n44.������ � �������� �� ����������.\n����� ������ � ���������� ���������-\n��, ������������ � ����� ����������.\n45.������������� ����� \"�\" ����� \n   �����.",
    L"46. ��������� ������ ��������\n���� ������ � ����� �������, ��� ��\n������ �������.\n47. ��������� ������ �������� ����\n������ �������� � ������ ����.\n48. �� ����� ������� ���� ���� ������.\n49. �������� ���������� ���� ������.\n50. ��������� �� ����� ���� �����.\n51. ������ ����� ������������ �������\n������ ������, ��� ��, ��� �� ������ ���\n�����.\n52. ���� ���-�� ��� �� ��� � � ����\n������� ������.\n53. ��� ������� �� ������� ��������-\n����.\n  54. ��� ������ ������� \"�������\"�",
    L"��� ������� ����.\n55. ������� 35 �� ���������������� ��\n������ ������ 16-�� ���.\n56. �� ����� ����� ���� �������� �����.\n57. 57-��� ������� ���.\n58. ��� �������� � �������� ���-����\n� ��� ������ ��� �������� ���\n�����������.\n59. �� ������ � 69.\n60. ������ ������� �������. �������\n����������.\n61. ���� ������ �������� ����� ������\n���� ��������. � ������ ���������� �\n���� ������������ �������� �����\n��������� ��� �������� ��������\n   (�������� ������� 16).",
    L"62. �������� ��� ���ܨ���� ����� ������.\n63. � ������� ��������� ���� ������\n���������������� ����.\n64. ����� �������� �������.\n65. ��, ��� �������� �� �������������\n��� �������� ����� �������.\n66. ��� ���� �����.\n67. �� �� ����������.\n68. ����� � ��� ������� � �������\n��������.\n69. � ������ ���� ������� ���������� �\n������� ���� ������ ������� 6, �����\n�������� ������� 9, � ������ �����\n��� ���� � �������� �������.\n",
    L"72. ���� � ����-���� ���� 2 ���������,\n�� ��� ����� ������� Bad apple.\n73. ���� � ����-���� ���� �����,\n�� ��� ����� ��������� Doom.\n74. ���� ���-���� ����� ������ ����,\n�� �� ��� ����� ������� Megolovania."
            };
            // 328 419
            static int N = 0;
            InteractionElements::setEnabeButtonOutline(false);
            if (N < 8)
                if (MyImageButton(Vector2f{ doc_pos_x,doc_pos_y } + Vector2f{ 328 - 32,419 - 32 }, { 32,32 }, L"", window, "sprites\\ui\\paper slice.png", { 0,0,16,16 }) == 2)
                    N++;
            if (N > 0)
                if (MyImageButton(Vector2f{ doc_pos_x,doc_pos_y } + Vector2f{ 0,419 - 32 }, { 32,32 }, L"", window, "sprites\\ui\\paper slice.png", { 16,0,16,16 }) == 2)
                    N--;

            //InteractionElements::setEnabeButtonOutline(true);
            if (Keyboard::isKeyPressed(Keyboard::Num1)) N = 0;
            if (Keyboard::isKeyPressed(Keyboard::Num2)) N = 1; text.setPosition(Vector2f{ doc_pos_x,doc_pos_y } + Vector2f{ 10,2 });
            if (Keyboard::isKeyPressed(Keyboard::Num3)) N = 2;
            if (Keyboard::isKeyPressed(Keyboard::Num4)) N = 3;
            if (Keyboard::isKeyPressed(Keyboard::Num5)) N = 4;
            if (Keyboard::isKeyPressed(Keyboard::Num6)) N = 5; text.setPosition(Vector2f{ doc_pos_x,doc_pos_y } + Vector2f{ 10,2 });
            if (Keyboard::isKeyPressed(Keyboard::Num7)) N = 6; text.setPosition(Vector2f{ doc_pos_x,doc_pos_y } + Vector2f{ 10,1 });
            if (Keyboard::isKeyPressed(Keyboard::Num8)) N = 7; text.setPosition(Vector2f{ doc_pos_x,doc_pos_y } + Vector2f{ 8,4 });
            text.setFont(font);
            text.setString(s[N]);
            text.setCharacterSize(20);
            text.setFillColor(Color::Black);

            if (N == 0) window.draw(sprite);
            window.draw(text);


            continue;
        }

        RectangleShape doc_rect(document.getSize());
        doc_rect.setFillColor(document.getColor());
        doc_rect.setPosition(Vector2f{ doc_pos_x,doc_pos_y });
        window.draw(doc_rect);
    }
    */
    
    texture.loadFromImage(stamp_img);
    sprite.setTexture(texture);
    sprite.setPosition(500, 500);
    sprite.setTextureRect({0,0,216,104  });
    sprite.setScale(1, 1);
    window.draw(sprite);
}

void DrawImage(RenderWindow& window, string texture_name)
{
    Image image;
    image.loadFromFile(texture_name);

    for (int i = 0; i < image.getSize().y; i++)
    {
        for (int j = 0; j < image.getSize().x; j++)
        {
            Color color = Color{ 0, image.getPixel(j, i + 1).g, 0, 255 };
            if (i % 2 == 0)
            {
                image.setPixel(j, i, color);
            }
            if (i < image.getSize().y && i % 2 == 1)
            {
                float multiplier = 0.25;// 0.75;
                Color icolor = { Uint8(color.r * multiplier),Uint8(color.g * multiplier),Uint8(color.b * multiplier),color.a };
                //Color icolor = {120,225,50,255};
                image.setPixel(j, i, icolor);
            }

        }
    }

    Texture texture;
    texture.loadFromImage(image);
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(3, 3);
    window.draw(sprite);
}