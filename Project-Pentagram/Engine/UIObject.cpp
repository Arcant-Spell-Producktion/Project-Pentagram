#include "UIObject.h"

UIObject::UIObject(const std::string& objName)
	: GameObject(objName)
{
	this->m_Tag = GameObjectTag::UIOBJECT;
	
	this->m_IsSlicing = false;
	this->m_SlicingBorder = 40.0f;
	this->m_SlicingBorderMultiplier = 1.0f;
	this->m_IsGradiant = false;
	this->m_GradiantValue = 0.0f;
}

void UIObject::Draw(Camera& camera, glm::mat4 parentModel)
{
	if (!m_IsActive)
	{
		return;
	}

	// Get UI(GameObject) Shader || Button Shader(Handle UI Slicing)
	ShaderCollector* shaderCollector = EngineDataCollector::GetInstance()->GetShaderCollector();
	Shader& shader = (m_IsGradiant ? shaderCollector->GradiantShader : shaderCollector->UISlicingShader);

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
	int screen_width = window->GetWindowWidth();
	int screen_height = window->GetWindowHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);

	shader.Activate();
	shader.setMat4("u_Model", model * scaleMat);
	shader.setMat4("u_View", glm::mat4(1.0f));
	shader.setMat4("u_Projection", proj);
	shader.setVec4("u_Color", this->color);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowDiffRatio(), 1.0f)));
	m_Texture->Activate(GL_TEXTURE0);
	shader.setInt("u_Texture", 0);
	shader.setBool("u_IsSlicing", m_IsSlicing);

	// Set Button Slicing
	if (m_IsSlicing)
	{
		const float Offset = 0.5f;
		const float u_SlicingBorder = m_SlicingBorder + Offset;

		shader.setInt("u_SlicingType", (int)m_SlicingType);

		glm::vec2 u_dimension = glm::vec2(this->scale.x, this->scale.y);
		glm::vec2 u_textureBorder = glm::vec2(u_SlicingBorder / m_Texture->GetImageSize());
		shader.setVec2("u_Dimensions", u_dimension);
		shader.setVec2("u_TextureBorder", u_textureBorder);
		shader.setFloat("u_Border", u_SlicingBorder);
		shader.setFloat("u_SlicingMultiplier", m_SlicingBorderMultiplier);

		if (m_SlicingType == SlicingType::REPEAT)
		{
			glm::vec2 detailDimension = glm::vec2(u_dimension - u_SlicingBorder * m_SlicingBorderMultiplier);
			glm::vec2 detailTexture = glm::vec2(m_Texture->GetImageSize() - u_SlicingBorder * m_SlicingBorderMultiplier);
			shader.setVec2("u_SlicingRepeatValue", glm::vec2(detailDimension / detailTexture));
		}
		// ------ Debug --------
		//std::cout << "u_Dimensions : " << u_dimension.x << ", " << u_dimension.y << "\n";
		//std::cout << "DBUG Border : " << (m_SlicingBorder / u_dimension).x << ", " << (m_SlicingBorder / u_dimension).y << "\n";
		//std::cout << "u_Texture : " << u_textureBorder.x << ", " << u_textureBorder.y << "\n";
		//std::cout << "u_Border : " << u_slicingBorder << "\n\n";
	}
	else if (m_IsGradiant)
	{
		m_StartGradiantTexture->Activate(GL_TEXTURE1);
		shader.setInt("u_StartGradiant", 1);
		
		m_EndGradiantTexture->Activate(GL_TEXTURE2);
		shader.setInt("u_EndGradiant", 2);

		shader.setFloat("u_InterpolateValue", m_GradiantValue);
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
bool UIObject::IsSlicing() const
{ 
	return this->m_IsSlicing; 
}
float UIObject::GetBorderSize() const
{ 
	return this->m_SlicingBorder; 
}
float UIObject::GetSlicingBorderMultiplier() const
{
	return this->m_SlicingBorderMultiplier;
}
SlicingType UIObject::GetSlicingType() const
{
	return this->m_SlicingType;
}
bool UIObject::IsGradiant() const
{
	return this->m_IsGradiant;
}
float UIObject::GetGradiantValue() const 
{
	return this->m_GradiantValue;
}
Texture* UIObject::GetStartGradiantTexture() const
{
	return this->m_StartGradiantTexture;
}
Texture* UIObject::GetEndGradiantTexture() const
{
	return this->m_EndGradiantTexture;
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
void UIObject::SetSlicingBorderMultiplier(const float& slicingBorderMultiplier)
{
	this->m_SlicingBorderMultiplier = slicingBorderMultiplier;
}
void UIObject::SetSlicingType(const SlicingType& slicingType)
{
	this->m_SlicingType = slicingType;
}
void UIObject::SetIsGradiant(const bool& active)
{
	this->m_IsGradiant = active;
}
void UIObject::SetGradiantValue(const float& gradiantValue)
{
	float gradiantClampValue = glm::clamp(gradiantValue, 0.0f, 1.0f);
	this->m_GradiantValue = gradiantClampValue;
}
void UIObject::SetStartGradiantTexture(const std::string& filePath) 
{
	Texture* texture = EngineDataCollector::GetInstance()->GetTextureCollector()->GetTexture(filePath);

	this->m_StartGradiantTexture = texture;
}
void UIObject::SetEndGradiantTexture(const std::string& filePath)
{
	Texture* texture = EngineDataCollector::GetInstance()->GetTextureCollector()->GetTexture(filePath);

	this->m_EndGradiantTexture = texture;
}