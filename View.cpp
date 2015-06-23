//
//  View.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "View.h"

// : returns/sets the parent view :
View *View::get_parent() const
{
    return _parent;
}

void View::set_parent(View *parent)
{
    _parent = parent;
}

// : getter for _children :
MVArray *View::get_children()
{
    return _children;
}

// : add child to _children :
void View::add_child(View *child)
{
    child->set_parent(this);
    get_children()->add(child);
}

View *View::get_child(size_t index)
{
    // size_t is always >= 0
    if (index < get_children()->get_count())
    {
        return (*get_children())[index];
    }

    // went outside bounds return  NULL
    return 0;
}

// : get child at i :
View *View::operator[](size_t index)
{
    return get_child(index);
}

// : update funtion for all child views :
void View::update(int t)
{
    LOOPV(i, this)
    {
        get_child(i)->update(t);
        // remove child if requested by child
        if (get_child(i)->should_remove_from_parent() == true)
        {
            delete get_children()->remove(i);
            --i;
        }
    }
}

// : draw funtion for all child views :
void View::draw()
{
    LOOPV(i, this)
    {
        get_child(i)->draw();
    }
}

// : Getter/Setter for _position :
Point<int> View::get_position() const
{
    return _position;
}

void View::set_position(Point<int> pos)
{
    _position = pos;
}

// : Getter/Setter for _position :
Point<int> View::get_size() const
{
    return _size;
}

void View::set_size(Point<int> size)
{
    _size = size;
}

bool View::should_remove_from_parent() const
{
    return _should_remove_from_parent;
}

void View::set_should_remove_from_parent(bool rem)
{
    _should_remove_from_parent = rem;
}

