#ifndef _GLUTFILE_
#define _GLUTFILE_

#include <GL/glut.h>
#include <utility>
#include "Node.h"
#include <math.h>


using namespace std;

const int radius = 15;

/*
* Gives a beautiful representation of the tree 
* denoted by the pointer to root.
*
* @param Node *root: Pointer to the root of the tree
* @param int scale: The value to scale the entire output by
* @param int *argc: The count of inline arguments
* @param char **argv: The inline arguments
*/
void drawTree(Node *root, int scale, int *argc, char** argv);

#endif