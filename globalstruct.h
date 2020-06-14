#ifndef GLOBALSTRUCT_H
#define GLOBALSTRUCT_H

#include <QString>

//选择框子按钮结构
class SubbutStr
{
public:
    int SubX;           //子按钮相对选择框的横坐标
    int SubY;           //纵坐标
    int SubWidth = 56;  //子按钮宽
    int SubHeight = 56; //高
    QString SubImgPath; //子按钮的图片路径
};

//坐标结构
class CoorStr
{
public:
    int x;
    int y;

    CoorStr(int x1, int y1) : x(x1), y(y1) {}
};

//子弹结构
class BulletStr
{
public:
    CoorStr coor;       //子弹坐标
    int k = 0, b = 0;   //用于计算出子弹路径函数
    bool dirflag = false;   //移动方向标识

    BulletStr(CoorStr fcoor) : coor(fcoor) {}

    int GetX()  const
    {
        return coor.x;
    }

    int GetY() const
    {
        return coor.y;
    }
};

#endif // GLOBALSTRUCT_H
