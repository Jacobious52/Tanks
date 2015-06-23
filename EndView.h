//
//  EndView.h
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "View.h"
#include <string>

#ifndef END_VIEW_H
#define END_VIEW_H

// :: EndView used for gameover view ::
class EndView : public View
{
public:
    EndView(std::string winner) : View(), _winner(winner)
    {
        _init();
    }
    ~EndView()
    {}

    void update(int t);
    void draw();

private:
    void _init();

     std::string _winner;
};

#endif // END_VIEW_H
