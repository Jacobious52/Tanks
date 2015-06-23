//
//  Timer.h
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef _TIMER_H
#define _TIMER_H

// :: forward declare Timer for use in ITimer Delegate ::
class Timer;

// :: delegate for timer ticks ::
class ITimerDelegate
{
public:
    virtual void timer_did_tick(Timer *sender, int t) = 0;
};

// :: Class to handle delays in increments ::
class Timer
{
public:
    // : default constructor :
    Timer()
        : _delay(0), _ticks(0), _tick_counter(0), _tick_overide(false), _force_break(false)
    {}

    // : delay and tick count constuctor :
    Timer(double delay, int ticks)
        : _delay(delay), _ticks(ticks), _tick_counter(0), _tick_overide(false), _force_break(false)
    {}

    // : delay and overide constructor, when override is true, tick forever :
    Timer(double delay, bool override)
        : _delay(delay), _ticks(0), _tick_counter(0), _tick_overide(true), _force_break(false)
    {}

    // : destructor uncouple delegate :
    ~Timer()
    {
        _delegate = 0;
    }

    /* : returns true while still ticking :
     * : returns false when complete :
     * : Ticks _ticks amount of times
     * : Usage :
     * while (timer.tick()) {}
     */
    bool tick();

    // : starts the timer for use with timerdelegate :
    void start();

    // : getter / setter for _delay :
    double get_delay() const;
    void set_delay(double delay);

    // : getter / setter for _tick :
    int get_ticks() const;
      void set_ticks(int ticks);

    // : getter for _tick_counter :
    int get_tick_count() const;

    // : getter / setter for _tick_overide :
    // : use break; to exit loop
    bool get_tick_overide() const;
    void set_tick_overide(bool override);

    // : sets _tick_count to 0 :
    void reset();

    // : ends the timer ticking :
    void end();

    // : sets _delegate to delegate
    void set_delegate(ITimerDelegate *delegate);

private:
    // : delays execution by _delay amount :
    void _wait();

    ITimerDelegate *_delegate;

    double _delay;
    int _ticks;
    int _tick_counter;
    bool _tick_overide;
    bool _force_break;
};

#endif
