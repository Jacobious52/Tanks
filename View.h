//
//  View.h
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef VIEW_H
#define VIEW_H

#include "MutableArray.h"
#include "Point.h"

// :: pre declare View for type def
class View;
// :: create a alias for easy use
typedef MutableArray<View *> MVArray;
// :: create a loop macro for view *. ITER_VAR is the varible to interate with, ITER_VIEW is the view *
#define LOOPV(ITER_VAR ,ITER_VIEW) for (size_t ITER_VAR = 0; ITER_VAR < ITER_VIEW->get_children()->get_count(); ++ITER_VAR)

// :: View container class for all subviews ::
// :: Has geometric properties (eg. pos, size) ::
class View
{
public:
    // : default contructor :
    View()
        : _position(), _size(), tag(0)
    {
        _parent = 0;
        _should_remove_from_parent = false;
        _children = new MVArray();
    }

    // : init with pos and size
    View(Point<int> pos, Point<int> size)
        : _position(pos), _size(size), tag(0)
    {
        _parent = 0;
        _should_remove_from_parent = false;
        _children = new MVArray();
    }

    // : init with x, y and w, h
    View(int x, int y, int w, int h)
        : _position(x, y), _size(w, h), tag(0)
    {
        _parent = 0;
        _should_remove_from_parent = false;
        _children = new MVArray();
    }

    virtual ~View()
    {
        // cleanup
        LOOPV(i, this)
        {
            delete _children->remove(i);
        }
    }

    // : update funtion for all child views :
    virtual void update(int t);

    // : draw funtion for all child views :
    virtual void draw();

    // : Getter/Setter for _position :
    Point<int> get_position() const;
    void set_position(Point<int> pos);

    // : Getter/Setter for _position :
    Point<int> get_size() const;
    void set_size(Point<int> size);

    // : getter for _children :
    MVArray *get_children();

    // : add child to _children :
    void add_child(View *child);

    // : get child at i :
    View *operator[](size_t index);
    View *get_child(size_t index);

    // : returns/sets the parent view :
    View *get_parent() const;
    void set_parent(View *parent);

    // getter for _should_remove_from_parent
    bool should_remove_from_parent() const;
    void set_should_remove_from_parent(bool rem);

    int tag;

protected:
    // : array of sub views :
    MVArray *_children;
    Point<int> _position;
    Point<int> _size;

    View *_parent;

    // : setting true will cause deletion after next update :
    bool _should_remove_from_parent;
};

#endif  // VIEW_H
