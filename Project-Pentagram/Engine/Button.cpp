#include "Button.h"

Button::Button(const std::string& objName)
	: UIObject(objName), textObject("Text_" + objName)
{
	m_Tag = GameObjectTag::BUTTON;
	border = 40.0f;
	hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	onHover = [](Button* button) { std::cout << button->name << " : OnHover\n"; };
	unHover = [](Button* button) { button->hoverColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); };
	onClick = [](Button* button) { std::cout << button->name << " : OnClick\n"; };
}

void Button::Draw(Camera& camera, glm::mat4 parentModel)
{
	if (!m_Active)
	{
		return;
	}

	Shader& shader = EngineDataCollector::GetInstance()->GetShaderCollector()->ButtonShader;

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
	glm::mat4 view = camera.getViewMatrix();

	shader.Activate();
	shader.setMat4("u_Model", model * scaleMat);
	shader.setMat4("u_View", glm::mat4(1.0f));
	shader.setMat4("u_Projection", proj);
	shader.setVec4("u_Color", (hoverColor == glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) ? color : hoverColor));
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowRatio(), 1.0f)));
	m_Texture->Activate(GL_TEXTURE0);
	shader.setInt("u_Texture", 0);

	// Set Button Slicing
	float minVal = std::min(scale.x, scale.y);
	glm::vec2 u_dimension = glm::vec2(scale.x, scale.y);
	glm::vec2 u_textureBorder = glm::vec2(0.5f, 0.5f);
	float u_border = (minVal >= 2 * border ? border : minVal / 2.0f);
	shader.setVec2("u_Dimensions", u_dimension);
	shader.setVec2("u_TextureBorder", u_textureBorder);
	shader.setFloat("u_Border", u_border);
	// ------ Debug --------
	//std::cout << "u_Dimensions : " << dimension.x << ", " << dimension.y << "\n";
	//std::cout << "u_Border : " << border.x << "," << border.y << "\n";
	if (m_Animation)
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

	textObject.RenderText(model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	// Draw Front Child
	for (unsigned int idx = 0; idx < m_FrontChildList.size(); idx++)
	{
		m_FrontChildList[idx]->Draw(camera, model);
	}
}

void Button::UnloadMesh()
{
	this->textObject.UnloadMesh();
	GameObject::UnloadMesh();
}