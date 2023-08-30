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
    int directionX;
    int directionY;

public:
    Circle(double r, GLfloat* c, double x, double y, double z):
        radius(r), color(c), x(x), y(y), z(z) 
    {
        directionY = randomOne();
        directionX = randomOne();
    }

    void update()
    {        
        bounce();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
        glTranslated(x, y, z);
        glutSolidSphere(radius, 30, 30);
        glPopMatrix();
    }

private:
    void bounce()
    {
        x += directionX * 0.02;
        if(x > 1)
        {
            directionX = -1;
            directionY = randomOne();
        }
        else if(x < -1)
        {
            directionX = 1;
            directionY = randomOne();
        }

        y += directionY * 0.02;
        if (y > 1)
        {
            directionY = -1;
            directionX = randomOne();
        } 
        else if (y < -1)
        {
            directionY = 1;
            directionX = randomOne();
        }

    }

    int randomOne()
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dist(0, 1);
        return dist(gen) * 2 - 1;
    }
};