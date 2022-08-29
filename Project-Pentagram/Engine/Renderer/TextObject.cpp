#include "TextObject.h"

TextObject::TextObject(const std::string& objName)
	: UIObject(objName)
{
	tag = GameObjectTag::TEXT;

	this->fontScale = 1.0f; 
	this->textAlignment = TextAlignment::MID;
}

void TextObject::Draw(Shader& shader, Camera& camera, const glm::mat4& parentModel)
{
	this->RenderText();
}

void TextObject::RenderText()
{
	this->RenderText(glm::vec3(0.0f, 0.0f, 0.0f));
}

void TextObject::RenderText(glm::vec3 positionOffset)
{
	// Activate corresponding render state
	Shader& shader = EngineDataCollector::GetInstance()->GetShaderCollector()->TextShader;
	shader.Activate();

	// Set Uniform in shader
	Window* window = ArcantEngine::GetInstance()->GetWindow();
	int screen_width = window->GetWidth();
	int screen_height = window->GetHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);
	shader.setMat4("u_View", glm::mat4(1.0f));
	shader.setMat4("u_Projection", proj);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowRatio(), 1.0f)));

	float sumX = 0.0f;
	float maxY = 0.0f;
	// Pre-Calculated for justify text alignment
	for (unsigned int idx = 0; idx < text.size(); idx++)
	{
		char c = text[idx];
		Character& ch = EngineDataCollector::GetInstance()->GetFontCollector()->characters[c];

		float w = ch.size.x * fontScale;
		float h = ch.size.y * fontScale;

		sumX += w + ch.bearing.x * fontScale;
		maxY = std::max(h - (ch.size.y - ch.bearing.y) * fontScale, maxY);
	}

	float x = position.x;
	float y = position.y;
	// Iterate through all characters
	for (unsigned int idx = 0; idx < text.size(); idx++)
	{
		char c = text[idx];
		Character& ch = EngineDataCollector::GetInstance()->GetFontCollector()->characters[c];

		float xpos = x + ch.bearing.x * fontScale;
		float ypos = y - (ch.size.y - ch.bearing.y) * fontScale;

		float w = ch.size.x * fontScale;
		float h = ch.size.y * fontScale;

		// Render glyph texture
		ch.texture.Bind();
		ch.texture.Activate(GL_TEXTURE0);

		// Set Uniform in shader
		glm::mat4 model = glm::translate(glm::mat4(1.0f), positionOffset);
		if (textAlignment == TextAlignment::LEFT)
		{
			model *= glm::translate(glm::mat4(1.0f), glm::vec3((xpos + w / 2.0f), ypos + h / 2.0f - maxY / 2.0f, 0.0f));
		}
		else if (textAlignment == TextAlignment::MID)
		{
			model *= glm::translate(glm::mat4(1.0f), glm::vec3((xpos + w / 2.0f) - sumX / 2.0f, ypos + h / 2.0f - maxY / 2.0f, 0.0f));
		}
		else
		{
			model *= glm::translate(glm::mat4(1.0f), glm::vec3((xpos + w / 2.0f) - sumX, ypos + h / 2.0f - maxY / 2.0f, 0.0f));
		}
		model *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::scale(glm::mat4(1.0f), glm::vec3(w, h, 1.0f));
		shader.setMat4("u_Model", model);
		shader.setVec4("u_Color", color);
		shader.setInt("u_Texture", 0);

		// Render quad
		this->mesh.Render();

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * fontScale;	// bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
}