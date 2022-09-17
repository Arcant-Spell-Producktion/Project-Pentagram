#include "UIObject.h"

UIObject::UIObject(const std::string& objName)
	: GameObject(objName)
{
	this->m_Tag = GameObjectTag::UIOBJECT;
	
	this->m_IsSlicing = false;
	this->m_SlicingBorder = 40.0f;
}

void UIObject::Draw(Camera& camera, glm::mat4 parentModel)
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
	for (unsigned int idx = 0; idx < m_BackRenderedChildList.size(); idx++)
	{
		m_BackRenderedChildList[idx]->Draw(camera, model);
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
	shader.setVec4("u_Color", this->color);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowRatio(), 1.0f)));
	m_Texture->Activate(GL_TEXTURE0);
	shader.setInt("u_Texture", 0);

	// Set Button Slicing
	if (m_IsSlicing)
	{
		float minVal = std::min(this->scale.x, this->scale.y);
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
		shader.setFloat("u_OffsetX", m_CurrentAnimationColumn * (1.0f / m_CurrentAnimationColumn));
		shader.setFloat("u_OffsetY", (m_CurrentAnimationRow - 1) * (1.0f / m_CurrentAnimationRow));
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
bool UIObject::IsSlicing() const
{ 
	return this->m_IsSlicing; 
}
float UIObject::GetBorderSize() const
{ 
	return this->m_SlicingBorder; 
}

// ----------------- Setter ----------------- 
void UIObject::SetIsSlicing(const bool& active)
{ 
	this->m_IsSlicing = active;
}
void UIObject::SetSlicingBorderSize(const float& slicingBorderSize) 
{ 
	this->m_SlicingBorder = slicingBorderSize; 
}