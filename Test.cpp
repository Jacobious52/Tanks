//
//  Test.cpp
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
#include "TextureTools.h"
#include "Sprite.h"
#include <cstdio>
#include <string>

typedef MutableArray<Timer *> MTArray;

class TestTimerDelegate : ITimerDelegate
{
public:
    TestTimerDelegate()
    {
        timer1 = Timer(0.1, 20);
        timer1.set_delegate(this);

        timer2 = Timer(0.05, true);
        timer2.set_delegate(this);

        printf("\nTesting delegate timer\n\n");
    }

    ~TestTimerDelegate()
    {
        printf("\n\n");
    }

    Timer timer1;
    Timer timer2;

    void test1()
    {
        timer1.start();
    }

    void test2()
    {
        timer2.start();
    }

    void timer_did_tick(Timer *sender, int t)
    {
        if (sender == &timer1)
        {
            ConsoleTools::move_cursor(ConsoleTools::up, 1);
            ConsoleTools::clear_line();
            printf("delegate tick 1: %d\n", t);
        }
        else if (sender == &timer2)
        {
            ConsoleTools::move_cursor(ConsoleTools::up, 1);
            ConsoleTools::clear_line();
            printf("delegate tick 2: %d\n", t);
            if (t == 15)
            {
                timer2.end();
            }
        }
    }
};

bool assert(bool test, const char *message)
{
    std::string result = (test == true) ? "Passed" : "Failed";
    printf("%s: %s\n", result.c_str(), message);
    return test;
}

void test_point()
{
    printf("Testing Point..\n\n");

    Point<int> p1(3, 4);
    assert(p1.length() == 5, "length");
    Point<int> p2(3, 4);
    assert(p1 == p2, "equality");
    Point<int> res(0, 0);
    assert(p1 - p2 == res, "minus");
    res.x = 6;
    res.y = 8;
    assert(p2 + p2 == res, "addition");
    res.x = 9;
    res.y = 16;
    assert(p1 * p2 == res, "times");
    res.x = 1;
    res.y = 1;
    assert(p1 / p2 == res, "divide");
}

void test_array()
{
    // ---testing marray using pointers----

    printf("\nTesting array (of timers)..\n\n");
    MTArray array(5);
    assert(array.get_size() == 5, "init size");
    assert(array.get_count() == 0, "init count");

    array.add(new Timer(0, 0));
    assert(array.get_count() == 1, "count 1");

    array.add(new Timer(1, 1));
    Timer *t0 = new Timer(2, 2);
    array.add(t0);
    array.add(new Timer(3, 3));
    assert(array.get_count() == 4, "count 4");

    array.add(new Timer(4, 4));
    assert(array.get_count() == 5, "count 5");

    array.add(new Timer(5, 5));
    array.add(new Timer(6, 6));
    assert(array.get_count() == 7, "count 7");
    assert(array.get_size() == 10, "resized to 10");

    Timer *t1 = array.remove(2);
    assert(t1 == t0, "remove and return");
    delete t1;

    assert(array.get_count() == 6, "count 6");

    for (int i = 0; i < array.get_count(); ++i)
    {
        int d = i;
        if (i >= 2)
        {
            d += 1;
        }
        assert(array[i]->get_delay() == static_cast<double>(d), "iterating ");
        ConsoleTools::move_cursor(ConsoleTools::up , 1);
        ConsoleTools::move_cursor(ConsoleTools::right , StringTools::string_width("Passed: interating"));
        printf(": timer delay: %.2lf\n", array[i]->get_delay());
    }

    for (int i = 0; i < array.get_count(); ++i)
    {
        delete array.remove(i);
    }

    array.clear();
    assert(array.get_count() == 0, "clear");

    // -----test using int array------

    printf("\nTesting int array..\n\n");
    MutableArray<int> i_array(5);
    assert(i_array.get_size() == 5, "init size");
    assert(i_array.get_count() == 0, "init count");

    i_array.add(10);
    i_array.add(20);
    i_array.add(30);
    assert(i_array.get_count() == 3, "count 3");

    int x2 = i_array.remove(2);
    assert(x2 == 30, "remove and return");

    i_array.clear();
    assert(i_array.get_count() == 0, "clear");
}

void test_timer()
{
    printf("\nTesting Timer..\n\n");
    Timer timer(0.1, 20);

    printf("interval 0.1s ticks 20\n\n");
    while (timer.tick())
    {
        ConsoleTools::move_cursor(ConsoleTools::up, 1);
        ConsoleTools::clear_line();
        printf("%d\n", timer.get_tick_count());
    }

    timer.reset();
    printf("\n");

    Timer inf(0.05, true);
    printf("infinite ticks. break at 50. interval 0.05s\n\n");

    while (inf.tick())
    {
        ConsoleTools::move_cursor(ConsoleTools::up, 1);
        ConsoleTools::clear_line();
        printf("%d\n", inf.get_tick_count());
        if (inf.get_tick_count() >= 50)
        {
            break;
        }
    }

    TestTimerDelegate test_timer;
    test_timer.test1();
    test_timer.test2();
}

void test_textures()
{
    printf("Testing textures..\n\n");
    assert(TextureTools::get_texture("tank1") != "$NO KEY", "tank1");
    assert(TextureTools::get_texture("tank2") != "$NO KEY", "tank2");
    assert(TextureTools::get_texture("title") != "$NO KEY", "title");
    assert(TextureTools::get_texture("vs") != "$NO KEY", "vs");
    assert(TextureTools::get_texture("bullet_up") != "$NO KEY", "bullet_up");
    assert(TextureTools::get_texture("bullet_down") != "$NO KEY", "bullet_down");
    assert(TextureTools::get_texture("bullet_flat") != "$NO KEY", "bullet_flat");
    assert(TextureTools::get_texture("bullet_vert") != "$NO KEY", "bullet_vert");
    assert(TextureTools::get_texture("gameover") != "$NO KEY", "gameover");
}

void test_view()
{
    printf("\nTesting views...\n");

    View *view = new View(0, 0, 600, 600);
    view->add_child(new View(0, 0, 20, 20));
    view->add_child(new View(40, 40, 30, 50));

    assert(view->get_children()->get_count() == 2, "children count");

    LOOPV(i, view)
    {
        View *v = view->get_child(i);
        assert(v->get_size().x == (i+2)*10, "iterate");
    }
}

bool fexists(std::string fname)
{
    bool exists = false;
    std::ifstream file(fname.c_str(), std::ios::binary);
    exists = file.good();
    file.close();
    return exists;
}

void test_sounds()
{
    printf("\nTesting sound files (passed/failed : found/not found)\n\n");

    assert(fexists("music.wav") == true, "music.wav");
    assert(fexists("boom.wav") == true, "boom.wav");
    assert(fexists("beep.wav") == true, "beep.wav");
    assert(fexists("fire.wav") == true, "fire.wav");
}

int main(int argc, char const *argv[])
{
    ConsoleTools::clear_screen();

    TextureTools::load_texture_file("textures.txt");

    test_point();
    test_array();
    test_view();
    test_textures();
    test_sounds();

    test_timer();

    ConsoleTools::set_cursor(0, ConsoleTools::get_terminal_size().y-1);
    ConsoleTools::end_color();

    return 0;
}
