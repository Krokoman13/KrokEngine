#ifndef _KeyBoard_hpp_
#define _KeyBoard_hpp_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Keyboard
{
public:
    enum class Key
    {
        Unknown = GLFW_KEY_UNKNOWN,           //!< Unhandled key

        Space = GLFW_KEY_SPACE,               //!< The Space key
        Apostrophe = GLFW_KEY_APOSTROPHE,     //!< The ' key
        Comma = GLFW_KEY_COMMA,               //!< The , key
        Minus = GLFW_KEY_MINUS,               //!< The - key
        Period = GLFW_KEY_PERIOD,             //!< The . key
        Slash = GLFW_KEY_SLASH,               //!< The / key

        Key0 = GLFW_KEY_0,      //!< The 0 key
        Key1,                   //!< The 1 key
        Key2,                   //!< The 2 key
        Key3,                   //!< The 3 key
        Key4,                   //!< The 4 key
        Key5,                   //!< The 5 key
        Key6,                   //!< The 6 key
        Key7,                   //!< The 7 key
        Key8,                   //!< The 8 key
        Key9,                   //!< The 9 key

        Semicolon = GLFW_KEY_SEMICOLON,    //!< The ; key
        Equal = GLFW_KEY_EQUAL,        //!< The = key

        A = GLFW_KEY_A,     //!< The A key
        B,                  //!< The B key
        C,                  //!< The C key
        D,                  //!< The D key
        E,                  //!< The E key
        F,                  //!< The F key
        G,                  //!< The G key
        H,                  //!< The H key
        I,                  //!< The I key
        J,                  //!< The J key
        K,                  //!< The K key
        L,                  //!< The L key
        M,                  //!< The M key
        N,                  //!< The N key
        O,                  //!< The O key
        P,                  //!< The P key
        Q,                  //!< The Q key
        R,                  //!< The R key
        S,                  //!< The S key
        T,                  //!< The T key
        U,                  //!< The U key
        V,                  //!< The V key
        W,                  //!< The W key
        X,                  //!< The X key
        Y,                  //!< The Y key
        Z,                  //!< The Z key

        LBracket = GLFW_KEY_LEFT_BRACKET,      //!< The [ key
        Backslash = GLFW_KEY_BACKSLASH,        //!< The \ key
        RBracket = GLFW_KEY_RIGHT_BRACKET,     //!< The ] key
        Grave = GLFW_KEY_GRAVE_ACCENT,         //!< The ` key

        World1 = GLFW_KEY_WORLD_1,     //! non-US #1
        World2 = GLFW_KEY_WORLD_2,     //! non-US #2

        Escape = GLFW_KEY_ESCAPE,       //!< The Escape key
        Enter,        //!< The Enter/Return keys
        Tab,          //!< The Tabulation key
        Backspace,    //!< The Backspace key
        Insert,       //!< The Insert key
        Delete,       //!< The Delete key

        Right = GLFW_KEY_RIGHT,      //!< Right arrow
        Left,                        //!< Left arrow
        Down,                        //!< Down arrow
        Up,                          //!< Up arrow

        PageUp = GLFW_KEY_PAGE_UP,         //!< The Page up key
        PageDown = GLFW_KEY_PAGE_DOWN,     //!< The Page down key
        Home = GLFW_KEY_HOME,              //!< The Home key
        End = GLFW_KEY_END,                //!< The End key
        CapsLock = GLFW_KEY_CAPS_LOCK,     //!< The Caps lock key
        ScrolLock = GLFW_KEY_SCROLL_LOCK,  //!< The Scroll lock key
        NumLock = GLFW_KEY_NUM_LOCK,
        PrintScreen = GLFW_KEY_PRINT_SCREEN,
        Pause = GLFW_KEY_PAUSE,        //!< The Pause key

        F1 = GLFW_KEY_F1,       //!< The F1 key
        F2,                     //!< The F2 key
        F3,                     //!< The F3 key
        F4,                     //!< The F4 key
        F5,                     //!< The F5 key
        F6,                     //!< The F6 key
        F7,                     //!< The F7 key
        F8,                     //!< The F8 key
        F9,                     //!< The F9 key
        F10,                    //!< The F10 key
        F11,                    //!< The F11 key
        F12,                    //!< The F12 key
        F13,                    //!< The F13 key
        F14,                    //!< The F14 key
        F15,                    //!< The F15 key
        F16,                    //!< The F16 key
        F17,                    //!< The F17 key
        F18,                    //!< The F18 key
        F19,                    //!< The F19 key
        F20,                    //!< The F20 key
        F21,                    //!< The F21 key
        F22,                    //!< The F22 key
        F23,                    //!< The F23 key
        F24,                    //!< The F24 key
        F25,                    //!< The F25 key

        Num0 = GLFW_KEY_KP_0,    //!< The Num0 key
        Num1,                    //!< The Num1 key
        Num2,                    //!< The Num2 key
        Num3,                    //!< The Num3 key
        Num4,                    //!< The Num4 key
        Num5,                    //!< The Num5 key
        Num6,                    //!< The Num6 key
        Num7,                    //!< The Num7 key
        Num8,                    //!< The Num8 key
        Num9,                    //!< The Num9 key

        NumDecimal = GLFW_KEY_KP_DECIMAL,
        NumDevide = GLFW_KEY_KP_DIVIDE,
        NumMultiply = GLFW_KEY_KP_MULTIPLY,
        NumSubtracht = GLFW_KEY_KP_SUBTRACT,
        NumAdd = GLFW_KEY_KP_ADD,
        NumEnter = GLFW_KEY_KP_ENTER,
        NumEqual = GLFW_KEY_KP_EQUAL,

        LShift = GLFW_KEY_LEFT_SHIFT,         //!< The left Shift key
        LControl = GLFW_KEY_LEFT_CONTROL,     //!< The left Control key
        LAlt = GLFW_KEY_LEFT_ALT,             //!< The left Alt key
        LSuper = GLFW_KEY_LEFT_SUPER,         //!< The left OS specific key: window (Windows and Linux), apple (macOS), ...

        RControl = GLFW_KEY_RIGHT_CONTROL,   //!< The right Control key
        RShift = GLFW_KEY_RIGHT_SHIFT,       //!< The right Shift key
        RAlt = GLFW_KEY_RIGHT_ALT,           //!< The right Alt key
        RSystem = GLFW_KEY_RIGHT_SUPER,      //!< The right OS specific key: window (Windows and Linux), apple (macOS), ...
        Menu = GLFW_KEY_MENU,                //!< The Menu key
    };
};

#endif // 