#include "Button.h"

Button::Button(const std::string& objName)
	: UIObject(objName), textObject("Text_" + objName)
{
	// Set-up Button Default
	m_Tag = GameObjectTag::BUTTON;
	m_IsSlicing = true;
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
	unHover = [](Button* button) { button->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); };
	onClick = [](Button* button) { std::cout << button->name << " : OnClick\n"; };
	onPress = [](Button* button) {};
	unPress = [](Button* button) {};

	// Set-up Text Default
	textObject.textAlignment = TextAlignment::MID;
	textObject.position = glm::vec3(0.0f, 0.0f, 0.0f);
	textObject.color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Button::Draw(Camera& camera, glm::mat4 parentModel)
{
	if (!m_IsActive)
	{
		return;
	}

	Shader& shader = EngineDataCollector::GetInstance()->GetShaderCollector()->UISlicingShader;

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
	glm::mat4 view = camera.GetViewMatrix();

	shader.Activate();
	shader.setMat4("u_Model", model * scaleMat);
	shader.setMat4("u_View", glm::mat4(1.0f));
	shader.setMat4("u_Projection", proj);
	shader.setVec4("u_Color", (this->hoverColor == glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) ? this->color : this->hoverColor));
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
		//std::cout << "u_Border : " << u_slicingBorder << "\n\n";
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

	this->textObject.RenderText(model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	// Draw Front Child
	for (unsigned int idx = 0; idx < m_FrontRenderedChildList.size(); idx++)
	{
		m_FrontRenderedChildList[idx]->Draw(camera, model);
	}
}
void Button::UnloadMesh()
{
	this->textObject.UnloadMesh();
	GameObject::UnloadMesh();
}