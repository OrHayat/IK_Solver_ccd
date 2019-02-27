#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "inputManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include<vector>
#include "Move.h"
#include "Cube.h"
#include "scene.h"
#include <math.h>





using namespace glm;
float depth;
float xpos1;
float ypos1;
bool spaceKey=false;
std::vector<Cube*>* cubearray = new std::vector<Cube*>();
int startindex = 0;
const double PI = 3.141592653589793238463;
static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
Cube* bigCube;
glm::mat4 P;
mat4 M = glm::rotate(0.0f, vec3(1, 1, 1));
Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
int pickingid = -1;
scene s=scene(); 
float oldx=0;
float oldy=0;
std::vector<glm::mat4> box;


void cursor_position_callback(GLFWwindow* window, double xpos,
	double ypos) {
	float deltax = oldx - xpos;
	xpos1=xpos;
	ypos1 = ypos;

	float deltay = oldy - ypos;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{

		if (pickingid != -1)
		{
			int width, height;
			glfwGetWindowSize(window, &width, &height);


			float xrel = oldx - xpos, yrel = oldy - ypos;
			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			float f = 100.0f;
			float n = 0.1f;
			float z = f +depth*( n-f);
				
			float transX = ((float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT)*(xrel) / (float)(viewport[2])*0.1*2.0f*tan(60.0f*PI / 360.0f)*(100.0f / z);
			float transY = ((float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT)*(yrel) / (float)(viewport[3])*0.1*2.0f*tan(60.0f*PI / 360.0f)*(100.0f / z);
				if (pickingid == s.getN() + 1)
			{
				float x = transX;
				float y = transY;
				glm::mat4 world = glm::transpose(s.m);//s-1

				glm::vec4 newx = world*glm::vec4(1, 0, 0, 0)*transX;
				glm::vec4 newy = world*glm::vec4(0, 1, 0, 0)*transY;
				glm::mat4 old= bigCube->getMove()->getTranslateafter();
				glm::mat4 tran = glm::translate(glm::vec3(newx));
				glm::mat4 trans2 = glm::translate(glm::vec3(newy));
				bigCube->translateafter(old*tran*trans2);
			}
			else
			{

					int width, height;
					glfwGetWindowSize(window, &width, &height);
					float x = transX;
					float y = transY;
					glm::mat4 world = glm::transpose(s.m);//s-1
					glm::vec4 newx = world*glm::vec4(1, 0, 0, 0)*transX;
					glm::vec4 newy = world*glm::vec4(0, 1, 0, 0)*transY;
					glm::mat4 old = cubearray->at(0)->getMove()->getTranslateafter();
					glm::mat4 tran = glm::translate(glm::vec3(newx));
					glm::mat4 trans2 = glm::translate(glm::vec3(newy));
					cubearray->at(0)->translateafter(old*tran*trans2);
			}
		}
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (pickingid != -1) {
			if (pickingid == s.getN() + 1)
			{
				if (deltax > 0) {
					glm::mat4 newpsi = glm::rotate(bigCube->getMove()->getpsi(), 3.0f, vec3(0, 1,0));
					bigCube->getMove()->setpsi(newpsi);
					glm::mat4 newphi = glm::rotate(bigCube->getMove()->getphi(), 3.0f, vec3(0, -1,0));
					bigCube->getMove()->setphi(newphi);

			}
				else if(deltax<0) {
					glm::mat4 newpsi = glm::rotate(bigCube->getMove()->getpsi(), -3.0f, vec3(0, 1,0));
					bigCube->getMove()->setpsi(newpsi);
					glm::mat4 newphi = glm::rotate(bigCube->getMove()->getphi(), -3.0f, vec3(0, -1,0));
					bigCube->getMove()->setphi(newphi);


				}

			else if (deltay > 0) {
				glm::mat4 newTehta = glm::rotate(bigCube->getMove()->gettheta(), 3.0f, vec3(1, 0, 0));
				bigCube->getMove()->setthata(newTehta);
			}
			else if (deltay < 0) {
				glm::mat4 newTehta = glm::rotate(bigCube->getMove()->gettheta(), 3.0f, vec3(-1, 0, 0));
				bigCube->getMove()->setthata(newTehta);
			}
			}
			else {
				if (deltax > 0) {
					glm::mat4 newpsi = glm::rotate(cubearray->at(pickingid)->getMove()->getpsi(), 3.0f, vec3(0, 1, 0));
					cubearray->at(pickingid)->getMove()->setpsi(newpsi);
					glm::mat4 newphi = glm::rotate(cubearray->at(pickingid)->getMove()->getphi(), 3.0f, vec3(0, -1, 0));
					cubearray->at(pickingid)->getMove()->setphi(newphi);


				}
				else if (deltax<0) {
					glm::mat4 newpsi = glm::rotate(cubearray->at(pickingid)->getMove()->getpsi(), -3.0f, vec3(0, 1, 0));
					cubearray->at(pickingid)->getMove()->setpsi(newpsi);
					glm::mat4 newphi = glm::rotate(cubearray->at(pickingid)->getMove()->getphi(), -3.0f, vec3(0, -1, 0));
					cubearray->at(pickingid)->getMove()->setphi(newphi);


				}

				else if (deltay > 0) {
					glm::mat4 newTehta = glm::rotate(cubearray->at(pickingid)->getMove()->gettheta(), 3.0f, vec3(1, 0, 0));
					cubearray->at(pickingid)->getMove()->setthata(newTehta);


				}
				else if (deltay < 0) {
					glm::mat4 newTehta = glm::rotate(cubearray->at(pickingid)->getMove()->gettheta(), 3.0f, vec3(-1, 0, 0));
					cubearray->at(pickingid)->getMove()->setthata(newTehta);

				}
			}
		}
		else
		{
			int sx = 1;
			int sy = 1;
			if (deltay < 0)
				sy = -1;
			if (deltax < 0)
				sx = -1;
			s.update_rotate_x(sx * 3);
			s.update_rotate_y(sy * 3);
		}
	}
	oldx = xpos;
	oldy = ypos;
	}

float clamp (float x,float min,float max){
	if (x > max)
		x = max;
	if (x < min)
		x = min;
	return x;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_SPACE:
	{		if (action == GLFW_PRESS)
	{
		glm::mat4 b = box[0];
		glm::mat4 cube = s.cubepos;
		cube = glm::translate(cube, vec3(-2, 0, -1));
		glm::vec4 p1 = b*glm::vec4(1, 1, 1, 1);
		glm::vec4 p2 = cube*glm::vec4(1, 1, 1, 1);
		float distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));



		if (distance > -1+4 * s.getN())
		{
			std::cout << "cant reach" << std::endl;
			break;
		}
		spaceKey = !spaceKey;
		break;
	}
	}
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	case GLFW_KEY_UP:
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			if (pickingid != -1) {
				if (pickingid == s.getN() + 1)
				{
					glm::mat4 newTehta = glm::rotate(bigCube->getMove()->gettheta(), 3.0f, vec3(1, 0, 0));
					bigCube->getMove()->setthata(newTehta);
				}
				else
				{
					glm::mat4 newTehta = glm::rotate(cubearray->at(pickingid)->getMove()->gettheta(), 3.0f, vec3(1, 0, 0));
					cubearray->at(pickingid)->getMove()->setthata(newTehta);
				}
			}
			else
			{
				s.update_rotate_y(2.9);

			}
		break;
	}
	case GLFW_KEY_DOWN:
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			if (pickingid != -1) {
				if (pickingid == s.getN() + 1)
				{
					glm::mat4 newTehta = glm::rotate(bigCube->getMove()->gettheta(), 3.0f, vec3(-1, 0, 0));
					bigCube->getMove()->setthata(newTehta);
				}
				else
				{
					glm::mat4 newTehta = glm::rotate(cubearray->at(pickingid)->getMove()->gettheta(), 3.0f, vec3(-1, 0, 0));
					cubearray->at(pickingid)->getMove()->setthata(newTehta);
				}

			}
			else
			{
				s.update_rotate_y(-2.9);
			}
		break;
	}
	case GLFW_KEY_RIGHT:

	{
		if (pickingid != -1) {
			if (pickingid == s.getN() + 1)
			{
				glm::mat4 newpsi = glm::rotate(bigCube->getMove()->getpsi(), -3.0f, vec3(0, 1, 0));
				bigCube->getMove()->setpsi(newpsi);
				glm::mat4 newphi = glm::rotate(bigCube->getMove()->getphi(), 3.0f, vec3(0, 1, 0));
				bigCube->getMove()->setphi(newphi);
			}
			else
			{
				glm::mat4 newpsi = glm::rotate(cubearray->at(pickingid)->getMove()->getpsi(), -3.0f, vec3(0, 1, 0));
				cubearray->at(pickingid)->getMove()->setpsi(newpsi);
				glm::mat4 newphi = glm::rotate(cubearray->at(pickingid)->getMove()->getphi(), 3.0f, vec3(0, 1, 0));
				cubearray->at(pickingid)->getMove()->setphi(newphi);
			}
		}
		else {
			s.update_rotate_x(-2.9);
		}


		break;
	}
	default:
		break;

	case GLFW_KEY_LEFT:

	{
		if (pickingid != -1) {
			if (pickingid == s.getN() + 1)
			{
				glm::mat4 newpsi = glm::rotate(bigCube->getMove()->getpsi(), 3.0f, vec3(0, 1, 0));
				bigCube->getMove()->setpsi(newpsi);
				glm::mat4 newphi = glm::rotate(bigCube->getMove()->getphi(), -3.0f, vec3(0, 1, 0));
				bigCube->getMove()->setphi(newphi);
			}
			else
			{
				glm::mat4 newpsi = glm::rotate(cubearray->at(pickingid)->getMove()->getpsi(), 3.0f, vec3(0, 1, 0));
				cubearray->at(pickingid)->getMove()->setpsi(newpsi);
				glm::mat4 newphi = glm::rotate(cubearray->at(pickingid)->getMove()->getphi(), -3.0f, vec3(0, 1, 0));
				cubearray->at(pickingid)->getMove()->setphi(newphi);
			}
		}
		else {
			s.update_rotate_x(2.9);
		}


		break;
	}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (pickingid != -1) {

		glm::mat4 world = glm::transpose(s.m);//s-1
	
		if (pickingid == s.getN() + 1) {
			float scaler = 0;

			if (yoffset > 0) {
				scaler = yoffset * 0.25; //make it bigger than current size

				glm::mat4 t = bigCube->getMove()->getTranslateafter();
				glm::vec4 newz = world*glm::vec4(0, 0, 1, 0)*scaler;
				glm::mat4 tran = glm::translate(glm::vec3(newz));
				bigCube->translateafter(t*tran);
			}
			else {
				scaler = yoffset * 0.25; //make it smaller than current size
				glm::mat4 t = bigCube->getMove()->getTranslateafter();
				glm::vec4 newz = world*glm::vec4(0, 0, 1, 0)*scaler;
				glm::mat4 tran = glm::translate(glm::vec3(newz));
				bigCube->translateafter(t*tran);
			}
		}
		else {
				float scaler = 0;

				if (yoffset > 0) {
					scaler = yoffset * 0.25; //make it bigger than current size

					glm::mat4 t = cubearray->at(0)->getMove()->getTranslateafter();
					glm::vec4 newz = world*glm::vec4(0, 0, 1, 0)*scaler;
					glm::mat4 tran = glm::translate(glm::vec3(newz));
					cubearray->at(0)->translateafter(t*tran);
				}
				else {
					scaler = yoffset * 0.25; //make it smaller than current size
					glm::mat4 t = cubearray->at(0)->getMove()->getTranslateafter();
					glm::vec4 newz = world*glm::vec4(0, 0, 1, 0)*scaler;
					glm::mat4 tran = glm::translate(glm::vec3(newz));
					cubearray->at(0)->translateafter(t*tran);				}
			
		}

	}
}
	




