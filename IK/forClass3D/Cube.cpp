#include "Cube.h"
#include <stdio.h>
#include <glm/gtx/matrix_interpolation.hpp>
#include <iostream>

Cube::Cube(int index,Mesh* mesh, Move* move, glm::mat4 scale)
{
	this->move = move;
	this->index = index;
	this->mesh = mesh;
	this->scale = scale;
}
Cube::Cube(){}

Cube::~Cube()
{
	delete this->mesh;
	delete this->move;
}

int Cube::Get_id() {
	return this->index;
}
void Cube::Draw()
{
	mesh->Draw();
}

void Cube::translateafter(glm::mat4 translate) {
	this->move->setTranslateafter(translate);
}

void Cube::setrotate(glm::mat4 rotat) {
	 this->move->setRotate(rotat);

}

glm::mat4 Cube::getrotate() {
	return this->move->getRotate();

}