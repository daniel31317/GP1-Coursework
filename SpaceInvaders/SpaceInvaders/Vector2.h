#pragma once
struct Vector2
{
	int x;
	int y;
	Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator== (const Vector2& p)
	{
		if (x == p.x && y == p.y)
		{
			return true;
		}
		return false;
	}

	Vector2 operator+ (const Vector2& p)
	{
		return Vector2(x + p.x, y + p.y);
	}
	
	Vector2 operator+= (const Vector2& p)
	{
		return Vector2(x + p.x, y + p.y);
	}
	
	Vector2 operator- (const Vector2& p)
	{
		return Vector2(x - p.x, y - p.y);
	}
	Vector2 operator-= (const Vector2& p)
	{
		return Vector2(x - p.x, y - p.y);
	}
};