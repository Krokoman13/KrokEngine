#include "Sprite.hpp"
#include <iostream>
#include <glew.h>

#include "../../resourceManager/ResourceManager.hpp"
#include "../../../../Assets/fileIndex.hpp"

Sprite::Sprite(const unsigned int a_resourceID) : Renderable(), m_resourceID(a_resourceID)
{
	SetLocalScale(Vec2(0, 0));

	m_minFilterParam = Sprite::defaultMinFilterParam;
	m_magFilterParam = Sprite::defaultMagFilterParam;
	m_displayMode = Sprite::defaultDisplayMode;
}

Sprite::~Sprite()
{

}

void Sprite::OnLoad()
{
	if (!loadTexture()) {
		std::cerr << "Something went wrong when loading the Texure" << std::endl;
	}

	if (!loadShader()) {
		std::cerr << "Something went wrong when loading the shader" << std::endl;
	}
	

	if (!loadUVBuffer()) {
		std::cerr << "Something went wrong when loading the UV buffer" << std::endl;
	}

	if (!loadVertexBuffer()) {
		std::cerr << "Something went wrong when loading the Vertex buffer" << std::endl;
	}
}

void Sprite::SetDisplayMode(const DisplayMode a_displayMode)
{
	if (m_displayMode == a_displayMode) return;

	m_displayMode = a_displayMode;

	if (m_vertexBuffer.GetId() == 0) return;

	bool succesful = loadVertexBuffer();
	if (!succesful) std::cerr << "Something went wrong when loading the Vertex buffer" << std::endl;
}

bool Sprite::loadTexture()
{
	Texture::defMinFilter = m_minFilterParam;
	Texture::defMagFilter = m_magFilterParam;

	m_texture = ResourceManager::GetTexture(m_resourceID);

	Vec2 textureSize = GetLocalScale();

	if (textureSize.x < 1.f) textureSize.x = static_cast<float>(m_texture.GetWidth());
	if (textureSize.y < 1.f) textureSize.y = static_cast<float>(m_texture.GetHeight());

	SetLocalScale(textureSize);

	if (!m_texture.SuccesfullLoad()) {
		std::cerr << "Error: Could not load texture" << std::endl;
		return false;
	}

	return true;
}

bool Sprite::loadUVBuffer()
{
	m_uvsBuffer = GLBuffer(DisplayMode::TopLeft);

	return m_uvsBuffer.GetId() != 0;
}

Vec2 Sprite::GetSize()
{
	return GetLocalScale();
}

void Sprite::SetSize(const Vec2 a_size)
{
	SetLocalScale(a_size);
}

void Sprite::Flip()
{
	identity.Scale(Vec2(-1.f, 1.f));
}

void Sprite::FlipBack()
{
	if (GetLocalXScale() > 0.f) return;
	Flip();
}

void Sprite::SetShader(const Shader& a_shader)
{
	m_texShader = a_shader;
}

bool Sprite::loadShader()
{
	m_texShader = ResourceManager::GetShader(RS__TEXTURE_VERT, RS__TEXTURE_FRAG);

	return m_texShader.GetProgramID() != 0;
}

bool Sprite::loadVertexBuffer()
{
	m_vertexBuffer = GLBuffer(m_displayMode);

	return m_vertexBuffer.GetId() != 0;
}

void Sprite::SetFilter(GLint a_minFilter, GLint a_magFilter)
{
	if (Texture::NeedsMipmaps(a_magFilter))
	{
		std::cerr << "Warning: Mag filter cannot use mipmaps!" << std::endl;
		return;
	}

	m_minFilterParam = a_minFilter;
	m_magFilterParam = a_magFilter;
}


void Sprite::Display(const Matrix3& a_pojectionMatrix) const
{
	initializeShader();

	setShaderValues(a_pojectionMatrix);

	drawAndDisableArrays();
}

void Sprite::initializeShader() const
{
	glUseProgram(m_texShader.GetProgramID());
}

void Sprite::setShaderValues(const Matrix3& a_pojectionMatrix) const
{
	Matrix modelView = a_pojectionMatrix * GetGlobalMatrix();
	glUniformMatrix3fv(m_texShader.GetMVPMatrix(), 1, GL_FALSE, modelView.GetArray().Data());

	glUniform4f(m_texShader.GetDiffuseColorIndex(),
		diffuseColor.GetRedUnit(),
		diffuseColor.GetGreenUnit(),
		diffuseColor.GetBlueUnit(),
		diffuseColor.GetAlphaUnit()
	);

	glUniformMatrix3fv(m_texShader.GetUVOffsetIndex(), 1, GL_FALSE, m_uvOffset.GetArray().Data());

	glEnableVertexAttribArray(m_texShader.GetVertexIndex());
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(m_texShader.GetVertexIndex(), 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(m_texShader.GetUvIndex());
	glBindBuffer(GL_ARRAY_BUFFER, m_uvsBuffer);
	glVertexAttribPointer(m_texShader.GetUvIndex(), 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetId());
	glUniform1i(m_texShader.GetDiffuseTextureIndex(), 0);
}

void Sprite::drawAndDisableArrays() const
{
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(m_texShader.GetVertexIndex());
	glDisableVertexAttribArray(m_texShader.GetUvIndex());
}

