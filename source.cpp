
#include "Drawer.h"
#include "Player.h"



float d = 0;
float t = 0;

float w = 0;
float dw = 0.001;
float speed = 0;
float accel = 0.001;

bool PressedW = 0;
bool PressedS = 0;
bool PressedA = 0;
bool PressedD = 0;
bool PressedSpacebar = 0;

Drawer Dr;
MyDib dib1;
MyDib dib2;
MyDib dib3;

Player P;



void MyLightInit() {

	
	GLfloat global_ambient[] = { 0.05, 0.05, 0.05, 1.0 };     //���� �ֺ��ݻ�

	GLfloat light0_ambient[] = { 1, 1, 1, 1 };    //0�� ���� Ư��
	GLfloat light0_diffuse[] = { 1, 1,1, 1 };
	GLfloat light0_specular[] = { 1, 1, 1, 1 };


	GLfloat material_ambient[] = { 1, 1, 1, 1.0 };  //��ü Ư��
	GLfloat material_diffuse[] = { 1, 1, 1, 1.0 };
	GLfloat material_specular[] = { 1, 1, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };

	
	glEnable(GL_LIGHT0);        //0�� ���� Ȱ��ȭ
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);   //0�� ���� �ʱ�ȭ
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);


	GLfloat Helicoptor_Spotlight[3][4] = {
		{ 0.8,0.8,1,1 },
		{ 0.8,0.8,1,1 },
		{ 0.8,0.8,1,1 }
	};
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Helicoptor_Spotlight[0]);   //�︮��Ÿ �����ʱ�ȭ
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Helicoptor_Spotlight[1]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Helicoptor_Spotlight[2]);


	GLfloat Ship_Spotlight[3][4] = {
		{ 1,0.3,0.3,1 },
		{ 1,0.3,0.3,1 },
		{ 1,0.3,0.3,1 }
	};
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Ship_Spotlight[0]);   //�� ���� �ʱ�ȭ
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Ship_Spotlight[1]);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Ship_Spotlight[2]);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);   //��ü Ư���Ҵ�
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); //�����ֺ��ݻ�
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    //��������
}

