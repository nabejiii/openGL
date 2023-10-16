#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define WINDOW_X (500)
#define WINDOW_Y (500)
#define WINDOW_NAME "test2"

void init_GL(int argc, char *argv[]);
void init();
void set_callback_functions();

void glut_display();
void glut_keyboard(unsigned char key, int x, int y);
void glut_mouse(int button, int state, int x, int y);
void glut_motion(int x, int y);

void draw_cube();

// グローバル変数
double g_angle1 = 0.0;
double g_angle2 = 0.0;
double g_distance = 10.0;
bool g_isLeftButtonOn = false;
bool g_isRightButtonOn = false;

int main(int argc, char *argv[]){
	/* OpenGLの初期化 */
	init_GL(argc,argv);

	/* このプログラム特有の初期化 */
	init();

	/* コールバック関数の登録 */
	set_callback_functions();

	/* メインループ */
	glutMainLoop();

	return 0;
}

void init_GL(int argc, char *argv[]){
	glutInit(&argc, argv);
	/* hatena */
	glutInitWindowSize(WINDOW_X,WINDOW_Y);
	glutCreateWindow(WINDOW_NAME);
}

void init(){
	/* 背景の塗りつぶし色を指定 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void set_callback_functions(){
	glutDisplayFunc(glut_display);
    glutKeyboardFunc(glut_keyboard);
    glutMouseFunc(glut_mouse);
    glutMotionFunc(glut_motion);
    glutPassiveMotionFunc(glut_motion);
}

void glut_keyboard(unsigned char key, int x, int y){
	switch(key){
	case 'q':
	case 'Q':
	case '\033':
		exit(0);
	}

	glutPostRedisplay();
}

void glut_mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_UP){
			g_isLeftButtonOn = false;
		}else if(state == GLUT_DOWN){
			g_isLeftButtonOn = true;
		}
	}

	if(button == GLUT_RIGHT_BUTTON){
		if(state == GLUT_UP){
			g_isRightButtonOn = false;
		}else if(state == GLUT_DOWN){
			g_isRightButtonOn = true;
		}
	}
}

void glut_motion(int x, int y){
	static int px = -1, py = -1;
	if(g_isLeftButtonOn == true){
		if(px >= 0 && py >= 0){
			g_angle1 += (double)-(x - px)/20;
			g_angle2 += (double)(y - py)/20;
		}
		px = x;
		py = y;
	}else if(g_isRightButtonOn == true){
		if(px >= 0 && py >= 0){
			g_distance += (double)(y - py)/20;
		}
		px = x;
		py = y;
	}else{
		px = -1;
		py = -1;
	}
	glutPostRedisplay();
}

void glut_display(){
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, 1.0, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	if (cos(g_angle2)>0){
        gluLookAt(
            g_distance*cos(g_angle2)*sin(g_angle1), 
            g_distance*sin(g_angle2), 
            g_distance*cos(g_angle2)*cos(g_angle1), 
            0.0, 0.0, 0.0, 0.0, 1.0, 0.0
        );
	} else {
        gluLookAt(
            g_distance*cos(g_angle2)*sin(g_angle1), 
            g_distance*sin(g_angle2), 
            g_distance*cos(g_angle2)*cos(g_angle1), 
            0.0, 0.0, 0.0, 0.0, -1.0, 0.0
        );
    }

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); //この行がないと関数を呼ばれた順で描画される。あるとカメラからの距離で描画される。
    draw_cube();
    glDisable(GL_DEPTH_TEST);

    glutSwapBuffers();
}


void draw_cube(){
	GLdouble point0[] = {0.5, 0.5, 0.5};
	GLdouble point1[] = {-0.5, 0.5, 0.5};
	GLdouble point2[] = {-0.5, -0.5, 0.5};
	GLdouble point3[] = {0.5, -0.5, 0.5};
	GLdouble point4[] = {0.5, 0.5, -0.5};
	GLdouble point5[] = {-0.5, 0.5, -0.5};
	GLdouble point6[] = {-0.5, -0.5, -0.5};
	GLdouble point7[] = {0.5, -0.5, -0.5};


	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3dv(point0);
	glVertex3dv(point1);
	glVertex3dv(point2);
	glVertex3dv(point3);
	glEnd();

	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3dv(point0);
	glVertex3dv(point1);
	glVertex3dv(point5);
	glVertex3dv(point4);
	glEnd();

	glColor3d(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3dv(point0);
	glVertex3dv(point3);
	glVertex3dv(point7);
	glVertex3dv(point4);
	glEnd();

	glColor3d(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3dv(point6);
	glVertex3dv(point7);
	glVertex3dv(point4);
	glVertex3dv(point5);
	glEnd();

	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3dv(point6);
	glVertex3dv(point7);
	glVertex3dv(point3);
	glVertex3dv(point2);
	glEnd();

	glColor3d(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3dv(point6);
	glVertex3dv(point2);
	glVertex3dv(point1);
	glVertex3dv(point5);
	glEnd();


}