#include "GameObject.h"

GameObject::GameObject(const std::string& objName, const int& animRow, const std::vector<int>& animCol)
	: m_Mesh(animRow, *std::max_element(animCol.begin(), animCol.end()))
{
	// Set GameObject Properties
	this->name = objName;
	this->m_Tag = GameObjectTag::GAMEOBJECT;
	this->m_IsActive = true;
	this->parent = nullptr;

	// Set Transformation
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation = 0.0f;
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);

	// Set Color
	this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Set Row & Coloumn of SpriteSheet
	this->m_AnimationRow = animRow;
	this->m_AnimationColumn = animCol;
	this->m_MaxAnimationColumn = *std::max_element(animCol.begin(), animCol.end());

	this->m_IsAnimationObject = false;
	this->m_IsAnimationPlaying = false;
	this->m_IsSpriteSheet = (m_AnimationRow == 1 && m_AnimationColumn[0] == 1 ? false : true);

	// Set Texture
	this->m_Texture = EngineDataCollector::GetInstance()->GetTextureCollector()->GetTexture("Sprites/default.png");
}
GameObject::~GameObject()
{

}

void GameObject::OnUpdate(const float& dt)
{

}
void GameObject::Draw(Camera& camera, glm::mat4 parentModel)
{
	// If object is not-active -> no need to render
	if (!m_IsActive)
	{
		return;
	}

	// Get GameObject Shader
	Shader& shader = EngineDataCollector::GetInstance()->GetShaderCollector()->GameObjectShader;

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
	glm::mat4 view = camera.GetViewMatrix();

	shader.Activate();
	if (m_IsSpriteSheet)
	{
		// SpriteSheet Offset
		shader.setFloat("u_OffsetX", m_CurrentAnimationColumn * (1.0f / m_MaxAnimationColumn));
		shader.setFloat("u_OffsetY", (m_CurrentAnimationRow - 1) * (1.0f / m_AnimationRow));
	}
	else
	{
		// Default Offset (0.0f, 0.0f)
		shader.setFloat("u_OffsetX", 0.0f);
		shader.setFloat("u_OffsetY", 0.0f);
	}
	shader.setMat4("u_Model", model * scaleMat);
	shader.setMat4("u_View", view);
	shader.setMat4("u_Projection", proj);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowRatio(), 1.0f)));
	shader.setVec4("u_Color", this->color);
	m_Texture->Activate(GL_TEXTURE0);
	shader.setInt("u_Texture", 0);

	m_Mesh.Render();
	m_Texture->UnBind();

	// Draw Front Child
	for (unsigned int idx = 0; idx < m_FrontRenderedChildList.size(); idx++)
	{
		m_FrontRenderedChildList[idx]->Draw(camera, model);
	}
}
void GameObject::UnloadMesh()
{
	this->m_Mesh.Delete();
	this->m_Texture = nullptr;
	this->m_AnimationColumn.clear();
	this->m_FrontRenderedChildList.clear();
	this->m_BackRenderedChildList.clear();
	this->parent= nullptr;
}

// ----------------- Getter ----------------- 
unsigned int GameObject::GetTag() const 
{ 
	return this->m_Tag; 
}
bool GameObject::IsActive() const 
{ 
	return this->m_IsActive; 
}
Texture* GameObject::GetTexture() const 
{ 
	return this->m_Texture; 
}
int GameObject::GetCurrentAnimationRow() const 
{ 
	return this->m_CurrentAnimationRow; 
}
int GameObject::GetCurrentAnimationColumn() const 
{ 
	return this->m_CurrentAnimationColumn; 
}
glm::ivec2 GameObject::GetCurrentAnimationIndex() const 
{ 
	return glm::ivec2(this->m_CurrentAnimationRow, this->m_CurrentAnimationColumn); 
}
int GameObject::GetAnimationRow() const 
{ 
	return this->m_AnimationRow; 
}
int GameObject::GetAnimationColumn(const int& row) const 
{ 
	return this->m_AnimationColumn[row]; 
}
float GameObject::GetAnimationPlayTime() const 
{ 
	return this->m_AnimationPlayTime; 
}
float GameObject::GetCurrentAnimationPlayTime() const 
{ 
	return this->m_CurrentPlayTime; 
}
bool GameObject::IsAnimationObject() const 
{ 
	return this->m_IsAnimationObject; 
}
bool GameObject::IsAnimationPlaying() const
{
	return this->m_IsAnimationPlaying;
}
bool GameObject::IsSpriteSheet() const
{
	return this->m_IsSpriteSheet;
}

// ----------------- Setter ----------------- 
void GameObject::SetActive(const bool& active) 
{ 
	// Set Active on current Object
	this->m_IsActive = active;

	// Set Active on their childs
	for (unsigned int idx = 0; idx < m_FrontRenderedChildList.size(); idx++)
	{
		m_FrontRenderedChildList[idx]->SetActive(active);
	}
	for (unsigned int idx = 0; idx < m_BackRenderedChildList.size(); idx++)
	{
		m_BackRenderedChildList[idx]->SetActive(active);
	}
}
void GameObject::SetChildRenderFront(GameObject* gameObj)
{
	m_FrontRenderedChildList.push_back(gameObj);
	gameObj->parent = this;
}
void GameObject::SetChildRenderBack(GameObject* gameObj)
{
	m_BackRenderedChildList.push_back(gameObj);
	gameObj->parent = this;
}
void GameObject::SetIsAnimationObject(const bool& active) 
{ 
	this->m_IsAnimationObject = active; 
	this->m_IsAnimationPlaying = (active == false ? false : m_IsAnimationPlaying);
}
void GameObject::SetSpriteByIndex(const int& row, const int& column)
{
	this->m_CurrentAnimationRow = row + 1;
	this->m_CurrentAnimationColumn = column + 1;
}
void GameObject::SetSpriteByValue(const int& row, const int& column)
{
	this->m_CurrentAnimationRow = row;
	this->m_CurrentAnimationColumn = column;
}
void GameObject::SetAnimationPlayTime(const float& animationPlayTime)
{
	this->m_AnimationPlayTime = animationPlayTime;
}
void GameObject::SetTexture(const std::string& filePath)
{
	this->m_Texture = EngineDataCollector::GetInstance()->GetTextureCollector()->GetTexture(filePath);
}
void GameObject::SetTexture(Texture* texture)
{
	this->m_Texture = texture;
}

// ----------------- Animation Update ----------------- 
void GameObject::UpdateAnimation(const float& deltaTime)
{
	// If Current Object are not AnimationObject or doesn't play Animation
	if (!m_IsAnimationObject)
	{
		return;
	}

	// Set IsPlaying
	m_IsAnimationPlaying = true;

	// Increment Time
	m_CurrentPlayTime += deltaTime;

	// m_Time reach AnimationTime or not?
	if (m_CurrentPlayTime >= m_AnimationPlayTime)
	{
		// Increment Column & Check Condition
		m_CurrentAnimationColumn++;
		if (m_CurrentAnimationColumn >= m_AnimationColumn[m_CurrentAnimationRow - 1]) 
		{ 
			m_CurrentAnimationColumn = 1; 
		}

		// Restart m_CurrentPlayTime
		m_CurrentPlayTime = 0.0f;
	}
}
