
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

	
	GLfloat global_ambient[] = { 0.05, 0.05, 0.05, 1.0 };     //전역 주변반사

	GLfloat light0_ambient[] = { 1, 1, 1, 1 };    //0번 광원 특성
	GLfloat light0_diffuse[] = { 1, 1,1, 1 };
	GLfloat light0_specular[] = { 1, 1, 1, 1 };


	GLfloat material_ambient[] = { 1, 1, 1, 1.0 };  //물체 특성
	GLfloat material_diffuse[] = { 1, 1, 1, 1.0 };
	GLfloat material_specular[] = { 1, 1, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };

	
	glEnable(GL_LIGHT0);        //0번 광원 활성화
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);   //0번 광원 초기화
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);


	GLfloat Helicoptor_Spotlight[3][4] = {
		{ 0.8,0.8,1,1 },
		{ 0.8,0.8,1,1 },
		{ 0.8,0.8,1,1 }
	};
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Helicoptor_Spotlight[0]);   //헬리콥타 광원초기화
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Helicoptor_Spotlight[1]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Helicoptor_Spotlight[2]);


	GLfloat Ship_Spotlight[3][4] = {
		{ 1,0.3,0.3,1 },
		{ 1,0.3,0.3,1 },
		{ 1,0.3,0.3,1 }
	};
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Ship_Spotlight[0]);   //배 광원 초기화
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Ship_Spotlight[1]);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Ship_Spotlight[2]);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);   //물체 특성할당
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); //전역주변반사
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    //근접시점
}

void MyDisplay() {



	GLfloat LightPosition0[] = { 0.0, 0.0, 2.0, 0.0 };     //0번 광원위치
	GLfloat LightPosition1[] = { 0, 0, 0.2, 1.0 };     //1번 광원위치
	GLfloat LightPositionDefault[] = { 0,0,0,1 };
	GLfloat LightDirection1[] = { -0.5, -1.0, -1.0 };       //1번 광원 방향
	GLfloat SpotAngle1[] = { 20.0 };                   //1번 광원 각도
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);                             //모델뷰 행렬
	glLoadIdentity();                                       //항등행렬 로드


	gluLookAt(
		P.x() + 10*cos(2*3.1415*(P.Angle()+180)/360), 
		P.y()+3, 
		P.z() - 10*sin(2*3.1415*(P.Angle()+180)/360),
		P.x(), P.y(), P.z(), 0.0, 1.0, 0.0
	);    //시점변환
	
	// 기준점 구
	glutWireSphere(0.01, 100, 100);
		
	glEnable(GL_LIGHTING); 
	
	// 스카이박스 정의 시작 ----------------------------------
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
	// 스카이박스 정의 끝 ----------------------------------

	// 바다 정의 시작 ----------------
	float dv[4][3] = {
		{ -10000 + t / 1000,-30,10000 }, // x좌표를 증가시켜서 흐르는 바다를 표현함
		{ 10000 + t / 1000,-30,10000 },
		{ 10000 + t / 1000,-30,-10000 },
		{ -10000 + t / 1000,-30,-10000 }
	};

	Dr.setTexture("sea");
	Dr.plane(dv, 100, 100);
	// 바다 정의 끝 --------------------

	GLfloat Spotlight_Position[4] = { 0,0,0,1 };
	GLfloat Spotlight_Direction[3] = { -1, -0.5,0 };
	GLfloat Spotlight_Angle[] = { 15.0 };
	// 스폿라이트 기본위치 (모델뷰)

	// 배 정의 시작 -------------------------------------
	Dr.setTexture("metal");
	glPushMatrix();
		glRotatef(-45+t/100, 0, 1, 0);
		glTranslatef(0, -20, -200);
		Dr.drawHexa(-20, -5, 10, 40, 20, 10);
		Dr.drawHexa(0, 5,5, 10, 10, 5);

		// 배에 붙은 빨간 조명 만들기
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

	// 배 정의 끝 -------------------------------------


	

	// 헬리콥터 정의 시작 ---------------------

	Dr.setTexture("metal");
	glPushMatrix();
		glTranslatef(P.x(), P.y(), P.z());

		glRotatef(P.Angle(), 0, 1, 0);
		//-------------------
		//움직이고자 할때 기울어지는 정도를 반영
		float bisudumSide = (-1)* 60 * w / 2;
		glRotatef(bisudumSide, 1, 0, 0);
		float bisudumFront = (-1) * 45 * speed / 2;
		glRotatef(bisudumFront, 0, 0, 1);
		//---------------------

		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		// 헬리콥터의 바디 정의

			// 헬리콥터 스팟라이트 정의
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
			

			// 헬리콥터의 바디 (육면체)
			Dr.drawHexa(-1, -0.5 ,0.5, 2, 1, 1);
			Dr.drawHexa(1, 0, 0.25, 2, 0.5, 0.5);
			Dr.drawHexa(-0.1, 0.5, +0.1, 0.2, 0.2, 0.5);

			Dr.setTexture("block");
			// 헬리콥터의 날개 정의 시작
			glPushMatrix();
				// 서브로터
				glTranslatef(2.75, 0.25, 0.3);
				glRotatef(90, 1, 0, 0);
				glRotatef(d*2, 0, 1, 0);
				Dr.drawRotor(0.1, 0.2);
			glPopMatrix();

			glPushMatrix();
				// 메인로터
				glTranslatef(0, 1, 0);
				glRotatef(d, 0, 1, 0);
				Dr.drawRotor(0.3,3.5);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	// 헬리콥터 정의 끝 --------------------------------
	
	
	glFlush();
}



