#include "Move.h"

Move::Move() {
}

Move::Move(glm::mat4 rotate, glm::mat4 translatebefor,
	glm::mat4 translateafter)
{
	this->rotate = rotate;
	this->translatebefor = translatebefor;
	this->translateafter = translateafter;
	this->phi = glm::mat4();
	this->psi = glm::mat4();
	this->theta = glm::mat4();

}
Move::~Move()
{
}


void Move::setTranslateBefor(glm::mat4 transbefor) {
	this->translatebefor = transbefor;
}
void Move::setTranslateafter(glm::mat4 transafter) {
	this->translateafter = transafter;
}
void Move::setRotate(glm::mat4 rotate) {
	this->rotate = rotate;
}

void Move::setRotateAfter(glm::mat4 r) {
	this->rotate = r;
}

glm::mat4 Move::getphi() {
	return this->phi;
}
glm::mat4 Move::gettheta() {
	return this->theta;
}
glm::mat4 Move::getpsi() {
	return this->psi;
}

void Move::setpsi(glm::mat4 psi) {
	this->psi = psi;
}
void Move::setphi(glm::mat4 phi) {
	this->phi = phi;
}
void Move::setthata(glm::mat4 theta) {
	this->theta = theta;
}
