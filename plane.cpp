#include "plane.h"

void Plane::Create
(
	std::vector<GLfloat> &v, 
	std::vector<GLfloat> &c, 
	std::vector<GLint> &i,
	int sizeX, int sizeY
)
{
	int m = v.capacity();

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			int index = x * sizeY + y;

			v[3 * index + 0] = (float)x;
			v[3 * index + 1] = 0;
			v[3 * index + 2] = (float)y;


			float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			c[3 * index + 0] = 0;
			c[3 * index + 1] = r1;
			c[3 * index + 2] = r2;

			//c[3 * index + 0] = 0;
			//c[3 * index + 1] = r1;
			//c[3 * index + 2] = r2;
		}
	}

	int idx = 0;
	for (int r = 0; r < sizeX - 1; r++)
	{
		i[idx++] = r * sizeY;
		for (int c = 0; c < sizeY; c++)
		{
			i[idx++] = r * sizeY + c;
			i[idx++] = (r + 1) * sizeY + c;
		}
		i[idx++] = (r + 1) * sizeY + (sizeY - 1);
	}
}