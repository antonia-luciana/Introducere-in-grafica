

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

// dimensiunea ferestrei in pixeli
#define dim 300
using namespace std;

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$


void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x2, y2);
	}
	glEnd();
}


// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
	double pi = 4 * atan(1.0);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}

void Display3() {
	double xmax, ymax, ratia;
	xmax = 100;
	ratia = 0.5;
	ymax = 1.01;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		if (x == 0) {
			x1 = 0;
			y1 = 1 /ymax;
		}
		else {
			x1 = x / xmax;
			y1 = (fabs(x - round(x)) / x) / ymax;
		}
		if (x1 <= 0.9) {
			glVertex2f(x1, y1);
		}
			
		
	}

	glEnd();
}



void Display4() {
	double xmax, ymax, ratia, a, b, pi;
	xmax = 1.15;
	ratia = 0.05;
	ymax = 1.02;
	a = 0.3;
	b = 0.2;
	pi = 4 * atan(1.0);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -pi; t < pi; t += ratia)
	{
		double x, y;
		x = 2 * (a*cos(t) + b)*cos(t) / xmax;
		y = 2 * (a*cos(t) + b)*sin(t) / ymax;
		glVertex2f(x, y);
	}

	glEnd();
}

void Display6() {
	double xmax, ymax, ratia, a, b;
	xmax = 1.1;
	ratia = 0.05;
	ymax = 1.05;
	a = 0.1;
	b = 0.2;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -90; t < 90; t += ratia)
	{
		double x, y;
		x = (a*t - b*sin(t)) / xmax;
		y = (a - b*cos(t)) / ymax;
		if (x < 0.9 && x > -0.9) {
			glVertex2f(x, y);
		}
		
	}

	glEnd();
}

void Display5() {
	double pi, a, ratia, xmax, ymax, cx, cy;
	ratia = 0.005;
	a = 0.2;
	xmax = 1.0;
	ymax = 1.0;
	pi = 4 * atan(1.0);
	cx = -0.9;
	cy = 0.99;
	glColor3f(0.2, 0.15, 0.88); // albastru
	int ok = 0;
	glBegin(GL_LINE_LOOP);
	glVertex2f(cx, cy);
	for (double t = (-pi / 2); t < -pi / 6; t += ratia)
	{
		double x, y;

		if (fabs(t) != (-pi) / 6 && fabs(t) != pi / 6) {
			x = (a / (4 * cos(t)*cos(t) - 3)) / xmax;
			y = (a*tan(t)) / (4 * cos(t)*cos(t) - 3) / ymax;

			if (y <= cy  && x >= cx) {
				if (ok == 0) {
					ok = 1;
					ymax = y;
				}
				glVertex2f(x, y);
			}

		}

	}

	glEnd();
	int nr = 0;
	ratia = 0.005;
	glColor3f(1, 0.1, 0.1);

	for (double t = (-pi / 2); t < -pi / 2.4; t += 2 * ratia)
	{
		double x1, y1, x2, y2;

		glBegin(GL_TRIANGLES);
		glVertex2f(cx, cy);

		x1 = (a / (4 * cos(t)*cos(t) - 3)) / xmax;
		y1 = (a*tan(t)) / (4 * cos(t)*cos(t) - 3) / ymax;

		if (y1 <= cy  && x1 >= cx) {
			glVertex2f(x1, y1);
		}


		t += ratia;

		x2 = (a / (4 * cos(t)*cos(t) - 3)) / xmax;
		y2 = (a*tan(t)) / (4 * cos(t)*cos(t) - 3) / ymax;

		if (y2 <= cy  && x2 >= cx) {
			glVertex2f(x2, y2);
		}

		glEnd();
	}

	glColor3f(1, 0.1, 0.1);


	for (double t = (-pi / 4.4); t < -pi / 6; t += 2 * ratia)
	{
		double x1, y1, x2, y2;

		glBegin(GL_TRIANGLES);
		glVertex2f(cx, cy);

		x1 = (a / (4 * cos(t)*cos(t) - 3)) / xmax;
		y1 = (a*tan(t)) / (4 * cos(t)*cos(t) - 3) / ymax;

		if (y1 <= cy  && x1 >= cx) {
			glVertex2f(x1, y1);
		}


		t += ratia;

		x2 = (a / (4 * cos(t)*cos(t) - 3)) / xmax;
		y2 = (a*tan(t)) / (4 * cos(t)*cos(t) - 3) / ymax;

		if (y2 <= cy  && x2 >= cx) {
			glVertex2f(x2, y2);
		}

		glEnd();
	}
}

void Display7() {
	double xmax, ymax, ratia, r, R, pi;
	xmax = 1.1;
	ratia = 0.05;
	ymax = 1.01;
	R = 0.1;
	r = 0.3;
	pi = 4 * atan(1.0);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t < 2 * pi; t += ratia)
	{
		double x, y;
		x = ((R + r)*cos(r / R * t) - r*cos(t + r / R*t)) / xmax;
		y = ((R + r)*sin(r / R * t) - r*sin(t + r / R*t)) / ymax;
		glVertex2f(x, y);
	}

	glEnd();
}
void Display8() {
	double xmax, ymax, ratia, r, R, pi;
	xmax = 1.1;
	ratia = 0.05;
	ymax = 1.01;
	R = 0.1;
	r = 0.3;
	pi = 4 * atan(1.0);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t < 2 * pi; t += ratia)
	{
		double x, y;
		x = ((R - r)*cos(r / R * t) - r*cos(t - r / R*t)) / xmax;
		y = ((R - r)*sin(r / R * t) - r*sin(t - r / R*t)) / ymax;
		glVertex2f(x, y);
	}

	glEnd();
}

void Display9() {
	double xmax, ymax, ratia, r, pi, a;
	xmax = 1.01;
	ymax = 1.01;
	ratia = 0.001;
	pi = 4 * atan(1.0);
	a = 0.4;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 4; t < pi / 4; t += ratia)
	{
		double x, y;
		r = (-a) * sqrt(2 * cos(2 * t));
		x = r*cos(t);
		y = r*sin(t);
		glVertex2f(x, y);
	}

	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 4; t < pi / 4; t += ratia)
	{
		double x2, y2;
		r = a * sqrt(2 * cos(2 * t));
		x2 = r*cos(t);
		y2 = r*sin(t);
		glVertex2f(x2, y2);
	}

	glEnd();


}


void Display10() {
	double  ratia, r, pi, a, xmax, ymax, t;
	ratia = 0.005;
	pi = 4 * atan(1.0);
	a = 0.02;
	xmax = 1.05;
	ymax = 1.05;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	for (double t = 0.0; t < 2.9; t += ratia) {
		double x, y;

		r = a*exp(t + 1);
		x = r*cos(t) / xmax;
		y = r*sin(t) / ymax;

		glVertex2f(x, y);		
		
	}

	glEnd();


}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
	case '9':
		Display9();
		break;
	case '0':
		Display10();
		break;
	default:
		break;
	}

	glFlush();
}
void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	glPolygonMode(GL_FRONT, GL_LINE);

}
void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
