#include "bigturret.h"

//大炮防御塔类函数实现
//构造
BigTurret::BigTurret(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    //初始化成员变量，这里不能用初始化列表
    mx = x, my = y;
    grade = 0;
    BaseImgPath = QString(":/image/绿瓶底座.png");
    DefImgPath = QString(":/image/一级大炮.png");
    width = Fwidth, height = Fheight;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;

    Range = 230;    //射程

    BullPath = QString(":/image/炮弹3.png");
    bullwidth = 40, bullheight = 40;           //子弹大小

    attack = 118;    //攻击力
}

BigTurret* BigTurret::GetTypeid()
{
    return this;
}
