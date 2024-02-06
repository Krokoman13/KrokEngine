#include "EventHandeler.hpp"
#include "../../Input/Input.hpp"
#include "../../Graphics/Core/Window/Window.hpp"
#include "../../../Essentials/GameObject.hpp"

#include "../../UI/Clickable/Clickable.hpp"

std::vector<Hoverable*> EventHandeler::m_hoverables;
Hoverable* EventHandeler::m_currentHoverable = nullptr;
Clickable* EventHandeler::m_currentClickable = nullptr;

EventHandeler::EventHandeler()
{
}

void EventHandeler::ClearAll()
{
	m_hoverables.clear();
	m_currentHoverable = nullptr;
	m_currentClickable = nullptr;
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

	if (m_currentClickable) m_currentClickable->OnClick((Mouse::Button)a_buttonValue);
}

void EventHandeler::setMouseButtonUp(int a_buttonValue)
{
	Input::m_mouseWentUp[a_buttonValue] = true;
	Input::m_mouseIsPressed[a_buttonValue] = false;

	if (m_currentClickable) m_currentClickable->OnRelease((Mouse::Button)a_buttonValue);
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

void EventHandeler::Add(const std::vector<GameObject*>& a_newlyAdded)
{
	for (GameObject* gameObject : a_newlyAdded)
	{
		GameObject* temp = gameObject;
		for (Hoverable* hoverable : temp->GetComponents<Hoverable>()) m_hoverables.push_back(hoverable);
	}
}

void EventHandeler::Remove(const std::vector<std::unique_ptr<GameObject>>& a_toDestroy)
{
	for (unsigned int i = 0; i < a_toDestroy.size(); i++)
	{
		for (Hoverable* hoverable : a_toDestroy[i]->GetComponents<Hoverable>()) remove(hoverable);
	}
}


void EventHandeler::remove(Hoverable* a_hoverable)
{
	for (unsigned int i = 0; i < m_hoverables.size(); i++)
	{
		if (a_hoverable == m_hoverables[i])
		{
			m_hoverables.erase(m_hoverables.begin() + i);
			return;
		}
	}
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
	Hoverable* nextHoverable = nullptr;

	for (int i = (int)m_hoverables.size() - 1; i >= 0; --i) {
		Hoverable* it = m_hoverables[i];

		if (!it->IsActive()) continue;
		if (!it->IsInside(Input::m_mousePosition)) continue;

		if (nextHoverable)
		{
			if (it->GetLayer() > nextHoverable->GetLayer()) nextHoverable = it;
			continue;
		}
			
		nextHoverable = it;
	}

	if (m_currentHoverable == nextHoverable) return;
	if (m_currentHoverable) m_currentHoverable->SetHovering(false);

	m_currentHoverable = nextHoverable;
	m_currentClickable = nullptr;

	if (!m_currentHoverable) return;

	m_currentHoverable->SetHovering(true);
	m_currentClickable = dynamic_cast<Clickable*>(m_currentHoverable);
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
