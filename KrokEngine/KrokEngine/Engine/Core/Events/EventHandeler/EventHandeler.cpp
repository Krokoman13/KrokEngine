#include "EventHandeler.hpp"
#include "../../Input/Input.hpp"
#include "../../Graphics/Core/Window/Window.hpp"
//#include "../../Core/Math/Vec2.hpp"

EventHandeler::EventHandeler()
{
}

void EventHandeler::setKeyDown(int a_buttonValue)
{
	Input::m_keyWentDown[a_buttonValue] = true;
	Input::m_keyIsPressed[a_buttonValue] = true;
}

void EventHandeler::setKeyUp(int a_buttonValue)
{
	Input::m_keyWentUp[a_buttonValue] = true;
	Input::m_keyIsPressed[a_buttonValue] = false;
}

void EventHandeler::setMouseButtonDown(int a_buttonValue)
{
	Input::m_mouseWentDown[a_buttonValue] = true;
	Input::m_mouseIsPressed[a_buttonValue] = true;
}

void EventHandeler::setMouseButtonUp(int a_buttonValue)
{
	Input::m_mouseWentUp[a_buttonValue] = true;
	Input::m_mouseIsPressed[a_buttonValue] = false;
}

void EventHandeler::UpdateEvents()
{
	Input::m_previousMousePosition = Input::m_mousePosition;
	Input::m_mouseMoved = false;

	for (auto& pair : Input::m_keyWentDown) pair.second = false;
	for (auto& pair : Input::m_keyWentUp) pair.second = false;

	for (auto& pair : Input::m_mouseWentDown) pair.second = false;
	for (auto& pair : Input::m_mouseWentUp) pair.second = false;
}

void EventHandeler::SetCallbacks(const Window& a_window)
{
	glfwSetKeyCallback(a_window.Get(), key_callback);
	glfwSetCursorPosCallback(a_window.Get(), cursor_position_callback);
	glfwSetCursorEnterCallback(a_window.Get(), cursor_enter_callback);
	glfwSetMouseButtonCallback(a_window.Get(), mouse_button_callback);
}

void EventHandeler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UNKNOWN) return;

	switch (action)
	{
	case GLFW_RELEASE:
		setKeyUp(key);
		break;

	case GLFW_PRESS:
		setKeyDown(key);
		break;

	default:
		break;
	}
}

void EventHandeler::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Input::m_mousePosition = Vec2((float)xpos, (float)ypos);
	Input::m_mouseMoved = true;
}

void EventHandeler::cursor_enter_callback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		Input::m_mouseInScreen = true;
	}
	else
	{
		Input::m_mouseInScreen = false;
	}
}

void EventHandeler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_KEY_UNKNOWN) return;

	//std::cout << button << std::endl;

	switch (action)
	{
	case GLFW_RELEASE:
		setMouseButtonUp(button);
		break;

	case GLFW_PRESS:
		setMouseButtonDown(button);
		break;

	default:
		break;
	}
}