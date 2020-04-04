/** @mainpage Graphics Assignment
 * @section authors Team members
 * These are the team members:
 * @author     Rut Vora
 * @author     Shyam Jesalpura
 * @author     Bharat Machan
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
#include "3d_definitions.h"

void displayCB(void) { /* function called whenever redisplay needed */
    glClear(GL_COLOR_BUFFER_BIT); /* clear the display */
    glColor3f(1.0, 1.0, 1.0);     /* set current color to white */
    //bottom square
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.5,0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    //top square
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    //connecting lines
    glBegin(GL_LINES);
        glVertex3f(+0.5, +0.5, +0.5);
        glVertex3f(+0.5, +0.5, -0.5);
        glVertex3f(-0.5, -0.5, +0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, +0.5, +0.5);
        glVertex3f(-0.5, +0.5, -0.5);
        glVertex3f(+0.5, -0.5, +0.5);
        glVertex3f(+0.5, -0.5, -0.5);
    glEnd();

    glutSwapBuffers(); /* Complete any pending operations */
}

class Camera{
    private:
        float field_of_view;
        float aspect_ratio;
        float z_near, z_far;

        Point3 eye, center;
        Vector3 up,u,v,n;

    public:
        void init()
        {
            eye.set(0.0, 0.0, 4.0);
            center.set(0.0, 0.0, 0.0);
            up.set(0, 1, 0);

            n.set(eye.x-center.x, eye.y-center.y, eye.z-center.z);
            n.normalize();

            u.set(up.cross(n));
            u.normalize();

            v.set(n.cross(u));
            v.normalize();

            field_of_view = 40.0;
            aspect_ratio = 1.0;
            z_near = -1.0;
            z_far = 1.0;     
            
            updatematrix();  
        }

        void translate(float du, float dv, float dn)
        {
            Vector3 delta = u.scale(du) + v.scale(dv) + n.scale(dn);

            eye.x += delta.x;
            eye.y += delta.y;
            eye.z += delta.z;

            center.x += delta.x;
            center.y += delta.y;
            center.z += delta.z;

            updatematrix();
        }

        void yaw(float angle)
        {
            // float radians = M_PI / 180 * angle;
            float radians = angle;
            float cosx = cos(radians);
            float sinx = sin(radians);

            Vector3 tempu,tempn;
            tempu.set(u.scale(cosx) + n.scale(sinx));
            tempn.set(-u.scale(sinx) + n.scale(cosx));

            u.set(tempu);
            n.set(tempn);

            center.x = eye.x - n.x;
            center.y = eye.y - n.y;
            center.z = eye.z - n.z;

            updatematrix();
        }
        
        void pitch(float angle)
        {
            // float radians = M_PI / 180 * angle;
            float radians = angle;
            float cosx = cos(radians);
            float sinx = sin(radians);

            Vector3 tempv,tempn;
            tempv.set(v.scale(cosx) + -n.scale(sinx));
            tempn.set(v.scale(sinx) + n.scale(cosx));

            v.set(tempv);
            n.set(tempn);

            center.x = eye.x - n.x;
            center.y = eye.y - n.y;
            center.z = eye.z - n.z;

            updatematrix();
        }

        void roll(float angle)
        {
            // float radians = M_PI / 180 * angle;
            float radians = angle;
            float cosx = cos(radians);
            float sinx = sin(radians);

            Vector3 tempu,tempv;

            tempu.set(u.scale(cosx) + -v.scale(sinx));
            tempv.set(u.scale(sinx) + v.scale(cosx));

            u.set(tempu);
            v.set(tempv);

            up.set(v);
            up.normalize();
            
            center.x = eye.x - n.x;
            center.y = eye.y - n.y;
            center.z = eye.z - n.z;

            updatematrix();
        }

        void pan(float dx)
        {
            field_of_view += dx;
            updatematrix();
        }
        
        void updatematrix()
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective( /* field of view in degree */ field_of_view,
            /* aspect ratio */ aspect_ratio,
            /* Z near */ z_near, /* Z far */ z_far);

            glMatrixMode(GL_MODELVIEW);
            //Reset stack
            glLoadIdentity();
            gluLookAt(eye.x, eye.y, eye.z,  /* eye is at (0,0,5) */
            center.x, center.y, center.z,      /* center is at (0,0,0) */
            up.x, up.y, up.z);      /* up is in positive Y direction */    
            glutPostRedisplay();
        }
} cybershot;

void keyCB(unsigned char key, int x, int y) { /* called on key press */
    if (key == 'q')
        exit(0);
    if (key == 'y')
    {
        cybershot.yaw(0.01);
    }
    if (key == 'Y')
    {
        cybershot.yaw(-0.01);
    }
    if (key == 'p')
    {
        cybershot.pitch(-0.01);
    }
    if (key == 'P')
    {
        cybershot.pitch(0.01);
    }
    if (key == 'r')
    {
        cybershot.roll(-0.01);
    }
    if (key == 'R')
    {
        cybershot.roll(0.01);
    }
    if (key == 'w')
    {
        cybershot.translate(0.0,0.05,0.0);
    }
    if (key == 'd')
    {
        cybershot.translate(0.05,0.0,0.0);   
    }
    if (key == 's')
    {
        cybershot.translate(0.0,-0.05,0.0);    
    }
    if (key == 'a')
    {
        cybershot.translate(-0.05,0.0,0.0);
    }
    if (key == '-')
    {
        cybershot.translate(0.0,0.0,0.05);
    }
    if (key == '=')
    {
        cybershot.translate(0.0,0.0,-0.05);
    }
    if (key == 'f')
    {
        cybershot.pan(1.0);
    }
    if (key == 'F')
    {
        cybershot.pan(-1.0);
    }
}

void init()
{
    /* from this point on the current window is win */
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0); /* set background to black */
    
    cybershot.init();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv); /* initialize GLUT system */

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500); /* width=400pixels height=500pixels */
    glutCreateWindow("3D_cube");     /* create window */

    init();
    glutDisplayFunc(displayCB);       /* set window's display callback */
    glutKeyboardFunc(keyCB);          /* set window's key callback */
    glutMainLoop(); /* start processing events... */
    /* execution never reaches this point */
    return 0;
}
