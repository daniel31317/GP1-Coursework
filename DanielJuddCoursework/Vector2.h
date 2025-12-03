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

	bool operator== (const Vector2& other) const
	{
		if (x == other.x && y == other.y)
		{
			return true;
		}
		return false;
	}
	
	Vector2 operator+ (const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator+ (const int& other) const
	{
		return Vector2(x + other, y + other);
	}

	Vector2 operator- (const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator- (const int& other) const
	{
		return Vector2(x - other, y - other);
	}
	
	Vector2& operator+= (const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& operator+= (const int& other)
	{
		x += other;
		y += other;
		return *this;
	}

	Vector2& operator-= (const Vector2& other)
	{
		x -= other.x;
		y-= other.y;
		return *this;
	}

	Vector2& operator-= (const int& other)
	{
		x -= other;
		y -= other;
		return *this;
	}
};