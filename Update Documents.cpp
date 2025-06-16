#include "Update Documents.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"


void Update_DragNDrop(vector<Document>& documents)
{
//		Optimization



//		For cicle

	for (vector<Document>::iterator it_doc = documents.begin(); it_doc != documents.end(); it_doc++)
	{
		if (it_doc->getDocID() == Document::Document_ID::Passport)
		{
			cout << "closed: " << it_doc->isAdditionalDataContains("closed") << endl;
			if(it_doc->getSelected() && it_doc->isAdditionalDataContains("closed"))
			{
				//if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				//	it_doc->anim_start();
				it_doc->setScale({1.1, 1.1});
				//it_doc->anim_pop_up(it_doc->getScale().x, 1, 1.2);
				//it_doc->anim_pop_up(it_doc->getScale().y, 1, 1.2);
			}
			else
				it_doc->setScale({1, 1});

		}

		it_doc->anim_update();
	}

//		return
}
