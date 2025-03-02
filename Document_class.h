#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Document
{
private:
	Vector2f size;
	Vector2f position;
	string texture_name;
	string opened_texture_name;
	string document_ID;
	bool selected = false;
	struct element
	{
		float x;
		float y;
		float w;
		float h;
		bool validity;
	};
	vector<element>document_elements = {};
	bool dragging = false;
	// DEBUG
	Color color;
	bool static give_new_docs;
public:
	Document(Vector2f size = {200,200}, Vector2f position = { 0,0 }, string doc_ID = "NULL", string texture_name = "placeholder.png", string open_texture_name = "placeholder.png", Color color = Color::White)
	{
		this->size = size;
		this->position = position;
		this->texture_name = texture_name;
		this->opened_texture_name = open_texture_name;
		this->color = color;
		this->document_ID = doc_ID;
	}
	Vector2f getPosition();
	Vector2f getSize();
	string getTextureName();
	string getOpenedTextureName();
	string getDocID();
	bool getSelected() { return this->selected; }
	element getElement(int i){return this->document_elements[i];}
	int getElementsAmount() { return this->document_elements.size(); }
	bool getDragging() { return this->dragging; }
	void setDragging(bool state) { this->dragging = state; }
	void setPosition(Vector2f);
	void move(Vector2f);
	void move(float,float);
	void setSize(Vector2f);
	void setTextureName(string);
	void setOpenedTextureName(string);
	void setDocID(string);
	void setSelected(bool selected) { this->selected = selected; }
	void setElement(Vector2f, Vector2f,bool);
	void setElement(int, Vector2f, Vector2f,bool);
	void static setGiveNewDocs(bool state) { give_new_docs = state; }
	bool static getGiveNewDocs() { return give_new_docs; }

	// DEBUG
	Color getColor() { return this->color; }
	void setColor(Color color) { this->color = color; }

};