void MyDisplay() {



	GLfloat LightPosition0[] = { 0.0, 0.0, 2.0, 0.0 };     //0�� ������ġ
	GLfloat LightPosition1[] = { 0, 0, 0.2, 1.0 };     //1�� ������ġ
	GLfloat LightPositionDefault[] = { 0,0,0,1 };
	GLfloat LightDirection1[] = { -0.5, -1.0, -1.0 };       //1�� ���� ����
	GLfloat SpotAngle1[] = { 20.0 };                   //1�� ���� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);                             //�𵨺� ���
	glLoadIdentity();                                       //�׵���� �ε�


	gluLookAt(
		P.x() + 10*cos(2*3.1415*(P.Angle()+180)/360), 
		P.y()+3, 
		P.z() - 10*sin(2*3.1415*(P.Angle()+180)/360),
		P.x(), P.y(), P.z(), 0.0, 1.0, 0.0
	);    //������ȯ
	
	// ������ ��
	glutWireSphere(0.01, 100, 100);
		
	glEnable(GL_LIGHTING); 
	
	// ��ī�̹ڽ� ���� ���� ----------------------------------
	Dr.setTexture("sky");

	glBegin(GL_QUADS);
		int garo = 800;
		int sero = 300;
		glTexCoord2f(0.0, 0.0); glVertex3f(P.x() - garo, P.y() - sero, P.z() + garo);
		glTexCoord2f(1.0, 0.0); glVertex3f(P.x() - garo, P.y() - sero, P.z() - garo);
		glTexCoord2f(1.0, 1.0); glVertex3f(P.x() - garo, P.y() + sero, P.z() - garo);
		glTexCoord2f(0.0, 1.0); glVertex3f(P.x() - garo, P.y() + sero, P.z() + garo);

		glTexCoord2f(0.0, 0.0); glVertex3f(P.x() + garo, P.y() - sero, P.z() + garo);
		glTexCoord2f(1.0, 0.0); glVertex3f(P.x() - garo, P.y() - sero, P.z() + garo);
		glTexCoord2f(1.0, 1.0); glVertex3f(P.x() - garo, P.y() + sero, P.z() + garo);
		glTexCoord2f(0.0, 1.0); glVertex3f(P.x() + garo, P.y() + sero, P.z() + garo);

		glTexCoord2f(0.0, 0.0); glVertex3f(P.x() - garo, P.y() - sero, P.z() - garo);
		glTexCoord2f(1.0, 0.0); glVertex3f(P.x() + garo, P.y() - sero, P.z() - garo);
		glTexCoord2f(1.0, 1.0); glVertex3f(P.x() + garo, P.y() + sero, P.z() - garo);
		glTexCoord2f(0.0, 1.0); glVertex3f(P.x() - garo, P.y() + sero, P.z() - garo);

		glTexCoord2f(0.0, 0.0); glVertex3f(P.x() + garo, P.y() - sero, P.z() - garo);
		glTexCoord2f(1.0, 0.0); glVertex3f(P.x() + garo, P.y() - sero, P.z() + garo);
		glTexCoord2f(1.0, 1.0); glVertex3f(P.x() + garo, P.y() + sero, P.z() + garo);
		glTexCoord2f(0.0, 1.0); glVertex3f(P.x() + garo, P.y() + sero, P.z() - garo);
	glEnd();
	// ��ī�̹ڽ� ���� �� ----------------------------------

	// �ٴ� ���� ���� ----------------
	float dv[4][3] = {
		{ -10000 + t / 1000,-30,10000 }, // x��ǥ�� �������Ѽ� �帣�� �ٴٸ� ǥ����
		{ 10000 + t / 1000,-30,10000 },
		{ 10000 + t / 1000,-30,-10000 },
		{ -10000 + t / 1000,-30,-10000 }
	};

	Dr.setTexture("sea");
	Dr.plane(dv, 100, 100);
	// �ٴ� ���� �� --------------------

	GLfloat Spotlight_Position[4] = { 0,0,0,1 };
	GLfloat Spotlight_Direction[3] = { -1, -0.5,0 };
	GLfloat Spotlight_Angle[] = { 15.0 };
	// ��������Ʈ �⺻��ġ (�𵨺�)

	// �� ���� ���� -------------------------------------
	Dr.setTexture("metal");
	glPushMatrix();
		glRotatef(-45+t/100, 0, 1, 0);
		glTranslatef(0, -20, -200);
		Dr.drawHexa(-20, -5, 10, 40, 20, 10);
		Dr.drawHexa(0, 5,5, 10, 10, 5);

		// �迡 ���� ���� ���� �����
		glPushMatrix();
			glTranslatef(0, 10, 0);
			glRotatef(t/10, 0, 1, 0);
			glutWireSphere(0.3, 100, 100);
			glLightfv(GL_LIGHT2, GL_POSITION, Spotlight_Position);
			//glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Spotlight_Direction);
			//glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, Spotlight_Angle);
			glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10);
			glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.09);
		glPopMatrix();


		glPopMatrix();
	glPopMatrix();

	// �� ���� �� -------------------------------------


	

	// �︮���� ���� ���� ---------------------

	Dr.setTexture("metal");
	glPushMatrix();
		glTranslatef(P.x(), P.y(), P.z());

		glRotatef(P.Angle(), 0, 1, 0);
		//-------------------
		//�����̰��� �Ҷ� �������� ������ �ݿ�
		float bisudumSide = (-1)* 60 * w / 2;
		glRotatef(bisudumSide, 1, 0, 0);
		float bisudumFront = (-1) * 45 * speed / 2;
		glRotatef(bisudumFront, 0, 0, 1);
		//---------------------

		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		// �︮������ �ٵ� ����

			// �︮���� ���̶���Ʈ ����
			glPushMatrix();
				glTranslatef(-1, -0.5, 0);
				//glRotatef(t/100, 0, 0, 0);
				glutWireSphere(0.3, 100, 100);
				glLightfv(GL_LIGHT1, GL_POSITION, Spotlight_Position);
				glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Spotlight_Direction);
				glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, Spotlight_Angle);
				glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10);
				glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01);
			glPopMatrix();
			

			// �︮������ �ٵ� (����ü)
			Dr.drawHexa(-1, -0.5 ,0.5, 2, 1, 1);
			Dr.drawHexa(1, 0, 0.25, 2, 0.5, 0.5);
			Dr.drawHexa(-0.1, 0.5, +0.1, 0.2, 0.2, 0.5);

			Dr.setTexture("block");
			// �︮������ ���� ���� ����
			glPushMatrix();
				// �������
				glTranslatef(2.75, 0.25, 0.3);
				glRotatef(90, 1, 0, 0);
				glRotatef(d*2, 0, 1, 0);
				Dr.drawRotor(0.1, 0.2);
			glPopMatrix();

			glPushMatrix();
				// ���η���
				glTranslatef(0, 1, 0);
				glRotatef(d, 0, 1, 0);
				Dr.drawRotor(0.3,3.5);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	// �︮���� ���� �� --------------------------------
	
	
	glFlush();
}



