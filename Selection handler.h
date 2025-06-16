#pragma once
#include "Selection.h"
#include "all_docs.h"
#include "Variables.h"
#include "Interactions.h"
#include "Selection.h"


void handler_Selection(vector<Document>& docs, const Vector2i& m_pos)
{
    for (int i = docs.size() - 1; i >= 0; i--)
    {
        if (CollisionPointRect({ float(m_pos.x),float(m_pos.y) }, { docs[i].getPosition(),docs[i].getSize() }))
        {
            if (Interaction::IsAnyElement(Interaction::Data::Mouse_Left_DoubleClick)
                && docs[i].getDocID() == Document::Document_ID::Passport && Stamp::getColliding() == false)
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
    //if (Interaction::IsAnyElement(Interaction::Data::Mouse_Left_DoubleClick))
    //{
    //}
}