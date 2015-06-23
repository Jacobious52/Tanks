//
//  IntroView.h
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef INTRO_VIEW_H
#define INTRO_VIEW_H

#include "View.h"
#include "Sprite.h"

// :: Class for introscreen logic ::
// :: gets players names ::
class IntroView : public View
{
public:
    IntroView() : View()
    {
        _init();
    }
    ~IntroView()
    {}

    void update(int t);
    void draw();

    // : name of player1 and player2
    std::string player1;
    std::string player2;

private:
    void _init();

    // : sprite for verses text
    Sprite _vs_text;
    // : string for fake loading bar
    std::string _load_num_string;
};

#endif // INTRO_VIEW_H
