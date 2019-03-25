/*
 * Binary Search Tree Visualization
 * Ashland University
 * Nathan Ahrens
 * Summer 2017
 *
 * Creation process:
 * This class is the BST and Node. This was built using a standard BST (from a C++ book),
 * but has been heavily modified to fit the needs of visualizing a BST. Some functions
 * have also been created to assist with drawing the BST.
 *
 * Drawing the BST:
 * In order to draw the BST, you must pass a QPainter object to the public draw() function.
 * This BST will take care of everything else - provided that the QWidget you are drawing on
 * is large enough.
 *
 * Sizing the "canvas" for the BST to fit:
 * This BST class also contains functions to assist with the sizing of the QWidget "canvas".
 * The functions "getTotalY()" and "getTotalX()" return the pixel dimensions required to
 * fully display the BST.
 * Then, on the canvas QWidget, you can just use setMinimumSize to ensure that the QWidget is
 * sized appropriately.
 */


#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <iostream>
#include <QPainter>
#include <QStack>
#include <QQueue>



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
    int x;
    Node<T> *leftChild;
    Node<T> *rightChild;
    Node<T> *parent;
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
    QString getPreOrderTraversal() const;
    QString getInOrderTraversal() const;
    QString getPostOrderTraversal() const;
    QString getBreadthFirstSearch();
    int getNodeCount() const;
    int getLeafNodeCount() const;
    int getTreeHeight() const;
    bool deleteItem(T);
    bool find(T) const;
    void draw(QPainter *painter, double &scale);
    int getTotalY() const;
    int getTotalX() const;
    bool deleteAtLocation(int x, int y);
private:
    QPainter *painter;
    Node<T> *root;
    int yspace;
    int xspace;
    int nodeRadius;
    double scale;
    int max(int a, int b) const;
    void recursivePreOrder(const Node<T> *) const;
    void recursiveInOrder(const Node<T> *) const;
    void recursivePostOrder(const Node<T> *) const;
    int recursiveCountNodes(const Node<T> *) const;
    int recursiveCountLeafNodes(const Node<T> *) const;
    int recursiveComputeHeightOfTree(const Node<T> *) const;
    void recursiveDeleteNodes(const Node<T> *);
    void recursiveDraw(Node<T> *node);
    Node<T>* getLeftmostNode(Node<T> *node) const;
    int getNodeLevel(Node<T> *node);
    int getPxLocOfLeftTree(const Node<T> *node);
    int getPxLocOfAncestor(const Node<T> *node);
    void resetNodePosition(Node<T> *node);
    bool recursiveDeleteAtLocation(Node<T> *node, int x, int y);
};

// Node constructor
template<typename T>
Node<T>::Node(const T &info) :
        data(info), x(0), leftChild(0), rightChild(0), parent(0)
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

// Delete a node at a given x, y location
template<typename T>
bool BinarySearchTree<T>::recursiveDeleteAtLocation(Node<T> *node, int x, int y)
{
    if (node == 0)
        return false;


    if (recursiveDeleteAtLocation(node->leftChild, x, y) == true)
        return true;

    int level = getNodeLevel(node);
    int nodey = (level * nodeRadius * 2 + yspace * (level-1)) - nodeRadius;
    int nodex = node->x - nodeRadius;

    // correct x, check y
    if (nodex <= x && x <=nodex + nodeRadius*2 )
    {
        // correct y, delete
        if (nodey <= y && y <= nodey + nodeRadius*2)
        {
            deleteItem(node->data);
            return true;
        }
    }
    return recursiveDeleteAtLocation(node->rightChild, x, y);
}

