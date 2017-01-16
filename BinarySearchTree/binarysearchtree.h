/*
 * binarysearchtree.h
 *
 *  Created on: Dec 10, 2016
 *      Author: nahrens
 */


#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <iostream>
#include <QPainter>

template<typename T> class BinarySearchTree;

// Class Node
template<typename T>
class Node
{
    friend class BinarySearchTree<T> ;
public:
    Node(const T &); // Constructor
private:
    T data;
    Node<T> *leftChild;
    Node<T> *rightChild;
};

// Class BinarySearchTree
template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();
    bool isEmpty() const;
    bool insert(const T &); // return false if duplicate...
    void resetTree();
    void preOrderTraversal() const;
    void inOrderTraversal() const;
    void postOrderTraversal() const;
    int getNodeCount() const;
    int getLeafNodeCount() const;
    int getTreeHeight() const;
    bool deleteItem(T);
    bool find(T) const;
    void draw(QPainter *painter, int width, double &scale);
private:
    Node<T> *root;
    double scale;
    int max(int a, int b) const;
    void recursivePreOrder(const Node<T> *) const;
    void recursiveInOrder(const Node<T> *) const;
    void recursivePostOrder(const Node<T> *) const;
    int recursiveCountNodes(const Node<T> *) const;
    int recursiveCountLeafNodes(const Node<T> *) const;
    int recursiveComputeHeightOfTree(const Node<T> *) const;
    void recursiveDeleteNodes(const Node<T> *);
    void recursiveDraw(const Node<T> *node, int x, int y, int height, QPainter *painter) const;
};

// Node constructor
template<typename T>
Node<T>::Node(const T &info) :
        data(info), leftChild(0), rightChild(0)
{
    // empty constructor
}

template<typename T>
int BinarySearchTree<T>::max(int a, int b) const
{
    return a > b ? a : b;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
        root(0), scale(1)
{

}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    // post order traverse to delete all nodes
    recursiveDeleteNodes(root);
    this->root = 0;
}
template<typename T>
bool BinarySearchTree<T>::isEmpty() const
{
    return root == 0;
}

template<typename T>
bool BinarySearchTree<T>::insert(const T &item)
{
    // return false if duplicate...

    Node<T> *newNode = new Node<T>(item);

    if (this->isEmpty())
    {
        this->root = newNode;
        return true; // successful insertion
    }

    Node<T> *currentNode = root;
    Node<T> *trailCurrentNode = root;

    while (currentNode != 0)
    {
        if (currentNode->data < item)
        {
            trailCurrentNode = currentNode;
            currentNode = currentNode->rightChild;
        }
        else if (currentNode->data > item)
        {
            trailCurrentNode = currentNode;
            currentNode = currentNode->leftChild;
        }
        else
        {
            return false; // duplicate
        }
    }

    if (trailCurrentNode->data < item)
        trailCurrentNode->rightChild = newNode;
    else
        trailCurrentNode->leftChild = newNode;

    return true; // Successful
}

template<typename T>
void BinarySearchTree<T>::resetTree()
{
    // delete each node ( just like in destructor )
    recursiveDeleteNodes(root);
    root = 0;
    return;
}

template<typename T>
void BinarySearchTree<T>::preOrderTraversal() const
{
    recursivePreOrder(root);
    return;
}

template<typename T>
void BinarySearchTree<T>::inOrderTraversal() const
{
    recursiveInOrder(root);
    return;
}

template<typename T>
void BinarySearchTree<T>::postOrderTraversal() const
{
    recursivePostOrder(root);
    return;
}

template<typename T>
int BinarySearchTree<T>::getNodeCount() const
{
    if (this->isEmpty())
        return 0;
    return recursiveCountNodes(root);
}

template<typename T>
int BinarySearchTree<T>::getLeafNodeCount() const
{
    if (this->isEmpty())
        return 0;
    return recursiveCountLeafNodes(root);
}

template<typename T>
int BinarySearchTree<T>::getTreeHeight() const
{
    if (this->isEmpty())
        return 0;
    return recursiveComputeHeightOfTree(root);
}

