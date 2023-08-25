#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// More references: https://cs.lmu.edu/~ray/notes/openglexamples/

class Circle {

private:
    double radius;
    GLfloat* color;
    double x;
    double y;
    double z;

public:
    Circle(double r, GLfloat* c, double x, double y, double z):
        radius(r), color(c), x(x), y(y), z(z) 
    {
        direction = -1;
    }

    void update()
    {
        y += direction * 0.02;
        if (y > 1){
            direction = -1;
        } 
        else if (y < -1){
            direction = 1;
        }

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
        glTranslated(x, y, z);
        glutSolidSphere(radius, 30, 30);
        glPopMatrix();
    }
};