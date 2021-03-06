#ifndef AUXILIARY_H
#define AUXILIARY_H

// Enum for collision physics
enum class CollisionType
{
  None,
  Top,
  Middle,
  Bottom,
  Left,
  Right
};

// Struct for collision physics
struct Contact
{
  CollisionType type;
  float penetration;
};

// Enum to indicate movement for paddles
enum Buttons
{
  PaddleOneUp = 0,
  PaddleOneDown,
  PaddleTwoUp,
  PaddleTwoDown,
};

#endif