#ifndef collision_h
#define collusion_h

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

#endif