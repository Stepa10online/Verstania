#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

#include "DialogText.h"

class Dialog_mngr
{
public:
	void play_dialog(Clock& dialog_clock)
	{
		if(start_dialog == false)
		{
			start_dialog = true;
			dialog_clock.restart();
		}
		
	}
	void DialogUpdate()
	{

	}
	void DrawDialogWindow(RenderWindow& window, const Clock& dialog_clock)
	{
		for (int i = 0; i < dialog[0].size();)
		{
			DrawSprite(window, pos[dialog[0][i].getFace()]);
			DrawText(window, font, dialog[0][i].getString(), pos[dialog[0][i].getFace()]);
			if (dialog[0][i].check())
				i++;
		}
		if (dialog_clock.getElapsedTime().asSeconds() > 1.5)
		for (int i = 0; i < dialog[1].size(); i++)
		{
			if (dialog[1][queue_number].check())
				queue_number++;
			DrawSprite(window, pos[dialog[1][queue_number].getFace()]);
			DrawText(window, font, dialog[1][queue_number].getString(), pos[dialog[1][queue_number].getFace()]);
		}
	}
	const bool setDialogFont(const string& path)
	{
		return font.loadFromFile(path);
	}
	void AppendText(bool dialog_face, string text)
	{
		dialog[dialog_face].push_back(Monolog(dialog_face, text));
	}
	void setText(bool dialog_face, int index, string text)
	{
		if(dialog[dialog_face].size() > index) dialog[dialog_face][index] = Monolog(dialog_face, text);
	}
	void set_dialog(bool dialog_face, vector<Monolog> dialog)
	{
		this->dialog[dialog_face] = dialog;
	}
private:
	void DrawText(RenderWindow&, const Font&, const string&, const Vector2f&);
	void DrawSprite(RenderWindow&, const Vector2f&);

	int queue_number = 0;
	Font font;
	Vector2f pos[2] = { {100,100},{500,100} };
	vector<Monolog> dialog[2];

	bool start_dialog = false; // как только начнется диалог, произойдет отсчет времени, а это указывает начался ли диалог
};