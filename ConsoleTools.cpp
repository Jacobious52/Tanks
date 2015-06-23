//
//  ConsoleTools.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include <unistd.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <fstream>
#include "ConsoleTools.h"

bool ConsoleTools::audio = true;
bool ConsoleTools::replay = false;

std::string ConsoleTools::get_line()
{
    std::string input;
    getline(std::cin, input);
    return input;
}

void ConsoleTools::set_title(char const *title)
{
    printf("\x1b]2;%s\x07", title);
}

void ConsoleTools::set_fcolor(ConsoleTools::Color color)
{
    printf("\033[%dm", color);
}

void ConsoleTools::set_bcolor(ConsoleTools::Color color)
{
   printf("\033[%dm", color+10);
}

void ConsoleTools::set_color(ConsoleTools::Color fcolor, ConsoleTools::Color bcolor)
{
    printf("\033[%d;%dm", fcolor, bcolor+10);
}

void ConsoleTools::end_color()
{
    printf("\033[%dm", endc);
}

void ConsoleTools::hide_text()
{
    printf("\033[8m");
}

void ConsoleTools::reverse_color()
{
    printf("\033[7m");
}

void ConsoleTools::clear_screen()
{
    printf("\033[2J");
    set_cursor(0, 0);
}

void ConsoleTools::clear_line()
{
    printf("\033[K");
}

void ConsoleTools::set_cursor(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

void ConsoleTools::set_cursor(Point<int> pos)
{
    printf("\033[%d;%dH", pos.y, pos.x);
}

void ConsoleTools::move_cursor(ConsoleTools::Direction dir, int dist)
{
    printf("\033[%d%c", dist, static_cast<char>(dir));
}

Point<int> ConsoleTools::get_terminal_size()
{
    winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    Point<int> p(win.ws_col, win.ws_row);
    return p;
}

void ConsoleTools::stop_music()
{
    if (audio == false)
    {
        return;
    }

    #ifdef __APPLE__
            system("killall afplay");
    #elif __linux__
            system("killall aplay");
    #endif
}

void ConsoleTools::play_music(std::string filename)
{
    if (audio == false)
    {
        return;
    }

    std::ifstream file(filename.c_str(), std::ios::binary);
    if (file.good() == true)
    {
        #ifdef __APPLE__
            system(std::string("afplay " + filename + "&").c_str());
        #elif __linux__
            system(std::string("aplay -q " + filename + " &").c_str());
        #endif
    }
    else
    {
        audio = false;
    }
    file.close();
}
