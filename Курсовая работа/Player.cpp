#include "Player.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
using namespace sf;
Player::Player(String F, float X, float Y, float W, float H, float Imx, float Imy)
{
	File = F;
	x = X; y = Y;
	w = W; h = H;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(Color(0,0,0));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(Imx, Imy, w, h));
}
void Player::newPosition(float time)
{
	switch (dir)
	{
	case 0: dx = -speed; dy = 0; break;
	case 1: dx = speed; dy = 0; break;
	case 2: dx = 0; dy = speed; break;
	case 3: dx = 0; dy = -speed; break;
	}
	x = x + dx * time;
	y = y + dy * time;
}
void Player::NewFrame(float X, float Y, float W, float H)
{
	sprite.setTextureRect(IntRect(X, Y, W, H));
}
void Player::Mov(int DIR, float SPEED, bool Up, bool Down, bool Ri, bool Le)
{
	dir = DIR; speed = SPEED; up = Up; down = Down; ri = Ri; le = Le;
}
bool Player::getBool(int A)
{
	bool S;
	switch (A) 
	{
	case 0: S = up; break;
	case 1: S = down; break;
	case 2: S = ri; break;
	case 3: S = le; break;
	case 4: S = life; break;
	}
	return S;
}
void Player::setHealth(int A){health = A;}
Sprite Player::getSprite(){return sprite;}
float Player::getX(){return x;}
float Player::getY(){return y;}
float Player::getdX(){return dx;}
float Player::getdY(){return dy;}
int Player::getHealth() { return health; }
void Player::setXY(float X, float Y)
{
	x = X; y = Y;
	speed = 0;
	sprite.setPosition(x, y);
}
int Player::getDir(){return dir;}
void Player::setLife(bool A){life = A;}
void Player::death(float* NowFrame, float time)
{
	Mov(0, 0, 0, 0, 0, 0);
	*NowFrame = *NowFrame + 0.01 * time;
	if (int(*NowFrame) == 0) NewFrame(326, 32); else
		if (int(*NowFrame) == 1 || int(*NowFrame) == 2) NewFrame(27 - 25 * (int(*NowFrame) - 1), 52); else
			NewFrame(77 + 25 * (int(*NowFrame) - 3), 0);
}
void Player::animation(float* NowFrame, float time, int a, int b ,int c, int d, int e)
{
	*NowFrame = *NowFrame + 0.01 * time;
	if (*NowFrame >= 3)*NowFrame = *NowFrame - 3;
	if (int(*NowFrame) == 0 || int(*NowFrame) == 1) NewFrame(2 + 25 * int(*NowFrame), a); else
		NewFrame(b, c, d, e);
}
void Player::MovKeyboard(float* NowFrame, float time, char** SHMap)
{

	float x = getX(), y = getY();
	int p = (x + 23) / 24, f = (y + 24) / 30, s = (x - 1) / 24, t = (y - 6) / 30, z = (y + 25) / 30, r = (y - 5) / 30, h = (x - 0) / 24, c = (x + 24) / 24;
	if ((Keyboard::isKeyPressed(Keyboard::Left)) || getBool(3))
	{
		if ((SHMap[r][s] == '*' || SHMap[r][s] == '/' || SHMap[r][s] == '!' || SHMap[r][s] == '~') && (SHMap[f][s] == '*' || SHMap[f][s] == '/' || SHMap[f][s] == '!' || SHMap[f][s] == '~'))
		{
			Mov(0, 0.065, 0, 0, 0, 1);
			animation(NowFrame, time, 25, 76, 0, -24,24);
		}
	}
	if ((Keyboard::isKeyPressed(Keyboard::Right)) || getBool(2))
	{
		if ((SHMap[r][c] == '*' || SHMap[r][c] == '/' || SHMap[r][c] == '!' || SHMap[r][c] == '~') && (SHMap[f][c] == '*' || SHMap[f][c] == '/' || SHMap[f][c] == '!' || SHMap[f][c] == '~'))
		{
			Mov(1, 0.065, 0, 0, 1, 0);
			animation(NowFrame, time, 0, 52, 0, 24, 24);
		}
	}
	if ((Keyboard::isKeyPressed(Keyboard::Up)) || getBool(0))
	{
		if ((SHMap[t][h] == '*' || SHMap[t][h] == '/' || SHMap[t][h] == '!' || SHMap[t][h] == '~') && (SHMap[t][p] == '*' || SHMap[t][p] == '/' || SHMap[t][p] == '!' || SHMap[t][p] == '~'))
		{
			Mov(3, 0.065, 1, 0, 0, 0);
			animation(NowFrame, time, 52, 326, 32, 24, 24);
		}
	}
	if ((Keyboard::isKeyPressed(Keyboard::Down)) || getBool(1))
	{
		if ((SHMap[z][h] == '*' || SHMap[z][h] == '/' || SHMap[z][h] == '!' || SHMap[z][h] == '~') && (SHMap[z][p] == '*' || SHMap[z][p] == '/' || SHMap[z][p] == '!' || SHMap[z][p] == '~'))
		{
			Mov(2, 0.065, 0, 1, 0, 0);
			animation(NowFrame, time, 76, 349, 55, -24, -24);
		}
	}
}
Enemies::Enemies(String F, float X, float Y, float W, float H, float Imx, float Imy, int Dir, bool Exit, bool Exitt)
{
	File = F; dir = Dir; exit = Exit; exitt = Exitt;
	x = X; y = Y;
	w = W; h = H;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(Color(0, 0, 0));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(Imx, Imy, w, h));
	sprite.setPosition(x, y);
}
void Enemies::newPosition(float time)
{
	switch (dir)
	{
	case 0: dx = -speed; dy = 0; break;
	case 1: dx = speed; dy = 0; break;
	case 2: dx = 0; dy = speed; break;
	case 3: dx = 0; dy = -speed; break;
	case 4: dx = 0; dy = 0; break;
	}
	x = x + dx * time;
	y = y + dy * time;
	sprite.setPosition(x, y);
}
void Enemies::Mov(int DIR, float SPEED)
{
	dir = DIR; speed = SPEED;
}
Sprite Enemies::getSprite() { return sprite; }
float Enemies::getX() { return x; }
float Enemies::getY() { return y; }
int Enemies::getDir() { return dir; }
void Enemies::setXY(float X, float Y)
{
	x = X; y = Y;
	speed = 0;
	sprite.setPosition(x, y);
}
void Enemies::animation(float* NowFrame, int dir, float y, float time, float timeR, int* FR)
{
	if (life)
	{
		if (!unrage)
		{
			int x = 152;
			switch (dir)
			{
			case 0: x = 52; break;
			case 1: x = 2; break;
			case 2: x = 152; break;
			case 3: x = 102; break;
			}
			*NowFrame = *NowFrame + 0.01 * time;
			if (*NowFrame >= 2)*NowFrame = *NowFrame - 2;
			if (int(*NowFrame) == 0 || int(*NowFrame) == 1) sprite.setTextureRect(IntRect(x + 25 * int(*NowFrame), y, 25, 25));
		}
		else
		{
			int timeT = timeR;
			int x;
			*NowFrame = *NowFrame + 0.01 * time;
			if (timeT <= 6 || (timeT > 6 && *FR == 0))x = 201; else x = 251;
			if (*NowFrame >= 2) { *NowFrame = *NowFrame - 2; *FR = *FR+1; }
			if (*FR >= 2)*FR -= 2;
			if (int(*NowFrame) == 0 || int(*NowFrame) == 1) sprite.setTextureRect(IntRect(x + 25 * int(*NowFrame), 101, 25, 25));
			if (timeT > 8) {unrage = false; *FR = 0;}
		}
	}
	else
	{
		int x = 152;
		switch (dir)
		{
		case 0: x = 52; break;
		case 1: x = 2; break;
		case 2: x = 152; break;
		case 3: x = 102; break;
		}
		*NowFrame = *NowFrame + 0.01 * time;
		if (*NowFrame >= 2)*NowFrame = *NowFrame - 2;
		if (int(*NowFrame) == 0 || int(*NowFrame) == 1) sprite.setTextureRect(IntRect(x + 25 * int(*NowFrame), 250, 25, 25));
	}
}
void Enemies::NewFrame(float X, float Y, float W, float H)
{
	sprite.setTextureRect(IntRect(X, Y, W, H));
}
bool Enemies::getFlag() { return flag; }
void Enemies::setFlag(bool A) {flag=A;}
void Enemies::MovGhost(float x, float y, int* kol, float sti, float stj, int k, float time, int* Fr, char** SHMap, int xP, int yP)
{
	int i = x / 24, j = (y - 4) / 30, i1 = (x + 23) / 24, j1 = (y + 25) / 30, isr = (x + 12) / 24, jsr = (y + 12) / 30, dir = 0, min = 2594, pi = (xP + 12) / 24, pj = (yP + 12) / 30, olddir =  getDir(), is = (312.9) / 24, js = (334) / 30, timee = time;
	if (SHMap[jsr][isr] != '!')
	{
		if ((getFlag() || !((timee - (k - 1) * 5 + 2) % 8)) && ! getexit()) { pi = (sti + 12) / 24, pj = (stj + 12) / 30; }
		if (! getLife()) { pi = is, pj = js; }
		if ( getexit() &&  getexitt() && time >= (k - 1) * 5 + 2) Mov(3 - k, 0.06);
		if (i == i1 && j == j1 && i == is && j == js && time >= (k - 1) * 5 + 2 || ( getexit() && ! getexitt() && time >= (k - 1) * 5 + 2)) { pi = (314 + 12) / 24, pj = (274 + 12) / 30;  Mov(3, 0.06);  setexitt(false); if (! getLife()) {  setLife(true);  setexit(true);  setUnrage(false); *Fr = 0; } }
		if (i == pi && j == pj &&  getexit()) {  setexit(false); }
		else if (i == pi && j == pj) setFlag(false);
		if (! getexit())
		{
			if (i == i1 && j == j1 && *kol >= 15)
			{
				if (!( getUnrage()) || (! getLife() &&  getUnrage()))
				{
					if ( getDir() != 3 && (SHMap[jsr + 1][isr] == '*' || SHMap[jsr + 1][isr] == '/' || SHMap[jsr + 1][isr] == '!' || SHMap[jsr + 1][isr] == '~' || (SHMap[jsr + 1][isr] == '-' && ! getLife())) && (pow(pi - isr, 2) + pow(pj - (jsr + 1), 2) < min)) { dir = 2; min = pow(pi - isr, 2) + pow(pj - (jsr + 1), 2); }
					if ( getDir() != 2 && (SHMap[jsr - 1][isr] == '*' || SHMap[jsr - 1][isr] == '/' || SHMap[jsr - 1][isr] == '!' || SHMap[jsr - 1][isr] == '~' || (SHMap[jsr - 1][isr] == '-' && ! getLife())) && (pow(pi - isr, 2) + pow(pj - (jsr - 1), 2) < min)) { dir = 3; min = pow(pi - isr, 2) + pow(pj - (jsr - 1), 2); }
					if ( getDir() != 1 && (SHMap[jsr][isr - 1] == '*' || SHMap[jsr][isr - 1] == '/' || SHMap[jsr][isr - 1] == '!' || SHMap[jsr][isr - 1] == '~' || (SHMap[jsr][isr - 1] == '-' && ! getLife())) && (pow(pi - (isr - 1), 2) + pow(pj - jsr, 2) < min)) { dir = 0; min = pow(pi - (isr - 1), 2) + pow(pj - jsr, 2); }
					if ( getDir() != 0 && (SHMap[jsr][isr + 1] == '*' || SHMap[jsr][isr + 1] == '/' || SHMap[jsr][isr + 1] == '!' || SHMap[jsr][isr + 1] == '~' || (SHMap[jsr][isr + 1] == '-' && ! getLife())) && (pow(pi - (isr + 1), 2) + pow(pj - jsr, 2) < min)) { dir = 1; min = pow(pi - (isr + 1), 2) + pow(pj - jsr, 2); }
					if (olddir != dir) *kol = 0;
					if (! getLife()) Mov(dir, 0.2); else  Mov(dir, 0.06);
				}
				else
				{
					if ( getDir() != 3 && (SHMap[jsr + 1][isr] == '*' || SHMap[jsr + 1][isr] == '/' || SHMap[jsr + 1][isr] == '!' || SHMap[jsr + 1][isr] == '~') && (pow(pi - isr, 2) + pow(pj - jsr + 1, 2) < min)) { dir = 2; min = pow(pi - isr, 2) + pow(pj - jsr + 1, 2); }
					if ( getDir() != 2 && (SHMap[jsr - 1][isr] == '*' || SHMap[jsr - 1][isr] == '/' || SHMap[jsr - 1][isr] == '!' || SHMap[jsr - 1][isr] == '~') && (pow(pi - isr, 2) + pow(pj - jsr - 1, 2) < min)) { dir = 3; min = pow(pi - isr, 2) + pow(pj - jsr - 1, 2); }
					if ( getDir() != 1 && (SHMap[jsr][isr - 1] == '*' || SHMap[jsr][isr - 1] == '/' || SHMap[jsr][isr - 1] == '!' || SHMap[jsr][isr - 1] == '~') && (pow(pi - isr - 1, 2) + pow(pj - jsr, 2) < min)) { dir = 0; min = pow(pi - isr - 1, 2) + pow(pj - jsr, 2); }
					if ( getDir() != 0 && (SHMap[jsr][isr + 1] == '*' || SHMap[jsr][isr + 1] == '/' || SHMap[jsr][isr + 1] == '!' || SHMap[jsr][isr + 1] == '~') && (pow(pi - isr + 1, 2) + pow(pj - jsr, 2) < min)) { dir = 1; min = pow(pi - isr + 1, 2) + pow(pj - jsr, 2); }
					if (olddir != dir) *kol = 0;
					 Mov(dir, 0.04);
				}
			}
		}
	}
	*kol = *kol + 1;
	if (SHMap[jsr][isr] == '!')
	{
		if ((i1 <= 0 || x <= 5) &&  getDir() != 1)
		{
			x = 620;
			*kol = 0;
			 setXY(x, y);
			 Mov(0, 0.06);
		}
		else if (i >= 26 &&  getDir() != 0)
		{
			x = 5;
			*kol = 0;
			 setXY(x, y);
			 Mov(1, 0.06);
		}
	}
}
void Enemies::Reestablish(float x, float y, float p, int dir, bool Exit, bool Exitt, bool Un)
{
	setXY(x, y);
	NewFrame(2, p);
	Mov(dir, 0.06);
	setFlag(true);
	exit = Exit; exitt = Exitt; unrage = Un; life = true;
}
bool Enemies::Crossing(float x, float y) { return (getX()-6 <= x + 12 && getY()-6 <= y + 12 && (getX() + 31) >= x + 12 && (getY() + 31) >= y + 12); }
bool Enemies::getexit() { return exit; }
void Enemies::setexit(bool Exit){exit = Exit;}
bool Enemies::getexitt() { return exitt; }
void Enemies::setexitt(bool Exit) { exitt = Exit; }
bool Enemies::getUnrage() { return unrage; }
void Enemies::setUnrage(bool A) { unrage = A; }
bool Enemies::getLife() { return life; }
void Enemies::setLife(bool A) { life = A; }
void Enemies::Invert()
{
	switch (dir)
	{
	   case 0: dir = 1; break;
	   case 1: dir = 0; break;
	   case 2: dir = 3; break;
	   case 3: dir = 2; break;
	}
}