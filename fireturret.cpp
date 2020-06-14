#include "fireturret.h"

//火防御塔类函数实现
//构造
FireTurret::FireTurret(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    //初始化成员变量，这里不能用初始化列表
    mx = x, my = y;
    grade = 0;
    BaseImgPath = QString(":/image/绿瓶底座.png");
    DefImgPath = QString(":/image/一级火瓶.png");
    width = Fwidth, height = Fheight;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;

    Range = 170;    //射程

    BullPath = QString(":/image/炮弹1.png");
    bullwidth = 40, bullheight = 40;           //子弹大小

    attack = 65;    //攻击力
}

FireTurret* FireTurret::GetTypeid()
{
    return this;
}
