#include <iostream>
#include <stdlib.h>
#include <vector>

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

/**
 * @brief      Finds an insert position for the new node in the BST.
 *
 * @param      root  The root of the tree
 * @param[in]  val   The value of the node
 *
 * @return     returns the node of the updated tree
 */
Node* findInsertPosition(Node * root, int val)
{
	if(!root) return NULL;
    while(root->getLeftChild() || root->getRightChild())
    {
        if(val < root->getVal() && root->getLeftChild()) {
        	root = root->getLeftChild(); /*If left child exists and the value to be inserted is less than the node value*/
        } 
        else if(val > root->getVal() && root->getRightChild()) {
        	root = root->getRightChild(); /*If right child exists and the value to be inserted is greater than the node value.*/
        }
        else return root;
    }
    return root;
}

/**
 * @brief      Makes a bst from array.
 *
 * @param[in]  array  The array containing the elements of the tree.
 *
 * @return     returns the pointer to the root of the tree.
 */
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

/**
 * @brief      Creates a bst from input.
 *
 * @return     returns the pointer to the root of the tree.
 */
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
    Node *root = makeBSTFromArray(array);
    return root;
}

/**
 * @brief      Sets the coordinates.
 *
 * @param      root  The root
 * @param[in]  x     The new value
 * @param[in]  y     The new value
 */
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

/**
 * @brief      Sets the coordinates.
 *
 * @param      root  The root fo the tree
 */
void setCoordinates(Node *root) {
	setCoordinates(root, 0, 0);
}

/**
 * @brief      Main function to draw the tree
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     0 when the program terminates properly.
 */
int main(int argc, char ** argv)
{
    Node *root = createBSTfromInput();
    if(!root) {
    	cout << "No Nodes!\n";
    	return 0;
    }
    setCoordinates(root);
    drawTree(root, scale, &argc, argv);
    return 0;
}