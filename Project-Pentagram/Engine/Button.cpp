#include "Button.h"

Button::Button(const std::string& objName)
	: UIObject(objName), textObject("Text_" + objName)
{
	m_Tag = GameObjectTag::BUTTON;
	uiList = nullptr;
}

void Button::Draw(Shader& shader, Camera& camera, const glm::mat4& parentModel)
{
	if (!m_Active)
	{
		return;
	}

	Shader& shader2 = EngineDataCollector::GetInstance()->GetShaderCollector()->ButtonShader;

	glm::mat4 model = glm::mat4(1.0f);

	model *= glm::translate(glm::mat4(1.0f), this->position);
	model *= glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model *= glm::scale(glm::mat4(1.0f), this->scale);

	Window* window = ArcantEngine::GetInstance()->GetWindow();
	int screen_width = window->GetWidth();
	int screen_height = window->GetHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);
	glm::mat4 view = camera.getViewMatrix();

	shader2.Activate();
	shader2.setMat4("u_Model", model);
	shader2.setMat4("u_View", glm::mat4(1.0f));
	shader2.setMat4("u_Projection", proj);
	shader2.setVec4("u_Color", color);
	shader2.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowRatio(), 1.0f)));
	m_Texture->Activate(GL_TEXTURE0);
	shader2.setInt("u_Texture", 0);
	float slice = 128.0f / 3.0f;
	shader2.setVec2("u_Dimensions", glm::vec2(slice / scale.x, slice / scale.y));
	shader2.setVec2("u_Border", glm::vec2(slice / 128.0f, slice / 128.0f));
	//std::cout << "u_Dimensions : " << slice / scale.x << ", " << slice / scale.y << "\n";
	//std::cout << "u_Border : " << slice / 128.0f << "," << slice / 128.0f << "\n";
	if (m_Animation)
	{
		// SpriteSheet Offset
		shader2.setFloat("u_OffsetX", m_CurAnimCol * (1.0f / m_MaxAnimCol));
		shader2.setFloat("u_OffsetY", (m_CurAnimRow - 1) * (1.0f / m_AnimRow));
	}
	else
	{
		// Default Offset (0.0f, 0.0f)
		shader2.setFloat("u_OffsetX", 0.0f);
		shader2.setFloat("u_OffsetY", 0.0f);
	}

	this->m_Mesh.Render();
	m_Texture->UnBind();

	textObject.RenderText(this->position);
	for (unsigned int idx = 0; idx < childList.size(); idx++)
	{
		childList[idx]->Draw(shader, camera);
	}
}

bool Button::onClick()
{
	if (!Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		return false;
	}

	return onHover();
}

bool Button::onHover()
{
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();

	float curX = (Input::mouseX - screen_width / 2.0f);
	float curY = (screen_height / 2.0f - Input::mouseY);

	float left = position.x - (scale.x / 2.0f);
	float right = position.x + (scale.x / 2.0f);
	float top = position.y + (scale.y / 2.0f);
	float bottom = position.y - (scale.y / 2.0f);

	// Debug
	/*
		std::cout << "MOUSE : " << curX << " " << curY << "\n";
		std::cout << "LEFT : " << left << "\n";
		std::cout << "RIGHT : " << right << "\n";
		std::cout << "TOP : " << top << "\n";
		std::cout << "BOTTOM : " << bottom << "\n";
		std::cout << "POS : " << position.x << " " << position.y << "\n\n";
	*/


	// If Mouse position hit with current Object
	if ((curX <= right && curX >= left) && (curY <= top && curY >= bottom))
	{
		for (int idx = uiList->size() - 1; uiList->at(idx) != this; idx--)
		{
			UIObject* curObj = uiList->at(idx);

			// If current Object is inactive (Not Render) => No need to check collision
			if (curObj == nullptr || !curObj->isActive())
			{
				continue;
			}
			// If current Object is TextObject or UIObject => No need to check
			if (dynamic_cast<Button*>(curObj) != nullptr)
			{
				left = curObj->position.x - (curObj->scale.x / 2.0f);
				right = curObj->position.x + (curObj->scale.x / 2.0f);
				top = curObj->position.y + (curObj->scale.y / 2.0f);
				bottom = curObj->position.y - (curObj->scale.y / 2.0f);

				if ((curX <= right && curX >= left) && (curY <= top && curY >= bottom))
				{
					return false;
				}
			}

		}
		return true;
	}
	else
	{
		return false;
	}
}