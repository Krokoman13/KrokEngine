#include "ImageGameObject.hpp"
#include "../Math/Vec2.hpp"

std::string ImageGameObject::ASSET_PATH = "";
std::string ImageGameObject::FILE_TYPE = ".png";

ImageGameObject::ImageGameObject(std::string pName, std::string pPath, Vec2 pPos, int pRenderlayer) : GameObject(pPos, pName)
{
	name = pName;
	_renderLayer = pRenderlayer;

	if (pPath[pPath.size() - 1] == '/')
	{
		pPath += pName;

		if (pPath.size() < 4) pPath += FILE_TYPE;
		else if (pPath[pPath.size() - 4] != '.') pPath += FILE_TYPE;;
	}

	loadTexture(pPath);
	_fullpath = pPath;
	//OnLoad();
}

ImageGameObject::ImageGameObject(std::string name, Vec2 pPos, int renderlayer) : ImageGameObject(name, ASSET_PATH, pPos, renderlayer)
{
}

ImageGameObject::ImageGameObject(std::string name, std::string path, float x, float y, int renderlayer) : ImageGameObject(name , path, Vec2(x, y), renderlayer)
{

}

ImageGameObject::ImageGameObject(std::string name, float x, float y, int renderlayer) : ImageGameObject(name, Vec2(x, y), renderlayer)
{
}

void ImageGameObject::loadTexture(std::string pPath)
{
	if (_texture.loadFromFile(pPath))
	{
		std::cout << "Loading : " << pPath << '\n';
		_sprite.setTexture(_texture);

		_canRender = true;
		_fullpath = pPath;

		_width = (float)_sprite.getTextureRect().width;
		_height = (float)_sprite.getTextureRect().height;
		return;
	}
}

void ImageGameObject::SetWidth(float pWidth)
{
	SetLocalScale(pWidth / _width, GetLocalScale().y);
}

void ImageGameObject::SetHeight(float pHeight)
{
	SetLocalScale(GetLocalScale().x, pHeight / _height);
}

void ImageGameObject::SetSize(float pWidth, float pHeight)
{
	if (pWidth < 0 || pHeight < 0) return;

	SetLocalScale(pWidth / _width, pHeight / _height);
}

float ImageGameObject::GetWidth()
{
	return _width * GetLocalScale().x;
}

float ImageGameObject::GetHeight()
{
	return _height * GetLocalScale().y;
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

	return &_sprite;
}

void ImageGameObject::CenterImageAround(Vec2 pPosition)
{
	Vec2 globalScale = GetGlobalScale();
	SetLocalPosition(pPosition.x - (globalScale.x * _width / 2), pPosition.y - (globalScale.y *_height / 2));
}

std::string ImageGameObject::GetFullPath() const
{
	return _fullpath;
}

void ImageGameObject::SetVisible(bool pVisable)
{
	_canRender = pVisable;
}
