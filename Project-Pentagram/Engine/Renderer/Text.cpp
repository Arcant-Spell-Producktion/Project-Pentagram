#include "Text.h"

Text::Text()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->rotation = 0.0f;
	this->fontSize = 0.5f;
}

void Text::RenderText()
{
	// Activate corresponding render state
	Shader& shader = ShaderCollector::GetInstance()->TextShader;
	shader.Activate();

	// Set Uniform in shader
	Window* window = ArcantEngine::GetInstance()->GetWindow();
	int screen_width = window->GetWidth();
	int screen_height = window->GetHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);
	shader.setMat4("u_View", glm::mat4(1.0f));
	shader.setMat4("u_Projection", proj);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowRatio(), 1.0f)));

	// For keep tracking position of each Text
	float x = position.x;
	float y = position.y;

	// Iterate through all characters
	for (int idx = 0; idx < text.size(); idx++)
	{
		char c = text[idx];
		Character ch = FontCollector::GetInstance()->characters[c];

		float xpos = x + ch.bearing.x * fontSize;
		float ypos = y - (ch.size.y - ch.bearing.y) * fontSize;

		float w = ch.size.x * fontSize;
		float h = ch.size.y * fontSize;

		// Render glyph texture
		ch.texture.Bind();
		ch.texture.Activate(GL_TEXTURE0);

		// Set Uniform in shader
		glm::mat4 model = glm::mat4(1.0f);
		model *= glm::translate(glm::mat4(1.0f), glm::vec3(xpos + w / 2.0f, ypos + h / 2.0f, 0.0f));
		model *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::scale(glm::mat4(1.0f), glm::vec3(w, h, 1.0f));
		shader.setMat4("u_Model", model);
		shader.setVec4("u_Color", color);
		shader.setInt("u_Texture", 0);

		// Render quad
		this->mesh.Render();

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * fontSize;	// bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
}