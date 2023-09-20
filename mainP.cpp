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
unsigned int thread_count = 0;

void init() {
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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

    // Incrementa el contador de cuadros
    frameCount++;

    // Calcula el tiempo actual
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    // Calcula el tiempo transcurrido desde el ultimo calculo de FPS
    unsigned int deltaTime = currentTime - previousTime;

    // Si ha pasado al menos un segundo, calcula y muestra los FPS
    if (deltaTime >= 1000) {
        // Calcula los FPS
        float fps = frameCount / (deltaTime / 1000.0f);

        // Muestra los FPS en la consola
        std::cout << "FPS: " << fps << std::endl;

        // Reinicia el contador de cuadros y el tiempo
        frameCount = 0;
        previousTime = currentTime;
    }

    // Paralelizar la actualizacion de circulos
  
    #pragma omp parallel for num_threads(thread_count)
    for(Circle &c : circles) c.update();    

    glEnd();
    glFlush();
    glutSwapBuffers();
}

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}

// ! Run code: 
// g++ mainP.cpp -fopenmp -lglut -lGL -lGLEW -lGLU -o mainP.exe
// ./mainP.exe num_objects
// ./mainP.exe 100 5
int main(int argc, char** argv)
{   
    if(argc < 3)
    {
        std::cout << "\nYou need to define the amount of objects to render" << std::endl;
        std::cout << "./main.exe num_objects threads" << std::endl;
        std::cout << "\nExample: " << std::endl;
        std::cout << "./main.exe 15 5\n" << std::endl;
        return -1;
    }

    int N = strtol(argv[1], NULL, 10);
    thread_count = strtol(argv[2], NULL, 10);

    if(N <= 0)
    {
        std::cout << "\nYou must define at least one object or upper\n" << std::endl;
        return -1;
    }

    #pragma omp parallel for num_threads(thread_count)
    for (int i = 0; i < N; i++)
    {        
        circles.push_back(Circle(0.15));
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Proyect 1 Parallel");
    glutReshapeFunc(reshape);
    glutDisplayFunc(circlesDisplay);
    glutTimerFunc(20, timer, 0);
    init();
    glutMainLoop();
    return 0;
}