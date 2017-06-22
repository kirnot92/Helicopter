#ifndef PLAYER_H
#define PLAYER_H



class Player {
public:
	Player() {
		m_coord[0] = 0;
		m_coord[1] = 10;
		m_coord[2] = 0;
		m_Angle = 90;

	}
	float x(float f=0) {
		m_coord[0] += f;
		return m_coord[0];
	}

	float y(float f=0) {
		m_coord[1] += f;
		return m_coord[1];
	}

	float z(float f=0) {
		m_coord[2] += f;
		return m_coord[2];
	}
	
	float Angle(float f = 0) {

		if (m_Angle >= 360 || m_Angle <= -360) m_Angle = 0;
		m_Angle += f;
		return m_Angle;
	}
	

private:
	float m_coord[3];
	float m_Angle;
	
};


#endif