
class Mouse
{
public:
    enum class Button
    {
        Left = 0,   //!< The left mouse button
        Right,  //!< The right mouse button
        Middle, //!< The middle (wheel) mouse button
        Extra1, //!< The first extra mouse button
        Extra2  //!< The second extra mouse button
    };

    static constexpr unsigned int ButtonCount{ static_cast<unsigned int>(Button::Extra2) + 1 };
};