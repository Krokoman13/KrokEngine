#pragma once
#include "../window/Renderable.hpp"

#include "../Texture/Texture.hpp"
#include "TextureShader.hpp"

#include "../glBuffer/GLBuffer.hpp"
#include "../../Clolor.hpp"

class Sprite : public Renderable
{
protected:
	const unsigned int m_resourceID;

	Texture m_texture;

	Matrix3 m_uvOffset;

	TextureShader m_texShader;

	GLBuffer m_vertexBuffer;
	GLBuffer m_uvsBuffer;

	GLint m_minFilterParam;
	GLint m_magFilterParam;
	
	DisplayMode m_displayMode;

public:
	Color diffuseColor = Color(255, 255, 255);

public:
	Sprite(const unsigned int a_resourceID);
	virtual ~Sprite();

public:
	inline static GLint defaultMinFilterParam = GL_LINEAR_MIPMAP_LINEAR;
	inline static GLint defaultMagFilterParam = GL_LINEAR;
	inline static DisplayMode defaultDisplayMode = DisplayMode::Center;

	virtual void OnLoad() override;
	virtual void Display(const Matrix3& a_pojectionMatrix) const override;
	void SetFilter(GLint a_minFilter, GLint a_magFilter);
	void SetDisplayMode(const DisplayMode a_displayMode);
	Vec2 GetSize();
	void SetSize(const Vec2 a_size);
	
	void Flip();
	void FlipBack();

protected:
	bool loadTexture();
	virtual bool loadShader();
	virtual bool loadUVBuffer();
	bool loadVertexBuffer();

	virtual void initializeShader() const;
	virtual void setShaderValues(const Matrix3& a_pojectionMatrix) const;
	virtual void drawAndDisableArrays() const;

};