
struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D() : x(0.0f), y(0.0f), z(0.0f)
	{
	}

	Vector3D(float X, float Y, float Z) : x(X), y(Y), z(Z)
	{
	}

	Vector3D& operator+=(const Vector3D& rhs) 
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3D operator+(const Vector3D& rhs) const
	{
		Vector3D sum;
		sum.x = x + rhs.x;
		sum.x = y + rhs.y;
		sum.x = z + rhs.z;
		return sum;
	}

	Vector3D& operator-=(const Vector3D& rhs) 
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3D operator-(const Vector3D& rhs) const
	{
		Vector3D res;
		res.x = x - rhs.x;
		res.x = y - rhs.y;
		res.x = z - rhs.z;
		return res;
	}

	Vector3D& operator/=(const float rhs) 
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	Vector3D operator/(const float rhs) const
	{
		Vector3D res;
		res.x = x / rhs;
		res.x = y / rhs;
		res.x = z / rhs;
		return res;
	}

	Vector3D& operator*=(const float rhs) 
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	Vector3D operator*(const float rhs) const
	{
		Vector3D res;
		res.x = x * rhs;
		res.x = y * rhs;
		res.x = z * rhs;
		return res;
	}

	float Length()
	{
		return sqrt(DotProduct(*this, *this));
	}

	static float DotProduct(Vector3D& first, Vector3D& second)
	{
		return first.x * second.x + first.y * second.y + first.z * second.z;
	}
};