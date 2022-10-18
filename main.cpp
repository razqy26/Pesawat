#include <windows.h>
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <windows.h>
#define PI 3.14
//variable untuk kamera
float angle=0.0, deltaAngle = 0.0, ratio;
float x=-10.0f,y=25.0f,z=160.0f; // posisi awal kamera
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
//variable pesawat dan gedung
float posY = 0, posX = 0, posZ = 0, wingDownY=0, wingDownX=0, bodyDownX=0,bodyDownY=0, angleWing=0;
static int rotAngleX =0, rotAngleY =0, rotAngleZ =0;
int planeBankLeft = 1;
float angleZ = 0, angleX = 0;
GLUquadricObj *IDquadric;

void init(void)
{
	glEnable (GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	IDquadric=gluNewQuadric(); // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(IDquadric, GLU_SMOOTH); // Create Smooth Normals ( NEW )
	gluQuadricTexture(IDquadric, GL_TRUE); // Create Texture Coords ( NEW )
}
void Reshape(int w1, int h1)
{
	// Fungsi reshape
	if(h1 == 0) h1 = 1;
	w = w1;
	h = h1;
	ratio = 1.0f * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

void update(int value) {
	    if (planeBankLeft) {
	        angleX += 0.5;
	    } else {
	        angleX -= 0.5;
	    }
	    if (angleX > 4) {
	        planeBankLeft = 0;
	    } else if (angleX < -4) {
	        planeBankLeft = 1;
	    }

    glutPostRedisplay();
    glutTimerFunc(50,update,0);//delay
}

void keyboard(unsigned char key, int x, int y)
{
	 switch (key)
	{
		case 'w': rotAngleX += 2; break;
		case 's': rotAngleX -= 2; break;
		case 'a': rotAngleY += 2; break;
		case 'd': rotAngleY -= 2; break;
		case 'q': rotAngleZ += 2; break;
		case 'e': rotAngleZ -= 2; break;
		case 'l': posZ -= 1; break;
		case 'j': posZ += 1; break;
		case 'i': posX -= 1; break;
		case 'k': posX += 1; break;
		case 'z' : exit(0);
		default:
		break;
	}glutPostRedisplay();
}

void badanP()
//Badan pesawat
{
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
	glTranslatef(-7.0f,12.0f,0.0f);
	glRotated(90, 0, 1, 0);
	gluCylinder(IDquadric, 2.5f, 2.5f, 17.5f, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10.0f,12.0f,0.0f);
	glRotated(53, 0, 1, 0);
	glRotated(55, 0, 1, 1);
	gluCylinder(IDquadric, 2.55f, 1.0f, 8.0f, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-11.8f,10.8f,0.0f);
	glRotated(53, 0, 1, 0);
	glRotated(55, 0, 1, 1);
	gluCylinder(IDquadric, 1.0f, 2.6f, 5.5f, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-11.5f,10.9f,0.0f);
	gluSphere(IDquadric, 1.0f, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(17.5f,13.7f,0.0f);
	gluSphere(IDquadric, 1.0f, 32, 32);
	glPopMatrix();

}
void triangularPrism()
{
    glBegin(GL_QUADS);
        glVertex3f(0.5, 0, 0.5);
        glVertex3f(0.5, 0, -0.5);
        glVertex3f(-0.5, 0, -0.5);
        glVertex3f(-0.5, 0, 0.5);
        glVertex3f(0.5,0,-0.5);
        glVertex3f(0.5,1,-0.5);
        glVertex3f(-0.5,1,-0.5);
        glVertex3f(-0.5,0,-0.5);
        glVertex3f(0.5,1,-0.5);
        glVertex3f(-0.5,1,-0.5);
        glVertex3f(-0.5,0,0.5);
        glVertex3f(0.5,0,0.5);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(0.5,0,0.5);
        glVertex3f(0.5,1,-0.5);
        glVertex3f(0.5,0,-0.5);
        glVertex3f(-0.5,0,0.5);
        glVertex3f(-0.5,1,-0.5);
        glVertex3f(-0.5,0,-0.5);
    glEnd();
}

void wingL(){
	//wingLeft
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(1.0,11.0,0.0);
	glRotated(-90,0,1,0);
	glRotated(-90,0,0,1);
	glScalef(0.5,25.5,5.0);
	triangularPrism();
	glPopMatrix();
}

void wingR(){
	//wingRight
	glPushMatrix();
	glTranslatef(1.0,11.0,0.0);
	glRotated(-90,0,1,0);
	glRotated(90,0,0,1);
	glScalef(0.5,25.5,5.0);
	triangularPrism();
	glPopMatrix();
}

void tailP(){
	//Tail
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(15.0,13.0,0.0);
	glRotated(-90,0,1,0);
	glScalef(0.5,8.0,5.0);
	triangularPrism();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(15.0,13.0,0.0);
	glRotated(-90,0,1,0);
	glRotated(-90,0,0,1);
	glScalef(0.5,8.0,5.0);
	triangularPrism();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(15.0,13.0,0.0);
	glRotated(-90,0,1,0);
	glRotated(90,0,0,1);
	glScalef(0.5,8.0,5.0);
	triangularPrism();
	glPopMatrix();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glRotated(rotAngleX+10, 1, 0, 0);
		glRotated(rotAngleY, 0, 1, 0);
		glRotated(rotAngleZ, 0, 0, 1);
		glRotated(-90,0,1,0);
		glTranslatef(50,15,0);
		glTranslated(posX, posY, posZ);
        glRotated(angleX, 1, 0, 0);
        badanP();
        tailP();
		wingL();
		wingR();
	glPopMatrix();
	glutSwapBuffers();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Pesawat");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutReshapeFunc(Reshape);
    glutTimerFunc(50, update, 0);
	init();
	glutMainLoop();
	return(0);
}

// Pesawat + Idle Animation + Movement + Kamera
// Razqy Merge
// CodenameRiq
//E1E1121007 sayap
// Sam (013)
