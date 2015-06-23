//
//  DebugView.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "DebugView.h"
#include "ConsoleTools.h"

// : init static shared instance of debugview
DebugView *DebugView::_shared_view = 0;

typedef std::map<std::string, float>::iterator map_iter;

void DebugView::watch(std::string key, float value)
{
    _deb_map[key] = value;
}

void DebugView::update(int t)
{
    View::update(t);
}

void DebugView::draw()
{
    // don't draw if not in debug mode
    if (show == false)
    {
        return;
    }

    ConsoleTools::set_bcolor(ConsoleTools::magneta);
    int i = 0;
    for (map_iter it = _deb_map.begin(); it != _deb_map.end(); ++it)
    {
        ConsoleTools::set_cursor(_position.x, _position.y + i++);
        printf("%s\t:\t%0.3f\n", it->first.c_str(), it->second);
    }
    ConsoleTools::end_color();

    View::draw();
}