template<typename T>
bool BinarySearchTree<T>::deleteItem(T item)
{
    if (this->isEmpty())
        return false;

    bool found = false;
    Node<T> *currentNode = root;
    Node<T> *trailCurrentNode = root;

    while (!found && currentNode != 0)
    {
        if (currentNode->data == item)
            found = true;
        else if (currentNode->data < item)
        {
            trailCurrentNode = currentNode;
            currentNode = currentNode->rightChild;
        }
        else
        {
            trailCurrentNode = currentNode;
            currentNode = currentNode->leftChild;
        }
    }

    if (!found)
        return found;

    if (currentNode->leftChild == 0 && currentNode->rightChild == 0)
    {
        if (currentNode == root)
        {
            delete root;
            root = 0;
        }
        else if (trailCurrentNode->data < item)
        {
            delete trailCurrentNode->rightChild;
            trailCurrentNode->rightChild = 0;
        }
        else
        {
            delete trailCurrentNode->leftChild;
            trailCurrentNode->leftChild = 0;
        }
        return found;
    }

    if (currentNode->leftChild == 0 && currentNode->rightChild != 0)
    {
        if (currentNode == root)
        {
            Node<T> *tempPtr = root;
            root = root->rightChild;
            delete tempPtr;
        }
        if (trailCurrentNode->data < item)
        {
            Node<T> *tempPtr = trailCurrentNode->rightChild;
            trailCurrentNode->rightChild = currentNode->rightChild;
            delete tempPtr;
        }
        else
        {
            Node<T> *tempPtr = trailCurrentNode->leftChild;
            trailCurrentNode->leftChild = currentNode->rightChild;
            delete tempPtr;
        }

        return found;
    }

    if (currentNode->leftChild != 0 && currentNode->rightChild == 0)
    {
        if (currentNode == root)
        {
            Node<T> *tempPtr = root;
            root = root->leftChild;
            delete tempPtr;
        }
        if (trailCurrentNode->data < item)
        {
            Node<T> *tempPtr = trailCurrentNode->rightChild;
            trailCurrentNode->rightChild = currentNode->leftChild;
            delete tempPtr;
        }
        else
        {
            Node<T> *tempPtr = trailCurrentNode->leftChild;
            trailCurrentNode->leftChild = currentNode->leftChild;
            delete tempPtr;
        }
        return found;
    }

    if (currentNode->leftChild != 0 && currentNode->rightChild != 0)
    {
        Node<T> *ptr = currentNode;
        trailCurrentNode = currentNode;
        currentNode = currentNode->leftChild;

        while (currentNode->rightChild != 0)
        {
            trailCurrentNode = currentNode;
            currentNode = currentNode->rightChild;
        }
        if (trailCurrentNode->data < item)
        {
            Node<T> *tempPtr = trailCurrentNode->rightChild;
            trailCurrentNode->rightChild = currentNode->leftChild;
            delete tempPtr;
        }
        else
        {
            Node<T> *tempPtr = trailCurrentNode->leftChild;
            trailCurrentNode->leftChild = currentNode->leftChild;
            delete tempPtr;
        }

        ptr->data = currentNode->data;

        return found;
    }

    return found;
}

template<typename T>
bool BinarySearchTree<T>::find(T item) const
{
    if (this->isEmpty())
        return false;

    Node<T> *currentNode = root;
    while (currentNode != 0)
    {
        if (currentNode->data == item)
            return true;
        else if (currentNode->data < item)
            currentNode = currentNode->rightChild;
        else
            currentNode = currentNode->leftChild;
    }

    return false;
}

// private
template<typename T>
void BinarySearchTree<T>::recursivePreOrder(const Node<T> *node) const
{
    if (node == 0)
        return;
    std::cout << node->data << " ";
    recursivePreOrder(node->leftChild);
    recursivePreOrder(node->rightChild);

    return;
}

template<typename T>
void BinarySearchTree<T>::recursiveInOrder(const Node<T> *node) const
{
    if (node == 0)
        return;
    recursiveInOrder(node->leftChild);
    std::cout << node->data << " ";
    recursiveInOrder(node->rightChild);

    return;
}

