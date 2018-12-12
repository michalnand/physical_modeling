#include "motion_tensor.h"
#include <iostream>

MotionTensor::MotionTensor()
{
  m_width   = 0;
  m_height  = 0;
  m_depth   = 0;
}

MotionTensor::MotionTensor(unsigned int width_, unsigned int height_, unsigned int depth_)
{
  init(width_, height_, depth_);
}

MotionTensor::MotionTensor(MotionTensor& other)
{
  copy(other);
}

MotionTensor::MotionTensor(const MotionTensor& other)
{
  copy(other);
}

MotionTensor::~MotionTensor()
{

}

MotionTensor& MotionTensor::operator= (MotionTensor& other)
{
  copy(other);
  return *this;
}

MotionTensor& MotionTensor::operator= (const MotionTensor& other)
{
  copy(other);
  return *this;
}

void MotionTensor::copy(MotionTensor& other)
{
  m_width   = other.m_width;
  m_height  = other.m_height;
  m_depth   = other.m_depth;

  v         = other.v;
  extremes  = other.extremes;
}

void MotionTensor::copy(const MotionTensor& other)
{
  m_width   = other.m_width;
  m_height  = other.m_height;
  m_depth   = other.m_depth;

  v         = other.v;
  extremes  = other.extremes;
}


void MotionTensor::init(unsigned int width_, unsigned int height_, unsigned int depth_)
{
  m_width   = width_;
  m_height  = height_;
  m_depth   = depth_;

  v.resize(m_depth);
  for (unsigned int z = 0; z < v.size(); z++)
  {
    v[z].resize(m_height);
    for (unsigned int y = 0; y < v[z].size(); y++)
    {
      v[z][y].resize(m_width);
      for (unsigned int x = 0; x < v[z][y].size(); x++)
        v[z][y][x] = 0.0;
    }
  }
}


float MotionTensor::get(unsigned int x, unsigned int y, unsigned int z)
{
  return v[z][y][x];
}

void MotionTensor::set(unsigned int x, unsigned int y, unsigned int z, float value)
{
  v[z][y][x] = value;
}

void MotionTensor::print(bool verbose)
{
  if (verbose)
  {
    for (unsigned int z = 0; z < v.size(); z++)
    {
      for (unsigned int y = 0; y < v[z].size(); y++)
      {
        for (unsigned int x = 0; x < v[z][y].size(); x++)
          std::cout << get(x, y, z) << " ";
        std::cout << "\n";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }

  std::cout << "dimensions = [ ";
  std::cout << width() << " ";
  std::cout << height() << " ";
  std::cout << depth() << " ]\n";

  std::cout << "extremes : \n";
  for (unsigned int i = 0; i < extremes.size(); i++)
  {
    std::cout << "[" << extremes[i].min << " " << extremes[i].max << "]" << "\n";
  }

  std::cout << "\n";
}

void MotionTensor::clear()
{
  for (unsigned int z = 0; z < depth(); z++)
    for (unsigned int y = 0; y < height(); y++)
      for (unsigned int x = 0; x < width(); x++)
        set(x, y, z, 0.0);
}


void MotionTensor::normalise()
{
  find_extremes();

  for (unsigned int x = 0; x < width(); x++)
    normalise_column(extremes[x], x);
}

void MotionTensor::add_noise(float noise_level)
{
  for (unsigned int z = 0; z < depth(); z++)
    for (unsigned int y = 0; y < height(); y++)
      for (unsigned int x = 0; x < width(); x++)
      {
        float rnd = (rand()%1000000)/1000000.0;
        if (rand()%2)
          rnd = -rnd;

        float v = (1.0 - noise_level)*get(x, y, z) + noise_level*rnd;
        set(x, y, z, v);
      }
}

void MotionTensor::velocity_from_position()
{
  unsigned int position_columns = width()/2;

  for (unsigned int z = 0; z < depth(); z++)
    for (unsigned int y = 1; y < height(); y++)
      for (unsigned int x = 0; x < position_columns; x++)
      {
        float v = get(x, y, z) - get(x, y - 1, z);
        set(x + position_columns, y, z, v);
      }
}

void MotionTensor::find_extremes()
{
  extremes.clear();
  for (unsigned int x = 0; x < width(); x++)
  {
    auto extreme = find_column_extreme(x);
    extremes.push_back(extreme);
  }
}

sMotionTensorExtreme MotionTensor::find_column_extreme(unsigned int column)
{
  sMotionTensorExtreme result;

  result.min = get(column, 0, 0);
  result.max = get(column, 0, 0);

  for (unsigned int z = 0; z < depth(); z++)
    for (unsigned int y = 0; y < height(); y++)
    {
      float v = get(column, y, z);

      if (v > result.max)
        result.max = v;

      if (v < result.min)
        result.min = v;
    }

  return result;
}

void MotionTensor::normalise_column(sMotionTensorExtreme extreme, unsigned int column)
{
    float k = 0.0;
    float q = 0.0;

    if (extreme.min < extreme.max)
    {
      k = (1.0 - 0.0)/(extreme.max - extreme.min);
      q = 1.0 - k*extreme.max;
    }

    for (unsigned int z = 0; z < depth(); z++)
      for (unsigned int y = 0; y < height(); y++)
      {
        float v = get(column, y, z);
        v = k*v + q;
        set(column, y, z, v);
      }
}
