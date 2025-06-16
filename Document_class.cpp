#include "Document_class.h"
#include "eMath.h"
#include "Lerp functions.h"

void Document::Update()
{
    if (this->dragging && anim_tick == 0)
    {
        anim_tick++;
    }
}


void Document::anim_update()
{
    if (this->animation_playing)
    {
        if (this->anim_tick >= this->max_anim_tick)
        {
            this->anim_tick = 0;
            this->animation_playing = false;
        }

        this->anim_tick++;
    }
}


void Document::anim_pop_up(float& element, float left_edge, float right_edge)
{
    if (!this->animation_playing) return;
    cout << "data: " << left_edge << ' ' << right_edge << ' ' << element << endl;
    cout << "animation ticks: " << (float)anim_tick / 100 << endl;

    element = (right_edge - left_edge) * smootherstep(left_edge, right_edge, (float)anim_tick / 100 + left_edge) + left_edge;

    cout << "element interpolation: " << element << endl;
}

void Document::anim_pop_down(float& element, float left_edge, float right_edge)
{
    if (!this->animation_playing) return;

    element = interpolate::expoEaseInOut((float)anim_tick/max_anim_tick, 2, 0.1, 10);
}

Vector2f Document::getPosition()
{
    return position;
}

Vector2f Document::getSize()
{
    return size;
}

string* Document::getTexture()
{
    return texture;
}

Document::Document_ID Document::getDocID()
{
    return this->document_ID;
}

bool Document::isAdditionalDataContains(const string& needed_data)
{
    for (const string& data : this->additional_data)
        if (data == needed_data) return true;
    return false;
}

bool Document::editAdditionalData(  const string& needed_data, 
                                    const string& change_data)
{
    for (string& data : this->additional_data)
        if (data == needed_data)
        {
            data = change_data;
            return true;
        }
    return false;
}

void Document::setPosition(Vector2f position)
{
    this->position = position;
}

void Document::move(Vector2f pos)
{
    this->position += pos;
}

void Document::move(float X, float Y)
{
    this->position += {X, Y};
}

void Document::setSize(Vector2f size)
{
    this->size = size;
}

void Document::setTexture(int index, string texture)
{
    this->texture[index] = texture;
}

void Document::setScale(Vector2f scale)
{
    this->scale = scale;
}

void Document::setDocID(Document_ID doc_id)
{
    this->document_ID = doc_id;
}

void Document::setElement(Vector2f position, Vector2f size, bool validity)
{
    this->document_elements.push_back(element{ position.x, position.y, size.x, size.y, validity });
}

void Document::setElement(int i, Vector2f position, Vector2f size, bool validity)
{
    this->document_elements[i] = element{ position.x, position.y, size.x, size.y, validity };
}
