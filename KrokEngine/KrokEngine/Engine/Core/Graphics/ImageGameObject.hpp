#pragma once
#include "../../Essentials/GameObject.hpp"

class ImageGameObject : public GameObject
{

public:
    ImageGameObject(std::string name, std::string path, Vec2 pPos = Vec2(), int renderlayer = -1);
    ImageGameObject(std::string name, Vec2 pPos = Vec2(), int renderlayer = -1);
    ImageGameObject(std::string name, std::string path, float x, float y, int renderlayer = -1);
    ImageGameObject(std::string name, float x, float y, int renderlayer = -1);

    static std::string ASSET_PATH;
    static std::string FILE_TYPE;

    void SetWidth(float width);
    void SetHeight(float height);
    void SetSize(float width, float height);

    float GetWidth();
    float GetHeight();

    sf::Sprite* GetSprite() override;

    bool centered = false;

    void CenterImageAround(Vec2 position);
    std::string GetFullPath() const;

    void SetVisible(bool pVisable);

private:
    std::string _fullpath;

    float _width = 0;
    float _height = 0;

    sf::Texture _texture;
    sf::Sprite _sprite;

    void loadTexture(std::string path);
};

