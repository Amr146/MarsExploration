#pragma once
//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file PriorityQueueADT.h */

template<class ItemType>
class PriorityQueueADT
{
public:
    /** Sees whether this queue is empty.
     @return  True if the queue is empty, or false if not. */
    virtual bool isEmpty() const = 0;

    /** Adds a new entry to the queue accourding to its priority.
     @post  If the operation was successful, newEntry is at the
        correct position in the queue.
     @param newEntry  The object to be added as a new entry.
     @return  True if the addition is successful or false if not. */
    virtual bool add(const ItemType& newEntry, double priority) = 0;

    /** Copies the front item of the queue to the passed parameter and removes it from queue
     @post  If the operation was successful, the front of the queue
        would be copied to FrontEntry parameter and removed from the queue.
     @return  True if the removal is successful or false if not. */
    virtual bool remove(ItemType& FrontEntry) = 0;

    /** Copies the front item of the queue to the passed parameter without removing it from queue
     @pre  The queue is not empty.
     @post  The front of the queue has been copied to FrontEntry param , and the
        queue is unchanged.
     @return  The front of the queue. */
    virtual bool peek(ItemType& FrontEntry) const = 0;

    /** Destroys this queue and frees its memory. */
    virtual ~PriorityQueueADT() { }
}; // end QueueADT