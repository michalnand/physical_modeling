#ifndef _V3_H_
#define _V3_H_

#include <string>

class V3
{
  private:
    float _x, _y, _z;

  public:
    V3();
    V3(float x, float y, float z);
    V3(V3& other);
    V3(const V3& other);

    virtual ~V3();
    V3& operator= (V3& other);
    V3& operator= (const V3& other);

  protected:

    void copy(V3& other);
    void copy(const V3& other);

  public:

    float x();
    float y();
    float z();

    void set(float x, float y, float z);

    void set_x(float x);
    void set_y(float y);
    void set_z(float z);

  public:

    V3 operator+ (V3 &other);
    V3 operator- (V3 &other);
    V3 operator* (V3 &other);
 
    V3 operator* (float c);
    V3 operator/ (float c);

    V3 operator+ (const V3 &other);
    V3 operator- (const V3 &other);
    V3 operator* (const V3 &other);


    float size();
    void zero();
    void ones();
    void constant(float v);
    void random(float min = -1.0, float max = 1.0);

    void print();
    std::string asString();

  public:
    void saturate(float min = -1.0, float max = 1.0);
};

#endif
