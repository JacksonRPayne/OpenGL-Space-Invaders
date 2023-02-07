#include "Shader.h"

Shader::Shader() : compiled(false), program(0) {
	// Create vertex and fragment shaders in opengl
	vert = glCreateShader(GL_VERTEX_SHADER);
	frag = glCreateShader(GL_FRAGMENT_SHADER);

}

Shader::Shader(const char* vertPath, const char* fragPath) : compiled(false), program(0) {
	// Create vertex and fragment shaders in opengl
	vert = glCreateShader(GL_VERTEX_SHADER);
	frag = glCreateShader(GL_FRAGMENT_SHADER);

	LoadFiles(vertPath, fragPath);
}

Shader::~Shader() {

}

void Shader::LoadFiles(const char* vertPath, const char* fragPath) {
	// Opens vertex shader source code
	std::ifstream fileStream;
	fileStream.open(vertPath, std::ios::in);
	// Makes sure file is successfully opened
	if (!fileStream.is_open()) {
		std::cout << "File: " << vertPath << " could not be opened." << std::endl;
		fileStream.close();
		return;
	}
	// To store the code from the file
	std::string srcVert = "";
	// Allocates space for reading a line
	char line[512];
	// Appends every line to the source code string
	while (fileStream.getline(line, 512)) {
		srcVert.append(line);
		srcVert.append("\n");
	}

	// Opens the fragment shader source code
	fileStream.close();
	fileStream.open(fragPath, std::ios::in);
	// Makes sure file is successfully opened
	if (!fileStream.is_open()) {
		std::cout << "File: " << fragPath << " could not be opened." << std::endl;
		fileStream.close();
		return;
	}
	std::string srcFrag = "";
	// Appends every line to the source code string
	while (fileStream.getline(line, 512)) {
		srcFrag.append(line);
		srcFrag.append("\n");
	}

	fileStream.close();

	// Compiles the two shaders to create the program
	CompileShader(srcVert.c_str(), srcFrag.c_str());
}

void Shader::Use() const{
	// If we havent even created the program to use, it shouldn't be used
	if (!compiled) {
		std::cout << "Warning: Shader is being used before being compiled" << std::endl;
		return;
	}

	// Uses the shader
	glUseProgram(program);
}

void Shader::CompileShader(const char* srcVert, const char* srcFrag) {
	// Gives opengl vert shader source code and compiles it
	glShaderSource(vert, 1, &srcVert, nullptr);
	glCompileShader(vert);
	// Checks for errors
	int success;
	glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
	// Logs errors
	if (!success) {
		char log[512];
		glGetShaderInfoLog(vert, 512, nullptr, log);
		std::cout << "Vertex shader compilation failure: \n" << log << std::endl;
	}

	// Compiles fragment shader
	glShaderSource(frag, 1, &srcFrag, nullptr);
	glCompileShader(frag);
	// Checks for errors
	glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
	// Logs errors
	if (!success) {
		char log[512];
		glGetShaderInfoLog(frag, 512, nullptr, log);
		std::cout << "Fragment shader compilation failure: \n" << log << std::endl;
	}

	// Creates the shader program and adds our vert and frag to it
	program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	// Links the vert and frag together
	glLinkProgram(program);
	// Check for linking errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	// Logs errors
	if (!success) {
		char log[512];
		glGetProgramInfoLog(program, 512, nullptr, log);
		std::cout << "Shader linking failure: \n" << log << std::endl;
	}

	// Tells us the shader is ready to use
	compiled = true;
	// Sets the projection matrix (same for all shaders)
	glUseProgram(program);

	// Once the program is created, we don't need to store these anymore
	glDeleteShader(vert);
	glDeleteShader(frag);
	
}

int Shader::FindUniform(const char* uniform) const{
	// If we havent even created the program we can't set uniforms
	if (!compiled) {
		std::cout << "Warning: Shader uniforms being set before the program is compiled" << std::endl;
		return -1;
	}
	// Locates uniform
	int location = glGetUniformLocation(program, uniform);
	// If uniform not found
	if (location == -1) {
		std::cout << "ERROR: Could not find uniform: " << uniform << std::endl;
		return -1;
	}

	return location;
}

void Shader::SetVec3(const char* uniform, const glm::vec3& value) const{
	// Locates and sets uniform
	int location = FindUniform(uniform);
	if(location >=0) glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetMat4(const char* uniform, const glm::mat4 &value) const{
	// Locates and sets uniform
	int location = FindUniform(uniform);
	if (location >= 0) glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}