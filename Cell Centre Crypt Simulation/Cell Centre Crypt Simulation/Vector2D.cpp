struct Vector2D
{
	float x;
	float y;

	Vector2D() : x(0.0f), y(0.0f)
	{
	}

	Vector2D(float X, float Y) : x(X), y(Y)
	{
	}

	Vector2D& operator+=(const Vector2D& rhs) 
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2D operator+(const Vector2D& rhs) const
	{
		Vector2D sum;
		sum.x = x + rhs.x;
		sum.y = y + rhs.y;
		return sum;
	}

	Vector2D& operator-=(const Vector2D& rhs) 
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2D operator-(const Vector2D& rhs) const
	{
		Vector2D res;
		res.x = x - rhs.x;
		res.y = y - rhs.y;
		return res;
	}

	Vector2D& operator/=(const float rhs) 
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	Vector2D operator/(const float rhs) const
	{
		Vector2D res;
		res.x = x / rhs;
		res.y = y / rhs;
		return res;
	}

	Vector2D& operator*=(const float rhs) 
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2D operator*(const float rhs) const
	{
		Vector2D res;
		res.x = x * rhs;
		res.y = y * rhs;
		return res;
	}

	float Length()
	{
		return sqrt(DotProduct(*this, *this));
	}

	static float DotProduct(Vector2D& first, Vector2D& second)
	{
		return first.x * second.x + first.y * second.y;
	}
};