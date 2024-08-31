#include <math.h>
#include <GL/glut.h>
#include <ctime>

float ballX = -0.8f;
float ballY = -0.3f;
float ballZ = -1.2f;

float colR = 1.0;
float colG = 0.0;
float colB = 0.0;

float bgcolR = 0.6;
float bgcolG = 0.0;
float bgcolB = 0.0;

static int flag = 1;

void drawsun() {
    glColor3f(colR, colG, colB);
    glTranslatef(ballX, ballY, ballZ);
    glutSolidSphere(0.1, 30, 30);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void update(int value) {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int current_time = now->tm_hour * 3600 + now->tm_min * 60 + now->tm_sec;

    if (flag) {
        ballX += 0.001f;
        ballY += 0.0007f;
        colR -= 0.00005;
        colG += 0.001;
        bgcolR -= 0.001;
        bgcolB += 0.06;

        if (ballX > 0.3) {
            flag = 0;
        }
    } else {
        ballX += 0.001f;
        ballY -= 0.0007f;
        colR += 0.00005;
        colG -= 0.001;
        bgcolR += 0.001;
        bgcolB -= 0.06;


        if (ballX < -0.3) {
            flag = 1;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1, update, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bgcolR, bgcolG, bgcolB, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    drawsun();
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 300);
    glutCreateWindow("SUN");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1, update, 0);
    glutMainLoop();
    return 0;
}

