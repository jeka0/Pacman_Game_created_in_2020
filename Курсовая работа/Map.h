#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Map 
{
private:
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	int Lv = 1;
public:
	int Wmap, Hmap;
	char** SHMap=new char*[35];
	Map(String,int,int);
	void setSprite(int,int,int,int);
	void Reestablish();
	void drawMapSprite(int, int);
	Sprite getSpriteMap();
	int getLev();
	void setLev(int);
};
class health
{
private:
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	health(String A);
	void setSprite(int, int, int, int);
	void setSpritePos(int, int);
	Sprite getSpriteHealth();
};