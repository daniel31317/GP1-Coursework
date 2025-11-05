#include "GameObject.h"


GameObject::GameObject()
{
	position = Vector2();
	body = ' ';
}

GameObject::GameObject(int xPos, int yPos, char body)
{
	position = Vector2(xPos, yPos);
	this->body = body;
}
GameObject::GameObject(Vector2 position, char body)
{
	this->position = position;
	this->body = body;
}
void GameObject::draw()
{
	std::cout << body;
}

void GameObject::move(int x, int y)
{
	position.x += x;
	position.y += y;
}
void GameObject::move(Vector2 move)
{
	position += move;
}
void GameObject::update()
{

}


