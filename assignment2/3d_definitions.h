#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

class Point2{
public:
	float x,y;
	Point2()
	{
		x = 0.0;
		y = 0.0;
	}
	Point2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

class Point3{
public:
	float x,y,z;
	Point3()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	Point3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class Vector3{
public:
	float x,y,z;
	Vector3()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void set(Vector3 temp)
	{
		x = temp.x;
		y = temp.y;
		z = temp.z;
	}
	void normalize(){
		float length = sqrt(x*x + y*y + z*z);
		x /= length;
		y /= length;
		z /= length;
	}
	Vector3 cross(Vector3 b)
	{
		Vector3 result;
		result.x = y*b.z - z*b.y;
		result.y = z*b.x - x*b.z;
		result.z = x*b.y - y*b.x;
		return result;
	}

	Vector3 scale(float dx)
	{
		Vector3 result;
		result.x = x*dx;
		result.y = y*dx;
		result.z = z*dx;
		return result;
	}
	
	//overriding + operator
	Vector3 operator+(const Vector3& b) {
        Vector3 temp;
        temp.x = this->x + b.x;
        temp.y = this->y + b.y;
        temp.z = this->z + b.z;
        return temp;
    }

	Vector3 operator-() const {
		Vector3 temp;
		temp.x = -this->x;
		temp.y = -this->y;
		temp.z = -this->z;
	    return temp;
   }
	
};