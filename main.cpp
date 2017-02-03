/*#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

//Includes
#include <Windows.h>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gl/glew.h>
#include <gl/GL.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>

*/



#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "plane.h"
#include "helper.h"
#include "shaders.h"


//Window
int width = 1280;
int height = 720;
GLFWwindow* window;

//OpenGL
GLuint shaders = 0;
GLuint vBuffer = 0;
GLuint vColorBuffer = 0;
GLuint vIndexBuffer = 0;
GLuint u_matrix = 0;
GLuint u_height = 0;

//Math
glm::mat4 proj;
glm::mat4 view;
glm::mat4 model;
glm::mat4 mvp;
glm::mat4 rot;
float h = 0.0f;
int planeX = 20;
int planeY = 20;

std::vector<GLfloat> vertices;
std::vector<GLfloat> colors;
std::vector<GLint> indices;

int Indices(int x, int y)
{
	int indicesPerRow = x * 2 + 2;
	int indicesDegenerated = (y - 1) * 2;
	int ind = indicesPerRow * y + indicesDegenerated;

	return ind;
}

void Initialize()
{
	shaders = LoadShaders("vertex.glsl", "fragment.glsl");

	vertices.resize(planeX * planeY * 3);
	colors.resize(planeX * planeY * 3);
	indices.resize(Indices(planeX, planeY));

	Plane::Create(vertices, colors, indices, planeX, planeY);
	
	glGenBuffers(1, &vBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);


	glGenBuffers(1, &vColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);


	glGenBuffers(1, &vIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glUseProgram(shaders);

	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	

	proj = glm::perspective
	(
		glm::radians(60.0f), 
		(float)width / (float)height, 
		0.1f, 
		100.0f
	);

	view = glm::lookAt
	(
		glm::vec3(0, 8, 15),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	model = glm::mat4(1.0f);

	glm::vec3 translation = glm::vec3(0.5f, 0, 0.5f);
	translation += glm::vec3(-(float)planeX / 2.0f, 0, -(float)planeY / 2.0f);
	model = glm::translate(model, translation);

	mvp = proj * view * model;

	rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, 90.0f, glm::vec3(0, 1, 0));

	u_matrix = glGetUniformLocation(shaders, "MVP");
	u_height = glGetUniformLocation(shaders, "height");
}

void Render (double dT)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUniformMatrix4fv(u_matrix, 1, GL_FALSE, &mvp[0][0]);
	glUniform1f(u_height, h);


	h += dT;


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glVertexAttribPointer
	(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vColorBuffer);
	glVertexAttribPointer
	(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vIndexBuffer);
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, (void*)0);
	glPointSize(4.0f);
	glDrawArrays(GL_POINTS, 0, indices.size());

	//glLineWidth(3.0f);
	//glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}


int main(void)
{
	glfwWindowHint(GLFW_SAMPLES, 2); // 2x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	glfwInit();
	window = glfwCreateWindow(1280, 720, "Simple example", NULL, NULL);
	glViewport(0, 0, width, height);

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	glfwSwapInterval(0);

	Initialize();

	double deltaTime = 0, lastTime = 0, timer = 0;
	int frames = 0, FPS = 0;

	while (!glfwGetKey(window, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		timer += deltaTime;

		frames++;

		if (timer > 0.1)
		{
			FPS = frames;
			timer = 0;
			frames = 0;
		}

		glfwSetWindowTitle(window, std::to_string(FPS).c_str());


		Render(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}