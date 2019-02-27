#pragma once
#include "Cube.h"
#include "mesh.h"
#include "Move.h"
class Cube
{
private:
	Mesh* mesh;
	Move* move;
	int index;
	glm::mat4 scale;

public:
	Cube(int index, Mesh* mesh,Move* move, glm::mat4 scale);
	~Cube();
	Cube();
	void Draw();
	void setrotate(glm::mat4 rotat);
	Move* getMove() {
		return this->move;
	}
	int Get_id();
	void translateafter(glm::mat4 translate);
	glm::mat4 getscale() {
		return this->scale;
	}



	glm::mat4 getrotate();

};

