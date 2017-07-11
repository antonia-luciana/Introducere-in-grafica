﻿

// #include <GL/glut.h>
/**/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

#define _USE_MATH_DEFINES
#include <cmath> 

unsigned char prevKey;

int mouseClick;

double dimensiuni[2];

double random()
{
	return (double)rand() / (double)RAND_MAX;
}

class GrilaCarteziana {
public:

	GrilaCarteziana() {}

	void grila(int d) {
		if (d <= 33) {
			glColor3f(0.0, 0.0, 0.0);

			double screenRatio = 1.0, xw, yw, xh, yh;

			w = d;
			h = d;

			if (dimensiuni[0] * w) {
				screenRatio = (dimensiuni[1] * h) / (dimensiuni[0] * w);
			}

			//screenRatio = h / w;
			/*if ( h % 2 == 1) {
			ratia_h = (2.0 / (h + 1));
			ratia_w = (2.0 / (w + 1));
			}
			else {*/
			ratia_h = floor((1.8 / h) * 1000 + 0.005) / 1000;
			ratia_w = floor((1.8 / w) * 1000 + 0.005) / 1000;
			//}


			printf("Ratio: %f\n", screenRatio);
			glBegin(GL_LINES);
			for (double i = -0.9; i <= 0.91; i += ratia_w) {
				xw = i, yw = 0.9;
				if (screenRatio > 1) {
					//xw /= screenRatio;
					yw /= screenRatio;
				}
				else {
					xw *= screenRatio;
					//yw *= screenRatio;
				}
				glVertex2f(xw, yw);
				glVertex2f(xw, -yw);
			}
			glEnd();
			//printf("Ratio: %f\n", screenRatio);
			glBegin(GL_LINES);
			for (double i = -0.9; i <= 0.91; i += ratia_h) {
				xh = i, yh = 0.9;
				if (screenRatio > 1) {
					xh /= screenRatio;
					//yh /= screenRatio;
				}
				else {
					//xh *= screenRatio;
					yh *= screenRatio;
				}

				glVertex2f(-yh, xh);
				glVertex2f(yh, xh);
			}
			glEnd();
		}
		else {
			printf("\nPrea multe celule!\n");
		}

	}

	~GrilaCarteziana() {}

	void write_pixel(int coord_x, int coord_y) {
		//glTranslated(coord_x * (ratia_w), coord_y * ( ratia_h ), 0.0);
		if (coord_x <= w && coord_y <= w) {
			double translate_w, translate_h;

			translate_w = coord_x * (ratia_w)-w / 2.0 * (ratia_w);
			translate_h = coord_y * (ratia_h)-h / 2.0 * (ratia_h);

			//glColor3f(1.0, 0.1, 0.1);


			float x, y, r, t, screenRatio = 1.0, inc = 0.01;
			if (dimensiuni[0] * w) {
				screenRatio = (dimensiuni[1] * h) / (dimensiuni[0] * w);
			}

			if (ratia_h < ratia_w)
				r = ratia_h / 5;
			else
				r = ratia_w / 5;

			glPolygonMode(GL_FRONT, GL_FILL);
			glBegin(GL_POLYGON);
			for (t = 0.0; t < 2 * M_PI; t += inc) {
				x = r*cos(t);
				y = r*sin(t);
				if (screenRatio > 1) {
					y /= screenRatio;
					glVertex2f(x + translate_w, y + translate_h / screenRatio);
				}
				else {
					x *= screenRatio;
					glVertex2f(x + translate_w * screenRatio, y + translate_h);

				}
			}
			glEnd();
		}

	}

