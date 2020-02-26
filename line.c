/** @mainpage Graphics Assignment
 * @section authors Team members
 * These are the team members:
 * @author     Rut Vora
 * @author     Shyam Jesalpura
 * @author     Bharat Malhan
 * @date       22 Feb 2020
 * @section part1 Assignment 1
 * This is the Part 1 of the Computer Graphics Assignment.
 *
 * Task 1 : Draw a Line via Bressenham's algorithm.\n
 * Task 2 : Draw a Circle via Bressenham's algorithm.\n
 * Task 3 : Beautiful tree representation.\n
 *
 * @section part2 Question 1 & 2
 * Draw a Line and a circle via Bressenham's algorithm.
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

/**
 * @brief      Puts a pixel.
 *
 * @param[in]  x     { x coordinate of the pixel to lit }
 * @param[in]  y     { y coordinate of the pixel to lit }
 */
void putPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

/**
 * @brief      Draws a line.
 *
 * @param[in]  x1    The x coordinate of point 1
 * @param[in]  y1    The y coordinate of point 1
 * @param[in]  x2    The x coordinate of point 2
 * @param[in]  y2    The y coordinate of point 2
 */
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1, y = y1;
    int xdir = x1 < x2 ? 1 : -1;
    int ydir = y1 < y2 ? 1 : -1;

    if (dy <= dx) {
        putPixel(x, y);
        dy = dy + dy;
        int d = dy - dx;

        for (int i = 0; i < dx; ++i) {
            if (d < 0) {
                d += dy;
            } else {
                y += ydir;
                d += dy - dx - dx;
            }
            putPixel(x, y);
            x += xdir;
        }

    } else {
        putPixel(x, y);
        dx = dx + dx;
        int d = dy - dx;

        for (int i = 0; i < dy; ++i) {
            if (d < 0) {
                x += xdir;
                d += dy + dy - dx;
            } else {
                d += -dx;
            }
            putPixel(x, y);
            y += ydir;
        }
    }
}

/**
 * @brief      {     // Plots 8 points of the circle }
 *
 * @param[in]  centerx  The center x coordinate
 * @param[in]  centery  The center y coordinate
 * @param[in]  x        { x coordinate relative to the center }
 * @param[in]  y        { y coordinate relative to the center }
 */
void plotCircle(int centerx, int centery, int x, int y) {
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

/**
 * @brief      Draws a circle.
 *
 * @param[in]  centerx  The center x coordinate
 * @param[in]  centery  The center y coordinate
 * @param[in]  radius   The radius
 */
void drawCircle(int centerx, int centery, int radius) {
    int x = 0, y = radius;
    plotCircle(centerx, centery, x, y);
    ++x;
    int d = 1 - radius;
    int dEast = 3;
    int dSouthEast = -2 * radius + 5;

    while (y >= x) {
        if (d < 0) {
            d += dEast;
            dEast += 2;
            dSouthEast += 2;
        } else {
            d += dSouthEast;
            dEast += 2;
            dSouthEast += 4;
            --y;
        }
        plotCircle(centerx, centery, x, y);
        ++x;
    }
}

void displayCB(void) { /* function called whenever redisplay needed */
    glClear(GL_COLOR_BUFFER_BIT); /* clear the display */
    glColor3f(1.0, 1.0, 1.0);     /* set current color to white */

    drawLine(200, 200, 200, 100);
    drawCircle(200, 200, 100);

    glFlush(); /* Complete any pending operations */
}

void keyCB(unsigned char key, int x, int y) { /* called on key press */
    if (key == 'q')
        exit(0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv); /* initialize GLUT system */

    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(400, 500); /* width=400pixels height=500pixels */
    glutCreateWindow("Line");     /* create window */

    /* from this point on the current window is win */

    glClearColor(0.0, 0.0, 0.0, 0.0); /* set background to black */
    gluOrtho2D(0, 400, 0, 500);       /* how object is mapped to window */
    glutDisplayFunc(displayCB);       /* set window's display callback */
    glutKeyboardFunc(keyCB);          /* set window's key callback */

    glutMainLoop(); /* start processing events... */

    /* execution never reaches this point */

    return 0;
}
