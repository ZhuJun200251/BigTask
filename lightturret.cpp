#include "lightturret.h"

//光炮防御塔函数实现
LightTurret::LightTurret(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    //初始化成员变量，这里不能用初始化列表
    mx = x, my = y;
    grade = 0;
    BaseImgPath = QString(":/image/绿瓶底座.png");
    DefImgPath = QString(":/image/一级光炮.png");
    width = Fwidth, height = Fheight;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;

    Range = 260;    //射程

    BullPath = QString(":/image/炮弹2.png");
    bullwidth = 40, bullheight = 40;           //子弹大小

    attack = 94;    //攻击
}

LightTurret* LightTurret::GetTypeid()
{
    return this;
}
