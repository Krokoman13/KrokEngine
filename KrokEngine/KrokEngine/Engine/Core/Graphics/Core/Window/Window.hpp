#pragma once
#include <iostream>
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glew.h>

#include "Renderable.hpp"

class Camera
{
private:
	Matrix3 m_ortho;
	float m_currentScale;

	unsigned int m_width;
	unsigned int m_height;

public:
	Matrix3 identity;

	Camera(const unsigned int a_width, const unsigned int a_height) : m_width(a_width), m_height(a_height)
	{
		SetScale(1.f);
		m_ortho.Translate(-Vec2(a_width / 2.f, a_height / 2.f));
	}

	Vec2 GetSize() const { return 2.f / m_ortho.GetScale(); }

	void SetScale(float a_scale)
	{
		const float minimum = 0.00000000001f;
		if (a_scale <= minimum) a_scale = minimum;

		Vec2 currentScale = m_ortho.GetScale();
		m_ortho.Scale(Vec2(1.f / currentScale.x, 1.f / currentScale.y));	//Sets scale to 1.f

		Vec2 normalScale = identity.GetScale();
		std::cout << currentScale << "," << normalScale << std::endl;

		Vec2 nextScale = Vec2(2.f / float(m_width), -2.f / float(m_height)) * a_scale;
		m_ortho.Scale(nextScale);	//Sets scale to desired value;
		m_currentScale = a_scale;
	}

	float GetScale() { return m_currentScale; };

	void Zoom(float a_zoomValue) 
	{  
		identity.Scale(Vec2(a_zoomValue, a_zoomValue));
	};

	void Reset()
	{
		identity = Matrix3();
		SetScale(1.f);
	}

	operator Matrix3() const { return getMatrix(); }

private:
	inline Matrix3 getMatrix() const { return (Matrix3)(identity * m_ortho); }
};

class Window
{
private:
	GLFWwindow* m_pWindow;

	unsigned int m_width;
	unsigned int m_height;

public:	
	Camera camera;

	Window(const char* a_title, const unsigned int a_width, const unsigned int a_height, const bool a_hasVsync = true);
	~Window();

public:
	inline void SetVSync(const bool a_hasVsync);

	bool IsOpen();

	void Draw(const Renderable* a_toRender);
	void Draw(const std::vector<Renderable*>& a_toRender);

	void Display();
	void Clear();

	void PollEvents();

	GLFWwindow* Get() const { return m_pWindow; };
};

