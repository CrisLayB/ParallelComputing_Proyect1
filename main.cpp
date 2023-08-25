#include <iostream>
#include <omp.h>
#include <chrono>
#include <thread>
#include <random>
#include <list>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

#include "circle.cpp"

/**
 * Universidad del Valle de Guatemala
 * Departamento de Ciencias de la Computación
 * Computación Paralela - Sección 20
 * 
 * Cristian Fernando Laynez Bachez
 * Sara Maria Paguaga Gonzales
 * Guillermo Santos Barrios
 * 
 * Proyecto 1
*/

// ! Instalation references of OpenGL:
// https://codingatharva.blogspot.com/2022/02/1-install-opengl-in-ubuntu-linux.html
// https://www.wikihow.com/Install-Mesa-(OpenGL)-on-Linux-Mint

// More references: https://cs.lmu.edu/~ray/notes/openglexamples/


GLfloat WHITE[] = {1, 1, 1};

std::list<Circle> circles;

unsigned int frameCount = 0;
unsigned int currentTime = 0;
unsigned int previousTime = 0;

struct ColorRGB {
    float r;
    float g;
    float b;
};

float floatRandom(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);

    return dis(gen);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void renderFunction()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
    
    glVertex2f(-0.1, -0.1);
    glVertex2f(-0.1, 0.1);
    glVertex2f(0.1, 0.1);
    glVertex2f(0.1, -0.1);

    glEnd();
    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void circlesDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
        
    for(Circle &c : circles) c.update();    

    glEnd();
    glFlush();
    glutSwapBuffers();
}

// ! Run code: 
// g++ main.cpp -fopenmp -lglut -lGL -lGLEW -lGLU -o main.exe
// ./main.exe num_objects
int main(int argc, char** argv)
{   
    if(argc < 2)
    {
        std::cout << "\nYou need to define the amount of objects to render" << std::endl;
        std::cout << "./main.exe num_objects" << std::endl;
        std::cout << "./main.exe 15\n" << std::endl;
        return -1;
    }

    int N = atoi(argv[1]);

    if(N <= 0)
    {
        std::cout << "\nYou must define at least one object or upper\n" << std::endl;
        return -1;
    }

    for (int i = 0; i < N; i++)
    {        
        GLfloat color_random[3];
        color_random[0] = floatRandom(0.2, 0.9);
        color_random[1] = floatRandom(0.2, 0.9);
        color_random[2] = floatRandom(0.2, 0.9);

        circles.push_back(            
            Circle(
                0.15, 
                color_random,
                floatRandom(-0.8, 0.8), 
                floatRandom(-0.8, 0.8), 
                floatRandom(-0.8, 0.8)
            )
        );
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Proyect 1");
    glutReshapeFunc(reshape);
    glutDisplayFunc(circlesDisplay);
    init();
    glutMainLoop();    

    // Render the objets N times and create colors of the random way and positions in the random way
    // Movement of the objects
    // Physics or trigonometry elements in the calculations (bounce in the walls, collisions and interactions)
    // Show the FPS
    return 0;
}