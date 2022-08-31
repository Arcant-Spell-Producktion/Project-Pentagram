#include "TextObject.h"

TextObject::TextObject(const std::string& objName)
	: UIObject(objName)
{
	m_Tag = GameObjectTag::TEXT;

	this->fontSize = 48; 
	this->textAlignment = TextAlignment::LEFT;
	this->outlineColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	this->m_SlowRender = false;
	this->m_CurrentTextIndex = -1;
	this->m_CurrentTime = 0.0f;
}

void TextObject::OnUpdate(const float& dt)
{
	m_CurrentTime += dt;
}

void TextObject::Draw(Shader& shader, Camera& camera, const glm::mat4& parentModel)
{
	if (m_SlowRender)
	{
		this->RenderText(glm::vec3(0.0f, 0.0f, 0.0f), 0, m_CurrentTextIndex + 1);
		if (m_CurrentTime >= m_RenderTime)
		{
			m_CurrentTextIndex++;
			m_CurrentTime = 0.0f;
		}
		// If Render All of Characters
		if (m_CurrentTextIndex >= text.size())
		{
			// No Need to do slow Render
			m_SlowRender = false;
		}
	}
	else if(!m_SlowRender)
	{
		this->RenderText();
	}
}

void TextObject::RenderText()
{
	this->RenderText(glm::vec3(0.0f, 0.0f, 0.0f));
}

void TextObject::SetSlowRender(const float& renderTime)
{
	m_SlowRender = true;
	m_CurrentTextIndex = 0;
	m_RenderTime = renderTime;
}

void TextObject::RenderText(glm::vec3 positionOffset, int start, int end)
{
	start = (start == -1 ? 0 : start);
	end = (end == -1 ? text.size() : end);

	// Calculate Glyph Structure
	CalculateGlyphText(end);

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
	shader.setVec4("u_TextColor", color);
	shader.setVec4("u_OutlineColor", outlineColor);

	float x = position.x;
	float y = position.y;
	float lineSpace = BASE_FONT_SIZE * m_FontScale;
	int countY = 0;
	// Iterate through all characters
	for (unsigned int idx = start; idx < end; idx++)
	{
		char c = text[idx];
		if (c == '\n')
		{
			countY++;
			x = position.x;
			continue;
		}
		Character& ch = EngineDataCollector::GetInstance()->GetFontCollector()->characters[c];

		float xpos = x + ch.bearing.x * m_FontScale;
		float ypos = y - (ch.size.y - ch.bearing.y) * m_FontScale;


		float w = ch.size.x * m_FontScale;
		float h = ch.size.y * m_FontScale;

		// Render glyph texture
		ch.texture.Bind();
		ch.texture.Activate(GL_TEXTURE0);

		// Set Uniform in shader
		glm::mat4 model = glm::translate(glm::mat4(1.0f), positionOffset);
		if (textAlignment == TextAlignment::LEFT)
		{
			model *= glm::translate(glm::mat4(1.0f), glm::vec3((xpos + w / 2.0f), ypos + (h / 2.0f) - (m_TextMaxY / 2.0f) - (lineSpace * countY), 0.0f));
		}
		else if (textAlignment == TextAlignment::MID)
		{
			model *= glm::translate(glm::mat4(1.0f), glm::vec3((xpos + w / 2.0f) - m_TextSumX / 2.0f, ypos + (h / 2.0f) - (m_TextMaxY / 2.0f) - (lineSpace * countY), 0.0f));
		}
		else
		{
			model *= glm::translate(glm::mat4(1.0f), glm::vec3((xpos + w / 2.0f) - m_TextSumX, ypos + (h / 2.0f) - (m_TextMaxY / 2.0f) - (lineSpace * countY), 0.0f));
		}
		model *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::scale(glm::mat4(1.0f), glm::vec3(w, h, 1.0f));
		shader.setMat4("u_Model", model);
		shader.setInt("u_Texture", 0);

		// Render quad
		this->mesh.Render();

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * m_FontScale;	// bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
}

void TextObject::CalculateGlyphText(const int& endIndex)
{
	m_TextSumX = 0.0f;
	m_TextMaxY = 0.0f;
	m_FontScale = fontSize / BASE_FONT_SIZE;
	// Pre-Calculated for justify text alignment
	for (unsigned int idx = 0; idx < endIndex; idx++)
	{
		char c = text[idx];
		Character& ch = EngineDataCollector::GetInstance()->GetFontCollector()->characters[c];

		float w = ch.size.x * m_FontScale;
		float h = ch.size.y * m_FontScale;

		m_TextSumX += ((ch.advance >> 6) + ch.bearing.x) * m_FontScale;
		m_TextMaxY = std::max(h - (ch.size.y - ch.bearing.y) * m_FontScale, m_TextMaxY);
	}
}