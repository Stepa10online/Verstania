#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Monolog
{
public:
	Monolog(const bool& face = true, const string& text_string = "Text Placeholder")
	{
		this->face = face;
		this->text_string = text_string;
	}
	void setString(string text)
	{
		this->text_string = text;
	}
	void setFace(bool state)
	{
		this->face = state;
	}
	const string& getString()
	{
		return this->text_string;
	}
	const bool getFace()
	{
		return this->face;
	}
	bool check()
	{
		if (this->monolog_clock.getElapsedTime().asSeconds() > 3)
		{
			return true;
		}
		return false;
	}
		
		/*void playText(RenderWindow& window)
	{
		RectangleShape rect;
		Font font;
		Text txt;
		Vector2f size = { 30,50 };
		for (int i = 0; i < text.size(); i++)
		{
			char simb = text[i];
			if (simb != '\n')
			{
				if (simb == 'i' || simb == 'l' || simb == '!' ||
					simb == 'r' || simb == 't')
					size.x += 3;
				else
					size.x += 7;
			}
			else
				size.y += 25;
		}

		if (face)
		{
			rect.setPosition(500, 25);
			txt.setPosition(500 + 10, 25 + 5);
		}
		else
		{
			rect.setPosition(1425 - size.x-5, 25);
			txt.setPosition(1425 - size.x+5, 25 + 5);
		}
		rect.setSize(size);
		font.loadFromFile("BOD_CR.TTF");
		txt.setFont(font);
		txt.setCharacterSize(25);
		txt.setString(text);
		txt.setFillColor(Color::Red);
		window.draw(rect);
		window.draw(txt);
	}
	*/
	
private:
	string text_string;
	bool face = true; // true - inspector, false - other
	Clock monolog_clock;
};