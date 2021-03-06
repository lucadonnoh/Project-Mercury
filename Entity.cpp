#include "Entity.hpp"

using namespace std;

Entity::Entity(int x, int y, char _c, int _color)
{
    setPos(x,y);
    buffer.x = 10;
    buffer.y = 10;
    c = _c;
    color = _color;
}

Entity::Entity(int x)
{
    setPos(x,0);
    buffer.x = 10;
    buffer.y = 10;
}

Entity::Entity()
{

}

int Entity::getX()
{
    return pos.x;
}

int Entity::getY()
{
    return pos.y;
}

int Entity::getBufferX()
{
    return buffer.x;
}

int Entity::getBufferY()
{
    return buffer.y;
}

void Entity::setPos(int x, int y)
{
    setBuffer();
    pos.x = x;
    pos.y = y;
}

void Entity::setPos(int x)
{
    setBuffer();
    pos.x = x;
}

void Entity::setBuffer()
{
    buffer.x = pos.x;
    buffer.y = pos.y;
}

char Entity::getChar()
{
    return c;
}

void Entity::setChar(char _c)
{
    c = _c;
}

int Entity::getColor()
{
    return color;
}

void Entity::setColor(int _color)
{
    color = _color;
}



void Entity::stampa()
{
	if(getBufferX() != getX() || getBufferY() != getY())
	{
		setCursorPosition(getBufferX(), getBufferY(), 6);
		cout << " ";
	}
	setCursorPosition(getX(), getY(), getColor());
	cout << getChar();
}
