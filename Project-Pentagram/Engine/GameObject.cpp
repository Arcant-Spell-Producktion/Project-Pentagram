#include "GameObject.h"

GameObject::GameObject(const std::string& objName, const int& animRow, const std::vector<int>& animCol)
	: m_Mesh(animRow, *std::max_element(animCol.begin(), animCol.end()))
{
	// Set GameObject Properties
	name = objName;
	m_Tag = GameObjectTag::GAMEOBJECT;
	m_Active = true;
	parent = nullptr;

	// Set Transformation
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = 0.0f;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	// Set Color
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Set Row & Coloumn of SpriteSheet
	m_AnimRow = animRow;
	m_AnimCol = animCol;
	m_MaxAnimCol = *std::max_element(animCol.begin(), animCol.end());

	// Set Current Sprite have animation or not
	m_Animation = (m_AnimRow == 1 && m_AnimCol[0] == 1 ? false : true);

	// Set Texture
	this->m_Texture = EngineDataCollector::GetInstance()->GetTextureCollector()->GetTexture("Sprites/default.png");
}

void GameObject::OnUpdate(const float& dt)
{

}

void GameObject::Draw(Shader& shader, Camera& camera, const glm::mat4& parentModel)
{
	// If object is not-active -> no need to render
	if (!m_Active)
	{
		return;
	}

	// Update MVP Matrixs
	glm::mat4 model = parentModel;
	model *= glm::translate(glm::mat4(1.0f), this->position);
	model *= glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	// !!Draw Child First(Only GameObject that draw child first)
	for (unsigned int idx = 0; idx < childList.size(); idx++)
	{
		childList[idx]->Draw(shader, camera, model);
	}
	// !!Not Set scale to child -> Messy to encounter with
	model *= glm::scale(glm::mat4(1.0f), this->scale);

	Window* window = ArcantEngine::GetInstance()->GetWindow();
	int screen_width = window->GetWidth();
	int screen_height = window->GetHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);
	glm::mat4 view = camera.getViewMatrix();

	shader.Activate();
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
	shader.setMat4("u_Model", model);
	shader.setMat4("u_View", view);
	shader.setMat4("u_Projection", proj);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowRatio(), 1.0f)));
	shader.setVec4("u_Color", color);
	m_Texture->Activate(GL_TEXTURE0);
	shader.setInt("u_Texture", 0);

	this->m_Mesh.Render();
	m_Texture->UnBind();
}

void GameObject::UnloadMesh()
{
	this->m_Mesh.Delete();
}

void GameObject::MakeChild(GameObject* gameObj)
{
	childList.push_back(gameObj);
	gameObj->parent = this;
}

// Implement Getter
unsigned int GameObject::GetTag() { return this->m_Tag; }
bool GameObject::isAnimation() { return this->m_Animation; }
bool GameObject::isActive() { return this->m_Active; }

// Implement Setter
void GameObject::SetAnimation(const bool& active) { this->m_Animation = active; }
void GameObject::SetActive(const bool& active) 
{ 
	// Set Active on current Object
	this->m_Active = active;

	// Set Active on their childs
	for (int idx = 0; idx < childList.size(); idx++)
	{
		childList[idx]->SetActive(active);
	}
}


// Implement Texture
void GameObject::SetTexture(const std::string& path)
{
	this->m_Texture = EngineDataCollector::GetInstance()->GetTextureCollector()->GetTexture(path);
}

// Implement Update Animation
void GameObject::UpdateAnimation(const float& deltaTime, const float& animTime)
{
	// Increment Time
	m_Time += deltaTime;

	// m_Time reach AnimationTime or not?
	if (m_Time >= animTime)
	{
		// Increment Column & Check Condition
		m_CurAnimCol++;
		if (m_CurAnimCol >= m_AnimCol[m_CurAnimRow - 1]) { m_CurAnimCol = 1; }

		// Restart m_Time
		m_Time = 0.0f;
	}
}
void GameObject::SetAnimationState(const int& animRow)
{
	// If newAnimationRow != currentRow
	// Reset AnimationColumn to 1(starting index)
	if (m_CurAnimRow != animRow)
	{
		m_CurAnimCol = 1;
	}
	m_CurAnimRow = animRow;
}