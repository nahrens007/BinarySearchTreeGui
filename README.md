# Visualizing data in a Binary Search Tree
The goal of this project is to be able to visualize data in a Binary Search Tree (BST). 

What's unique about BST's is that the value of the data in the left child node is less than the value in its parent node, and the value stored in the right child node is greater than the parent. This makes searching for a value more efficient than other searching methods (data stored in an array or linked list, for example). 
This project allows faculty to be able to graphically display Binary Search Trees while explaining them to students.

# Features
- Load and save Binary Search Trees to a text file
- Save a BST as an image file
- Insert nodes graphically, after the BST has already been built (or build a tree from scratch)
- Delete nodes graphically (you can not click on the node to delete it, however)
- Easily view common properties of a Binary Search Tree including: height, total node count, leaf node count, and internal node count
- Easily view preorder, inorder, and postorder traversals of a BST
- Zoom in and out in order to more easily view a large or small tree

# Design
This project is programmed completely in C++ using the Qt GUI framework. The Qt framework allows for advanced graphical programming and efficient drawing. 

## Why C++
I chose to build this project in C++ for the learning experience. I have wanted to learn C++ since I became a college student so I decided I would learn by working on a project. Java may have been a better option for this sort of project since it has strong GUI support (the swing library), but again, I wanted to learn C++. C++'s use of pointers has made it an extremely effective language for this project. I have used pointers unsparingly, trying to make the program as efficiently as possible. As many of the programs functions are recursive, pointers have proven to be very effective. 

## Why Qt?
I chose to use Qt as the GUI framework because of its expansive documentation. There is almost no other C++ GUI library out there with documentation as good as Qt. Qt's documentation has made it a lot easier learning how to program GUI's with C++. 
