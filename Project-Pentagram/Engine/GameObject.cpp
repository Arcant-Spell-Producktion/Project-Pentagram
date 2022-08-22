#include "GameObject.h"

GameObject::GameObject()
{
	isActive = true;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = 0.0f;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	SetTexture("Sprites/default.png");
}

void GameObject::Draw(Shader& shader, Camera& camera)
{
	if (!isActive)
	{
		return;
	}

	glm::mat4 model = glm::mat4(1.0f);
	model *= glm::translate(glm::mat4(1.0f), this->position);
	model *= glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model *= glm::scale(glm::mat4(1.0f), this->scale);

	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);
	glm::mat4 view = camera.getViewMatrix();

	shader.Activate();
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", proj);
	shader.setVec4("ObjColor", color);
	texture.Activate(GL_TEXTURE0);
	shader.setInt("ObjTexture", 0);

	this->mesh.Render();

	texture.UnBind();
}

void GameObject::UnloadMesh()
{
	this->mesh.Delete();
}

// Implement Texture
void GameObject::SetTexture(const char* src)
{
	this->texture.SetTexture(src, GL_UNSIGNED_BYTE);
}