	void segmentDreapta3(int x0, int y0, int x1, int y1, int grosime) {

		glColor3d(random(), random(), random());

		if (grosime % 2 == 1 && grosime > 0 && grosime <= abs(y0 - y1)) {

			//printf("%d %d %d %d\t", x0, y0, x1, y1);
			int x, y, xn, dNE, dE, d;

			int dx = x1 - x0;
			int dy = y1 - y0;
			//printf("%d %d %d\n", dx, dy, dx*dy);

			//int dx = x0 - x1;
			//int dy = y0 - y1;
			float panta;
			if (dx != 0) {
				panta = float(dy) / float(dx);
			}
			else {
				if (dy != 0) {
					panta = float(dx) / float(dy);
				}
			}

			printf("%f\n", panta);



			if (panta < 0) {
				
				dx = x0 - x1;
				dy = y0 - y1;

				d = 2 * dy + dx;
				dE = 2 * dy;
				dNE = 2 * (dy + dx);

				x = x0, y = y0;
				xn = x1;

				write_pixel(x, y);
				for (int i = 0; i < grosime - 1; i += 2) {
					write_pixel(x, y - 1 - i / 2);
					write_pixel(x, y + 1 + i / 2);
				}

				while (x < xn)
				{
					if (d <= 0) {
						d += dE; x++;
					}
					else {
						d += dNE; x++; y--;
					}

					write_pixel(x, y);

					for (int i = 0; i < grosime - 1; i += 2) {
						write_pixel(x, y - 1 - i / 2);
						write_pixel(x, y + 1 + i / 2);
					}

				}
			}
			else
			{
				
				d = 2 * dy - dx;
				dE = 2 * dy;
				dNE = 2 * (dy - dx);

				x = x0, y = y0;
				xn = x1;

				write_pixel(x, y);
				for (int i = 0; i < grosime - 1; i += 2) {
					write_pixel(x, y - 1 - i / 2);
					write_pixel(x, y + 1 + i / 2);
				}

				while (x < xn)
				{
					if (d <= 0) {
						d += dE; x++;
					}
					else {
						d += dNE; x++; y++;
					}

					write_pixel(x, y);

					for (int i = 0; i < grosime - 1; i += 2) {
						write_pixel(x, y - 1 - i / 2);
						write_pixel(x, y + 1 + i / 2);
					}

				}
			}




		}
		else
		{
			printf("Apel %d %d %d %d %d\t : ", x0, y0, x1, y1, grosime);
			printf("Grosimea trebuie sa fie pozitiva, impara si mai mica ca 2*dy!\n");

		}


	}

private:
	int h, w;
	double ratia_h, ratia_w;

};


GrilaCarteziana gc;

void Display1() {

	gc.grila(15);
	//gc.write_pixel(1, 1);

	//gc.write_pixel(11, 11)
	gc.segmentDreapta3(0, 0, 15, 7, 1);
	gc.segmentDreapta3(0, 15, 15, 10, 3);
	int x0 = 0, y0 = 15, x1 = 15, y1 = 10;
	//gc.segmentDreapta3(x0 + 1, y0, x1, y1 + 1, 1);
	//gc.segmentDreapta3(x0, y0 - 1, x1, y1 - 1, 1);

}

void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	glPointSize(1);

	glPolygonMode(GL_FRONT, GL_LINE);
	glLoadIdentity();

}



void Display(void) {
	printf("Call Display\n");

	glClear(GL_COLOR_BUFFER_BIT);
	/*
	gc.grila(10);

	if (mouseClick == 1) {
	gc.write_pixel(2, 5);
	}
	*/


	//glFlush();

	switch (prevKey) {
	case '1':
		Display1();
		break;

	default:
		break;
	}

	glFlush();
}


void Reshape(int w, int h) {
	printf("Call Reshape : latime = %d, inaltime = %d\n", w, h);

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	dimensiuni[0] = w;
	dimensiuni[1] = h;
}

void KeyboardFunc(unsigned char key, int x, int y) {
	//printf("Ati tastat <%c>. Mouse-ul este in pozitia %d, %d.\n",key, x, y);
	prevKey = key;
	if (key == 27)
		exit(0);
	glutPostRedisplay();
}


void MouseFunc(int button, int state, int x, int y) {
	/*printf("Call MouseFunc : ati %s butonul %s in pozitia %d %d\n",
	(state == GLUT_DOWN) ? "apasat" : "eliberat",
	(button == GLUT_LEFT_BUTTON) ?
	"stang" :
	((button == GLUT_RIGHT_BUTTON) ? "drept" : "mijlociu"),
	x, y);*/
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		mouseClick = 1;
		Display();
		glutPostRedisplay();
		printf("%d %d\n", x, y);

	}


}

int main(int argc, char** argv) {

	glutInit(&argc, argv);


	glutInitWindowSize(300, 300);

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
