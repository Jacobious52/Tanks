//
//  MutableArray.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef _MUTABLE_ARRAY_H
#define _MUTABLE_ARRAY_H

#define DEFAULT_ARRAY_SIZE 128

#include <algorithm>

// :: template class for mutable array ::
// :: MutableArray<typename> array ::
template<typename T>
class MutableArray
{
public:
    // : default constructor :
    MutableArray()
    {
        init(DEFAULT_ARRAY_SIZE);
    }

    // : constructor for setting initial array capacaity :
    MutableArray(int size)
    {
        init(size);
    }

    // : deletes pointer to array. does not remove actual items :
    // : use clear first :
    ~MutableArray()
    {
        delete[] _items;
    }

    // : adds item to array :
    // : if reached capacity resize array :
    void add(T item)
    {
        if (_count >= _size)
        {
            // increasr the size of the array if we need
            _resize();
        }
        _items[_count++] = item;
    }

    // : remove item from array and return pointer to deleted item :
    T remove(size_t index)
    {
        if (index >= 0 && index < _count)
        {
            // get item being removed
            T item = _items[index];
            // shift everything right once
            for (size_t i = index; i < _count; ++i)
            {
                _items[i] = _items[i+1];
            }

            --_count;

            return item;
        }

        return T();
    }

    // : get item at index :
    T operator[](size_t index)
    {
        return get_item(index);
    }

    // : return item at index :
    T get_item(size_t index)
    {
        if (index >= 0 && index < _count)
        {
            return _items[index];
        }

        return T();
    }

    // : remove all the items :
    // : deleting is left to the user :
    void clear()
    {
        for (int i = 0; i < _count; ++i)
        {
            if (_items[i] != 0)
            {
                remove(i);
            }
        }

        _count = 0;
    }

    // : returns how many items in array :
    size_t get_count() const
    {
        return _count;
    }

    // : returns the current capacity of the array :
    size_t get_size() const
    {
        return _size;
    }

    // : set item at index to item :
    void set_item(size_t index, T item)
    {
        if (index >= 0 && index < _count)
        {
            _items[index] = item;
        }
    }

private:
    T *_items;
    size_t _count;
    size_t _size;
    size_t _increment_size;

    // : init the array
    void init(size_t size)
    {
        _count = 0;
        _size = size;
        _increment_size = _size;
        _items = new T[_size];
    }

    // increase the size of the array
    void _resize()
    {
        size_t new_size = _size + _increment_size;

        T *new_items = new T[new_size];
        std::copy(_items, _items+_size, new_items);

        _size = new_size;
        delete[] _items;
        _items = new_items;
    }
};

#endif  // _MUTABLE_ARRAY_H
