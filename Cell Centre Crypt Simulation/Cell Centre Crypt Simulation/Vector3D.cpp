
struct Vector3D
{
	double x;
	double y;
	double z;

	Vector3D() : x(0.0f), y(0.0f), z(0.0f)
	{
	}

	Vector3D(double X, double Y, double Z) : x(X), y(Y), z(Z)
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
		sum.y = y + rhs.y;
		sum.z = z + rhs.z;
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
		res.y = y - rhs.y;
		res.z = z - rhs.z;
		return res;
	}

	Vector3D& operator/=(const double rhs) 
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	Vector3D operator/(const double rhs) const
	{
		Vector3D res;
		res.x = x / rhs;
		res.y = y / rhs;
		res.z = z / rhs;
		return res;
	}

	Vector3D& operator*=(const double rhs) 
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	Vector3D operator*(const double rhs) const
	{
		Vector3D res;
		res.x = x * rhs;
		res.y = y * rhs;
		res.z = z * rhs;
		return res;
	}

	double Length()
	{
		return sqrt(DotProduct(*this, *this));
	}

	static double DotProduct(Vector3D& first, Vector3D& second)
	{
		return first.x * second.x + first.y * second.y + first.z * second.z;
	}
};