#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Map.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace sf;
RenderWindow window(VideoMode(600, 720), "Pac-Man", Style::Titlebar| Style::Close);
View wind;
Player Pacman("Pacman.png", 314, 515, 24.0, 24.0, 52.0, 0.0);
Enemies Ghost("Pacman.png", 314, 274, 25.0, 25.0, 2.0, 101.0, 0, false, false);
Enemies Ghost2("Pacman.png", 312.9, 334, 25.0, 25.0, 2.0, 126.0, 4, true, false);
Enemies Ghost3("Pacman.png", 264.9, 334, 25.0, 25.0, 2.0, 151.0, 4, true, true);
Enemies Ghost4("Pacman.png", 360.9, 334, 25.0, 25.0, 2.0, 176.0, 4, true, true);
std::string namen;
Music music;
Map map("Map.jpg", 35, 25);
health Health("Pacman.png");
bool flag = true, click =true, ESC=false, Fmenu=false;
void drawHealth();
void Interaction(float, float, Enemies*, float*, int*, Sound* sound);
void PositionPacman(float,int*, float*, float*, Sound*, int*);
void drawMap(bool*, float*);
void Reestablish(float*);
void EnterWindow(Sprite, Text,Text, Text, Text, Music*,bool*);
bool Enter(String, String);
bool Registration(String, String);
void Records(int, int);
void Record_List(Sprite, Text, Text, Text, Text, Music*);
void Menu()
{
    wind.reset(FloatRect(24, 0, 600, 720));
    Music musicMenu;
    musicMenu.openFromFile("Music/MusicMenu.ogg");
    musicMenu.setVolume(15);
    musicMenu.play();
    musicMenu.setLoop(true);
    Font font;
    font.loadFromFile("Bender-Bold.ttf");
    Text text1("", font, 30), text2("", font, 30), text3("", font, 30), text4("", font, 30), TextName("", font, 30);
    TextName.setFillColor(Color::White); TextName.setStyle(Text::Bold); TextName.setPosition(290, 630);
    text1.setFillColor(Color(192,120,56)); text1.setStyle(Text::Bold); text1.setPosition(294, 430); text1.setString("Play");
    text4.setFillColor(Color(192, 120, 56)); text4.setStyle(Text::Bold); text4.setPosition(244, 480); text4.setString("Record list");
    text3.setFillColor(Color(192, 120, 56)); text3.setStyle(Text::Bold); text3.setPosition(234, 530); text3.setString("Change user");
    text2.setFillColor(Color(192, 120, 56)); text2.setStyle(Text::Bold); text2.setPosition(294, 580); text2.setString("Exit");
    Texture menuTexture1;
    menuTexture1.loadFromFile("images/pacman1.png");
    Sprite menu1(menuTexture1);
    bool isMenu = true;
    int menuNum = 0;
    Clock clock;
    menu1.setPosition(24, 0);
    while (isMenu)
    {
        menuNum = 0;
        TextName.setString(namen);
        text1.setFillColor(Color(192, 120, 56));
        text3.setFillColor(Color(192, 120, 56));
        text4.setFillColor(Color(192, 120, 56));
        text2.setFillColor(Color(192, 120, 56));
        menuNum = 0;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                musicMenu.stop(); window.close();
            }
        }
        window.setView(wind);
        window.clear();
        if (IntRect(270, 430, 60, 33).contains(Mouse::getPosition(window))) { text1.setFillColor(Color::Yellow); menuNum = 1; }else
        if (IntRect(209, 533, 190, 33).contains(Mouse::getPosition(window))) { text3.setFillColor(Color::Yellow); menuNum = 2; }else
        if (IntRect(219, 483, 170, 33).contains(Mouse::getPosition(window))) { text4.setFillColor(Color::Yellow); menuNum = 4; }else
        if (IntRect(270, 580, 60, 33).contains(Mouse::getPosition(window))) { text2.setFillColor(Color::Yellow); menuNum = 3; }else
            menuNum = 0;
        if (Mouse::isButtonPressed(Mouse::Left) && click)
        {
            click = false;
            if (menuNum == 1) isMenu = false;
            if (menuNum == 2) EnterWindow(menu1, text1, text3, text4, text2, &musicMenu, &flag);
            if (menuNum == 4) Record_List(menu1, text1, text3, text4, text2, &musicMenu);
            if (menuNum == 3) { window.close(); isMenu = false; }
        }
        if (!(Mouse::isButtonPressed(Mouse::Left)))click = true;
        window.draw(menu1);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(TextName);
        window.display();
        if(flag)EnterWindow(menu1, text1,text3,text4, text2, &musicMenu,&flag);
    }
}
void Record_List(Sprite menu1, Text text1, Text text3, Text text4, Text text2, Music* musicMenu)
{
    Font font;
    font.loadFromFile("Bender-Bold.ttf");
    Text text("", font, 30), text11("", font, 30), text22("", font, 30), text33("", font, 30), textTOP("", font, 30), textt("", font, 30);
    textTOP.setFillColor(Color::White); textTOP.setStyle(Text::Bold); textTOP.setPosition(290, 164); textTOP.setString("TOP 7:");
    textt.setStyle(Text::Bold); textt.setPosition(290, 510); textt.setString("Menu");
    text11.setFillColor(Color::White); text11.setStyle(Text::Bold);
    text22.setFillColor(Color::White); text22.setStyle(Text::Bold);
    text33.setFillColor(Color::White); text33.setStyle(Text::Bold);
    Image image;
    image.loadFromFile("images/pacman4.png");
    image.createMaskFromColor(Color::Red);
    Texture menuTexture1;
    menuTexture1.loadFromImage(image);
    Sprite List(menuTexture1);
    List.setPosition(159, 134);
    Record A, B;
    std::ifstream fin("Records.txt");
    int kol = 0, menuNum = 0;
    fin >> B.Name >> B.Score >> B.Level;
    while (!(B.Name == A.Name && A.Score == B.Score && A.Level == B.Level))
    {
        kol++;
        A.Name = B.Name;
        A.Score = B.Score;
        A.Level = B.Level;
        fin >> B.Name >> B.Score >> B.Level;
    }
    fin.close();
    std::vector <Record> Mas(kol);
    fin.open("Records.txt");
    for (int i = 0; i < kol; i++)
    {
        fin >> Mas[i].Name >> Mas[i].Score >> Mas[i].Level;
    }
    fin.close();
    bool isList=true;
    while (isList)
    {
        textt.setFillColor(Color(192, 120, 56));
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {musicMenu->stop(); window.close(); isList = false;}
        }
        if (IntRect(260, 510, 90, 33).contains(Mouse::getPosition(window))) { textt.setFillColor(Color::Yellow); menuNum = 1; }
        else
            menuNum = 0;
        if (Mouse::isButtonPressed(Mouse::Left) && click)
        {
            click = false;
            if (menuNum == 1) isList = false;
        }
        if (!(Mouse::isButtonPressed(Mouse::Left)))click = true;
        window.clear();
        window.draw(menu1);
        window.draw(text1);
        window.draw(text4);
        window.draw(text3);
        window.draw(text2);
        window.draw(List);
        window.draw(textTOP);
        window.draw(textt);
        for (int i=0; i < kol; i++)
        {
            std::ostringstream ScoreString;
            std::ostringstream ScoreStringLev;
            std::ostringstream StrInd;
            StrInd << i + 1;
            text11.setPosition(180, 224 + 40 * i);
            text11.setString(StrInd.str() + ": " +Mas[i].Name);
            text22.setPosition(346, 224 + 40 * i);
            ScoreString << Mas[i].Score;
            text33.setPosition(438, 224 + 40 * i);
            ScoreStringLev << Mas[i].Level;
            text22.setString(ScoreString.str());
            text33.setString(ScoreStringLev.str());
            window.draw(text11);
            window.draw(text22);
            window.draw(text33);
            ScoreString.clear();
            ScoreStringLev.clear();
        }
        window.display();
    }
}
void EnterWindow(Sprite menu1,Text text1,Text text3, Text text4, Text text2, Music* musicMenu, bool* flag)
{
    Font font;
    font.loadFromFile("Bender-Bold.ttf");
    Text text("", font, 30), textt("", font, 30), textE("", font, 30), textR("", font, 30), textN("", font, 30), textP("", font, 30), ERR("", font, 30);
    ERR.setFillColor(Color::Red); ERR.setStyle(Text::Bold); ERR.setPosition(290, 500);
    textE.setFillColor(Color(192, 120, 56)); textE.setStyle(Text::Bold); textE.setPosition(170, 465); textE.setString("Enter");
    textR.setFillColor(Color(192, 120, 56)); textR.setStyle(Text::Bold); textR.setPosition(305, 465); textR.setString("Registration");
    textN.setFillColor(Color::White); textN.setStyle(Text::Bold); textN.setPosition(220, 350); textN.setString("Name:");
    textP.setFillColor(Color::White); textP.setStyle(Text::Bold); textP.setPosition(160, 415); textP.setString("Password:");
    String TEXT, TEXTT;
    int indx = -1, indx2 = -1, newstring=0, newstringi = 0, menuNum=0;
    text.setFillColor(Color::White); text.setStyle(Text::Bold); text.setPosition(330, 345);
    textt.setFillColor(Color::White); textt.setStyle(Text::Bold); textt.setPosition(330, 410);
    Image image, image2;
    image2.loadFromFile("images/pacman3.png"); image2.createMaskFromColor(Color::Red);
    image.loadFromFile("images/pacman2.png"); image.createMaskFromColor(Color(237,28,36));
    Texture Texture2, Texture3;
    Texture2.loadFromImage(image);
    Texture3.loadFromImage(image2);
    Sprite menu2(Texture2), menu3(Texture3),menu4(Texture3);
    menu2.setPosition(99, 300);
    menu3.setPosition(320, 335);
    menu4.setPosition(320, 400);
    bool isMenu2 = true;
    *flag = false;
    while (isMenu2)
    {
        menu3.setColor(Color::Blue);
        menu4.setColor(Color::Blue);
        textE.setFillColor(Color(192, 120, 56));
        textR.setFillColor(Color(192, 120, 56));
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                musicMenu->stop(); window.close(); isMenu2 = false;
            }
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode < 128 && event.text.unicode!=32 && event.text.unicode != 13 && event.text.unicode != 9)
                {
                    if ((Keyboard::isKeyPressed(Keyboard::BackSpace))) 
                    { 
                        if (newstring == 1 && indx >= 0) { TEXT.erase(indx, 1); indx--; }else
                            if (newstring == 2 && indx2 >= 0) { TEXTT.erase(indx2, 1); indx2--; }
                    }
                    else
                        {
                            if (newstring == 1 && indx <= 5) { indx++; TEXT += static_cast<char>(event.text.unicode); }else
                                if (newstring == 2 && indx2 <= 5) { indx2++; TEXTT += static_cast<char>(event.text.unicode); }
                        }
                    text.setString(TEXT);
                    textt.setString(TEXTT);
                }
            }
        }
        window.clear();
        if (IntRect(145, 465, 85, 33).contains(Mouse::getPosition(window))) { textE.setFillColor(Color::Yellow); menuNum = 1; }else
        if (IntRect(280, 465, 190, 33).contains(Mouse::getPosition(window))) { textR.setFillColor(Color::Yellow); menuNum = 2; }
        else menuNum = 0;
        if (IntRect(295, 335, 205, 57).contains(Mouse::getPosition(window))) { menu3.setColor(Color::White); newstringi = 1; }else
        if (IntRect(295, 400, 205, 57).contains(Mouse::getPosition(window))) { menu4.setColor(Color::White); newstringi = 2; }
        else newstringi = 0;
        if (Mouse::isButtonPressed(Mouse::Left)&&click)
        {
            click = false;
            if (newstringi == 1) newstring = 1;
            if (newstringi == 2) newstring = 2;
            if (menuNum == 1) if (Enter(TEXT, TEXTT)){ isMenu2 = false; }else ERR.setString("Error");
            if (menuNum == 2) if (Registration(TEXT, TEXTT)){ isMenu2 = false; }else ERR.setString("Error");
        }
        if (!(Mouse::isButtonPressed(Mouse::Left)))click = true;
        window.draw(menu1);
        window.draw(text1);
        window.draw(text4);
        window.draw(text3);
        window.draw(text2);
        window.draw(menu2);
        window.draw(menu3);
        window.draw(menu4);
        window.draw(text);
        window.draw(textt);
        window.draw(textE);
        window.draw(textR);
        window.draw(textN);
        window.draw(textP);
        window.draw(ERR);
        window.display();
    }
}
void lossWindow(Text text1, Text text2, Text text3, int Score, int Level)
{
    Font font;
    font.loadFromFile("Bender-Bold.ttf");
    Text text("", font, 30), textt("", font, 30), textR("", font, 30), textC("", font, 30);
    text.setFillColor(Color(192, 120, 56)); text.setStyle(Text::Bold); text.setPosition(160, 374); text.setString("Restart");
    textt.setStyle(Text::Bold); textt.setPosition(280, 424); textt.setString("Menu");
    textR.setStyle(Text::Bold); textR.setPosition(320, 374); textR.setString("Save record");
    textC.setFillColor(Color(192, 120, 56)); textC.setStyle(Text::Bold); textC.setPosition(160, 374); textC.setString("Continue");
    Image image;
    image.loadFromFile("images/pacman2.png");
    image.createMaskFromColor(Color(237, 28, 36));
    Texture Texture1;
    Texture1.loadFromImage(image);
    Sprite menu1(Texture1);
    menu1.setPosition(99,234);
    text1.setPosition(160,284);
    text2.setPosition(370, 284);
    text3.setPosition(280, 324);
    bool isMenu = true, New = false, Colr=true;
    int menuNum = 0;
    float A=0;
    while (isMenu)
    {
        text.setFillColor(Color(192, 120, 56));
        textt.setFillColor(Color(192, 120, 56));
        textC.setFillColor(Color(192, 120, 56));
        if(Colr)textR.setFillColor(Color(192, 120, 56));
        menuNum = 0;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (IntRect(130, 374, 120, 33).contains(Mouse::getPosition(window))&& !ESC) { text.setFillColor(Color::Yellow); menuNum = 1; }else
            if (IntRect(130, 374, 140, 33).contains(Mouse::getPosition(window))&& ESC) { textC.setFillColor(Color::Yellow); menuNum = 4; }
            else
        if (IntRect(250, 424, 90, 33).contains(Mouse::getPosition(window))) { textt.setFillColor(Color::Yellow); menuNum = 2; }else
        if (IntRect(293, 374, 190, 33).contains(Mouse::getPosition(window))) { if (Colr)textR.setFillColor(Color::Yellow); menuNum = 3; }else
            menuNum = 0;
        if (Mouse::isButtonPressed(Mouse::Left)&&click)
        {
            click = false;
            if (menuNum == 1) { Pacman.setHealth(3); map.setLev(1); map.Reestablish(); isMenu = false; }
            if (menuNum == 2) { music.stop(); Menu();  music.play(); Pacman.setHealth(3); map.setLev(1); map.Reestablish(); isMenu = false; Fmenu = true; }
            if (menuNum == 3) { Records(Score, Level); Colr = false; textR.setFillColor(Color::Green); }
            if (menuNum == 4) isMenu = false;
        }
        if (!(Mouse::isButtonPressed(Mouse::Left)))click = true;
        window.clear();
        drawMap(&New, &A);
        window.draw(Pacman.getSprite());
        window.draw(Ghost.getSprite());
        window.draw(Ghost2.getSprite());
        window.draw(Ghost3.getSprite());
        window.draw(Ghost4.getSprite());
        window.draw(menu1);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        if(!ESC)window.draw(text);else window.draw(textC);
        window.draw(textt);
        window.draw(textR);
        window.display();
    }
}
int main()
{
    Menu();
    music.openFromFile("Music/Music.ogg");
    music.setVolume(15);
    music.play();
    music.setLoop(true);
    SoundBuffer Buf;
    Buf.loadFromFile("Music/Death.ogg");
    Sound sound(Buf);
    sound.setVolume(15);
    Font font;
    font.loadFromFile("Bender-Bold.ttf");
    Text text("", font, 30);
    text.setFillColor(Color::White); text.setStyle(Text::Bold); text.setPosition(34, 3);
    Text texttime("", font, 30), textLev("", font, 30);
    texttime.setFillColor(Color::White); texttime.setStyle(Text::Bold); texttime.setPosition(474, 3);
    textLev.setFillColor(Color::White); textLev.setStyle(Text::Bold); textLev.setPosition(474, 680);
    bool NewLev = false;
    int Score = 0, kol[4] = { 15 }, timee, FR[4] = { 0 }, level = 1;
    float timeG = 0, timeR=0;
    float NowFrame = 0, NowFrameG[4] = { 0 };
    Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        timeG= timeG + clock.getElapsedTime().asMicroseconds()/1000000.0;
        timee = timeG;
        int a = clock.getElapsedTime().asMicroseconds();
        timeR= timeR + clock.getElapsedTime().asMicroseconds() / 1000000.0;
        clock.restart();
        time = time / 900;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Pacman.getBool(4) && Pacman.getHealth() > 0)
        {
            std::ostringstream ScoreString;
            std::ostringstream ScoreStringTime;
            std::ostringstream ScoreStringLev;
            Pacman.MovKeyboard(&NowFrame, time, map.SHMap);
            Pacman.newPosition(time);
            Ghost.MovGhost(Ghost.getX(), Ghost.getY(),&kol[0], 48.8832, 65.9082, 0, timeG, &FR[0], map.SHMap, Pacman.getX(), Pacman.getY());
            Ghost2.MovGhost(Ghost2.getX(), Ghost2.getY(), &kol[1], 576.101, 635, 1, timeG, &FR[1], map.SHMap, Pacman.getX(), Pacman.getY());
            Ghost3.MovGhost(Ghost3.getX(), Ghost3.getY(), &kol[2], 576.127, 66, 2, timeG, &FR[2], map.SHMap, Pacman.getX(), Pacman.getY());
            Ghost4.MovGhost(Ghost4.getX(), Ghost4.getY(), &kol[3], 48.93, 635, 3, timeG, &FR[3], map.SHMap, Pacman.getX(), Pacman.getY());
            Ghost.animation(&NowFrameG[0],Ghost.getDir(),101,time, timeR, &FR[0]);
            Ghost2.animation(&NowFrameG[1], Ghost2.getDir(), 126, time, timeR, &FR[1]);
            Ghost3.animation(&NowFrameG[2], Ghost3.getDir(), 151, time, timeR, &FR[2]);
            Ghost4.animation(&NowFrameG[3], Ghost4.getDir(), 176, time, timeR, &FR[3]);
            Ghost.newPosition(time);
            Ghost2.newPosition(time);
            Ghost3.newPosition(time);
            Ghost4.newPosition(time);
            PositionPacman(time, &Score, &NowFrame, &timeR,&sound, kol);
            ScoreString << Score;
            ScoreStringTime << timee;
            ScoreStringLev << level;
            text.setString("Score:" + ScoreString.str());
            texttime.setString("Time:" + ScoreStringTime.str());
            textLev.setString("Level:" + ScoreStringLev.str());
            
        }
        int b = clock.getElapsedTime().asMicroseconds();
        if (b > a)clock.restart();
        if (Pacman.getHealth() <= 0 && NowFrame >= 14 || NewLev)
        { 
            if (!NewLev) { lossWindow(text, texttime, textLev, Score, level); Score = 0; level = 0; }  NowFrame = 0; timeG = 0; timeR = 0; level++; Fmenu = false;
            for (int i = 0; i < 4; i++) {NowFrameG[i] = 0; kol[i] = 15; FR[i] = 0; NewLev = false;}
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            ESC = true;
            lossWindow(text, texttime, textLev, Score, level);
            if (Fmenu)
            {
                Reestablish(&timeG);
                Score = 0; level = 0; NowFrame = 0; timeG = 0; timeR = 0; level++; Fmenu = false;
                for (int i = 0; i < 4; i++) { NowFrameG[i] = 0; kol[i] = 15; FR[i] = 0; NewLev = false; }
            }
            ESC = false;
            clock.restart();
        }
        if (!Pacman.getBool(4))Pacman.death(&NowFrame, time);
        if ((!Pacman.getBool(4) && Pacman.getHealth() > 0 && NowFrame >= 14)) { Reestablish(&timeG);
        }
        window.setView(wind);
        window.clear();
        drawMap(&NewLev, &timeG);
        window.draw(text);
        window.draw(texttime);
        window.draw(textLev);
        window.draw(Pacman.getSprite());
        window.draw(Ghost.getSprite());
        window.draw(Ghost2.getSprite());
        window.draw(Ghost3.getSprite());
        window.draw(Ghost4.getSprite());
        drawHealth();
        window.display();
    }
    return 0;
}
void drawMap(bool* NewLev, float* time)
{
     *NewLev = true;
    for (int i = 0; i < map.Hmap; i++)
    {
        for (int j = 0; j < map.Wmap; j++)
        {
            if (map.SHMap[i][j] == '~'|| map.SHMap[i][j] == '*') {*NewLev = false; break;}
        }
    }
    if (*NewLev) { int A = map.getLev() + 1; map.setLev(A); Reestablish(time); map.Reestablish(); }
    for (int i = 0; i < map.Hmap; i++)
    {
        for (int j = 0; j < map.Wmap; j++)
        {
            map.drawMapSprite(i, j);
            window.draw(map.getSpriteMap());
        }
    }
}
void drawHealth()
{
    int dlin = Pacman.getHealth()-1;
    for (int i = 0; i < dlin; i++)
    {
        Health.setSprite(204, 27, 19, 21);
        Health.setSpritePos(34 + 20 * i, 690);
        window.draw(Health.getSpriteHealth());
    }
}
void PositionPacman(float time, int* Score, float* NowFrame, float* timeR, Sound* sound, int* kol)
{
    float x = Pacman.getX(), y = Pacman.getY();
    int i = x / 24, j = y / 30,p = (x+20) / 24, f = (y + 20) / 30, s=(x+12)/24, h=(y+15)/30;
    if (Ghost.Crossing(x,y)|| Ghost2.Crossing(x, y) || Ghost3.Crossing(x, y) || Ghost4.Crossing(x, y))
    {
        Interaction(x, y, &Ghost, NowFrame, Score, sound);
        Interaction(x, y, &Ghost2, NowFrame, Score, sound);
        Interaction(x, y, &Ghost3, NowFrame, Score, sound);
        Interaction(x, y, &Ghost4, NowFrame, Score, sound);
    }
    if (map.SHMap[h][s] == '*')
    {
        *Score += 10;
        map.SHMap[h][s] = '/';
    }
    if (map.SHMap[h][s] == '~')
    {
        *timeR = 0;
        *Score += 50;
        if (!Ghost.getUnrage())
        {
            Ghost.Invert(); kol[0] = 20;
            Ghost2.Invert(); kol[1] = 20;
            Ghost3.Invert(); kol[2] = 20;
            Ghost4.Invert(); kol[3] = 20;
        }
        Ghost.setUnrage(true);
        Ghost2.setUnrage(true);
        Ghost3.setUnrage(true);
        Ghost4.setUnrage(true);
        map.SHMap[h][s] = '/';
    }
    if (map.SHMap[j][i] == '!' || map.SHMap[f][p] == '!')
    {
            if (x <= 0 && Pacman.getDir() == 0)
            {
                x = 624;
            }
            else if (i >= 26 && Pacman.getDir() == 1)
            {
                x = 0;
            }
    }
    Pacman.setXY(x, y);
}
void Reestablish(float* time)
{
    Pacman.Mov(0, 0, 0, 0, 0, 0);
    Pacman.setXY(314, 515);
    Pacman.setLife(true);
    Pacman.NewFrame(52, 0);
    Ghost.Reestablish(314, 274, 101, 0, false, false, false);
    Ghost2.Reestablish(312.9, 334, 126, 4, true, false, false);
    Ghost3.Reestablish(264.9, 334, 151, 4, true, true, false);
    Ghost4.Reestablish(360.9, 334, 176, 4, true, true, false);
    *time = 0;
}
void Interaction(float x, float y, Enemies* A, float* NowFrame, int* Scor, Sound* sound)
{
    if (A->Crossing(x,y) && A->getLife())
    {
        if (A->getUnrage()) {A->setLife(false); *Scor += 200;}
        else
        {
            Pacman.setLife(false);
            *NowFrame = 0;
            sound->play();
            int health = Pacman.getHealth() - 1;
            A->NewFrame(252, 49);
            Pacman.setHealth(health);
        }
    }
}
bool Enter(String Name, String Password)
{
    players A, B;
    std::ifstream fin("Players.txt");
    fin >> B.Name;
    while (B.Name != A.Name)
    {
        fin >> B.Password;
        if (B.Name == Name && B.Password == Password) { namen = B.Name; return true; }
        A.Name = B.Name;
        A.Password = B.Password;
        fin >> B.Name;
    }
    fin.close();
    return false;
}
bool Registration(String Name, String Password)
{
    players A, B;
    std::ifstream fin("Players.txt");
    fin >> B.Name;
    while (B.Name!=A.Name)
    {
        fin >> B.Password;
        if (B.Name == Name || Name.isEmpty() || Password.isEmpty()) return false;
        A.Name = B.Name;
        A.Password= B.Password;
        fin >> B.Name;
    }
    fin.close();
    B.Name = Name;
    namen = B.Name;
    B.Password = Password;
    std::ofstream fout("Players.txt", std::ios::app);
    fout <<' '<< B.Name << ' ' << B.Password;
    fout.close();
    return true;
}
void Records(int Score, int Level)
{
    Record A, B;
    std::ifstream fin("Records.txt");
    int kol=0;
    bool flag, same=true;
    fin >> B.Name >> B.Score >> B.Level;
    while (!(B.Name == A.Name && A.Score == B.Score && A.Level == B.Level))
    {
        if (B.Name == namen && Score == B.Score && Level == B.Level)same = false;
        kol++;
        A.Name = B.Name;
        A.Score = B.Score;
        A.Level = B.Level;
        fin >> B.Name >> B.Score >> B.Level;
    }
    fin.close();
    if (same)
    {
        std::vector <Record> Mas(kol + 1);
        fin.open("Records.txt");
        for (int i = 0; i < kol; i++)
        {
            fin >> Mas[i].Name >> Mas[i].Score >> Mas[i].Level;
        }
        fin.close();
        Mas[kol].Name = namen; Mas[kol].Score = Score; Mas[kol].Level = Level;
        sort(Mas.begin(), Mas.end(), [](Record A, Record B) {int a = A.Score + A.Level * 1000, b = B.Score + B.Level * 1000; return a > b; });
        std::ofstream fout("Records.txt");
        for (int i = 0; i < kol + 1 && i < 7; i++)
        {
            fout << ' ' << Mas[i].Name << ' ' << Mas[i].Score << ' ' << Mas[i].Level;
        }
        fout.close();
    }
}