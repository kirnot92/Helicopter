#include <iostream>
#include <gl\glut.h>
#include <gl\GL.h>
#include <math.h>
#include "dib.h"
using namespace std;


class Drawer {
public:
	float random[2500];
	Drawer() {

		m_TextureBlock.ReadBMP("wall.bmp");
		m_TextureSky.ReadBMP("sky.bmp");
		m_TextureSea.ReadBMP("sea.bmp");
		m_TextureMetal.ReadBMP("Metal1.bmp");

		glEnable(GL_TEXTURE_2D);
		for (int i = 0; i < 2500; i++)
			random[i] = (rand() % 8) / (float)10;

		setTexture("dd");
	}
	void drawTriangle() {
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-3, -3, 0);
		glTexCoord2f(1.0, 0.0); glVertex3f(+3, -3, 0);
		glTexCoord2f(1.0, 1.0); glVertex3f(+3, +3, 0);
		glEnd();
	}

	void setTexture(char* select) {

		if (strcmp(select, "sky") == 0) {
			glTexImage2D(GL_TEXTURE_2D, 0, 3, m_TextureSky.GetWidth(), m_TextureSky.GetHeight(), 0,
				GL_BGR_EXT, GL_UNSIGNED_BYTE, m_TextureSky.m_lpImage);

		}
		else if (strcmp(select, "sea") == 0) {
			glTexImage2D(GL_TEXTURE_2D, 0, 3, m_TextureSea.GetWidth(), m_TextureSea.GetHeight(), 0,
				GL_BGR_EXT, GL_UNSIGNED_BYTE, m_TextureSea.m_lpImage);
		}
		else if (strcmp(select, "block") == 0) {
			glTexImage2D(GL_TEXTURE_2D, 0, 3, m_TextureBlock.GetWidth(), m_TextureBlock.GetHeight(), 0,
				GL_BGR_EXT, GL_UNSIGNED_BYTE, m_TextureBlock.m_lpImage);
		}
		else if (strcmp(select, "metal") == 0) {
			glTexImage2D(GL_TEXTURE_2D, 0, 3, m_TextureMetal.GetWidth(), m_TextureMetal.GetHeight(), 0,
				GL_BGR_EXT, GL_UNSIGNED_BYTE, m_TextureMetal.m_lpImage);
		}
		else {
			glDisable(GL_TEXTURE_2D);
			//printf("failed to change texture\n");
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}


	void drawRotor(float size = 0.2, float length = 1.5) {
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		drawHexa(0.1, 0, 0.1, length, size, size);
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		drawHexa(0.1, 0, 0.1, length, size, size);
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		drawHexa(0.1, 0, 0.1, length, size, size);
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		drawHexa(0.1, 0, 0.1, length, size, size);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	}


	void drawHexa(float startX, float startY, float startZ,
		float garo, float sero, float height) {

		float vector[8][3];
		int slice[3];

		vector[0][0] = startX;			vector[0][1] = startY;			vector[0][2] = startZ;
		vector[1][0] = startX + garo;	vector[1][1] = startY;			vector[1][2] = startZ;
		vector[2][0] = startX + garo;	vector[2][1] = startY + height;	vector[2][2] = startZ;
		vector[3][0] = startX;			vector[3][1] = startY + height;	vector[3][2] = startZ;
		vector[4][0] = startX;			vector[4][1] = startY;			vector[4][2] = startZ - sero;
		vector[5][0] = startX + garo;	vector[5][1] = startY;			vector[5][2] = startZ - sero;
		vector[6][0] = startX + garo;	vector[6][1] = startY + height;	vector[6][2] = startZ - sero;
		vector[7][0] = startX;			vector[7][1] = startY + height;	vector[7][2] = startZ - sero;
		// 좌하단 전방을 시작점으로 하여, 가로, 세로, 높이를 입력받아
		// 벡터 연산에 적합한 형태로 변환한다. 그리고 육면체를 그리는 함수를 호출한다.
		hexa(vector);
	}

	void hexa(float v[][3]) {
		/*
		배열에 들어온 순서			구현해야 하는 평면

		7----6					1) 0 1 2 3
		/|   /|					2) 1 5 6 2
		/ |  / |					3) 5 4 7 6
		3--+-2  |					4) 4 0 3 7
		|  4 +--5					5) 3 2 6 7
		| /  | /					6) 1 0 4 5
		0----1

		*/
		const int sequence[6][4]{
			{ 0,1,2,3 },
			{ 1,5,6,2 },
			{ 5,4,7,6 },
			{ 4,0,3,7 },
			{ 3,2,6,7 },
			{ 1,0,4,5 }
		};

		float plane_v[4][3];

		for (int seq = 0; seq < 6; seq++) {
			for (int i = 0; i < 4; i++) {
				int select_vector = sequence[seq][i];
				__VectorMulti(v[select_vector], plane_v[i], 1);
			}
			plane(plane_v);

		}

	}

	void plane(float v[][3], int width_n = 0, int height_n = 0) {

		// 배열에 들어온 순서
		// 3 2
		// 0 1
		// 하나의 평면은 구로 쉐이딩에서 좋지 못한 결과를 나타낸다
		// 따라서 하나의 평면을 여러개의 평면으로 분할하여
		// 퐁 쉐이딩의 효과를 내도록 한다.


		float width = __getLength(v[0], v[1]); // 사각형 밑변의 길이
		float height = __getLength(v[0], v[3]); // 사각형 높이의 길이

		if (width_n == 0) {
			width_n = (int)width / 3.0 + 1;
		}
		if (height_n == 0) {
			height_n = (int)height / 3.0 + 1;
		}
		if (3 > 4) {
			printf("dd");
		}

		int SequenceX, SequenceY;
		float Vector[3] = { 0,0,0 };

		float dVectorWidth[3];
		__VectorMinus(v[1], v[0], dVectorWidth);
		__VectorMulti(dVectorWidth, 1 / (float)width_n);

		float dVectorHeight[3];
		__VectorMinus(v[3], v[0], dVectorHeight);
		__VectorMulti(dVectorHeight, 1 / (float)height_n);


		float dVw[3] = { 0,0,0 };
		float dVh[3] = { 0,0,0 };
		float new_v[3];
		for (SequenceX = 0; SequenceX < width_n; SequenceX++) {
			for (SequenceY = 0; SequenceY < height_n; SequenceY++) {

				glBegin(GL_QUADS);

				__VectorMulti(dVectorWidth, dVw, SequenceX);
				__VectorMulti(dVectorHeight, dVh, SequenceY);

				__VectorPlus(v[0], dVw, new_v);
				__VectorPlus(new_v, dVh, new_v);
				glTexCoord2f(0.0, 0.0);
				glVertex3fv(new_v);


				__VectorMulti(dVectorWidth, dVw, SequenceX + 1);
				__VectorMulti(dVectorHeight, dVh, SequenceY);

				__VectorPlus(v[0], dVw, new_v);
				__VectorPlus(new_v, dVh, new_v);
				glTexCoord2f(1.0, 0.0);
				glVertex3fv(new_v);


				__VectorMulti(dVectorWidth, dVw, SequenceX + 1);
				__VectorMulti(dVectorHeight, dVh, SequenceY + 1);

				__VectorPlus(v[0], dVw, new_v);
				__VectorPlus(new_v, dVh, new_v);
				glTexCoord2f(1.0, 1.0);
				glVertex3fv(new_v);

				__VectorMulti(dVectorWidth, dVw, SequenceX);
				__VectorMulti(dVectorHeight, dVh, SequenceY + 1);

				__VectorPlus(v[0], dVw, new_v);
				__VectorPlus(new_v, dVh, new_v);
				glTexCoord2f(0.0, 1.0);
				glVertex3fv(new_v);

				glEnd();
			}
		}
	}
private:


	MyDib m_TextureSky;
	MyDib m_TextureSea;
	MyDib m_TextureBlock;
	MyDib m_TextureMetal;


	float __getLength(float v1[3], float v2[3]) {
		float sum = 0;
		for (int i = 0; i < 3; i++) {
			sum += pow((v1[i] - v2[i]), 2);
		}
		return sqrt(sum);
	}

	void __VectorPlus(float v1[], float v2[], float newV[]) {
		for (int i = 0; i < 3; i++) {
			newV[i] = v1[i] + v2[i];

		}
	}
	void __VectorMinus(float v1[], float v2[], float newV[]) {
		for (int i = 0; i < 3; i++)
			newV[i] = v1[i] - v2[i];
	}
	void __VectorMulti(float v1[], float k) {
		for (int i = 0; i < 3; i++)
			v1[i] = v1[i] * k;
	}
	void __VectorDiv(float v1[], float k) {
		for (int i = 0; i < 3; i++)
			v1[i] = v1[i] / k;
	}
	void __VectorMulti(float v1[], float v2[], float k) {
		for (int i = 0; i < 3; i++)
			v2[i] = v1[i] * k;
	}
	void __VectorDiv(float v1[], float v2[], float k) {
		for (int i = 0; i < 3; i++)
			v2[i] = v1[i] / k;
	}

};