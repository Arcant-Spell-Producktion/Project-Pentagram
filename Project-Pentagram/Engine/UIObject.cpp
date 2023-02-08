#include "UIObject.h"

UIObject::UIObject(const std::string& objName)
	: GameObject(objName)
{
	this->m_Tag = GameObjectTag::UIOBJECT;
	this->m_IsZoomObject = false;

	this->m_IsSlicing = false;
	this->m_SlicingBorder = 40.0f;
	this->m_SlicingBorderMultiplier = 1.0f;
	this->m_IsGradient = false;
	this->m_GradientValue = 0.0f;
}

void UIObject::Draw(Camera& camera, glm::mat4 parentModel)
{
	if (!m_IsActive)
	{
		return;
	}

	// Get UI(GameObject) Shader || Button Shader(Handle UI Slicing)
	ShaderCollector* shaderCollector = EngineDataCollector::GetInstance()->GetShaderCollector();
	Shader& shader = (m_IsGradient ? shaderCollector->GradientShader : shaderCollector->UISlicingShader);

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
	else if (m_IsGradient)
	{
		m_StartGradientTexture->Activate(GL_TEXTURE1);
		shader.setInt("u_StartGradient", 1);
		
		m_EndGradientTexture->Activate(GL_TEXTURE2);
		shader.setInt("u_EndGradient", 2);

		shader.setFloat("u_InterpolateValue", m_GradientValue);
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
bool UIObject::IsGradient() const
{
	return this->m_IsGradient;
}
float UIObject::GetGradientValue() const 
{
	return this->m_GradientValue;
}
Texture* UIObject::GetStartGradientTexture() const
{
	return this->m_StartGradientTexture;
}
Texture* UIObject::GetEndGradientTexture() const
{
	return this->m_EndGradientTexture;
}
bool UIObject::IsBlockRaycast() const
{
	return m_BlockRaycast;
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
void UIObject::SetIsGradient(const bool& active)
{
	this->m_IsGradient = active;
}
void UIObject::SetGradientValue(const float& gradiantValue)
{
	float gradiantClampValue = glm::clamp(gradiantValue, 0.0f, 1.0f);
	this->m_GradientValue = gradiantClampValue;
}
void UIObject::SetStartGradientTexture(const std::string& filePath) 
{
	Texture* texture = EngineDataCollector::GetInstance()->GetTextureCollector()->GetTexture(filePath);

	this->m_StartGradientTexture = texture;
}
void UIObject::SetEndGradientTexture(const std::string& filePath)
{
	Texture* texture = EngineDataCollector::GetInstance()->GetTextureCollector()->GetTexture(filePath);

	this->m_EndGradientTexture = texture;
}
void UIObject::SetBlockRaycast(const bool& active)
{
	this->m_BlockRaycast = active;
}