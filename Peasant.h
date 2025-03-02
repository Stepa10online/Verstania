#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Peasant
{
private:
	string texture;
	vector<string> texts;
	wstring name;
	wstring surname;
	wstring sex;
	wstring given_from;
	wstring given_till;
	wstring country;
	wstring town;
	wstring birth;
	int weight;
	string photo_texture;

	// for pasport

	// for right
	static wstring purpose;
	static wstring duration;
	// for qr

	struct data_naming { wstring sex; wstring name; wstring surname; };
	static data_naming name_list[100];
	static data_naming false_name_list[100];
	static wstring purpose_list[100];
	static wstring duration_list[100];




public:
	struct Data {
		// passport
		wstring name;
		wstring surname;
		wstring sex;
		wstring country;
		wstring birth;
		wstring till;
		wstring town;
		wstring index;
		wstring photo_texture;
		// pass
		wstring pass_till;
		// qrcode
		wstring qrcode_texture;
		wstring qrcode_index;
		// right
		wstring right_name;
		wstring right_surname;
		wstring right_purpose;
		wstring right_till;
		wstring right_id;
		wstring right_duration;
	} static data;
	enum data_name {
		Name,
		Surname,
		Country,
		Sex,
		Index,
		Town,
		Birth,
		PhotoTexture,
		Till,
		PassTill,
		RightTill,
		RightIndex,
		RightPurpose,
		RightDuration,
		RightName,
		RightSurname,
		QrcodeIndex,
		QrcodeTexture,
	};
	struct CountryIndex {
		wstring verstania[100];
		wstring orban[100];
		wstring mpdr[100];
		wstring neitral[100];
		wstring usr[100];
	} static index_list;

	void setName(wstring name) { this->name = name; }
	void setSurname(wstring surname) { this->surname = surname; }
	void setSex(wstring sex) { this->sex = sex; }
	void setBirth(wstring birth) { this->birth = birth; }
	void setTown(wstring town) { this->town = town; }
	void setGivenFrom(wstring given) { this->given_from = given; }
	void setGivenTill(wstring given) { this->given_till = given; }
	void setCountry(wstring country) { this->country = country; } 
	void setWeight(int weight) { this->weight = weight; }
	void setConstData(string photo_texture)
	{
		this->photo_texture = photo_texture;
	}

	static data_naming* getNameList() { return name_list; }
	static data_naming* getFalseNameList() { return false_name_list; }
	static wstring* getPurposeList() { return purpose_list; }
	static wstring* getDurationList() { return duration_list; }

	static Data getData() { return data; }
	static void setData(const data_name& d1, const wstring& d2)
	{

		switch (d1)
		{
		case Peasant::Name:
			data.name = d2;
			break;
		case Peasant::Surname:
			data.surname = d2;
			break;
		case Peasant::Country:
			data.country = d2;
			break;
		case Peasant::Sex:
			data.sex = d2;
			break;
		case Peasant::Index:
			data.index = d2;
			break;
		case Peasant::Birth:
			data.birth = d2;
			break;
		case Peasant::PhotoTexture:
			data.photo_texture = d2;
			break;
		case Peasant::Till:
			data.till = d2;
			break;
		case Peasant::Town:
			data.town = d2;
			break;
		case Peasant::PassTill:
			data.pass_till = d2;
			break;
		case Peasant::RightTill:
			data.right_till = d2;
			break;
		case Peasant::RightName:
			data.right_name = d2;
			break;
		case Peasant::RightIndex:
			data.right_id = d2;
			break;
		case Peasant::RightSurname:
			data.right_surname = d2;
			break;
		case Peasant::RightPurpose:
			data.right_purpose = d2;
			break;
		case Peasant::RightDuration:
			data.right_duration = d2;
			break;
		case Peasant::QrcodeIndex:
			data.qrcode_index = d2;
			break;
		case Peasant::QrcodeTexture:
			data.qrcode_texture = d2;
			break;
		default:
			break;
		}
	}
	wstring getSex() { return this->sex; }
	wstring getBirth() { return this->birth; }
	wstring getName() { return this->name; }
	wstring getSurname() { return this->surname; }
	wstring getCountry() { return this->country; }
	wstring getTown() { return this->town; }

};
Peasant::Data Peasant::data = { L"name",L"surname",L"sex",L"country",L"birth",L"till",L"pass_till",L"town",L"index",L"photo_texture", L"qrcode_texture", L"qrcode_index", L"right_name", L"right_surname",L"right_purpose", L"right_till", L"right_duration", };
Peasant::data_naming Peasant::name_list[] = {
		{L"M", L"Альбрахам", L"Вирд"},
		{L"M", L"Васнилав", L"Числов"},
		{L"M", L"Апоров", L"Ложницкий"},
		{L"M", L"Этож", L"Цункейдо"},
		{L"M", L"Нетето", L"Юрко"},
		{L"M", L"Тахарт", L"Ниртэк"},
		{L"M", L"Джоржи", L"Котсава"},
		{L"M", L"Тивар", L"Фенльев"},
		{L"M", L"Пельр", L"Синитер"},
		{L"M", L"Лонтак", L"Шозар"},
		{L"M", L"Тахион", L"Блак"}, // X
		{L"M", L"Борис", L"Ковал"}, // X
		{L"M", L"Зем", L"Миклев"}, // X
		// JDH993fd
		{L"F", L"nF1", L"sF1"},
		{L"F", L"nF2", L"sF2"},
		{L"F", L"nF3", L"sF3"},
		{L"F", L"nF4", L"sF4"},
		{L"F", L"nF5", L"sF5"},
		{L"F", L"nF6", L"sF6"},
		{L"F", L"nF7", L"sF7"},
		{L"F", L"nF8", L"sF8"},
		{L"F", L"nF9", L"sF9"},
		{L"F", L"nF10", L"sF10"},
		{L"F", L"nF11", L"sF11"},
};
Peasant::data_naming Peasant::false_name_list[] = {
		{L"M", L"Алъбрахам", L"Вирд"},
		{L"M", L"Васнилав", L"Чизлов"},
		{L"M", L"Апоров", L"Ложицкий"},
		{L"M", L"Этаж", L"Цункейдо"},
		{L"M", L"Нетэто", L"Юрко"},
		{L"M", L"Тахарт", L"Ниртек"},
		{L"M", L"Джоржи", L"Костава"},
		{L"M", L"Тивор", L"Фенльев"},
		{L"M", L"Пельр", L"Синетер"},
		{L"M", L"Лонтак", L"Щозар"},
		{L"M", L"Тахион", L"Блакк"}, // X
		{L"M", L"Борисс", L"Ковал"}, // X
		{L"M", L"Зем", L"Милкев"}, // X
		// JDH993fd
		{L"F", L"nF1-f", L"sF1-f"},
		{L"F", L"nF2-f", L"sF2-f"},
		{L"F", L"nF3-f", L"sF3-f"},
		{L"F", L"nF4-f", L"sF4-f"},
		{L"F", L"nF5-f", L"sF5-f"},
		{L"F", L"nF6-f", L"sF6-f"},
		{L"F", L"nF7-f", L"sF7-f"},
		{L"F", L"nF8-f", L"sF8-f"},
		{L"F", L"nF9-f", L"sF9-f"},
		{L"F", L"nF10-f", L"sF10-f"},
		{L"F", L"nF11-f", L"sF11-f"},
};
wstring Peasant::purpose_list[] = {
	L"В гости",
	L"Транзит",
	L"Работа",
};
wstring Peasant::duration_list[] = {
	L"ПОСТОЯННО",
	L"1 День",
	L"2 Дня",
	L"3 Дня",
	L"7 Дней",
	L"14 Дней",
	L"1 Мес",
	L"3 Мес",
	L"6 Мес",
	L"12 Мес",
	L"1 Год",
	L"2 Года",
};
Peasant::CountryIndex  Peasant::index_list = {
/* verstaina */	{L"",L"",}, // fromat: { sim, num } ...-...
/*   orban   */	{L"",L"",}, // fromat: { sim }		sssss
/*   mpdr    */	{L"",L"",}, // fromat: { sim, num } nnns
/*    usr    */	{L"",L"",}, // fromat: { sim, num } U..S..R.
/*  neitral  */	{L"",L"",}, // fromat: { num }		nnnn
};