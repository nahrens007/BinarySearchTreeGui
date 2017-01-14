#ifndef QUEUE_H_
#define QUEUE_H_

#include "list.h"

template< typename T >
class Queue : private List< T >
{
public:
    void enqueue( const T &data )
    {
        this->insertAtBack( data );
    }

    bool dequeue( T &data )
    {
        return this->removeFromFront( data );
    }

    bool isQueueEmpty() const
    {
        return this->isEmpty();
    }

    void printQueue() const
    {
        this->print();
    }
};

#endif // QUEUE_H_
