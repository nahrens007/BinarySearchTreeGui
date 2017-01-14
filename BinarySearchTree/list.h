/*
 * LinkedList.h
 *
 *  Created on: Oct 13, 2016
 *      Author: Nathan
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>

/*
 * Forward declaration of class List required to announce that class List
 * exists so it can be used in the friend declaration
 */
template< typename NODETYPE > class List;

template< typename NODETYPE >
class ListNode
{
    friend class List< NODETYPE > ; // make List a friend

public:
    ListNode(const NODETYPE &);
    NODETYPE getData() const; // return data in node
private:
    NODETYPE data; // data
    ListNode< NODETYPE > *nextPtr; // next node in list
};

template< typename NODETYPE >
ListNode< NODETYPE >::ListNode(const NODETYPE &info) :
        data(info), nextPtr(0)
{
    // empty body
}

//return copy of data in node
template< typename NODETYPE >
NODETYPE ListNode< NODETYPE >::getData() const
{
    return data;
}

/*
 * LinkedList class follows
 */

template< typename NODETYPE >
class List
{
public:
    List();
    ~List(); // deconstructor
    void insertAtFront(const NODETYPE &);
    void insertAtBack(const NODETYPE &);
    bool removeFromFront(NODETYPE &);
    bool removeFromBack(NODETYPE &);
    bool isEmpty() const;
    void print() const;
private:
    ListNode< NODETYPE > *firstPtr; // pointer to first node
    ListNode< NODETYPE > *lastPtr; // pointer to last node

    // utility function to allocate new node
    ListNode< NODETYPE > *getNewNode(const NODETYPE &);
};
// default constructor
template< typename NODETYPE >
List< NODETYPE >::List() :
        firstPtr(0), lastPtr(0)
{
    //empty body
}

// deconstructor
template< typename NODETYPE >
List< NODETYPE >::~List()
{
    if (!isEmpty())
    {
        ListNode< NODETYPE > *currentPtr = firstPtr;
        ListNode< NODETYPE > *tempPtr;

        while (currentPtr != 0) // delete remaining nodes
        {
            tempPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
        } // end while
    } // end if
} // end List deconstructor

// insert node at front of list
template< typename NODETYPE >
void List< NODETYPE >::insertAtFront(const NODETYPE &value)
{
    ListNode< NODETYPE > *newPtr = getNewNode(value); // new node

    if (isEmpty()) // List is empty
        firstPtr = lastPtr = newPtr; // new list has only one node
    else // List is not empty
    {
        newPtr->nextPtr = firstPtr; // point new node to previous 1st node
        firstPtr = newPtr; // firstPtr point to the new node
    } // end else
} // end function insertAtFront

// insert node at back of list
template< typename NODETYPE >
void List< NODETYPE >::insertAtBack(const NODETYPE &value)
{
    ListNode< NODETYPE > *newPtr = getNewNode(value); // new node

    if (isEmpty()) // List is empty
        firstPtr = lastPtr = newPtr; // new list has only one node
    else // List is not empty
    {
        lastPtr->nextPtr = newPtr; // update previous last node
        lastPtr = newPtr; // new last node
    } // end else
} // end function insertAtBack

// delete node from front of the list
template< typename NODETYPE >
bool List< NODETYPE >::removeFromFront(NODETYPE &value)
{
    if (isEmpty())
        return false;
    else
    {
        ListNode< NODETYPE > *tempPtr = firstPtr; // hold tempPtr to delete

        if (firstPtr == lastPtr)
            firstPtr = lastPtr = 0; // no nodes remain after removal
        else
            firstPtr = firstPtr->nextPtr; // point to previous 2nd node

        value = tempPtr->data; // return data being removed
        delete tempPtr; // reclaim previous front node
        return true; // delete successful
    } // end else
}

// delete node from back of the list
template< typename NODETYPE >
bool List< NODETYPE >::removeFromBack(NODETYPE &value)
{
    if (isEmpty())
        return false; // delete unsuccessful
    else
    {
        ListNode< NODETYPE > *tempPtr = lastPtr; // hold tempPtr to delete

        if (firstPtr == lastPtr)
            firstPtr = lastPtr = 0; // no nodes remain after removal
        else
        {
            ListNode< NODETYPE > *currentPtr = firstPtr;

            //locate second-to-last element
            while (currentPtr->nextPtr != lastPtr)
                currentPtr = currentPtr->nextPtr; // move to the next node

            lastPtr = currentPtr; // remove last node
            currentPtr->nextPtr = 0; // this is now the last node
        } // end else

        value = tempPtr->data; // return value from old last node
        delete tempPtr; // reclaim former last node
        return true; // delete successful
    } // end else
} // end function removeFromBack

// is list empty?
template< typename NODETYPE >
bool List< NODETYPE >::isEmpty() const
{
    return firstPtr == 0;
} // end function isEmpty

// return pointer to newly allocated node
template< typename NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode(const NODETYPE &value)
{
    return new ListNode< NODETYPE >(value);
} // end function getNewNode

// display contents of List
template< typename NODETYPE >
void List< NODETYPE >::print() const
{
    if (isEmpty()) // List is empty
    {
        std::cout << "The list is empty\n\n";
        return;
    } // end if

    ListNode< NODETYPE > *currentPtr = firstPtr;

    std::cout << "The list is: ";

    while (currentPtr != 0)
    {
        std::cout << currentPtr->data << ' ';
        currentPtr = currentPtr->nextPtr;
    } // end while

    std::cout << "\n\n";
} // end function print

#endif /* LIST_H_ */
