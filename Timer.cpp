//
//  Timer.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "Timer.h"
#include <cstdio>
#include <ctime>

bool Timer::tick()
{
    // GET OUT OF THERE!!
    if (_force_break == true)
        return false;

    // tick if not reached count or override on
    if (get_tick_count() < get_ticks() || get_tick_overide() == true)
    {
        _wait();
        return true;
    }
    return false;
}

void Timer::start()
{
    while (tick())
    {
        if (_delegate != 0)
        {
            // call tick for delegate
            _delegate->timer_did_tick(this, get_tick_count());
        }
    }
}

void Timer::end()
{
    set_tick_overide(false);
    _tick_counter = get_ticks()+1;
    _force_break = true;
}

void Timer::set_delegate(ITimerDelegate *delegate)
{
    _delegate = delegate;
}

void Timer::_wait()
{
    const std::clock_t start_time = std::clock();
    while ((static_cast<double>((clock() - start_time))/CLOCKS_PER_SEC) < get_delay())
    {
        // wait
    }
    ++_tick_counter;
}

void Timer::reset()
{
    _tick_counter = 0;
}

// : getter / setter for _delay :
double Timer::get_delay() const
{
    return _delay;
}

void Timer::set_delay(double delay)
{
    if (delay > 0)
    {
        _delay = delay;
    }
}

// : getter / setter for _tick :
int Timer::get_ticks() const
{
    return _ticks;
}

void Timer::set_ticks(int ticks)
{
    if (ticks > 0)
    {
        _ticks = ticks;
    }
}

// : getter for _tick_counter :
int Timer::get_tick_count() const
{
    return _tick_counter;
}

// : getter / setter for _tick_overide :
bool Timer::get_tick_overide() const
{
    return _tick_overide;
}

void Timer::set_tick_overide(bool override)
{
    _tick_overide = true;
}
