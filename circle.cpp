#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <omp.h>

// More references: https://cs.lmu.edu/~ray/notes/openglexamples/

class Circle {

private:
    double radius;
    GLfloat color[3];
    double x;
    double y;
    double z;
    int directionX;
    int directionY;
    double speed;

public:
    Circle(double r):
        radius(r), 
        x(floatRandom(-0.8, 0.8)), 
        y(floatRandom(-0.8, 0.8)), 
        z(floatRandom(-0.8, 0.8)) 
    {
        directionY = randomOne();
        directionX = randomOne();
        speed = 0.02;
        changueColor();
    }

    Circle(double r, int thread_count):
        radius(r), 
        x(floatRandom(-0.8, 0.8)), 
        y(floatRandom(-0.8, 0.8)), 
        z(floatRandom(-0.8, 0.8)) 
    {
        directionY = randomOne();
        directionX = randomOne();
        speed = 0.02;
        changueColor(thread_count);
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
        }
        else if(x < -1)
        {
            directionX = 1;
            directionY = randomOne();
            speed = floatRandom(0.01, 0.04);
        }

        y += directionY * speed;
        if (y > 1)
        {
            directionY = -1;
            directionX = randomOne();
            speed = floatRandom(0.01, 0.04);
        } 
        else if (y < -1)
        {
            directionY = 1;
            directionX = randomOne();
            speed = floatRandom(0.01, 0.04);
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
            floatRandom(0.1f, 1.0f), 
            floatRandom(0.1f, 1.0f), 
            floatRandom(0.1f, 1.0f)
        };

        for (int i = 0; i < 3; i++) {
            color[i] = colorRandom[i];
        }
    }

    void changueColor(int thread_count)
    {
        GLfloat colorRandom[] = {
            floatRandom(0.1f, 1.0f), 
            floatRandom(0.1f, 1.0f), 
            floatRandom(0.1f, 1.0f)
        };

        #pragma omp parallel for num_threads(thread_count)
        for (int i = 0; i < 3; i++) {
            color[i] = colorRandom[i];
        }
    }
};