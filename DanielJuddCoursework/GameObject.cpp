#include "GameObject.h"


GameObject::GameObject()
{
	m_position = Vector2();
	m_body = ' ';
}

GameObject::GameObject(int xPos, int yPos, char body) : m_position(xPos, yPos), m_body(body)
{

}
GameObject::GameObject(Vector2 position, char body) : m_position(position), m_body(body)
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
void GameObject::update()
{

}


