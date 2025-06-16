#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Document
{
public:
	enum class Document_ID
	{
		None,
		Passport,
		Pass,
		Right,
		QR,
		Internet_rules,
	};
private:
	struct element
	{
		float x;
		float y;
		float w;
		float h;
		bool validity;
	};
	enum animation_type
	{
		None,
		Linear,
		Bounce,
		EaseIn,
		EaseOut,
	};
private:	
	Vector2f size;
	Vector2f position;
	Vector2f scale = {1,1};
	string* texture;
	Document_ID document_ID;
	bool selected = false;

   // juice
	int anim_tick = 0;
	int max_anim_tick = 100;
	bool animation_playing = false;
	animation_type animation_type = Linear;

	
	vector<element>document_elements = {};
	vector<string> additional_data = {};
	bool dragging = false;
	// DEBUG
	Color color;
	bool static give_new_docs;
public:
	Document(Vector2f size = {200,200}, 
		Vector2f position = { 0,0 }, 
		Document_ID doc_ID = Document_ID::None, 
		vector<string> textures = { },
		vector<string> additional_data = {},
		Color color = Color::White)
	{
		this->size = size;
		this->position = position;
		for (int i = 0; i < textures.size(); i++) this->texture[i] = textures[i];
		this->document_ID = doc_ID;
		this->additional_data = additional_data;
		this->color = color;
	}

	void		setPosition(Vector2f);
	void		setSize(Vector2f);
	void		setTexture(int, string);
	void		setScale(Vector2f);
	void		setDocID(Document_ID);
	void		setSelected(bool selected) { this->selected = selected; }
	void		setElement(Vector2f, Vector2f, bool);
	void		setElement(int, Vector2f, Vector2f, bool);
	void		setDragging(bool state) { this->dragging = state; }
	void static setGiveNewDocs(bool state) { give_new_docs = state; }
	void		setColor(Color color) { this->color = color; }
	void		setAdditionalData(const string& data) { this->additional_data.push_back(data); }

	Vector2f		getPosition();
	Vector2f		getSize();
	Vector2f&		getScale() { return this->scale; }
	string*			getTexture();
	Document_ID		getDocID();
	bool			getSelected() { return this->selected; }
	element			getElement(int i){return this->document_elements[i];}
	int				getElementsAmount() { return this->document_elements.size(); }
	bool			getDragging() { return this->dragging; }
	bool static		getGiveNewDocs() { return give_new_docs; }
	Color			getColor() { return this->color; }
	vector<string>	getAdditionalData() { return this->additional_data; }
	bool			isAdditionalDataContains(const string&);
	bool			editAdditionalData(const string&, const string&);

	void		Update();
	void		move(Vector2f);
	void		move(float,float);

	void		anim_update();
	void		anim_pop_up(float&, float, float);
	void		anim_pop_down(float&, float, float);
	bool		is_anim_playing() { return this->animation_playing; }
	void		anim_start() { this->animation_playing = true; this->anim_tick = 0; }
	void		anim_stop() { this->anim_tick = 0; this->animation_playing = false; }

	// DEBUG

};