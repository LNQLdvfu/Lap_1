#include <GL/glut.h>
#include <cmath>

const float PI = 3.1415926;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color to green
    glColor3f(0.0f, 1.0f, 0.0f);

    // Calculate the coordinates of the vertices of the equilateral triangle
    GLfloat x1 = 0.0f, y1 = 0.5f, x2 = -0.5f, y2 = -0.5f, x3 = 0.5f, y3 = -0.5f;
    GLfloat angle = 60 * PI / 180.0f; // 60 degrees in radians
    GLfloat temp_x, temp_y;

    temp_x = x1 * cos(angle) - y1 * sin(angle);
    temp_y = x1 * sin(angle) + y1 * cos(angle);
    x1 = temp_x;
    y1 = temp_y;

    temp_x = x2 * cos(angle) - y2 * sin(angle);
    temp_y = x2 * sin(angle) + y2 * cos(angle);
    x2 = temp_x;
    y2 = temp_y;

    temp_x = x3 * cos(angle) - y3 * sin(angle);
    temp_y = x3 * sin(angle) + y3 * cos(angle);
    x3 = temp_x;
    y3 = temp_y;

    // Draw the equilateral triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Equilateral Triangle");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

//clang -Wall -framework CoreFoundation -framework OpenGL main.cpp /opt/homebrew/Cellar/glfw/3.3.8/lib/libglfw.3.3.dylib
