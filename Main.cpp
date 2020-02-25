#include <iostream>
#include <stdlib.h>
#include <vector>
#include <chrono>

#include "Node.h"
#include "GLUT.h"

/**
* Compile using: g++ Main.cpp Node.cpp GLUT.cpp -g -lglut -lGL -lGLU
* You can remove the -g option if you are not debugging
*/

using namespace std;

vector<int> rightmost;	//Stores the current rightmost element at each level.
int minSeparation = 45;	//Minimum separation between two node horizontally.
int verticalDistance = 45;
int scale = 1;
auto start = chrono::high_resolution_clock::now(); 
auto stop = chrono::high_resolution_clock::now(); 


Node* findInsertPosition(Node * root, int val)
{
	if(!root) return NULL;
    while(root->getLeftChild() || root->getRightChild())
    {
        if(val < root->getVal() && root->getLeftChild()) {
        	root = root->getLeftChild();
        } 
        else if(val > root->getVal() && root->getRightChild()) {
        	root = root->getRightChild();
        }
        else return root;
    }
    return root;
}

Node* makeBSTFromArray(vector<int> array)
{
    Node *root = NULL;
    for(int val : array)
    {
        Node *node = new Node(val);
        if(!root)
        {
            root = node;
            continue;
        }
        Node *parent = findInsertPosition(root, val);
        if(parent && val > parent->getVal()) 
        	parent->setRightChild(node);
        else if (parent && val < parent->getVal()) 
        	parent->setLeftChild(node);
    }
    return root;
}

Node *createBSTfromInput()
{
    cout << "How many numbers do you want to enter?\nAns: ";
    int count;
    cin >> count;
    cout << "Enter the numbers separated by a space\nAns: ";
    vector<int> array;
    int temp;
    while(count--)
    {
        cin >> temp;
        array.push_back(temp);
    }
    cout << "Scale the image by a factor of (int): ";
    cin >> scale;
    start = chrono::high_resolution_clock::now(); 
    Node *root = makeBSTFromArray(array);
    return root;
}

void setCoordinates(Node *root, int x, int y) {
	if(rightmost.size() < y + 1) rightmost.push_back(x);
	else if(x < rightmost[y] + minSeparation) x = rightmost[y] + minSeparation;
	if(root->getLeftChild()) {
		Node *lChild = root->getLeftChild();
		setCoordinates(lChild, x - minSeparation/2, y + 1);
	} 
	if(root->getRightChild()) {
		Node *rChild = root->getRightChild();
		setCoordinates(rChild, x + minSeparation/2, y + 1);
	}
	if(root->getLeftChild() && root->getRightChild()) x = max(x, (root->getLeftChild()->getCoordinates().first + root->getRightChild()->getCoordinates().first)/2);
	else if (root->getLeftChild()) x = max(x, root->getLeftChild()->getCoordinates().first + minSeparation/2);
	rightmost[y] = x;

	//Store the value to be drawn
	root->setCoordinates(x,-1*y*verticalDistance);
} 

void setCoordinates(Node *root) {
	setCoordinates(root, 0, 0);
}

int main(int argc, char ** argv)
{
    Node *root = createBSTfromInput();
    if(!root) {
    	cout << "No Nodes!\n";
    	return 0;
    }
    setCoordinates(root);
    stop = chrono::high_resolution_clock::now(); 
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
    cout << duration.count() << " microseconds" << endl; 

    drawTree(root, scale, &argc, argv);
    return 0;
}