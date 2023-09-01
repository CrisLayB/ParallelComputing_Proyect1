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
    double speed;

public:
    Circle(double r, GLfloat* c, double x, double y, double z):
        radius(r), color(c), x(x), y(y), z(z) 
    {
        directionY = randomOne();
        directionX = randomOne();
        speed = 0.02;
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
        x += directionX * speed;
        if(x > 1)
        {
            directionX = -1;
            directionY = randomOne();
            speed = floatRandom(0.01, 0.04);
            changueColor();
        }
        else if(x < -1)
        {
            directionX = 1;
            directionY = randomOne();
            speed = floatRandom(0.01, 0.04);
            changueColor();
        }

        y += directionY * speed;
        if (y > 1)
        {
            directionY = -1;
            directionX = randomOne();
            speed = floatRandom(0.01, 0.04);
            changueColor();
        } 
        else if (y < -1)
        {
            directionY = 1;
            directionX = randomOne();
            speed = floatRandom(0.01, 0.04);
            changueColor();
        }
    }

    int randomOne()
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dist(0, 1);
        return dist(gen) * 2 - 1;
    }

    float floatRandom(float min, float max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min, max);

        return dis(gen);
    }

    void changueColor()
    {
        GLfloat colorRandom[] = {
            floatRandom(0.0f, 1.0f), 
            floatRandom(0.0f, 1.0f), 
            floatRandom(0.0f, 1.0f)
        };

        for (int i = 0; i < 3; i++) {
            color[i] = colorRandom[i];
        }
    }
};