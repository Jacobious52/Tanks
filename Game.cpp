//
//  Game.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "Point.h"
#include "ConsoleTools.h"
#include "Timer.h"
#include "MutableArray.h"
#include "View.h"
#include "IntroView.h"
#include "GameView.h"
#include "EndView.h"
#include "TextureTools.h"
#include "Sprite.h"
#include "DebugView.h"
#include <signal.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// :: Simple Game class for memory managment and timer delegate ::
// :: Main body of game runs here ::
class Game : public ITimerDelegate
{
public:
    // : constructor to take runtime args :
    Game(bool skip, float game_time, int rain)
        : _skip_intro(skip)
    {
        ConsoleTools::play_music("music.wav");

        // clear computer.txt for writing
        if (DebugView::shared_view()->show == true)
        {
            std::ofstream file("computer.txt");
            file << "Computer 1" << std::endl << "Computer 2" << std::endl;
            file.close();
        }

        // write the seed of this game for replay
        if (ConsoleTools::replay == false)
        {
            std::ofstream file("replay.txt");
            int t = time(0);
            file << t << std::endl;
            file.close();
            srand(t);
        }
        else
        {
            printf("seed: ");
            srand(ConsoleTools::get_input<int>("int: ", Point<int>(StringTools::string_width("seed: "), 0)));
        }

        // load texture map file
        TextureTools::load_texture_file("textures.txt");

        // setup intro view
        intro_view = new IntroView();
        current_view = intro_view;
        intro_view->tag = rain;

        // switch to gameview straight away
        if (_skip_intro == true)
        {
            game_view = new GameView("Default 1", "Default 2");
            game_view->tag = rain;
            current_view = game_view;
            current_view->draw();
        }

        // : create timer and link to self
        timer = Timer(game_time, true);
        timer.set_delegate(this);

        tick_time = 0;
    }

    ~Game()
    {
        // cleanup
        current_view = 0;

        if (intro_view != 0)
        {
            delete intro_view;
        }

        if (game_view != 0)
        {
            delete game_view;
        }

        if (end_view != 0)
        {
            delete end_view;
        }

        ConsoleTools::end_color();
        ConsoleTools::clear_screen();

        ConsoleTools::stop_music();
    }

    // : enter main game loop :
    void run()
    {
        timer.start();
    }

    // : main game loop :
    void timer_did_tick(Timer *sender, int t)
    {
        tick_time++;

        std::cin.clear();

        // update
	    current_view->update(tick_time);

        // clear and draw
        ConsoleTools::end_color();
        ConsoleTools::clear_screen();
        current_view->draw();

        // Exit introview and goto gameview
        if (current_view == intro_view && current_view->should_remove_from_parent())
        {
            game_view = new GameView(intro_view->player1, intro_view->player2);
            game_view->tag = intro_view->tag;
            current_view = game_view;

            delete intro_view;
            intro_view = 0;

            ConsoleTools::end_color();
            ConsoleTools::clear_screen();
            current_view->draw();
            tick_time = 0;
        }
        // Exit gameview and goto endview
        if (current_view == game_view && current_view->should_remove_from_parent())
        {
            end_view = new EndView(game_view->get_winner());
            end_view->tag = game_view->tag;
            current_view = end_view;

            delete game_view;
            game_view = 0;

            ConsoleTools::end_color();
            ConsoleTools::clear_screen();
            current_view->draw();
            tick_time = 0;
        }
        // Exit endview and exit game
        if (current_view == end_view && current_view->should_remove_from_parent())
        {
            current_view = 0;
            delete end_view;
            end_view = 0;

            //end game loop
            timer.end();
        }
    }

private:
    View *current_view;
    IntroView *intro_view;
    GameView *game_view;
    EndView *end_view;

    Timer timer;
    int tick_time;
    bool _skip_intro;
};

// : capture control-c to exit gracefully
void signal_handler(int signum)
{
    ConsoleTools::stop_music();
    ConsoleTools::end_color();
    ConsoleTools::clear_screen();
    std::exit(0);
}

// : entry point :
int main(int argc, char const *argv[])
{
    signal(SIGINT, signal_handler);

    // default args
    float game_time = 0.05;
    int rain = 1;
    DebugView::shared_view()->show = false;
    bool skip = false;

    // handle args from terminal input
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--skip")
        {
            skip = true;
        }
        else if (std::string(argv[i]) == "--noaudio")
        {
            ConsoleTools::audio = false;
        }
        else if (std::string(argv[i]) == "--debug")
        {
            DebugView::shared_view()->show = true;
        }
        else if (std::string(argv[i]) == "--norain")
        {
            rain = 0;
        }
        else if (std::string(argv[i]) == "--replay")
        {
            ConsoleTools::replay = true;
        }
        else if (std::string(argv[i]) == "--gametime")
        {
            if (++i > argc)
            {
                break;
            }
            std::stringstream ss;
            ss << argv[i];
            ss >> game_time;
        }
        else if (std::string(argv[i]) == "--help")
        {
            std::ifstream helpfile("help.txt");
            ConsoleTools::set_fcolor(ConsoleTools::green);
            printf("\n%s\n", std::string(std::istreambuf_iterator<char>(helpfile),
                                        std::istreambuf_iterator<char>()).c_str());
            ConsoleTools::end_color();
            std::exit(0);
        }
    }

    // start
    Game game(skip, game_time, rain);
    game.run();

    return 0;
}
