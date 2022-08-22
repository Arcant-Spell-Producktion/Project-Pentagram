#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
	private:
		GLuint m_ID;
		void checkCompileError(GLuint shaderID, const std::string& type);
	public:
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
		~Shader();
		void Activate() const;
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setVec3(const std::string& name, glm::vec3 value) const;
		void setVec4(const std::string& name, glm::vec4 value) const;
		void setMat4(const std::string& name, glm::mat4 value) const;

		GLuint getID() const;
};