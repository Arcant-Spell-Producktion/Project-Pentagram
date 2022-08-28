#include "UIObject.h"

UIObject::UIObject(const std::string& objName)
	: GameObject(objName)
{
	tag = GameObjectTag::UIOBJECT;
}

void UIObject::Draw(Shader& shader, Camera& camera, const glm::mat4& parentModel)
{
	if (!active)
	{
		return;
	}


	glm::mat4 model = glm::mat4(1.0f);

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
	shader.setMat4("u_View", glm::mat4(1.0f));
	shader.setMat4("u_Projection", proj);
	shader.setVec4("u_Color", color);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowRatio(), 1.0f)));
	texture->Activate(GL_TEXTURE0);
	shader.setInt("u_Texture", 0);

	this->mesh.Render();

	texture->UnBind();

	for (unsigned int idx = 0; idx < childList.size(); idx++)
	{
		childList[idx]->Draw(shader, camera);
	}
}