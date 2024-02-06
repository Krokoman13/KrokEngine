#pragma once
#include <Vector>
#include <Memory>

class Hoverable;
class Clickable;
class Window;
class GameObject;

struct GLFWwindow;

class EventHandeler
{
private:
	static std::vector<Hoverable*> m_hoverables;
	static Hoverable* m_currentHoverable;
	static Clickable* m_currentClickable;

public:
	EventHandeler();

public:
	void UpdateEvents();
	void SetCallbacks(const Window& a_window);

	void Add(const std::vector<GameObject*>& a_newlyAdded);
	void Remove(const std::vector<std::unique_ptr<GameObject>>& a_toDestroy);

	void ClearAll();

private:
	static void setKeyDown(const int a_buttonValue);
	static void setKeyUp(const int a_buttonValue);

	static void setMouseButtonUp(const int a_buttonValue);
	static void setMouseButtonDown(const int a_buttonValue);

	static void key_callback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);
	static void cursor_position_callback(GLFWwindow* a_window, double a_xpos, double a_ypos);
	static void cursor_enter_callback(GLFWwindow* a_window, int a_entered);
	static void mouse_button_callback(GLFWwindow* a_window, int a_button, int a_action, int a_mods);

	void remove(Hoverable* a_renderable);
};

