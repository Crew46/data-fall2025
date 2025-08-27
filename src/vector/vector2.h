#ifndef VECTOR_H
#define VECTOR_H
#include "math.h"
#include "misc.h"

//components of x, followed by components of y, with pointers to result components
void AddVector2Components(float xA, float xB, float yA, float yB, float* resultX, float* resultY)
{
  *resultX = xA + xB;
  *resultY = yA + yB;
}

void SubtractVector2Components(float xA, float xB, float yA, float yB, float* resultX, float* resultY)
{
  AddVector2Components(xA, -xB, yA, -yB, resultX, resultY);
}

void MultiplyVector2ByScalar(float x, float y, float scalar, float* resultX, float* resultY)
{
  *resultX = x * scalar; 
  *resultY = y * scalar;
}

void DivideVector2ByScalar(float x, float y, float scalar, float* resultX, float* resultY)
{
  *resultX = x / scalar; 
  *resultY = y / scalar;
}

float GetVector2Magnitude(float x, float y)
{
  return sqrt(pow(x, 2) + pow(y, 2));
}

float GetDistanceBetweenVector2s(float xA, float yA, float xB, float yB)
{
  float dX = xA - xB;
  float dY = yA - yB;
  return GetVector2Magnitude(dX, dY);
}

void NormalizeVector2(float x, float y, float* resultX, float* resultY)
{
  float len = GetVector2Magnitude(x, y);
  if(len != 0)
  {
    *resultX = x / len;
    *resultY = y / len;
  }
}

#endif // VECTOR_H
