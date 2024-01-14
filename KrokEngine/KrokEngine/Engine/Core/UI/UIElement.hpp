#pragma once
#include <vector>
#include <string>

class UI;

class UIElement
{
public:
    UIElement(std::string name, std::string path, float x = 0, float y = 0);
    UIElement(std::string name, float x = 0, float y = 0);
    UIElement(std::string name, float x, float y, float width, float heigth);
    virtual ~UIElement();

    std::string name;
    float x;
    float y;

    static std::string ASSET_PATH;
    static std::string FILE_TYPE;
    static Font DEFAULT_FONT;

    void SetText(const std::string text, unsigned int textSize = 24, const Uint32 style = Text::Style::Regular, const Color fillColor = Color::Black);
    void SetText(const std::string text, const Font& font, unsigned int textSize = 24, const Uint32 style = Text::Style::Regular, const Color fillColor = Color::Black);

    void SetWidth(float width);
    void SetHeight(float height);
    void SetSize(float width, float height);
    void SetScale(float xScale, float yScale);
    void SetScale(float uniformScale);

    float GetWidth();
    float GetHeight();

    void SetUI(UI* ui);
    void ClearUI();

    void SetVisible(bool visible);
    bool IsVisible();

    std::vector<Drawable*> GetDrawables();

protected:
    virtual Sprite* getSprite();

    std::string _fullpath;
    UI* _ui;

private:
    Texture _texture;
    Sprite _sprite;
    Text _sfTtext;

    void loadTexture(std::string path);

    float _originalWidth = 0;
    float _originalHeight = 0;
    unsigned int _originalTextSize;

    float _xScale = 1;
    float _yScale = 1;

    bool visible = true;
};

