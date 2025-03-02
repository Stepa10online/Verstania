#include "Document_class.h"

Vector2f Document::getPosition()
{
    return position;
}

Vector2f Document::getSize()
{
    return size;
}

string Document::getTextureName()
{
    return texture_name;
}

string Document::getOpenedTextureName()
{
    return opened_texture_name;
}

string Document::getDocID()
{
    return this->document_ID;
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

void Document::setTextureName(string texture_name)
{
    this->texture_name = texture_name;
}

void Document::setOpenedTextureName(string opened_texture_name)
{
    this->opened_texture_name = opened_texture_name;
}

void Document::setDocID(string doc_id)
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
