//
//  Point.h
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef _POINT_H
#define _POINT_H

#include <cmath>

// :: Point structure class ::
// :: Allows direct manipulation ::
template<typename T>
class Point
{
public:
    Point()
    : x(0), y(0)
    {}

    Point(T _x, T _y)
    : x(_x), y(_y)
    {}

    // : return the diagonal length of the vector x,y :
    T length()
    {
        return sqrt(x*x + y*y);
    }

    // x value
    T x;
    // y value
    T y;

    // == operator
    bool operator==(const Point<T> &p1)
    {
        if (x == p1.x && y == p1.y)
        {
            return true;
        }
        return false;
    }

    // : - operator
    Point<T> operator-(const Point<T> &rhs)
    {
        Point<T> delta(x-rhs.x, y-rhs.y);
        return delta;
    }

    // : + operator
    Point<T> operator+(const Point<T> &rhs)
    {
        Point<T> delta(x+rhs.x, y+rhs.y);
        return delta;
    }

    // : * operator
    Point<T> operator*(const Point<T> &rhs)
    {
        Point<T> delta(x*rhs.x, y*rhs.y);
        return delta;
    }

    // : / operator
    Point<T> operator/(const Point<T> &rhs)
    {
        Point<T> delta(x/rhs.x, y/rhs.y);
        return delta;
    }

    // : return a point for (0, 0)
    static Point<T> zero()
    {
        return Point<T>(0, 0);
    }
};

#endif /* _POINT_H */
