#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>

using namespace std;

#include "cell.hpp"
#include "grid.hpp"
//int argc, char* argv[]

void display();

int main(int argc, char* argv[])
{   
    srand(time(NULL));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutCreateWindow("Celular automata");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(display);

    glutMainLoop(); 
    return 0;
}

void display()
{   
    Grid grid(100);

    // reproduction_rate,  max_population, migration_pararameter
    grid.set_params(0.99, 100, 0.05);
    cout << "fert: " << grid.fertility << " mort: " << grid.mortality << endl;
    grid.fill_present_grid();

    int month = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int t = 0; t < 48; t++) //simulate for t years
    {
        //DISPLAY THE MATRIX
        GLfloat minSize = 300.0f/grid.width;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, 100, 100, 0.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glViewport(0, 0, 600, 600);

        for(int y = 0; y <= grid.width; y++) //for row in matrix
        {
            for(int x = 0; x <= grid.width; x++) //for col in matrix
            {   
                if(grid.present_grid[grid.order_from_coords(x, y)].state < 0.1) {
                    glColor3f(0.0f, 0.0f, 0.0f);
                }
                else if (grid.present_grid[grid.order_from_coords(x, y)].state < 0.2) {
                    glColor3f(0.0f, 0.301f, 0.301f);
                }
                else if (grid.present_grid[grid.order_from_coords(x, y)].state < 0.3) {
                    glColor3f(0.32157f, 0.0941f, 0.0f);
                }
                else if (grid.present_grid[grid.order_from_coords(x, y)].state < 0.4) {
                    glColor3f(0.0f, 1.0f, 1.0f );
                }
                else if (grid.present_grid[grid.order_from_coords(x, y)].state < 0.5) {
                    glColor3f(0.5f, 1.0f, 0.5f);
                }
                else
                {
                    glColor3f(1.0f, 0.0f, 1.0f);
                }

                glBegin(GL_QUADS); // 2x2 pixels
                glVertex2f(0.0f+minSize*x, 0.0f+minSize*y);
                glVertex2f(0.0f+minSize*(x+1), 0.0f+minSize*y);
                glVertex2f(0.0f+minSize*(x+1), 0.0f+minSize*(y+1));
                glVertex2f(0.0f+minSize*x, 0.0f+minSize*(y+1));
                glEnd();

                glEnd();
            }
        }
        glutSwapBuffers();
        usleep(10000);
        month = t % 12;
        grid.get_future_grid(month);
        grid.copy_future_to_present_grid();
    }    
}