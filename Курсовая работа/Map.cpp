#include "Map.h"
#include <SFML/Graphics.hpp>
#include <fstream>
using namespace sf;
Map::Map(String File, int WMAP, int HMAP)
{
	std::ifstream fin("Maps/Map.txt");
    for (int i = 0; i < 35; i++)
    {
        SHMap[i] = new char[37];
    }
	Wmap = WMAP; Hmap = HMAP;
	image.loadFromFile("images/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	for (int i = 0; i < Hmap; i++)
	{
		fin >> SHMap[i];
	}
    fin.close();
}
void Map::setSprite(int A, int B, int C, int D)
{
	sprite.setTextureRect(IntRect(A, B, C, D));
}
Sprite Map::getSpriteMap(){return sprite;}
void  Map::drawMapSprite(int i, int j)
{
    if (SHMap[i][j] == '~' || SHMap[i][j] == '*' || SHMap[i][j] == '-')
    {
        sprite.setColor(Color::White);
        if (SHMap[i][j] == '-') setSprite(250, 222, 24, 30); else
            if (SHMap[i][j] == '*') setSprite(115, 90, 24, 30); else
                if (SHMap[i][j] == '~') setSprite(23, 53, 24, 30);
    }
    else
    {
        if (Lv == 1)sprite.setColor(Color(29, 87, 175)); else
            if(Lv == 2)sprite.setColor(Color(153,6,6));else
                if (Lv == 3)sprite.setColor(Color(49, 148, 35));
        if (SHMap[i][j] == '0') setSprite(1, 31, 24, 30); else
        if (SHMap[i][j] == 'n') setSprite(144, 122, 24, 30); else
        if (SHMap[i][j] == 'N') setSprite(144, 147, 24, 30); else
        if (SHMap[i][j] == '_') setSprite(67, 35, 24, 30); else
        if (SHMap[i][j] == '+') setSprite(67, 65, 24, 30); else
        if (SHMap[i][j] == 'q') setSprite(50, 35, 24, 30); else
        if (SHMap[i][j] == 'w') setSprite(50, 65, 24, 30); else
        if (SHMap[i][j] == 'e') setSprite(76, 35, -24, 30); else
        if (SHMap[i][j] == '#') setSprite(50, 205, 24, 30); else
        if (SHMap[i][j] == '$') setSprite(76, 205, -24, 30); else
        if (SHMap[i][j] == 'r') setSprite(76, 65, -24, 30); else
        if (SHMap[i][j] == 'u') setSprite(144, 152, 24, -30); else
        if (SHMap[i][j] == '}') setSprite(144, 172, 24, 30); else
        if (SHMap[i][j] == '7') setSprite(88, 395, 24, 30); else
        if (SHMap[i][j] == 'R') setSprite(88, 428, 24, -30); else
        if (SHMap[i][j] == 'L') setSprite(113, 395, -24, 30); else
        if (SHMap[i][j] == 'D') setSprite(113, 428, -24, -30); else
        if (SHMap[i][j] == '{') setSprite(169, 172, -24, 30); else
        if (SHMap[i][j] == '/' || SHMap[i][j] == '!') setSprite(15, 200, 24, 30); else
        if (SHMap[i][j] == '1') setSprite(1, 342, 24, 30); else
        if (SHMap[i][j] == '2') setSprite(1, 166, 24, 30); else
        if (SHMap[i][j] == '(') setSprite(50, 117, 24, 30); else
        if (SHMap[i][j] == 'T') setSprite(255, 117, 24, 30); else
        if (SHMap[i][j] == 'V') setSprite(255, 150, 24, -30); else
        if (SHMap[i][j] == ')') setSprite(75, 117, -24, 30); else
        if (SHMap[i][j] == '=') setSprite(66, 117, 24, 30); else
        if (SHMap[i][j] == '3') setSprite(94, 342, 24, 30); else
        if (SHMap[i][j] == '^') setSprite(454, 313, 43, 32); else
        if (SHMap[i][j] == '&') setSprite(477, 313, -43, 32); else
        if (SHMap[i][j] == '4') setSprite(94, 166, 24, 30); else
        if (SHMap[i][j] == '[') setSprite(1, 450, 24, 30); else
        if (SHMap[i][j] == ']') setSprite(24, 450, -24, 30); else
        if (SHMap[i][j] == '|') setSprite(474, 200, 24, 30); else
        if (SHMap[i][j] == 'z') setSprite(25, 555, 24, 30);
    }
     sprite.setPosition(j * 24, i * 30);
}
void Map::Reestablish()
{
    std::ifstream fin;
    if (Lv >= 4)Lv -= 3;
    if(Lv == 1) fin.open("Maps/Map.txt");
    if (Lv == 2) fin.open("Maps/Map2.txt");
    if (Lv == 3) fin.open("Maps/Map3.txt");
    for (int i = 0; i < Hmap; i++)
    {
        fin >> SHMap[i];
    }
    fin.close();
}
int Map::getLev() { return Lv; }
void Map::setLev(int A) { Lv = A; }
health::health(String A)
{
	image.loadFromFile("images/" + A);
	image.createMaskFromColor(Color(0, 0, 0));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}
void health::setSprite(int A, int B, int C, int D)
{
	sprite.setTextureRect(IntRect(A, B, C, D));
}
void health::setSpritePos(int A, int B)
{
	sprite.setPosition(A, B);
}
Sprite health::getSpriteHealth(){return sprite;}
