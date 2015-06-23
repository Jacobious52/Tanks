//
//  DebugView.h
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef DEBUG_VIEW_H
#define DEBUG_VIEW_H

#include "View.h"
#include <string>
#include <map>

// :: Singleton class for DebugView ::
// :: allows global access to the one instance of debug view
//    without passing around pointer everywhere
class DebugView : public View
{
public:
    // : lazy instantiate shared debug view
    static DebugView *shared_view()
    {
        if (_shared_view == 0)
        {
            _shared_view = new DebugView();
        }
        return _shared_view;
    }

    // : add a float to print to debug view
    void watch(std::string key, float value);

    void update(int t);
    void draw();

    // : flag to show debug view or not
    bool show;

private:
    std::map<std::string, float> _deb_map;

    // : static shared instance of sharedview
    static DebugView *_shared_view;

    // : private constructor :
    // : private to stop creation of one than one debugview
    //   by someone else :
    DebugView() : View()
    {
        show = false;
        _position = Point<int>(2, 2);
        _size = Point<int>::zero();
        _deb_map = std::map<std::string, float>();
    }
};

#endif // DEBUG_VIEW_H
