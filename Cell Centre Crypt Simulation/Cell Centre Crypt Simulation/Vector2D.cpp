struct Vector2D
{
	double x;
	double y;

	Vector2D() : x(0.0f), y(0.0f)
	{
	}

	Vector2D(double X, double Y) : x(X), y(Y)
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

	Vector2D& operator/=(const double rhs) 
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	Vector2D operator/(const double rhs) const
	{
		Vector2D res;
		res.x = x / rhs;
		res.y = y / rhs;
		return res;
	}

	Vector2D& operator*=(const double rhs) 
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2D operator*(const double rhs) const
	{
		Vector2D res;
		res.x = x * rhs;
		res.y = y * rhs;
		return res;
	}

	double Length()
	{
		return sqrt(DotProduct(*this, *this));
	}

	static double DotProduct(Vector2D& first, Vector2D& second)
	{
		return first.x * second.x + first.y * second.y;
	}
};