#ifndef VECTOR_H
#define VECTOR_H
#include "math.h"
#include "misc.h"

struct Vector2 
{
  float x;
  float y;
};

Vector2* CreateVector2(float x, float y)
{
  Vector2* vector2 = (Vector2*)malloc(sizeof(Vector2));
  vector2->x = x;
  vector2->y = y;
  return vector2;
}

void AddVector2Components(Vector2* a, Vector2* b, Vector2* out)
{
  out->x = a->x + b->x;
  out->y = a->y + b->y;
}

void SubtractVector2Components(Vector2* a, Vector2* b, Vector2* out)
{
  out->x = a->x - b->x;
  out->y = a->y - b->y;
}

void MultiplyVector2ByScalar(Vector2* vector2, float scalar)
{
  vector2->x *= scalar;
  vector2->y *= scalar;
}

void DivideVector2ByScalar(Vector2* vector2, float scalar)
{
  vector2->x /= scalar;
  vector2->y /= scalar;
}

float GetVector2Magnitude(Vector2* vector2)
{
  return sqrt(pow(vector2->x, 2) + pow(vector2->y, 2));
}

float GetDistanceBetweenVector2s(Vector2* a, Vector2* b)
{
  float dx = a->x - b->x;
  float dy = a->y - b->y;
  return sqrt(pow(dx, 2) + pow(dy, 2));
}

void NormalizeVector2(Vector2* vector2)
{
  float len = GetVector2Magnitude(vector2);
  if(len != 0)
  {
    vector2->x = vector2->x / len;
    vector2->y = vector2->y / len;
  }
}

float GetDotProductBetweenVector2s(Vector2* a, Vector2* b)
{
  return (a->x * b->x) + (a->y * b->y);
}

#endif
