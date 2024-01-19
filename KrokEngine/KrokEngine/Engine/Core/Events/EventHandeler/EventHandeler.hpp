
//#include "../Event/Event.hpp"

class Window;
struct GLFWwindow;

class EventHandeler
{
public:
	EventHandeler();

public:
	void UpdateEvents();
	void SetCallbacks(const Window& a_window);

private:
	static void setKeyDown(int a_buttonValue);
	static void setKeyUp(int a_buttonValue);

	static void setMouseButtonUp(int a_buttonValue);
	static void setMouseButtonDown(int a_buttonValue);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void cursor_enter_callback(GLFWwindow* window, int entered);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

