#include "Slider.h"

Slider::Slider(const std::string& objName)
	: UIObject(objName)
{
	this->m_Tag = GameObjectTag::SLIDER;
	this->m_IsZoomObject = false;
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(500.0f, 50.0f, 1.0f);
	this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	this->m_Value = 0.5f;
	this->onValueChanged = [](Slider* slider) {};

	m_ForeGround = new UIObject("Slider_" + objName + "_ForeGround");
	m_ForeGround->color = AC_GREEN;
	m_ForeGround->scale = { 1.0f, this->scale.y, 1.0f };
	this->SetChildRenderFront(m_ForeGround);

	InitButton();
}

void Slider::InitButton()
{
	this->m_Button = new Button(name + "_Button");
	this->SetChildRenderFront(this->m_Button);

	this->m_Button->scale = glm::vec3(60.0f, 80.0f, 1.0f);
	this->m_Button->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	this->m_Button->onPress = [this](Button* button) { m_IsPress = true; };
	this->m_Button->onHover = [this](Button* button) { button->hoverColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f); };
	this->m_Button->unPress = [this](Button* button) { m_IsPress = false; };
	this->m_Button->unHover = [this](Button* button) { if (!m_IsPress) { button->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); } m_IsPress = false; };
}
void Slider::OnUpdate(const float& dt)
{
	m_ForeGround->scale.x = (m_Button->position.x + this->scale.x / 2.0f);
	m_ForeGround->position.x = (m_Button->position.x + this->scale.x / 2.0f) / 2.0f - this->scale.x / 2.0f;

	if (m_IsPress)
	{
		this->m_Button->position.x += Input::deltaMouseX / ArcantEngine::GetInstance()->GetWindow()->GetViewportDiffRatio().x;
		if (this->m_Button->position.x > this->scale.x / 2.0f)
		{
			this->m_Button->position.x = this->scale.x / 2.0f;
		}
		else if (this->m_Button->position.x < -this->scale.x / 2.0f)
		{
			this->m_Button->position.x = -this->scale.x / 2.0f;
		}

		// Value Change by Mouse Position
		this->onValueChanged(this);
	}

	this->m_Value = (this->m_Button->position.x + this->scale.x / 2.0f) / this->scale.x;
}
void Slider::Draw(Camera& camera, glm::mat4 parentModel)
{
	if (!m_IsActive)
	{
		return;
	}

	// Get UI(GameObject) Shader || Button Shader(Handle UI Slicing)
	Shader& shader = EngineDataCollector::GetInstance()->GetShaderCollector()->UISlicingShader;

	// Update MVP Matrix
	glm::mat4 model = parentModel;
	model *= glm::translate(glm::mat4(1.0f), this->position);
	model *= glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	// Draw Back Child
	for (unsigned int idx = 0; idx < m_BackRenderedChildList.size(); idx++)
	{
		m_BackRenderedChildList[idx]->Draw(camera, model);
	}

	// !!Not Set scale to child -> Messy to encounter with
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), this->scale);

	Window* window = ArcantEngine::GetInstance()->GetWindow();
	
	shader.Activate();
	shader.setMat4("u_Model", model * scaleMat);
	shader.setMat4("u_View", glm::mat4(1.0f));
	shader.setMat4("u_Projection", camera.GetProjectionMatrix(m_IsZoomObject));
	shader.setVec4("u_Color", this->color);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowDiffRatio(), 1.0f)));
	m_Texture->Activate(GL_TEXTURE0);
	shader.setInt("u_Texture", 0);
	shader.setBool("u_IsSlicing", m_IsSlicing);

	// Set Button Slicing
	if (m_IsSlicing)
	{
		float minVal = min(this->scale.x, this->scale.y);
		glm::vec2 u_dimension = glm::vec2(this->scale.x, this->scale.y);
		glm::vec2 u_textureBorder = glm::vec2(0.5f, 0.5f);
		float u_slicingBorder = (minVal >= 2 * m_SlicingBorder ? m_SlicingBorder : minVal / 2.0f);
		shader.setVec2("u_Dimensions", u_dimension);
		shader.setVec2("u_TextureBorder", u_textureBorder);
		shader.setFloat("u_Border", u_slicingBorder);
		// ------ Debug --------
		//std::cout << "u_Dimensions : " << dimension.x << ", " << dimension.y << "\n";
		//std::cout << "u_Border : " << border.x << "," << border.y << "\n";
	}

	if (m_IsSpriteSheet)
	{
		// SpriteSheet Offset
		shader.setFloat("u_OffsetX", (m_CurrentAnimationColumn - 1) * (1.0f / m_MaxAnimationColumn));
		shader.setFloat("u_OffsetY", (m_CurrentAnimationRow - 1) * (1.0f / m_AnimationRow));
	}
	else
	{
		// Default Offset (0.0f, 0.0f)
		shader.setFloat("u_OffsetX", 0.0f);
		shader.setFloat("u_OffsetY", 0.0f);
	}

	m_Mesh.Render();
	m_Texture->UnBind();

	// Draw Front Child
	for (unsigned int idx = 0; idx < m_FrontRenderedChildList.size(); idx++)
	{
		m_FrontRenderedChildList[idx]->Draw(camera, model);
	}
}

// ----------------- Getter -----------------
float Slider::GetValue() 
{ 
	return this->m_Value; 
}
bool Slider::IsButtonPressed() 
{ 
	return this->m_IsPress; 
}
UIObject* Slider::GetForegroundUI()
{
	return this->m_ForeGround;
}
Button* Slider::GetSliderButton() 
{ 
	return this->m_Button; 
}

// ----------------- Setter -----------------
void Slider::SetValue(const float& value)
{
	this->m_Button->position.x = (-this->scale.x / 2.0f) + (value * this->scale.x);
	this->m_Value = value;

	// Value Change from Setter
	this->onValueChanged(this);
}