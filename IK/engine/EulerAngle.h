#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
class EulerAngle
{
private :
	glm::mat4 phi;
	glm::mat4 theta;
	glm::mat4 psi;


public:
	EulerAngle();
	EulerAngle(glm::mat4 phi, glm::mat4 theta,glm::mat4 psi);
	~EulerAngle();
	glm::mat4 getphi();
	glm::mat4 gettheta();
	glm::mat4 getpsi();
	void setpsi(glm::mat4 psi);
	void setphi(glm::mat4 phi);
	void setthata(glm::mat4 theta);


};