template<typename T>
bool BinarySearchTree<T>::deleteAtLocation(int x, int y)
{
    return recursiveDeleteAtLocation(root, x, y);
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
            std::cout << "Duplicate value: " << currentNode->data << std::endl;
            return false; // duplicate
        }
    }

    if (trailCurrentNode->data < item)
        trailCurrentNode->rightChild = newNode;
    else
        trailCurrentNode->leftChild = newNode;

    newNode->parent = trailCurrentNode;

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

    // NO LEFT, YES RIGHT
    if (currentNode->leftChild == 0 && currentNode->rightChild != 0)
    {
        // ROOT WITH RIGHT
        if (currentNode == root)
        {
            Node<T> *tempPtr = root;
            root->rightChild->parent = 0;
            root = root->rightChild;
            delete tempPtr;
            return found;
        }

        if (trailCurrentNode->data < item)
        {
            Node<T> *tempPtr = trailCurrentNode->rightChild;
            trailCurrentNode->rightChild = currentNode->rightChild;
            currentNode->rightChild->parent = trailCurrentNode;
            delete tempPtr;
        }
        else
        {
            Node<T> *tempPtr = trailCurrentNode->leftChild;
            trailCurrentNode->leftChild = currentNode->rightChild;
            currentNode->rightChild->parent = trailCurrentNode;
            delete tempPtr;
        }

        return found;
    }
    // LEFT CHILD, NO RIGHT CHILD
    if (currentNode->leftChild != 0 && currentNode->rightChild == 0)
    {
        // Root with left child
        if (currentNode == root)
        {
            Node<T> *tempPtr = root;
            root = root->leftChild;
            root->parent = 0;
            delete tempPtr;
        }
        if (trailCurrentNode->data < item)
        {
            Node<T> *tempPtr = trailCurrentNode->rightChild;
            trailCurrentNode->rightChild = currentNode->leftChild;
            currentNode->leftChild->parent = trailCurrentNode;
            delete tempPtr;
        }
        else
        {
            Node<T> *tempPtr = trailCurrentNode->leftChild;
            trailCurrentNode->leftChild = currentNode->leftChild;
            currentNode->leftChild->parent = trailCurrentNode;
            delete tempPtr;
        }
        return found;
    }

    //if the node has both children
    //find the succesor of the node to be deleted, replace the value and delete the succesor
    if (currentNode->leftChild != 0 && currentNode->rightChild != 0)
    {
        //if the leftchildren of the node we want to delete is a leaf, it means the children itself is the succesor
        Node<T> *ptr = currentNode;
        trailCurrentNode = currentNode;
        ptr = ptr->leftChild;
        if(ptr->rightChild==NULL)
        {
            if(ptr->leftChild==NULL)
            {
                currentNode->data=ptr->data;
                currentNode->leftChild=NULL;
                delete ptr;
            }
            else
            {
               currentNode->data=ptr->data;
               currentNode->leftChild=ptr->leftChild;
               ptr->leftChild->parent=currentNode;
               delete ptr;

            }

        }
        else
            {
            //else we look for the succesor in the subtree

            while (ptr->rightChild!=0)
               ptr=ptr->rightChild;
            trailCurrentNode=ptr->parent;
            trailCurrentNode->rightChild=NULL;
            currentNode->data=ptr->data;
            delete ptr;
            }
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
QString BinarySearchTree<T>::getPreOrderTraversal() const
{
    QStack<Node<T>*> stack;
    QString traversal;
    Node<T> *root = this->root;
    while (true) {
        // Go to the left extreme insert all the elements to stack, add to string as encountered
        while (root != 0) {
            traversal.append(QString::number(root->data) + " ");
            stack.push(root);
            root = root->leftChild;
        }
        // check if Stack is empty, if yes, exit from everywhere
        if (stack.isEmpty()) {
            return traversal;
        }
        // pop the element from the stack, add the nodes at
        // the right to the Stack
        root = stack.pop();
        root = root->rightChild;
    }
}

template<typename T>
QString BinarySearchTree<T>::getInOrderTraversal() const
{
    QStack<Node<T>*> stack;
    QString traversal;
    Node<T> *root = this->root;
    while (true) {
        // Go to the left extreme insert all the elements to stack
        while (root != 0) {
            stack.push(root);
            root = root->leftChild;
        }
        // check if Stack is empty, if yes, exit from everywhere
        if (stack.isEmpty()) {
            return traversal;
        }
        // pop the element from the stack , print it and add the nodes at
        // the right to the Stack
        root = stack.pop();
        traversal.append(QString::number(root->data) + " ");
        root = root->rightChild;
    }
}

template<typename T>
QString BinarySearchTree<T>::getPostOrderTraversal() const
{

    if (this->isEmpty())
            return QString("");
    QStack<Node<T>*> stack1;
    QStack<Node<T>*> stack2;
    QString traversal;
    Node<T> *root = this->root;
    stack1.push(root);
    while (!stack1.isEmpty())
    {
        // Take out the root and insert into stack 2
        Node<T> *temp = stack1.pop();
        stack2.push(temp);

        // now we have the root, push the left and right child of root into the first stack
        if (temp->leftChild != 0)
            stack1.push(temp->leftChild);
        if (temp->rightChild != 0)
            stack1.push(temp->rightChild);
    }

    while(!stack2.isEmpty())
        traversal.append(QString::number(stack2.pop()->data) + " ");

    return traversal;
}
 /*
  * Return a string of the breadth first traversal.
  */
template<typename T>
QString BinarySearchTree<T>::getBreadthFirstSearch()
{
    QString traversal("");

    /* Points to node we are processing. */
    Node<T> *traverse;

    if (this->root == 0)
        return traversal;  /* Nothing to traverse. */

    /* Create a queue to hold node pointers. */
    QQueue<Node<T>*> ptrQueue;

    /*
    * Gotta put something in the queue initially,
    * so that we enter the body of the loop.
    */
    ptrQueue.enqueue(this->root);

    while (!ptrQueue.isEmpty()) {
        traverse = ptrQueue.dequeue();

        //Visit the node pointed to by traverse.
        traversal.append(QString::number(traverse->data) + " ");

        /*
        * If there is a left child, add it
        * for later processing.
        */
        if (traverse->leftChild != 0)
        ptrQueue.enqueue(traverse->leftChild);

        /*
        * If there is a right child, add it
        * for later processing.
        */
        if (traverse->rightChild != 0)
        ptrQueue.enqueue(traverse->rightChild);
    }

    return traversal;
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

// Set all nodes' x value to 0 in preperation for redrawing with a scale multiplier applied.
template<typename T>
void BinarySearchTree<T>::resetNodePosition(Node<T> *node)
{
    if (node == 0)
        return;
    resetNodePosition(node->leftChild);
    node->x = 0;
    resetNodePosition(node->rightChild);

    return;
}


template<typename T>
void BinarySearchTree<T>::draw(QPainter *painter, double &scale)
{
    if(this->root == 0)
        return;
    // Set properties of the painter for drawing the tree
    this->painter = painter;
    this->painter->setFont(QFont("Times", 12 * scale, QFont::Normal));

    // Set variables for drawing the tree
    this->scale = scale;
    this->nodeRadius = 20 * scale;
    this->xspace = nodeRadius;
    this->yspace = nodeRadius * 5;

    // Before drawing, must make sure that all nodes have x = 0 since in recursiveDraw() we check value of x on some nodes.
    resetNodePosition(root);

    // first node drawn (leftmost node) needs to have a static, predefined
    // location for the rest of the tree to be based off.
    Node<T> *leftmost = getLeftmostNode(root);
    leftmost->x = nodeRadius * 2;

    // Draw the tree
    this->recursiveDraw(root);

    return;
}



// Recursively get the leftmost node
template<typename T>
Node<T>* BinarySearchTree<T>::getLeftmostNode(Node<T> *node) const
{
    if (node->leftChild == 0)
        return node;
    return getLeftmostNode(node->leftChild);
}



// Get the level of the node by tracing back its parents
template<typename T>
int BinarySearchTree<T>::getNodeLevel(Node<T> *node)
{
    int level = 1;
    Node<T> *current = node;

    while(current->parent != 0){
        current = current->parent;
        ++level;
    }
    return level;
}



// Calculate where the rightmost node is drawn of a left subtree
template<typename T>
int BinarySearchTree<T>::getPxLocOfLeftTree(const Node<T> *node)
{
    if(node->rightChild == 0){
        return node->x;
    }
    return getPxLocOfLeftTree(node->rightChild);
}



// Calculate where the ancestor of a node is so that the leftmost node of the right
// subtree can be drawn just to the right of the ancestor
template<typename T>
int BinarySearchTree<T>::getPxLocOfAncestor(const Node<T> *node)
{
    // All ancestor's node->x will be 0 unless it has already been drawn -
    // find the ancestor who's x != 0
    Node<T> *currentNode = node->parent;

    while(currentNode->x == 0)
        currentNode = currentNode->parent;

    return currentNode->x;
}

template<typename T>
int BinarySearchTree<T>::getTotalY() const
{
    int level = getTreeHeight() + 1;
    return (level * nodeRadius * 2 + yspace * (level-1)) + nodeRadius * 2;
}

template<typename T>
int BinarySearchTree<T>::getTotalX() const
{
    if (this->root == 0)
        return nodeRadius*3;

    Node<T> *current = root;
    while (current->rightChild != 0)
        current = current->rightChild;
    return current->x + nodeRadius * 3;
}

template<typename T>
void BinarySearchTree<T>::recursiveDraw(Node<T> *node)
{
    // Base case
    if (node == 0)
        return;

    // Draw left subtree
    this->recursiveDraw(node->leftChild);

    // Set the y position of the node based off of the level of the node and the nodeRadius
    int level = getNodeLevel(node);
    int y = level * nodeRadius * 2 + yspace * (level-1);

    // if there is a left child, we need to draw this parent relative to it
    if (node->leftChild != 0)
    {
        node->x = getPxLocOfLeftTree(node->leftChild) + nodeRadius + xspace;

        // Draw line to left child
        painter->drawLine(QPoint(node->x, y + nodeRadius), QPoint(node->leftChild->x + 2,((level + 1)* nodeRadius * 2 + yspace * level) - nodeRadius));
    }

    // in case of a node without a left child that is not the leftmost in the tree
    // - rules out root of tree (would be leftmost)
    // - must be the right child of some ancestor (parent, grandparent, etc..)
    // - must draw relative to first ancestor where x != 0
    else if (node->x == 0)
        node->x = getPxLocOfAncestor(node) + nodeRadius + xspace;

    // Draw the node
    painter->drawEllipse(QPoint(node->x, y),nodeRadius,nodeRadius);

    // Adjust the text horizontally depending on how many digits are in it
    int textAdjuster;
    if(std::abs(node->data) < 10)
        textAdjuster = 4;
    else if (std::abs(node->data) < 100)
        textAdjuster = 7;
    else if (std::abs(node->data) < 1000)
        textAdjuster = 12;
    else
        textAdjuster = 16;

    painter->drawText(QPoint(node->x-(textAdjuster*scale), y+(5*scale)), QString::number(node->data));

    // Draw the right subtree
    this->recursiveDraw(node->rightChild);

    // Draw the line to the right child (if applicable).
    // Must be done after recursively drawing right child, otherwise x values will still be 0.
    if (node->rightChild != 0)
        painter->drawLine(QPoint(node->x, y + nodeRadius), QPoint(node->rightChild->x - 2,((level + 1)* nodeRadius * 2 + yspace * level) - nodeRadius));

    return;
}

#endif /* BINARYSEARCHTREE_H_ */