void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if ((button == GLFW_MOUSE_BUTTON_RIGHT|| button == GLFW_MOUSE_BUTTON_LEFT) && action == GLFW_PRESS)
	{
	//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			box=s.draw(1, &display, M, P);
			glFlush();
			glFinish();
	
		double x1;
		double y1;
		glfwGetCursorPos(window, &x1, &y1);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		unsigned char data[4];
		glReadPixels((int)x1, viewport[3] - y1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glReadPixels(xpos1, viewport[3] - ypos1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		int pickedID =
			data[0] +
			data[1] * 256 +
			data[2] * 256 * 256;
		if (pickedID == 0x00ffffff) { // Full white, must be the background !
			pickingid = -1;
		}
		else {
			pickingid = pickedID;
		}
	}

}

void IkSolver() {
	glm::mat4 b = box[s.getN() - 1];
	glm::mat4 cube = s.cubepos;
	cube = glm::translate(cube, vec3(-2,0, -1));
	glm::vec4 p1 = b*glm::vec4(1, 1, 1, 1);
	glm::vec4 p2 = cube*glm::vec4(1, 1, 1, 1);
	float distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
	

	 if (distance > 0.1)
	{
			//std::cout << "distance" << distance << std::endl;
			glm::vec4 lastbox = b*vec4(1, 1, 1, 1);
			//glm::vec3 lastbox1 = vec3(lastbox.x, lastbox.y, lastbox.z);
			glm::vec4 thisbox = glm::translate(box[startindex], vec3(0, 0, -2))* vec4(1, 1, 1, 1);
			//glm::vec3 thisbox1 = vec3(thisbox.x, thisbox.y, thisbox.z);
			glm::vec4 ej = lastbox - thisbox;//e-j
			//glm::vec3 ej1 = lastbox1 - thisbox1;
			glm::vec4 tj = p2 - thisbox;
			//glm::vec3 tj1 = vec3(tj.x, tj.y, tj.z);

			glm::vec4 normalizedej = glm::normalize(ej);
			//glm::normalize(glm::vec3(ej.x, ej.y, ej.z));
			glm::vec4 normalizedtj = glm::normalize(tj);
			//glm::normalize(glm::vec3(tj.x, tj.y, tj.z));

			float dot =glm::dot(vec3(normalizedej), vec3(normalizedtj));
			glm::vec3 c = glm::normalize(glm::cross(vec3(normalizedej), vec3(normalizedtj)));
			float cosangle = glm::clamp(dot, -1.0f, 1.0f);
			float angle = glm::acos(cosangle) * 180 / (30 * PI);
			glm::mat4 rot = cubearray->at(startindex)->getrotate();

			cubearray->at(startindex)->setrotate(glm::rotate(rot, angle, c));

		}
	else {
		std::cout << "reached distance= " <<distance<< std::endl;
	}
		startindex -= 1;
		if (startindex < 0) {
			startindex = s.getN() - 1;
		
	}

}



int main(int argc, char** argv)
{
	
	Vertex vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0))
	};



	unsigned int indices[] = {0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	                          };
	int n = 4;
	s.insertn(n);
	startindex = s.getN() - 1;
	Mesh* mesh=new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	//std::cout << (data1 == NULL) << std::endl;
	glm::mat4 bigscale = glm::scale(glm::mat4(), vec3(1,1,1));
	glm::mat4 bigid = glm::mat4();
	glm::mat4 bigafter= glm::translate(mat4(), vec3(5.0f, 0.0f, 0.0f));
	glm::mat4 bigtranslatebefore = glm::translate(mat4(), vec3(0.0f, 0.0f, 0.0f));
	Move* mov=new Move(bigid, bigtranslatebefore, bigafter);
	bigCube =new Cube((n + 1), mesh, mov,bigscale);
	s.insertBigCube(bigCube);
	Shader* shader=new Shader("./res/shaders/basicShader");
	Shader* picking=new Shader("./res/shaders/þþbasicShader2");
	std::vector<Shader*> shadervector= std::vector<Shader*>();
	shadervector.push_back(shader);
	shadervector.push_back(picking);
	s.set_shader(shadervector);
	vec3 pos = vec3(0, 0, -30);
	vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
	vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	

	P = glm::perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	P = P * glm::lookAt(pos, pos + forward, up);
	mat4 MVP = P*M;
	glfwSetKeyCallback(display.m_window,key_callback);
	glfwSetMouseButtonCallback(display.m_window, mouse_button_callback);
	glfwSetCursorPosCallback(display.m_window, cursor_position_callback);
	glfwSetScrollCallback(display.m_window, scroll_callback);
	for (int i = 0; i < n; i++) {
		Mesh* m = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
		glm::mat4 scale = glm::scale(glm::mat4(), vec3(1, 1, 2));
		glm::mat4 id = glm::mat4();
		glm::mat4 translatebefore = glm::mat4();
		if (i != 0)
		{		translatebefore = glm::translate(mat4(), vec3(0.0f, 0.0f, 4.0f));
	}
		glm::mat4 translateafter = glm::translate(mat4(), vec3(0, 0.0f,4.0f));
		Move* trarot = new Move(id,translatebefore, translateafter);
		Cube* cube = new Cube(i,m,trarot,scale);
		cubearray->push_back(cube);
	}

	s.insertCubeArray(cubearray);

	while(!glfwWindowShouldClose(display.m_window))
	{
		Sleep(4);
		if (spaceKey) {
			IkSolver();
		}
		box=s.draw(0, &display, M,P);
		

		display.SwapBuffers();
		glfwPollEvents();
	}
	delete shader;
	delete picking;
	return 0;
}





