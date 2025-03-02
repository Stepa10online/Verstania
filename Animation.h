#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Animation
{
public:
	Animation();
	
	void setTexture(string texture_name) { this->texture_name = texture_name; }
	void setAnimationStart(int start) { this->animation_frame_s = start; }
	void setAnimationEnd(int end) { this->animation_frame_e = end; }
	void setAnimationStep(int step) { this->animation_step = step; }
	void setFrameTime(float time) { this->frame_time = time; }
	void setFrame(FloatRect size) { this->frame_size = size; }
	void setScale(Vector2f scale) { this->scale = scale; }
	void setPosition(Vector2f position) { this->position = position; }
	void play(RenderWindow& window, int frame);
	bool getPlayed() { return this->played; }
	void stop() { this->played = false; }

private:
	Clock clock;
	// animation settings
	bool played = false;
	bool stoped = false;
	FloatRect frame_size;
	float frame_time = 0;
	int animation_frame_s=0;
	int animation_frame_e = -1;
	int animation_step=1;
	int frame_x = animation_frame_s, frame_y = 0;
	// sprite settings
	string texture_name = "Animation_check.png";
	Vector2f scale = {1,1};
	Vector2f position;
};

Animation::Animation()
{
}
void Animation::play(RenderWindow&window, int frame = -1)
{
	if (played == true)
	{
		frame_x = 0;
		frame_y = 0;
		played = false;
	}
	if (stoped == true) return;
	float cur_time = clock.getElapsedTime().asSeconds();
	Texture texture;
	texture.loadFromFile(this->texture_name);
	Sprite sprite;
	sprite.setTexture(texture);
	int max_frame_amount = texture.getSize().x / frame_size.width;
	/* if (frame_x > max_frame_amount){ frame_y++; frame_x = 0; } */
	if (frame != -1)
		frame_x = frame;
	sprite.setTextureRect(IntRect{
		int(this->frame_size.left + this->frame_size.width * frame_x + this->frame_size.width * animation_frame_s),
		int(this->frame_size.top + this->frame_size.height * frame_y),
		int(this->frame_size.width),
		int(this->frame_size.height)
		});
	sprite.setScale(scale);
	sprite.setPosition(this->position);
	window.draw(sprite);

	if(cur_time >= this->frame_time)
	{
		frame_x += this->animation_step;
		cur_time = 0;
		clock.restart();
	}
	if (frame_x + animation_frame_s >= max_frame_amount)
		played = true;
	/*if(animation_frame_e == -1)
	{
		cout << "max_frame_amount" << endl;
		if (animation_step > 0)
			if (frame_x + animation_frame_s >= max_frame_amount)
				played = true;
		else
			if (frame_x - animation_frame_s <= max_frame_amount)
				played = true;
	}
	else
	{
		cout << "animation_frame_e" << endl;
		if(animation_step > 0)
			if (frame_x + animation_frame_s >= animation_frame_e)
				played = true;
		else
			if (frame_x - animation_frame_s <= animation_frame_e)
				played = true;
	}*/

}










/* Анимации */