#include "GLUT.h"
#include <iostream>
#include <climits>

using namespace std;

Node *ROOT;
int xMin = INT_MAX, yMin = INT_MAX, xMax = INT_MIN, yMax = INT_MIN;

void putPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plotCircle(int centerx, int centery, int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(centerx + x, centery + y);   /// 90 to 45 degree
    glVertex2i(centerx + y, centery + x);   /// 45 to 0 degree
    glVertex2i(centerx + -x, centery + y);  /// 135 to 90 degree
    glVertex2i(centerx + y, centery + -x);  /// 180 to 135 degree
    glVertex2i(centerx + x, centery + -y);  ///-45 to -90 degree
    glVertex2i(centerx + -y, centery + x);  /// 0 to -45 degree
    glVertex2i(centerx + -x, centery + -y); ///-90 to -135 degree
    glVertex2i(centerx + -y, centery + -x); ///-135 to 180 degree
    glEnd();
}

void drawCircle(int centerx, int centery)
{
    int x = 0, y = radius;
    plotCircle(centerx, centery, x, y);
    ++x;
    int d = 1 - radius;
    int dEast = 3;
    int dSouthEast = -2 * radius + 5;

    while (y >= x)
    {
        if (d < 0)
        {
            d += dEast;
            dEast += 2;
            dSouthEast += 2;
        }
        else
        {
            d += dSouthEast;
            dEast += 2;
            dSouthEast += 4;
            --y;
        }
        plotCircle(centerx, centery, x, y);
        ++x;
    }
}

void drawLine(pair<int, int> p1, pair<int, int> p2)
{
    int x1 = p1.first;
    int y1 = p1.second;
    int x2 = p2.first;
    int y2 = p2.second;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1, y = y1;
    int xdir = x1 < x2 ? 1 : -1;
    int ydir = y1 < y2 ? 1 : -1;

    if (dy <= dx)
    {
        putPixel(x, y);
        dy = dy + dy;
        int d = dy - dx;

        for (int i = 0; i < dx; ++i)
        {
            if (d < 0)
            {
                d += dy;
            }
            else
            {
                y += ydir;
                d += dy - dx - dx;
            }
            putPixel(x, y);
            x += xdir;
        }

    }
    else
    {
        putPixel(x, y);
        dx = dx + dx;
        int d = dy - dx;

        for (int i = 0; i < dy; ++i)
        {
            if (d < 0)
            {
                x += xdir;
                d += dy + dy - dx;
            }
            else
            {
                d += -dx;
            }
            putPixel(x, y);
            y += ydir;
        }
    }
}

void drawNode(Node *root)
{
    auto rootCoordinates = root->getCoordinates();
    drawCircle(rootCoordinates.first, rootCoordinates.second);	//The node itself
    if(root->getLeftChild()) drawLine(rootCoordinates, root->getLeftChild()->getCoordinates());
    if(root->getRightChild()) drawLine(rootCoordinates, root->getRightChild()->getCoordinates());
}

void drawTree(Node *root)
{
    if(root->getLeftChild())
    {
        Node *lChild = root->getLeftChild();
        drawTree(lChild);
    }
    if(root->getRightChild())
    {
        Node *rChild = root->getRightChild();
        drawTree(rChild);
    }
    drawNode(root);
}

void displayCB(void)   /* function called whenever redisplay needed */
{
    glClear(GL_COLOR_BUFFER_BIT); /* clear the display */
    glColor3f(1.0, 1.0, 1.0);     /* set current color to white */

    Node *root = ROOT;
    drawTree(root);

    glFlush(); /* Complete any pending operations */
}

void keyCB(unsigned char key, int x, int y)   /* called on key press */
{
    if (key == 27)
        exit(0);
    else
        cout << x << "\t" << y << endl;
}

void init(int *argc, char **argv, int scale)
{
    glutInit(argc, argv); /* initialize GLUT system */

    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize((xMax - xMin + 100)*scale, (yMax - yMin + 100)*scale); /* width=400pixels height=500pixels */
    glutCreateWindow("BST");     /* create window */

    /* from this point on the current window is win */

    glClearColor(0.0, 0.0, 0.0, 0.0);								/* set background to black */
    gluOrtho2D(xMin - 100, xMax + 100, yMin - 100, yMax + 100);			/* how object is mapped to window */
    glutDisplayFunc(displayCB);										/* set window's display callback */
    glutKeyboardFunc(keyCB);										/* set window's key callback */

    glutMainLoop(); /* start processing events... */
}

void getWindowLimits(Node *root)
{
    Node *temp = root;
    while(temp && temp->getLeftChild())
    {
        auto coordinates = temp->getCoordinates();
        if(xMin > coordinates.first) xMin = coordinates.first;
        if(yMin > coordinates.second) yMin = coordinates.second;
        if(xMax < coordinates.first) xMax = coordinates.first;
        if(yMax < coordinates.second) yMax = coordinates.second;
        temp = temp->getLeftChild();
    }

    temp = root;
    while(temp && temp->getRightChild()) {
    	auto coordinates = temp->getCoordinates();
        if(xMin > coordinates.first) xMin = coordinates.first;
        if(yMin > coordinates.second) yMin = coordinates.second;
        if(xMax < coordinates.first) xMax = coordinates.first;
        if(yMax < coordinates.second) yMax = coordinates.second;
        temp = temp->getRightChild();	
    }

}

void drawTree(Node *root, int scale, int *argc, char **argv)
{
    ROOT = root;
    getWindowLimits(root);
    init(argc, argv, scale);
    drawTree(root);
}