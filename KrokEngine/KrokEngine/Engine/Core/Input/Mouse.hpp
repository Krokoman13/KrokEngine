#ifndef _Mouse_hpp_
#define _Mouse_hpp_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Mouse
{
public:
    enum class Button
    {
        Left = GLFW_MOUSE_BUTTON_LEFT,          //!< The left mouse button
        Right = GLFW_MOUSE_BUTTON_RIGHT,        //!< The right mouse button
        Middle = GLFW_MOUSE_BUTTON_MIDDLE,      //!< The middle (wheel) mouse button

        Extra1 = GLFW_MOUSE_BUTTON_4,           //!< The first extra mouse button
        Extra2 = GLFW_MOUSE_BUTTON_5,           //!< The second extra mouse button
        Extra3 = GLFW_MOUSE_BUTTON_6,           //!< The second extra mouse button
        Extra4 = GLFW_MOUSE_BUTTON_7,           //!< The second extra mouse button
        Extra5 = GLFW_MOUSE_BUTTON_8,           //!< The second extra mouse button
    };
};

#endif