void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);                //�������
	glLoadIdentity();                           //�׵���� �ε�
	
	gluPerspective(60, 1, 0.1, 10000); //���� ����
	glMatrixMode(GL_MODELVIEW);                  // �𵨺� ����� ����
	glLoadIdentity();                            // �𵨺� ����� �����Ѵ�
	
}


void InitGL() {
	glShadeModel(GL_SMOOTH);    //���� ���̵�
	glEnable(GL_DEPTH_TEST);    //���� ���� Ȱ��ȭ
	glClearColor(0.6, 1.0, 0.99, 0.6);
	
	glEnable(GL_DEPTH_TEST);                       // �����׽�Ʈ�� Ŵ
	glDepthFunc(GL_LEQUAL);                        // ������ �����׽�Ʈ�� ����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// ���� ����� �� ���־����ٰ� ��. (�˻����� ã�Ҵµ� �� ��.)
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //GL_DECAL,GL_REPLACE, GL_MODULATE
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);      //���� Ȱ��ȭ

}


GLfloat SunLight[3][3][4] = {
	{	{ 1, 0.4, 0.4, 1 },
		{ 1, 0.4, 0.4, 1 },
		{ 1, 0.4, 0.4, 1 }
	}, // ��������� ǥ���ϰ� �;���

	{	{ 0.1, 0.1, 0.1, 1 },
		{ 0.1, 0.1, 0.1, 1 },
		{ 0.1, 0.1, 0.1, 1 }
	}, // ��ο� ��
	{	{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 }
	}, // ���� ����
};
int SunNum = 2;

void MyKeyboardDown(unsigned char key, int x, int y) {
	float move = 10;
	switch (key) {


	case 'q': case 'Q': case '\033':
		exit(0);
		break;
	case 'w':
		PressedW = true;
		break;
	case 's':
		PressedS = true;
		break;
	case 'a':
		PressedA = true;
		break;
	case 'd':
		PressedD = true;
		break;
	case 32: // spacebar
		break;

	case 't':
		SunNum++;
		if (SunNum > 2) SunNum = 0;
		glLightfv(GL_LIGHT0, GL_AMBIENT, SunLight[SunNum][0]);   //0�� ���� Ư���Ҵ�
		glLightfv(GL_LIGHT0, GL_DIFFUSE, SunLight[SunNum][1]);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SunLight[SunNum][2]);

		break;
	}
}


void MyKeyboardUp(unsigned char key, int x, int y) {
	float move = 10;
	switch (key) {
	case 'w':
		PressedW = false;
		break;
	case 's':
		PressedS = false;
		break;
	case 'a':
		PressedA = false;
		break;
	case 'd':
		PressedD = false;
		break;

	}
}
void MyIdle() {


	// �¿� ������ ���ӵ� ���
	int direction = ((PressedA)*(+1) + (PressedD)*(-1));
	if (PressedA || PressedD) {
		w += direction * dw;
		if (w > 2) w = 2;
		P.Angle(w);
	}
	else {
		float buho = w / fabs(w);
		float yang_su = fabs(w);
		if (yang_su > 0.000001) w = buho * (yang_su - 3*dw);
		else w = 0;
		P.Angle(w);
	}
	//�յ� ������ ���ӵ� ���
	int direction2 = ((PressedW)*(+1) + (PressedS)*(-1));
	if (PressedW || PressedS) {
		speed += direction2 * accel;
		if (speed > 2) speed = 2;
		P.x(speed * cos(2 * 3.1415*(-P.Angle() / 360)));
		P.z(speed * sin(2 * 3.1415*(-P.Angle() / 360)));
		
	}
	else {
		float buho = speed / fabs(speed);
		float yang_su = fabs(speed);
		if (yang_su > 0.01) speed = buho * (yang_su - 4 * accel);
		else speed = 0;
		P.x(speed * cos(2 * 3.1415*(-P.Angle() / 360)));
		P.z(speed * sin(2 * 3.1415*(-P.Angle() / 360)));
	}


	// ��򰡿� ��� ���̴� �ǽð� ������ ������
	t += 10;
	if (t > 100000000) t = 0;
	d += 30;
	if (d > 360) d = 0;
	glutPostRedisplay();
}

void explane() {
	printf("--------���۹�--------\n");
	printf("w: ���� ����\n");
	printf("s: �Ĺ� ����\n");
	printf("a: �������� ȸ��\n");
	printf("d: �������� ȸ��\n");
	printf("t: �ð��� ����(�� -> ���� -> �� -> ��...)");
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("openGL Sample Drawing");


	InitGL();

	MyLightInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutIdleFunc(MyIdle);
	glutKeyboardFunc(MyKeyboardDown);
	glutKeyboardUpFunc(MyKeyboardUp);

	explane();

	glutMainLoop();
	
	
	return 0;
}

