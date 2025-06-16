#pragma once
#include "Document_class.h"
class Stamp
{
private:
	static Vector2f position;
	static string stamp_texture;
	static unsigned int pressed;
	static bool colliding;
	static bool hidden;
	static bool accepted;
public:
	Stamp(Vector2f pos = {0,0}, string texture = "")
	{
		position = pos;
		stamp_texture = texture;
	}
	static void setStampOffset(Vector2f offset)
	{
		position = offset;
	}
	static Vector2f getStampOffset()
	{
		return position;
	}
	static void setTexture(string texture)
	{
		stamp_texture = texture;
	}
	static string getTexture()
	{
		return stamp_texture;
	}
	static void setColliding(const bool& state) { colliding = state; }
	static const bool& getColliding() { return colliding; }
	static void setHidden(const bool& state) { hidden = state; }
	static bool getHidden() { return hidden; }
	static void setAccepted(const bool& state ) { accepted = state; }
	static bool getAccepted() { return accepted; }
	//1 - accepted
	//2 - denied
	//0 - nothing
	static unsigned int& getPressed() { return pressed; }
	//1 - accepted
	//2 - denied
	//0 - nothing
	static void setPressed(unsigned int state) { pressed = state;  }

};
		Vector2f Stamp::position = {0,0};
		string Stamp::stamp_texture = "denied";
		int unsigned Stamp::pressed = 0;
		bool Stamp::colliding = false;
		bool Stamp::hidden = false;
		bool Stamp::accepted = false;


class Passport : public Document
{
public:
	struct PassportData
	{
		wstring name;
		wstring surname;
		wstring country;
		wstring birth;
		wstring town;
		wstring id;
		wstring sex;
		wstring till;
	};
	enum State
	{
		USUAL,
		TEMP_VISA,
	};

	void setPassportData(PassportData tpd)
	{
		passport_data.name = tpd.name;
		passport_data.surname = tpd.surname;
		passport_data.country = tpd.country;
		passport_data.birth = tpd.birth;
		passport_data.town = tpd.town;
		passport_data.id = tpd.id;
		passport_data.sex = tpd.sex;
		passport_data.till = tpd.till;
	}
	static PassportData& getPassportData()
	{
		return passport_data;
	}
	static void setStamped(bool state)
	{
		stamped = state;
	}
	static bool getStamped()
	{
		return stamped;
	}

	void setStampTexture(string texture)
	{
		stamp.setTexture(texture);
		if (Stamp::getPressed())
		{
			state = 1;
			cout << "Setted ACCEPTED stamp. State changed" << endl;
		}
		if (Stamp::getPressed())
		{
			state = 2;
			cout << "Setted DENIED stamp. State changed" << endl;
		}
	}
	string getStampTexture()
	{
		return stamp.getTexture();
	}
	void setStampOffset(Vector2f offset)
	{
		stamp.setStampOffset(offset);
	}
	static Vector2f getStampOffset()
	{
		return stamp.getStampOffset();
	}



private:
	Image image;
	static bool stamped;
	unsigned int state; // 0-undefied 1-accepted 2-denied
	static Stamp stamp;
	static PassportData passport_data;
};
		Passport::PassportData Passport::passport_data = {L".s",L",",L"1"};
		bool Passport::stamped = false;
		bool Document::give_new_docs = true;

class InteractionElement
{
private:
	Vector2f pos;
	Vector2f size;
	string id;
	bool pressed = false;

public:
	enum Element
	{
		Pressed,
		Position,
		Size,
		Id
	};
	InteractionElement(Vector2f pos, Vector2f size, string id)
	{
		this->pos = pos;
		this->size = size;
		this->id = id;
	}
	void setPosition(Vector2f pos)
	{
		this->pos = pos;
	}
	void setSize(Vector2f size)
	{
		this->size = size;
	}
	void setID(string id)
	{
		this->id = id;
	}
	void setPressed(bool state)
	{
		this->pressed = state;
	}
	Vector2f getPosition()
	{
		return this->pos;
	}
	Vector2f getSize()
	{
		return this->size;
	}
	string getID()
	{
		return this->id;
	}
	bool getPressed()
	{
		return this->pressed;
	}
};
class Rules : public Document
{
private:
	vector<vector<InteractionElement>>all_interaction_elements = {};
	int page=0;
	struct InterElem {
		Vector2f pos;
		Vector2f size;
		string id;
		bool pressed;
	};
public:
	void addInterElem(int page, Vector2f pos, Vector2f size, string id)
	{
		all_interaction_elements[page].push_back(InteractionElement(pos, size, id));
	}
	int getCurrentPage() { return this->page; }
	void setCurrentPage(int page) { this->page = page; }

	void setInterElem(int i, Vector2f pos = { 0,0 }, Vector2f size = { 10,10, }, string id = "", bool pressed = false)
	{
		all_interaction_elements[page][i].setPosition(pos);
		all_interaction_elements[page][i].setSize(size);
		all_interaction_elements[page][i].setPressed(pressed);
		all_interaction_elements[page][i].setID(id);
	}
	void setPressed(int i, bool pressed)
	{
		all_interaction_elements[page][i].setPressed(pressed);
	}
	InterElem getInterElem(int i)
	{
		return {
			all_interaction_elements[page][i].getPosition(),
			all_interaction_elements[page][i].getSize(),
			all_interaction_elements[page][i].getID(),
			all_interaction_elements[page][i].getPressed()
		};
	}
	int getIEAmount()
	{
		return all_interaction_elements[page].size();
	}

};
class Pass
{
private:
	wstring text; // date till:<(string)date>
public:
	Pass() {}
	Pass(wstring text)
	{
		this->text = text;
	}
	void setText(wstring text)
	{
		this->text = text;
	}
	wstring getText()
	{
		return this->text;
	}
};
class Papers : public Document
{
private:
	struct text
	{
		wstring str;
		Vector2f pos;
	};
	vector<text> texts;
public:
	Papers(string texture_name = "placeholder.png")
	{
		this->setTexture(0, texture_name);
	}
	void setString(const unsigned int& i, const wstring& str)
	{
		if (i <= texts.size())
			texts[i].str = str;
		else
			wcout << "[ERROR OUT OF RANGE]\t{message: \"" << str << "\" index:" << i << " }" << endl;
	}
	void appendText(const wstring& str, const Vector2f& pos)
	{
		texts.push_back({ str, pos });
	}
	void read_current_text(const unsigned int& i)
	{
		if (i < texts.size())
			wcout << "(" << i << ") STR: \"" << texts[i].str << "\"\tPOS: x:" << texts[i].pos.x << " y:" << texts[i].pos.y << endl;
		else
			cout << "[ERROR OUT OF RANGE] (\"read_current_text\") INDEX: " << i << endl;
	}
	void read_all_texts()
	{
		for (int i = 0; i < texts.size(); i++)
		{
			wcout << "[" << i << "] STR: \"" << texts[i].str << "\"\tPOS: x:" << texts[i].pos.x << " y:" << texts[i].pos.y << endl;
		}
	}
	vector<text>& getTexts() { return this->texts; }

};