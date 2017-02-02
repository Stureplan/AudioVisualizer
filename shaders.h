#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

std::string ReadFile(const char* path)
{
	std::string content;
	std::string line = "";
	std::ifstream stream(path, std::ios::in);

	if (!stream.is_open())
	{
		std::cerr << "Could not read file " << path << std::endl;
		return "";
	}

	while (!stream.eof())
	{
		std::getline(stream, line);
		content.append(line + "\n");
	}

	stream.close();
	return content;
}

GLuint LoadShaders(const char* vs, const char* ps)
{
	GLuint program;

	//Create the shaders
	GLuint vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	//Read the filepaths
	std::string vs_str = ReadFile(vs);
	std::string fs_str = ReadFile(ps);

	//Convert to char*
	const char* vs_src = vs_str.c_str();
	const char* fs_src = fs_str.c_str();

	//Compile shaders
	glShaderSource(vertex_shader, 1, &vs_src, NULL);
	glCompileShader(vertex_shader);

	glShaderSource(fragment_shader, 1, &fs_src, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}

#endif

//functions for compiling and loading shaders