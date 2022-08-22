#include "UI.h"

UI::UI()
{

}

void UI::Draw(Shader& shader, Camera& camera)
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
	shader.setMat4("view", glm::mat4(1.0f));
	shader.setMat4("projection", proj);
	shader.setVec4("ObjColor", color);
	texture.Activate(GL_TEXTURE0);
	shader.setInt("ObjTexture", 0);

	this->mesh.Render();

	texture.UnBind();
}

bool UI::onClick()
{
	if (!Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		return false;
	}

	return onHover();
}

bool UI::onHover()
{
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();

	float curX = (Input::mouseX - screen_width / 2.0f) / (screen_width / 2.0f);
	float curY = (Input::mouseY - screen_height / 2.0f) / (screen_height / 2.0f);

	glm::vec4 mousePos = glm::vec4(curX, curY, 0.0f, 1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model *= glm::translate(glm::mat4(1.0f), this->position);
	model *= glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model *= glm::scale(glm::mat4(1.0f), this->scale);
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);

	glm::vec4 v1 = proj * model * glm::vec4(squareVertices[0].Position, 1.0f);
	glm::vec4 v2 = proj * model * glm::vec4(squareVertices[1].Position, 1.0f);
	glm::vec4 v3 = proj * model * glm::vec4(squareVertices[2].Position, 1.0f);
	glm::vec4 v4 = proj * model * glm::vec4(squareVertices[3].Position, 1.0f);

	float minX = std::min({ v1.x, v2.x, v3.x, v4.x });
	float maxX = std::max({ v1.x, v2.x, v3.x, v4.x });
	float minY = std::min({ v1.y, v2.y, v3.y, v4.y });
	float maxY = std::max({ v1.y, v2.y, v3.y, v4.y });

	// Debug
	/* 
		std::cout << "MOUSE : " << mousePos.x << " " << mousePos.y << "\n";
		std::cout << "V1 : " << v1.x << " " << v1.y << "\n";
		std::cout << "V2 : " << v2.x << " " << v2.y << "\n";
		std::cout << "V3 : " << v3.x << " " << v3.y << "\n";
		std::cout << "V4 : " << v4.x << " " << v4.y << "\n\n";
	*/
	return (curX <= maxX && curX >= minX) && (curY <= maxY && curY >= minY);
}