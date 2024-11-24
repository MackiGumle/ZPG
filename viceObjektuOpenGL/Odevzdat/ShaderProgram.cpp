#include "ShaderProgram.h"
#include "Lights.h"
#include "Material.h"

ShaderProgram::ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader)
	: vertexShader(vertexShader), fragmentShader(fragmentShader)
{
	shaderProgramID = glCreateProgram();
	std::cout << "[i] Shader program created: " << shaderProgramID << '\n';

	linkShaders();
}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	loadShader(vertexFile, fragmentFile);
	vertexPath = vertexFile;
	fragmentPath = fragmentFile;
}

ShaderProgram::~ShaderProgram()
{
	//glDeleteProgram(shaderProgramID);
	deleteShader();
	std::cout << "[i] Shader program deleted: " << shaderProgramID << '\n';
}

void ShaderProgram::update() // Observer of Camera
{
	applyUniform("viewMatrix", camera->getViewMatrix());
	applyUniform("projectionMatrix", camera->getProjectionMatrix());
	

	if (hasUniform("viewPos"))
	{
		applyUniform("viewPos", camera->getPosition());
	}

	if (hasUniform("numLights"))
	{
		applyUniform("numLights", camera->getPosition());
	}
}

void ShaderProgram::setCamera(Camera* camera)
{
	this->camera = camera;
}

bool ShaderProgram::hasUniform(const std::string& name) const
{
	use();
	GLint location = glGetUniformLocation(shaderProgramID, name.c_str());
	return location != -1;
	glUseProgram(0);
}

template<typename T>
void ShaderProgram::applyUniform(const std::string& name, const T& value) const
{
	use();

	if constexpr (std::is_same_v<T, Material>)
	{
		applyUniform(name + ".ambient", value.ambient);
		applyUniform(name + ".diffuse", value.diffuse);
		applyUniform(name + ".specular", value.specular);
		applyUniform(name + ".shininess", value.shininess);
		applyUniform(name + ".color", value.color);
		return;
	}
	
	// if type inherits from BaseLight
	if constexpr (std::is_base_of_v<BaseLight, T>)
	{
		applyUniform(name + ".position", value.position);
		applyUniform(name + ".color", value.color);
		applyUniform(name + ".intensity", value.intensity);
		applyUniform(name + ".constant", value.constant);
		applyUniform(name + ".linear", value.linear);
		applyUniform(name + ".quadratic", value.quadratic);
		
		if constexpr (std::is_same_v<T, SpotLight>)
		{
			applyUniform(name + ".direction", value.direction);
			applyUniform(name + ".angle", value.angle);
			applyUniform(name + ".type", 2);
		}
		else if constexpr (std::is_same_v<T, DirectionalLight>)
		{
			applyUniform(name + ".direction", value.direction);
			applyUniform(name + ".type", 1);
		}
		else if constexpr (std::is_same_v<T, PointLight>)
		{
			applyUniform(name + ".type", 0);
		}

		return;
	}


	GLint location = glGetUniformLocation(shaderProgramID, name.c_str());
	if (location == -1)
	{
		std::cout << "[x] ERROR::SHADER::UNIFORM::NOT_FOUND\t'" << name <<
			"'\t" << getVertexPath() << '\t' << getFragmentPath() << '\n';
		throw std::runtime_error("Uniform not found: " + getVertexPath());
	}

	if constexpr (std::is_same_v<T, glm::mat4>)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	else if constexpr (std::is_same_v<T, glm::mat3>)
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	else if constexpr (std::is_same_v<T, glm::vec3>)
	{
		glUniform3fv(location, 1, glm::value_ptr(value));
	}
	else if constexpr (std::is_same_v<T, glm::vec4>)
	{
		glUniform4fv(location, 1, glm::value_ptr(value));
	}
	else if constexpr (std::is_same_v<T, float>)
	{
		glUniform1f(location, value);
	}
	else if constexpr (std::is_same_v<T, int>)
	{
		glUniform1i(location, value);
	}
	//else
	//{
	//	static_assert(always_false<T>::value, "Unsupported uniform type");
	//}

	glUseProgram(0);
}

template void ShaderProgram::applyUniform<glm::mat4>(const std::string& name, const glm::mat4& value) const;
template void ShaderProgram::applyUniform<glm::mat3>(const std::string& name, const glm::mat3& value) const;
template void ShaderProgram::applyUniform<glm::vec3>(const std::string& name, const glm::vec3& value) const;
template void ShaderProgram::applyUniform<glm::vec4>(const std::string& name, const glm::vec4& value) const;
template void ShaderProgram::applyUniform<int>(const std::string& name, const int& value) const;
template void ShaderProgram::applyUniform<float>(const std::string& name, const float& value) const;

template void ShaderProgram::applyUniform<BaseLight>(const std::string& name, const BaseLight& value) const;
template void ShaderProgram::applyUniform<SpotLight>(const std::string& name, const SpotLight& value) const;
template void ShaderProgram::applyUniform<DirectionalLight>(const std::string& name, const DirectionalLight& value) const;
template void ShaderProgram::applyUniform<PointLight>(const std::string& name, const PointLight& value) const;
template void ShaderProgram::applyUniform<Material>(const std::string& name, const Material& value) const;



//void ShaderProgram::addPointLight(std::shared_ptr<PointLight> pointLight)
//{
//	pointLights.push_back(pointLight);
//}



std::string ShaderProgram::getVertexPath() const
{
	return vertexPath;
}

std::string ShaderProgram::getFragmentPath() const
{
	return fragmentPath;
}

void ShaderProgram::use() const
{
	glUseProgram(shaderProgramID);
}

void ShaderProgram::linkShaders()
{
	vertexShader.lock()->attachToProgram(shaderProgramID);
	fragmentShader.lock()->attachToProgram(shaderProgramID);
	glLinkProgram(shaderProgramID);

	GLint status;
	char infoLog[512];
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		std::cout << "[x] ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
		throw std::runtime_error("Shader linking failed\n\n");
	}

	std::cout << "[i] Shader program linked: " << shaderProgramID << ' ' << vertexShader.lock()->getPath() + " + " + fragmentShader.lock()->getPath() << '\n';
}