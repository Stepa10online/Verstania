#pragma once

#include "Game Data.h"
#include "Interface.h"

void handler_Interface_Lists()
{
    Interface::List_functions::UpdateListsActiveness();
    Interface::List_functions::UpdateLists();

    if (!ImGui::IsMouseClicked(ImGuiMouseButton_Left)) return;
    if (Interface::List_functions::IsListActive("List Open"))
    {
        Interface::List_functions::LoadListArea("List Open area");
    }
    if (Interface::List_functions::IsListActive("List About"))
    {
        Interface::List_functions::LoadListArea("List About area");
    }
    if (Interface::List_functions::IsListActive("List Passport country"))
    {
        Interface::List_functions::LoadListArea("List Passport country area");
    }
    if (Interface::List_functions::IsListActive("List Scale"))
    {
        Interface::List_functions::LoadListArea("List Scale area");
    }
    if (Interface::List_functions::IsListActive("List WorkspaceSelector"))
    {
        Interface::List_functions::LoadListArea("List Workspace area");
    }
}

void handler_Interface_Buttons()
{
    if (Interface::InterfaceData::IsButtonPressed("Log in"))
    {
        Interface::UnLoad_Area("Load screen");
        Interface::Load_Area("Main top");
    }

    if (Interface::InterfaceData::IsButtonPressed("Select Workspace"))
    {
        Interface::List_functions::SetActiveList("List WorkspaceSelector");
    }

    if (Interface::InterfaceData::IsButtonPressed("Database"))
    {
        Interface::PopUps::AddPopUp(Interface::PopUps::PopUp_class::Warning, "db err",
            "Error.type.none Error.type.none Error.type.none\n\
Error.type.none Error.type.none Error.type.none\n\
Error.type.none Error.type.none Error.type.none\n\
Error.type.none Error.type.none Error.type.none\n\
Error.type.none Error.type.none",
            { 0,70 }, { 2,2 });
    }

    if (Interface::InterfaceData::IsButtonPressed("Open"))
    {
        Interface::List_functions::SetActiveList("List Open");
    }

    if (Interface::InterfaceData::IsButtonPressed("About"))
    {
        Interface::List_functions::SetActiveList("List About");
    }
    
    if (Interface::InterfaceData::IsButtonPressed("Passport"))
    {
        Interface::List_functions::SetActiveList("List Passport country");
    }

    if (Interface::InterfaceData::IsButtonPressed("Scale"))
    {
        Interface::List_functions::SetActiveList("List Scale");
    }

    if (Interface::InterfaceData::IsButtonPressed("Exit"))
    {
        Interface::UnLoad_All_Areas();
        Interface::Load_Area("Load screen");
    }
    
    if (Interface::List_functions::IsListActive("List Open") &&
        Interface::List_functions::WhatListElementPressed() == "Documents")
    {
     /// Unloaders
        Interface::UnLoad_Area("Map page");
        Interface::UnLoad_Area("Tasks page");
     /// Loaders
        Interface::Load_Area("Documents page");
    }
    
    if (Interface::List_functions::IsListActive("List Open") &&
        Interface::List_functions::WhatListElementPressed() == "Map")
    {
     /// Unloaders
        Interface::UnLoad_Area("Documents page");
        Interface::UnLoad_Area("Tasks page");
     /// Loaders
        Interface::Load_Area("Map page");

    }

    if (Interface::List_functions::IsListActive("List Open") &&
        Interface::List_functions::WhatListElementPressed() == "Tasks")
    {
     /// Unloaders
        Interface::UnLoad_Area("Documents page");
        Interface::UnLoad_Area("Map page");
     /// Loaders
        Interface::Load_Area("Tasks page");
    }

    if (Interface::List_functions::IsListActive("List Open") &&
        Interface::List_functions::WhatListElementPressed() == "Scan")
    {
        //Interface::LoadOnly("Document page1", "Document page2", "Document page3");

     /// Unloaders
        //Interface::UnLoadArea("Documents page");
        //Interface::UnLoadArea("Map page");
        //Interface::LoadArea("Tasks page");
     /// Loaders
    }

    if (ImGui::IsKeyPressed(ImGuiKey_A))
    {
        cout << "Added new ME: " << Interface::movls.size() << endl;
        Interface::MoveEl::AddMoveEl("test" + to_string(Interface::movls.size()), { 100,100 }, "",
            "sprites\\ui\\Computer Interface\\popup-Warning-movable.png", 
            { {"ok", true}, {"close", false}, {"cancel", true} }, { 2, 2 });
        
    }

}

void handler_InterfaceElements()
{
// additional updates
    Interface::CheckBoxes::CheckBoxesUpdate();
    Interface::PopUps::PopUpsUpdate();
    Interface::MoveEl::Update_MovableElements();
    Interface::ComputerButtons::Update();
    Interface::Sliders::Update_Sliders();

// handlers
    handler_Interface_Buttons();
    handler_Interface_Lists();

// 
}