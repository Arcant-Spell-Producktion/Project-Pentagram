#include "GameObject.h"

GameObject::GameObject(const std::string& objName)
{	
	// Set GameObject Properties
	this->name = objName;
	this->m_Tag = GameObjectTag::GAMEOBJECT;
	this->m_IsActive = true;
	this->parent = nullptr;
	this->m_IsZoomObject = true;

	// Set Transformation
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation = 0.0f;
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);

	// Set Color
	this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Texture* texture = EngineDataCollector::GetInstance().GetTextureCollector()->GetTexture("Sprites/default.png");

	// Set Row & Coloumn of SpriteSheet
	this->m_AnimationRow = texture->GetImageRow();
	this->m_AnimationColumn = texture->GetImageColumn();
	this->m_MaxAnimationColumn = texture->GetMaxImageColumn();
	this->m_IsAnimationLoop = true;

	this->m_IsAnimationObject = false;
	this->m_IsAnimationPlaying = false;
	this->m_IsSpriteSheet = (m_AnimationRow == 1 && m_AnimationColumn[0] == 1 ? false : true);

	// Set Texture
	this->m_Texture = texture;
	this->m_TexturePath = "Sprites/default.png";
}
GameObject::GameObject(const std::string& objName, const int& animRow, const std::vector<int>& animCol)
	: m_Mesh(animRow, *std::max_element(animCol.begin(), animCol.end()))
{
	// Set GameObject Properties
	this->name = objName;
	this->m_Tag = GameObjectTag::GAMEOBJECT;
	this->m_IsActive = true;
	this->parent = nullptr;
	this->m_IsZoomObject = true;

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
	this->m_IsAnimationLoop = true;

	// Set Texture
	this->m_Texture = EngineDataCollector::GetInstance().GetTextureCollector()->GetTexture("Sprites/default.png");
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
	Shader& shader = EngineDataCollector::GetInstance().GetShaderCollector()->GameObjectShader;

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

	Window* window = ArcantEngine::GetInstance().GetWindow();

	shader.Activate();
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
	shader.setMat4("u_Model", model * scaleMat);
	shader.setMat4("u_View", camera.GetViewMatrix());
	shader.setMat4("u_Projection", camera.GetProjectionMatrix(m_IsZoomObject));
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowDiffRatio(), 1.0f)));
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
GameObject* GameObject::FindChildObject(const std::string& childObjectName)
{
	// Find in BackRenderedChildList
	for (int idx = 0; idx < m_BackRenderedChildList.size(); idx++)
	{
		GameObject* childObj = m_BackRenderedChildList[idx];
		if (childObj->name == childObjectName)
		{
			return childObj;
		}
	}
	// Find in FrontRenderedChildList
	for (int idx = 0; idx < m_FrontRenderedChildList.size(); idx++)
	{
		GameObject* childObj = m_FrontRenderedChildList[idx];
		if (childObj->name == childObjectName)
		{
			return childObj;
		}
	}
}
unsigned int GameObject::GetChildSize() const
{
	return this->m_BackRenderedChildList.size() + this->m_FrontRenderedChildList.size();
}
unsigned int GameObject::GetFrontRenderChildSize() const
{
	return this->m_FrontRenderedChildList.size();
}
unsigned int GameObject::GetBackRenderChildSize() const
{
	return this->m_BackRenderedChildList.size();
}
std::vector<GameObject*> GameObject::GetFrontRenderChildList() const
{
	return this->m_FrontRenderedChildList;
}
std::vector<GameObject*> GameObject::GetBackRenderChildList() const
{
	return this->m_BackRenderedChildList;
}
std::vector<GameObject*> GameObject::GetChildList() const
{
	std::vector<GameObject*> childList;
	childList.insert(childList.end(), m_BackRenderedChildList.begin(), m_BackRenderedChildList.end());
	childList.insert(childList.end(), m_FrontRenderedChildList.begin(), m_FrontRenderedChildList.end());
	return childList;
}
glm::vec3 GameObject::GetWorldPosition() const
{
	glm::vec3 worldPosition = this->position;

	GameObject* curParent = parent;
	while (curParent != nullptr) 
	{
		worldPosition += curParent->position;
		curParent = curParent->parent;
	}

	return worldPosition;
}
bool GameObject::IsZoomObject() const
{
	return this->m_IsZoomObject;
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
bool GameObject::IsAnimationLoop() const
{
	return this->m_IsAnimationLoop;
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
void GameObject::RemoveChild(GameObject* gameObj)
{
	auto it = std::find(m_FrontRenderedChildList.begin(), m_FrontRenderedChildList.end(), gameObj);
	if (it != m_FrontRenderedChildList.end())
	{
		m_FrontRenderedChildList.erase(it);
		return;
	}

	it = std::find(m_BackRenderedChildList.begin(), m_BackRenderedChildList.end(), gameObj);
	if (it != m_BackRenderedChildList.end())
	{
		m_BackRenderedChildList.erase(it);
		return;
	}
}
void GameObject::SetIsZoomObject(const bool& active)
{
	this->m_IsZoomObject = active;
}
void GameObject::SetIsAnimationObject(const bool& active) 
{ 
	this->m_IsAnimationObject = active; 
	this->m_IsAnimationPlaying = (active == false ? false : m_IsAnimationPlaying);
}
void GameObject::SetIsAnimationLoop(const bool& active)
{
	this->m_IsAnimationLoop = active;
}
void GameObject::SetSpriteByIndex(const int& row, const int& column, const bool& doChangeNextFrame)
{
	// Change on Next Frame
	if (doChangeNextFrame)
	{
		m_DoChangeToNextFrame = true;
		m_NextFrameRow = row + 1;
		m_NextFrameColumn = column + 1;
	}
	// Change Frame Immediate
	else
	{
		this->m_CurrentAnimationRow = row + 1;
		this->m_CurrentAnimationColumn = column + 1;
		// Restart m_CurrentPlayTime
		m_CurrentPlayTime = 0.0f;
	}
}
void GameObject::SetSpriteByValue(const int& row, const int& column, const bool& doChangeNextFrame)
{
	// Change on Next Frame
	if (doChangeNextFrame)
	{
		m_DoChangeToNextFrame = true;
		m_NextFrameRow = row;
		m_NextFrameColumn = column;
	}
	// Change Frame Immediate
	else
	{
		this->m_CurrentAnimationRow = row;
		this->m_CurrentAnimationColumn = column;
		// Restart m_CurrentPlayTime
		m_CurrentPlayTime = 0.0f;
	}
}
void GameObject::SetAnimationPlayTime(const float& animationPlayTime)
{
	this->m_AnimationPlayTime = animationPlayTime;
}
void GameObject::SetTexture(const std::string& filePath)
{
	if (this->m_TexturePath == filePath) { return; }

	Texture* texture = EngineDataCollector::GetInstance().GetTextureCollector()->GetTexture(filePath);
	
	this->m_Texture = texture;
	this->m_TexturePath = filePath;
	// Set Row & Coloumn of SpriteSheet
	this->m_AnimationRow = texture->GetImageRow();
	this->m_AnimationColumn = texture->GetImageColumn();
	this->m_MaxAnimationColumn = texture->GetMaxImageColumn();
	this->m_IsSpriteSheet = (m_AnimationRow == 1 && m_AnimationColumn[0] == 1 ? false : true);

	m_Mesh.SetTextureCoord(m_AnimationRow, m_MaxAnimationColumn);
}
void GameObject::SetTexture(Texture* texture)
{
	this->m_Texture = texture;
}

// ----------------- Animation Update ----------------- 
void GameObject::UpdateAnimation(const float& deltaTime)
{
	// If Current Object are not AnimationObject or doesn't play Animation
	if (!m_IsAnimationObject || (m_CurrentAnimationColumn > m_AnimationColumn[m_CurrentAnimationRow - 1] && !m_IsAnimationLoop))
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
		if (m_DoChangeToNextFrame)
		{
			m_CurrentAnimationRow = m_NextFrameRow;
			m_CurrentAnimationColumn = m_NextFrameColumn;
			m_DoChangeToNextFrame = false;
		}
		else
		{
			// Increment Column & Check Condition
			m_CurrentAnimationColumn++;
			if (m_CurrentAnimationColumn > m_AnimationColumn[m_CurrentAnimationRow - 1]) 
			{
				m_CurrentAnimationColumn = (m_IsAnimationLoop ? 1 : m_AnimationColumn[m_CurrentAnimationRow - 1]);
			}
		}

		// Restart m_CurrentPlayTime
		m_CurrentPlayTime = 0.0f;
	}
}
