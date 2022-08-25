#include "GameObject.h"

GameObject::GameObject(const std::string& objName)
{
	// Set GameObject Properties
	name = objName;
	tag = GameObjectTag::GAMEOBJECT;
	active = true;
	parent = nullptr;

	// Set Transformation
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = 0.0f;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	
	// Set Color
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	// Set Row & Coloumn of SpriteSheet
	animRow = 1;
	animCol = 1;

	// Set Texture
	SetTexture("Sprites/default.png");
}

void GameObject::OnUpdate(const float& dt)
{

}

void GameObject::Draw(Shader& shader, Camera& camera)
{
	// If object is not-active -> no need to render
	if (!active)
	{
		return;
	}

	glm::mat4 model = glm::mat4(1.0f);
	// Current Object has parent
	if (parent != nullptr)
	{
		// Update Transform related with Parents
		model *= glm::translate(glm::mat4(1.0f), parent->position);
		model *= glm::rotate(glm::mat4(1.0f), glm::radians(parent->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::scale(glm::mat4(1.0f), parent->scale);
	}

	// Update MVP Matrixs
	model *= glm::translate(glm::mat4(1.0f), this->position);
	model *= glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model *= glm::scale(glm::mat4(1.0f), this->scale);

	Window* window = ArcantEngine::GetInstance()->GetWindow();
	int screen_width = window->GetWidth();
	int screen_height = window->GetHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);
	glm::mat4 view = camera.getViewMatrix();

	shader.Activate();
	shader.setMat4("u_Model", model);
	shader.setMat4("u_View", view);
	shader.setMat4("u_Projection", proj);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f),glm::vec3(window->GetWindowRatio(), 1.0f)));
	shader.setVec4("u_Color", color);
	texture.Activate(GL_TEXTURE0);
	shader.setInt("u_Texture", 0);

	this->mesh.Render();
	texture.UnBind();

	for (unsigned int idx = 0; idx < childList.size(); idx++)
	{
		childList[idx]->Draw(shader, camera);
	}
}

void GameObject::UnloadMesh()
{
	this->mesh.Delete();
}

void GameObject::MakeChild(GameObject* gameObj)
{
	childList.push_back(gameObj);
	gameObj->parent = this;
}

// Implement Tag
unsigned int GameObject::GetTag()
{
	return this->tag;
}

// Implement Texture
void GameObject::SetTexture(const std::string& path)
{
	this->texture.SetTexture(path.c_str(), GL_UNSIGNED_BYTE);
}
// Implement SpriteSheet Animation
void GameObject::SetSpriteSheet(const int& row, const int& col)
{
	this->animRow = row;
	this->animCol = col;
}