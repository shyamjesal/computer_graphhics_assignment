#ifndef _NODE_
#define _NODE_

#include <utility>
#include <stdlib.h>

using namespace std;

/**
*   Class to store the nodes of a binary tree
*
*	The coordinates are considered with center as origin
*	and the top right corner of window as (1,1)
*/
class Node
{
private:
    Node *lChild, *rChild; 	//Left and right children
    int val = 0;			//Value of the node
    int x, y;				//Coordinates of the node
public:
    /**
    *   Constuctor to create a node without children
    *
    *   @param int v: Value to be stored in the node
    */
    Node(int v);

    /**
    *   Constuctor to create a node with children
    *
    *   @param int v: Value to be stored in the node
    *	@param Node leftChild: Node which is the left child
    *	@param Node rightChild: Node which is the right child
    */
    Node(int v, Node leftChild, Node rightChild);

    // bool leftChildExists();
    // bool rightChildExists();

    /**
    *   @return Returns the left child of the current node
    */
    Node *getLeftChild();

    /**
    *   @return Returns the right child of the current node
    */
    Node *getRightChild();

    /**
    *   @return Returns the value of the current node
    */
    int getVal();

    /**
    *   @return Returns a pair of integers which are the coordinate values of the node
    */
    pair<int, int> getCoordinates();

    /**
    *   Sets the coordinates of a node
    *
    *	@param int X: The X coordinate of the node
    *	@param int Y: The Y coordinate of the node
    */
    void setCoordinates(int X, int Y);

    /**
    *   Sets the node passed as parameter as the left child of the current node
    *
    *	@param Node child: The node to be set as the left child of the current node
    */
    void setLeftChild(Node *child);

    /**
    *   Sets the node passed as parameter as the left child of the current node
    *
    *	@param Node child: The node to be set as the right child of the current node
    */
    void setRightChild(Node *child);
};

#endif