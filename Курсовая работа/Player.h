#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Player {
private:
		float x, y, w, h, dx, dy, speed = 0;
		bool up = false, down = false, ri = false, le = false, life=true;
		int dir=0, health=3;
		String File;
		Image image;
		Texture texture;
		Sprite sprite;
public:
	Player(String F, float X, float Y, float W, float H, float Imx, float Imy);
	void newPosition(float);
	void NewFrame(float X, float Y, float W = 24, float H = 24);
	void Mov(int, float,bool, bool, bool, bool);
	void setLife(bool);
	int getHealth();
	void setHealth(int);
	void MovKeyboard(float* NowFrame, float time, char** SHMap);
	float getX();
	float getY();
	float getdX();
	float getdY();
	int getDir();
	void animation(float*, float, int, int, int, int, int);
	void death(float*, float);
	void setXY(float,float);
	Sprite getSprite();
	bool getBool(int);
};
class Enemies
{
private:
	float x, y, w, h, dx, dy, speed = 0.07;
	int dir;
	bool flag = true, exit, exitt, unrage=false, life=true;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Enemies(String F, float X, float Y, float W, float H, float Imx, float Imy, int dir, bool exit, bool exitt);
	void newPosition(float);
	void Mov(int, float);
	bool getFlag();
	void setFlag(bool);
	bool getexit();
	void MovGhost(float x, float y, int* kol, float sti, float stj, int k, float time, int* Fr, char** SHMap, int xP, int yP);
	void setexit(bool);
	bool getLife();
	void setLife(bool);
	bool getUnrage();
	void setUnrage(bool);
	void Invert();
	bool getexitt();
	void setexitt(bool);
	void animation(float*, int, float, float, float, int*);
	int getDir();
	Sprite getSprite();
	void NewFrame(float X, float Y, float W = 25, float H = 25);
	float getX();
	float getY();
	void setXY(float, float);
	void Reestablish(float, float, float, int, bool, bool, bool);
	bool Crossing(float, float);
};
struct players
{
	std::string Name;
	std::string Password;
};
struct Record
{
	std::string Name;
	int Score;
	int Level;
};