void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);                //투상행렬
	glLoadIdentity();                           //항등행렬 로드
	
	gluPerspective(60, 1, 0.1, 10000); //원근 투상
	glMatrixMode(GL_MODELVIEW);                  // 모델뷰 행렬을 선택
	glLoadIdentity();                            // 모델뷰 행렬을 리셋한다
	
}


void InitGL() {
	glShadeModel(GL_SMOOTH);    //구로 셰이딩
	glEnable(GL_DEPTH_TEST);    //깊이 버퍼 활성화
	glClearColor(0.6, 1.0, 0.99, 0.6);
	
	glEnable(GL_DEPTH_TEST);                       // 깊이테스트를 킴
	glDepthFunc(GL_LEQUAL);                        // 수행할 깊이테스트의 종류
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// 원근 투상시 더 멋있어진다고 함. (검색으로 찾았는데 잘 모름.)
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //GL_DECAL,GL_REPLACE, GL_MODULATE
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);      //조명 활성화

}


GLfloat SunLight[3][3][4] = {
	{	{ 1, 0.4, 0.4, 1 },
		{ 1, 0.4, 0.4, 1 },
		{ 1, 0.4, 0.4, 1 }
	}, // 저녁노을을 표현하고 싶었음

	{	{ 0.1, 0.1, 0.1, 1 },
		{ 0.1, 0.1, 0.1, 1 },
		{ 0.1, 0.1, 0.1, 1 }
	}, // 어두운 밤
	{	{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 }
	}, // 밝은 오후
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
		glLightfv(GL_LIGHT0, GL_AMBIENT, SunLight[SunNum][0]);   //0번 광원 특성할당
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


	// 좌우 기울어짐 가속도 계산
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
	//앞뒤 기울어짐 가속도 계산
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


	// 어딘가에 계속 쓰이는 실시간 계측용 변수들
	t += 10;
	if (t > 100000000) t = 0;
	d += 30;
	if (d > 360) d = 0;
	glutPostRedisplay();
}

void explane() {
	printf("--------조작법--------\n");
	printf("w: 전방 가속\n");
	printf("s: 후방 가속\n");
	printf("a: 좌측으로 회전\n");
	printf("d: 우측으로 회전\n");
	printf("t: 시간대 조절(낮 -> 노을 -> 밤 -> 낮...)");
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

