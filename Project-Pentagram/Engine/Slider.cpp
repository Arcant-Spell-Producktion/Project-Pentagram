#include "Slider.h"

Slider::Slider(const std::string& objName)
	: UIObject(objName)
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(500.0f, 50.0f, 1.0f);
	this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->m_Value = 0.5f;
}

void Slider::InitButton(Button* button)
{
	this->button = button;
	SetChildRenderFront(this->button);

	this->button->scale = glm::vec3(50.0f, 75.0f, 1.0f);
	this->button->color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

	this->button->onPress = [this](Button* button) { this->m_IsPress = true; };
	this->button->unPress = [this](Button* button) { this->m_IsPress = false; };
	this->button->unHover = [this](Button* button) { if (!m_IsPress) { button->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); } };
}

void Slider::OnUpdate(const float& dt)
{
	if (m_IsPress)
	{
		this->button->position.x += Input::deltaMouseX;
		if (this->button->position.x > this->position.x + this->scale.x / 2.0f)
		{
			this->button->position.x = this->position.x + this->scale.x / 2.0f;
		}
		else if (this->button->position.x < this->position.x - this->scale.x / 2.0f)
		{
			this->button->position.x = this->position.x - this->scale.x / 2.0f;
		}
	}

	this->m_Value = (this->button->position.x - (this->position.x - this->scale.x / 2.0f)) / this->scale.x;
}

void Slider::Draw(Camera& camera, glm::mat4 parentModel)
{
	if (!m_IsActive)
	{
		return;
	}

	// Get UI(GameObject) Shader || Button Shader(Handle UI Slicing)
	Shader& shader = (m_IsSlicing ? EngineDataCollector::GetInstance()->GetShaderCollector()->ButtonShader : EngineDataCollector::GetInstance()->GetShaderCollector()->GameObjectShader);

	// Update MVP Matrix
	glm::mat4 model = parentModel;
	model *= glm::translate(glm::mat4(1.0f), this->position);
	model *= glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	// Draw Back Child
	for (unsigned int idx = 0; idx < m_BackChildList.size(); idx++)
	{
		m_BackChildList[idx]->Draw(camera, model);
	}

	// !!Not Set scale to child -> Messy to encounter with
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), this->scale);

	Window* window = ArcantEngine::GetInstance()->GetWindow();
	int screen_width = window->GetWidth();
	int screen_height = window->GetHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);

	shader.Activate();
	shader.setMat4("u_Model", model * scaleMat);
	shader.setMat4("u_View", glm::mat4(1.0f));
	shader.setMat4("u_Projection", proj);
	shader.setVec4("u_Color", color);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowRatio(), 1.0f)));
	m_Texture->Activate(GL_TEXTURE0);
	shader.setInt("u_Texture", 0);

	// Set Button Slicing
	if (m_IsSlicing)
	{
		float minVal = std::min(scale.x, scale.y);
		glm::vec2 u_dimension = glm::vec2(scale.x, scale.y);
		glm::vec2 u_textureBorder = glm::vec2(0.5f, 0.5f);
		float u_border = (minVal >= 2 * m_Border ? m_Border : minVal / 2.0f);
		shader.setVec2("u_Dimensions", u_dimension);
		shader.setVec2("u_TextureBorder", u_textureBorder);
		shader.setFloat("u_Border", u_border);
		// ------ Debug --------
		//std::cout << "u_Dimensions : " << dimension.x << ", " << dimension.y << "\n";
		//std::cout << "u_Border : " << border.x << "," << border.y << "\n";
	}

	if (m_IsAnimation)
	{
		// SpriteSheet Offset
		shader.setFloat("u_OffsetX", m_CurAnimCol * (1.0f / m_MaxAnimCol));
		shader.setFloat("u_OffsetY", (m_CurAnimRow - 1) * (1.0f / m_AnimRow));
	}
	else
	{
		// Default Offset (0.0f, 0.0f)
		shader.setFloat("u_OffsetX", 0.0f);
		shader.setFloat("u_OffsetY", 0.0f);
	}

	this->m_Mesh.Render();

	m_Texture->UnBind();

	// Draw Front Child
	for (unsigned int idx = 0; idx < m_FrontChildList.size(); idx++)
	{
		m_FrontChildList[idx]->Draw(camera, model);
	}
}

void Slider::SetValue(const float& value)
{
	this->button->position.x = ((this->position.x + this->scale.x) * value) - this->scale.x / 2.0f;
}
float Slider::GetValue() { return this->m_Value; }