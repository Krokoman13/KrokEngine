#include "ImageGameObject.hpp"
#include "../Math/Vec2.hpp"

std::string ImageGameObject::ASSET_PATH = "";
std::string ImageGameObject::FILE_TYPE = ".png";

ImageGameObject::ImageGameObject(std::string name, std::string path, float x, float y, int renderlayer) : GameObject(Vec2(x, y), name)
{
	this->name = name;
	this->_renderLayer = renderlayer;

	if (path[path.size() - 1] == '/')
	{
		path += name;

		if (path.size() < 4) path += FILE_TYPE;
		else if (path[path.size() - 4] != '.') path += FILE_TYPE;;
	}

	loadTexture(path);
	this->_fullpath = path;
	//OnLoad();
}

ImageGameObject::ImageGameObject(std::string name, float x, float y, int renderlayer) : ImageGameObject(name, ASSET_PATH, x, y, renderlayer)
{
}

void ImageGameObject::loadTexture(std::string path)
{
	if (this->_texture.loadFromFile(path))
	{
		std::cout << "Loading : " << path << '\n';
		this->_sprite.setTexture(_texture);

		this->_canRender = true;
		this->_fullpath = path;

		this->_width = (float)_sprite.getTextureRect().width;
		this->_height = (float)_sprite.getTextureRect().height;
		return;
	}
}

void ImageGameObject::SetWidth(float width)
{
	this->SetSize(width, this->_height);
}

void ImageGameObject::SetHeight(float height)
{
	this->SetSize(this->_width, height);
}

void ImageGameObject::SetSize(float pWidth, float pHeight)
{
	if (pWidth < 0 || pHeight < 0) return;

	this->SetLocalScale(pWidth / this->_width, pHeight / this->_height);
}

float ImageGameObject::GetWidth()
{
	return this->_width * this->GetLocalScale().x;
}

float ImageGameObject::GetHeight()
{
	return this->_height * this->GetLocalScale().y;
}

sf::Sprite* ImageGameObject::GetSprite()
{	
	Matrix3 identity = GetGlobalMatrix();

	Vec2 scale = identity.GetScale();
	Vec2 pos = identity.GetPos();
	float rot = identity.GetRotRad();

	if (centered)
	{
		Vec2 diffrence = Vec2(scale.x * _width / 2, scale.y * _height / 2);
		diffrence.RotateRadians(rot);
		pos = pos - diffrence;
	}

	_sprite.setScale(scale.x, scale.y);
	_sprite.setPosition(pos.x, pos.y);
	_sprite.setRotation(Vec2::Rad2Deg(rot));

	return &this->_sprite;
}

void ImageGameObject::CenterImageAround(Vec2 position)
{
	Vec2 globalScale = GetGlobalScale();
	this->SetLocalPosition(position.x - (globalScale.x * _width / 2), position.y - (globalScale.y *_height / 2));
}

std::string ImageGameObject::GetFullPath() const
{
	return this->_fullpath;
}

void ImageGameObject::SetVisible(bool pVisable)
{
	_canRender = pVisable;
}
