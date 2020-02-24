#include "Node.h"

using namespace std;

Node::Node(int v)
{
    lChild = NULL;
    rChild = NULL;
    val = v;
    x = -1;
    y = -1;
}

Node::Node(int v, Node leftChild, Node rightChild)
{
    *lChild = leftChild;
    *rChild = rightChild;
    val = v;
    x = -1;
    y = -1;
}

// bool Node::leftChildExists() {
// 	if(lChild) return true;
// }

// bool Node::rightChildExists() {
// 	if(rChild) return true;
// }

Node *Node::getLeftChild()
{
    return lChild;
}

Node *Node::getRightChild()
{
    return rChild;
}

int Node::getVal()
{
    return val;
}

pair<int, int> Node::getCoordinates()
{
    return make_pair(x, y);
}

void Node::setCoordinates(int X, int Y)
{
    x = X;
    y = Y;
}

void Node::setLeftChild(Node *child)
{
    lChild = child;
}

void Node::setRightChild(Node *child)
{
    rChild = child;
}