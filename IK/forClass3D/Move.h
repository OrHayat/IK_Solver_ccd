#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
class Move
{
private:
	glm::mat4 rotate= glm::mat4();
	glm::mat4 translatebefor= glm::mat4();
	glm::mat4 translateafter=glm::mat4();
	glm::mat4 phi;
	glm::mat4 theta;
	glm::mat4 psi;

public:
	Move();
	Move(glm::mat4 rotate, glm::mat4 translatebefor, glm::mat4 translateafter);
	~Move();
	void setRotateAfter(glm::mat4 r);
	glm::mat4 getTranslatebefor() const {
		return this->translatebefor;
	}
	glm::mat4 getTranslateafter() const {
		return this->translateafter;
	}

	glm::mat4 getRotate() const {
		return this->rotate;
	}
	void setTranslateBefor(glm::mat4 transbefor);
	void setTranslateafter(glm::mat4 transafter);
	void setRotate(glm::mat4 rotate);
	glm::mat4 getphi();
	glm::mat4 gettheta();
	glm::mat4 getpsi();
	void setpsi(glm::mat4 psi);
	void setphi(glm::mat4 phi);
	void setthata(glm::mat4 theta);
};
