#include "scene.h"
#include <Windows.h>
#include <iostream>
#include "display.h"
#include "Mesh.h"
#include "Shader.h"
#include "inputManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include<vector>
#include "Move.h"





scene::scene()
{

}

void scene::drawAxis() {
	glBegin(GL_LINE_STRIP);
	glVertex3f(-9.0f, 0.0f, 0.0f-1.0f);
	glVertex3f(9.0f, 0.0f, 0.0f - 1.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, 0.0f, -9.0f- 0.0f);
	glVertex3f(0.0f, 0.0f, 9.0f - 0.0f);
	glEnd();
}


scene::~scene()
{
}
void scene::insertBigCube(Cube* bigCube) {
	this->bigCube = bigCube;
}
void scene::insertn(int n) {
	this->n = n;
}
void scene::insertCubeArray(std::vector<Cube*>* cubearray) {
	this->cubearray = cubearray;
}


std::vector<glm::mat4> scene::draw(int numshader,Display* display,glm::mat4 M ,glm::mat4 P) {
	std::vector<glm::mat4> box = std::vector<glm::mat4>();
	display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
	
	Shader* shader = this->shaders[numshader];
	
	//shader->texture(data1, width1, height1);
	this->m = glm::rotate(-90.0f, glm::vec3(1, 0, 0))*glm::rotate(rotate_x, glm::vec3(0, 0, 1))*glm::rotate(rotate_y, glm::vec3(1, 0, 0));
	if (numshader == 0)
	{
		glm::mat4 mvp = P*glm::rotate(-90.0f, glm::vec3(1, 0, 0));
		shader->Bind();
		shader->Update(mvp, M, -1);
		drawAxis();
	}
	Move* mov = bigCube->getMove();
	glm::mat4 scale = bigCube->getscale();
	glm::mat4 movebefore = mov->getTranslatebefor();
	glm::mat4 moveafter = mov->getTranslateafter();
	glm::mat4 rotate = mov->getRotate();
	glm::mat4 bigphi = mov->getphi();
	glm::mat4 bigtheta = mov->gettheta();
	glm::mat4 bigpsi = mov->getpsi();
	glm::mat4 MVP = P*m*moveafter*bigphi*bigtheta*bigpsi* scale;
	this->cubepos = moveafter*bigphi*bigtheta*bigpsi* scale;
//	glm::translate(glm::mat4(), glm::vec3(0, -1, 0))*mov->getTranslateafter()*glm::translate(glm::mat4(), glm::vec3(0, 0, 1))*mov->getRotate()*mov->getpsi()*mov->gettheta()*mov->getphi()*glm::translate(glm::mat4(), glm::vec3(0, 0, -1))*mov->getTranslatebefor();
shader->Bind();
	shader->Update(MVP,M,bigCube->Get_id());

	bigCube->Draw();
	
	glm::mat4 t1rt0 = glm::translate(glm::mat4(), glm::vec3(0, 0, -3));
	for (unsigned int i = 0; i < cubearray->size(); i++) {

		//MVP = MVP*glm::translate(glm::mat4(), glm::vec3(0, 2, 0));

		mov = cubearray->at(i)->getMove();
		glm::mat4 cuberotate = cubearray->at(i)->getrotate();
		glm::mat4 cubescale = cubearray->at(i)->getscale();
		glm::mat4 cubetranslateafter = mov->getTranslateafter();
		glm::mat4 cubetranslatebefore = mov->getTranslatebefor();
		glm::mat4 cubetheta = mov->gettheta();
		glm::mat4 cubepsi = mov->getpsi();
		glm::mat4 cubephi = mov->getphi();
		t1rt0 = t1rt0*glm::translate(glm::mat4(), glm::vec3(0, 0, -2))*cubetranslateafter*cuberotate*cubepsi*cubetheta*glm::translate(glm::mat4(),glm::vec3(0,0,2));
		//t1rt0 = t1rt0*mov->getTranslateafter()*glm::translate(glm::mat4(), glm::vec3(0, 0, 2))*mov->getRotate()*mov->getpsi()*mov->gettheta()*mov->getphi()*glm::translate(glm::mat4(), glm::vec3(0,0,-2))*mov->getTranslatebefor();
		//glm::mat4 m = glm::rotate(-90.0f, glm::vec3(1, 0, 0));
		MVP = P*m*t1rt0*cubescale;
		box.push_back(t1rt0*cubescale);
		shader->Bind();
		shader->Update(MVP, M, cubearray->at(i)->Get_id());
	
		cubearray->at(i)->Draw();
		if (numshader == 0)
		{
			//MVP = MVP*glm::translate(glm::mat4(), glm::vec3(0,-2,0));
			drawAxis();
		}
	}
	return box;
}

void scene::update_rotate_x(float x) {
	this->rotate_x =(float) fmod((this->rotate_x + x), 360);
}
void scene::update_rotate_y(float y) {
	this->rotate_y = (float) fmod((this->rotate_y + y), 360);
	}