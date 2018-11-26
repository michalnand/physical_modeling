#include "v3.h"

#include <math.h>
#include <iostream>

V3::V3()
{
  _x = 0.0;
  _y = 0.0;
  _z = 0.0;
}

V3::V3(float x, float y, float z)
{
  _x = x;
  _y = y;
  _z = z;
}

V3::V3(V3& other)
{
  copy(other);
}

V3::V3(const V3& other)
{
  copy(other);
}

V3::~V3()
{

}

V3& V3::operator= (V3& other)
{
  copy(other);
  return *this;
}

V3& V3::operator= (const V3& other)
{
  copy(other);
  return *this;
}

void V3::copy(V3& other)
{
  _x = other._x;
  _y = other._y;
  _z = other._z;
}

void V3::copy(const V3& other)
{
  _x = other._x;
  _y = other._y;
  _z = other._z;
}


float V3::x()
{
  return _x;
}

float V3::y()
{
  return _y;
}

float V3::z()
{
  return _z;
}

void V3::set(float x, float y, float z)
{
  _x = x;
  _y = y;
  _z = z;
}

void V3::set_x(float x)
{
  _x = x;
}

void V3::set_y(float y)
{
  _y = y;
}

void V3::set_z(float z)
{
  _z = z;
}


V3 V3::operator+ (V3 &other)
{
  return V3(_x+other._x, _y+other._y, _z+other._z);
}

V3 V3::operator- (V3 &other)
{
  return V3(_x-other._x, _y-other._y, _z-other._z);
}

V3 V3::operator* (V3 &other)
{
  return V3(_x*other._x, _y*other._y, _z*other._z);
}



V3 V3::operator+ (const V3 &other)
{
  return V3(_x+other._x, _y+other._y, _z+other._z);
}

V3 V3::operator- (const V3 &other)
{
  return V3(_x-other._x, _y-other._y, _z-other._z);
}

V3 V3::operator* (const V3 &other)
{
  return V3(_x*other._x, _y*other._y, _z*other._z);
}


V3 V3::operator* (float c)
{
  return V3(_x*c, _y*c, _z*c);
}

V3 V3::operator/ (float c)
{
  return V3(_x/c, _y/c, _z/c);
}



float V3::size()
{
  return sqrt(_x*_x + _y*_y + _z*_z);
}

void V3::zero()
{
  _x = 0.0;
  _y = 0.0;
  _z = 0.0;
}

void V3::ones()
{
  _x = 1.0;
  _y = 1.0;
  _z = 1.0;
}

void V3::constant(float v)
{
  _x = v;
  _y = v;
  _z = v;
}

void V3::random(float min, float max)
{
  _x = (rand()%1000000)/1000000.0;
  _y = (rand()%1000000)/1000000.0;
  _z = (rand()%1000000)/1000000.0;

  _x = (max - min)*_x + min;
  _y = (max - min)*_y + min;
  _z = (max - min)*_z + min;
}

void V3::print()
{
  std::cout << x() << " ";
  std::cout << y() << " ";
  std::cout << z() << " ";
}

std::string V3::asString()
{
  std::string res;
  res+= std::to_string(x()) + " ";
  res+= std::to_string(y()) + " ";
  res+= std::to_string(z()) + " ";

  return res;
}


void V3::saturate(float min, float max)
{
  if (_x < min)
    _x = min;

  if (_x > max)
    _x = max;

  if (_y < min)
    _y = min;

  if (_y > max)
    _y = max;

  if (_z < min)
    _z = min;

  if (_z > max)
    _z = max;
}
