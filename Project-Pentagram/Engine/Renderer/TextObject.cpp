#include "TextObject.h"

TextObject::TextObject(const std::string& objName)
	: UIObject(objName)
{
	this->m_Tag = GameObjectTag::TEXT;
	this->m_IsZoomObject = false;
	
	this->m_Fonts = "Fonts/OldGameFatty.ttf";
	this->fontSize = 48; 
	this->textAlignment = TextAlignment::LEFT;
	this->outlineColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	this->m_SlowRender = false;
	this->m_CurrentTextIndex = -1;
	this->m_CurrentTime = 0.0f;
	this->lineSpacing = 1.15f;
}

void TextObject::OnUpdate(const float& dt)
{
	this->m_CurrentTime += dt;
}
void TextObject::Draw(Camera& camera, glm::mat4 parentModel)
{
	if (!m_IsActive)
	{
		return;
	}

	if (m_SlowRender)
	{
		this->RenderText(glm::vec3(0.0f, 0.0f, 0.0f), camera, parentModel, 0, m_CurrentTextIndex + 1);
		if (m_CurrentTime >= m_RenderTime)
		{
			m_CurrentTextIndex++;
			// If current index is tab -> Skip RenderText
			/*
				while (m_CurrentTextIndex < text.size() && text[m_CurrentTextIndex] == 9) { m_CurrentTextIndex++; }
			*/
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
		this->RenderText(glm::vec3(0.0f, 0.0f, 0.0f), camera, parentModel);
	}
}
void TextObject::UnloadMesh()
{
	this->m_TextSumX.clear();
	this->text.clear();
	GameObject::UnloadMesh();
}

// ----------------- Setter -----------------
void TextObject::SetRenderTime(const float& renderTime)
{
	this->m_SlowRender = true;
	this->m_CurrentTextIndex = 0;
	this->m_RenderTime = renderTime;
}
void TextObject::SetFonts(const std::string& fontPath)
{
	this->m_Fonts = fontPath;
}

// ----------------- Render Text -----------------
void TextObject::RenderText(glm::vec3 positionOffset, Camera& camera, glm::mat4 parentModel, int start, int end)
{
	start = (start == -1 ? 0 : start);
	end = (end == -1 ? this->text.size() : end);

	// Calculate Glyph Structure
	CalculateGlyphText(end);

	// Activate corresponding render state
	Shader& shader = EngineDataCollector::GetInstance()->GetShaderCollector()->TextShader;
	shader.Activate();

	// Update MVP Matrix
	glm::mat4 model = parentModel;
	model *= glm::translate(glm::mat4(1.0f), this->position);
	model *= glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	// Draw Back Child
	for (unsigned int idx = 0; idx < m_BackRenderedChildList.size(); idx++)
	{
		m_BackRenderedChildList[idx]->Draw(camera, model);
	}

	// Set Uniform in shader
	Window* window = ArcantEngine::GetInstance()->GetWindow();

	shader.setMat4("u_View", glm::mat4(1.0f));
	shader.setMat4("u_Projection", camera.GetProjectionMatrix(m_IsZoomObject));
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowDiffRatio(), 1.0f)));
	shader.setVec4("u_TextColor", this->color);
	shader.setVec4("u_OutlineColor", this->outlineColor);
	shader.setInt("u_Texture", 0);

	float x = this->position.x;
	float y = this->position.y;
	float lineSpace = BASE_FONT_SIZE * m_FontScale * this->lineSpacing;
	int countLine = 0;
	std::map<GLchar, Character>* characters = EngineDataCollector::GetInstance()->GetFontCollector()->GetFonts(m_Fonts);
	// Iterate through all characters
	for (unsigned int idx = start; idx < end; idx++)
	{
		char c = this->text[idx];
		// If current character is tab no need to render
		if (c == 9) { continue; }

		// If current character is new line('\n') -> Go To New Line
		if (c == '\n')
		{
			countLine++;
			x = this->position.x;
			continue;
		}
		Character& ch = characters->at(c);
		float xpos = x + ch.bearing.x * m_FontScale;
		float ypos = y - (ch.size.y - ch.bearing.y) * m_FontScale;

		float w = ch.size.x * m_FontScale;
		float h = ch.size.y * m_FontScale;

		// Activate current glyph texture
		ch.texture.Bind();
		ch.texture.Activate(GL_TEXTURE0);

		// Set Uniform in shader
		glm::mat4 textModel = parentModel;
		textModel *= glm::translate(glm::mat4(1.0f), positionOffset);
		if (textAlignment == TextAlignment::LEFT)
		{
			textModel *= glm::translate(glm::mat4(1.0f), glm::vec3((xpos + w / 2.0f), ypos + (h / 2.0f) - (m_TextMaxY / 2.0f) - (lineSpace * countLine), 0.0f));
		}
		else if (textAlignment == TextAlignment::MID)
		{
			textModel *= glm::translate(glm::mat4(1.0f), glm::vec3((xpos + w / 2.0f) - m_TextSumX[countLine] / 2.0f, ypos + (h / 2.0f) - (m_TextMaxY / 2.0f) - (lineSpace * countLine), 0.0f));
		}
		else
		{
			textModel *= glm::translate(glm::mat4(1.0f), glm::vec3((xpos + w / 2.0f) - m_TextSumX[countLine], ypos + (h / 2.0f) - (m_TextMaxY / 2.0f) - (lineSpace * countLine), 0.0f));
		}
		textModel *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		textModel *= glm::scale(glm::mat4(1.0f), glm::vec3(w, h, 1.0f));
		shader.setMat4("u_Model", textModel);

		// Render quad
		m_Mesh.Render();

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * m_FontScale;	// bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}

	// Draw Front Child
	for (unsigned int idx = 0; idx < m_FrontRenderedChildList.size(); idx++)
	{
		m_FrontRenderedChildList[idx]->Draw(camera, model);
	}
}

// ----------------- Private Function -----------------
void TextObject::CalculateGlyphText(const int& endIndex)
{
	m_TextMaxY = 0.0f;
	m_FontScale = this->fontSize / BASE_FONT_SIZE;

	float curTextSumX = 0.0f;
	int countLine = 0;
	std::map<GLchar, Character>* characters = EngineDataCollector::GetInstance()->GetFontCollector()->GetFonts(m_Fonts);
	// Pre-Calculated for justify text alignment
	for (unsigned int idx = 0; idx < endIndex; idx++)
	{
		char c = this->text[idx];
		Character& ch = characters->at(c);
		// If current character is tab no need to render
		if (c == 9) { continue; }

		// If current character is new line -> save m_TextSumX
		if (c == '\n')
		{
			// If index countLine doesn't have in m_TextSumX -> Create New
			if (countLine == m_TextSumX.size())
			{
				m_TextSumX.push_back(curTextSumX);
			}
			// else -> Modify existing index in vector
			else
			{
				m_TextSumX[countLine] = curTextSumX;
			}
			curTextSumX = 0.0f;
			countLine++;
			continue;
		}

		float w = ch.size.x * m_FontScale;
		float h = ch.size.y * m_FontScale;

		curTextSumX += (ch.advance >> 6) * m_FontScale;
		m_TextMaxY = std::max(h - (ch.size.y - ch.bearing.y) * m_FontScale, m_TextMaxY);
	}

	// If index countLine doesn't have in m_TextSumX -> Create New
	if (countLine == m_TextSumX.size())
	{
		m_TextSumX.push_back(curTextSumX);
	}
	// else -> Modify existing index in vector
	else
	{
		m_TextSumX[countLine] = curTextSumX;
	}
}