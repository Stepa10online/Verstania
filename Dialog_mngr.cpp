#include "Dialog_mngr.h"

//bool Dialog_mngr::setDialogFont(const string& path)
//{
//	//return DialogWindow::setFont(path);
//}

void Dialog_mngr::DrawText(RenderWindow& window, const Font& font, const string& text, const Vector2f& pos)
{
	Text dt_text;

	dt_text.setFillColor(Color::Black);
	dt_text.setFont(font);
	dt_text.setString(text);
	dt_text.setPosition(pos);

	window.draw(dt_text);
}

void Dialog_mngr::DrawSprite(RenderWindow& win, const Vector2f& pos)
{
	Texture texture;
	texture.loadFromFile("sprites\\ui\\dialogpopup.png");
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(2,2);
	sprite.setPosition(pos);
	win.draw(sprite);
}
