#include "GameObject.h"


GameObject::GameObject()
{
	m_position = Vector2();
	m_body = ' ';
}

GameObject::GameObject(int xPos, int yPos, char body, WORD colour) : m_position(xPos, yPos), m_body(body), m_colour(colour)
{

}
GameObject::GameObject(Vector2 position, char body, WORD colour) : m_position(position), m_body(body), m_colour(colour)
{
	
}
void GameObject::draw() const
{
	std::cout << m_body;
}

void GameObject::move(int x, int y)
{
	m_position.x += x;
	m_position.y += y;
}
void GameObject::move(Vector2 move)
{
	m_position += move;
}
void GameObject::update(float deltaTime)
{

}