template<typename T>
void BinarySearchTree<T>::recursivePostOrder(const Node<T> *node) const
{
    if (node == 0)
        return;
    recursivePostOrder(node->leftChild);
    recursivePostOrder(node->rightChild);
    std::cout << node->data << " ";

    return;
}

template<typename T>
int BinarySearchTree<T>::recursiveCountNodes(const Node<T> *node) const
{
    if (node == 0)
        return 0;
    return (1 + recursiveCountNodes(node->leftChild)
            + recursiveCountNodes(node->rightChild));

}

template<typename T>
int BinarySearchTree<T>::recursiveCountLeafNodes(const Node<T> *node) const
{
    if (node == 0)
        return 0;
    if (node->leftChild == 0 && node->rightChild == 0)
        return 1;

    return (recursiveCountLeafNodes(node->leftChild)
            + recursiveCountLeafNodes(node->rightChild));
}

template<typename T>
int BinarySearchTree<T>::recursiveComputeHeightOfTree(const Node<T> *node) const
{
    if (node == 0 || (node->leftChild == 0 && node->rightChild == 0))
        return 0;

    return 1
            + max(recursiveComputeHeightOfTree(node->leftChild),
                    recursiveComputeHeightOfTree(node->rightChild));
}

template<typename T>
void BinarySearchTree<T>::recursiveDeleteNodes(const Node<T> *node)
{
    if (node == 0)
        return;
    recursiveDeleteNodes(node->leftChild);
    recursiveDeleteNodes(node->rightChild);
    delete node;

    return;
}

template<typename T>
void BinarySearchTree<T>::draw(QPainter *painter, int width, double &scale)
{

    painter->setFont(QFont("Times", 12 * scale, QFont::Normal));
    this->scale = scale;
    this->recursiveDraw(root, width/2, 30, getTreeHeight(), painter);

    return;
}

template<typename T>
void BinarySearchTree<T>::recursiveDraw(const Node<T> *node, int x, int y, int height, QPainter *painter) const
{
    if (node == 0)
        return;

    int hvar = height;

    // Draw the children nodes further away to give room for
    // the rest of the decendants to be drawn
    if (height > 2)
        hvar = std::pow(2, height - 1);

    // Radius of the node's circle
    int nodeRadius = 20 * scale;

    // The amount of pixels between two nodes which share the same parent.
    // Basically, this value is the amount of pixels from the center of
    // a node to the edge of another node.
    int xseparation = nodeRadius + 2;
    int yseperation = nodeRadius * 5;



    // display node data and the circle encompassing the data
    painter->drawEllipse(QPoint(x, y),nodeRadius,nodeRadius);
    painter->drawText(QPoint(x-7, y+5), QString::number(node->data));

    // Draw the line to the left child
    if(node->leftChild != 0){
        QPen lpen;
        lpen.setColor(QColor(0, 0, 255, 255));
        lpen.setWidth(2);
        painter->setPen(lpen);
        painter->drawLine(QPoint(x, y+nodeRadius), QPoint(x-(hvar * xseparation), y+(yseperation - nodeRadius) ));
        lpen.setColor(QColor(0, 0, 0, 255));
        painter->setPen(lpen);
    }
    // Draw the line to the right child
    if(node->rightChild != 0){
        QPen rpen;
        rpen.setColor(QColor(0, 200, 0, 255));
        rpen.setWidth(2);
        painter->setPen(rpen);
        painter->drawLine(QPoint(x, y+nodeRadius), QPoint(x+(hvar * xseparation), y+(yseperation - nodeRadius) ));
        rpen.setColor(QColor(0, 0, 0, 255));
        painter->setPen(rpen);
    }

    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    // recursive display left child
    this->recursiveDraw(node->leftChild, x - (hvar * xseparation ), y + yseperation, height - 1, painter);

    brush.setColor(Qt::darkGreen);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    // recursive display right child
    this->recursiveDraw(node->rightChild, x + (hvar * xseparation ), y + yseperation, height - 1, painter);

    return;
}

#endif /* BINARYSEARCHTREE_H_ */
