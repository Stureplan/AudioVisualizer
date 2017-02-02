#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include <GL/glew.h>

static class Plane
{
public:
	static void Create
	(
		std::vector<GLfloat> &v,
		std::vector<GLfloat> &c,
		std::vector<GLint> &i,
		int x, int y
	);

private:

};

#endif