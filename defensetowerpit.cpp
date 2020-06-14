#include "defensetowerpit.h"

//构造
DefenseTowerPit::DefenseTowerPit(int x, int y, int width, int height)
    : mx(x), my(y), mwidth(width), mheight(height) {}

int DefenseTowerPit::GetX() const     //获取横坐标
{
    return mx;
}

int DefenseTowerPit::GetY() const     //获取横坐标
{
    return my;
}

int DefenseTowerPit::GetWidth() const //获取宽
{
    return mwidth;
}

int DefenseTowerPit::GetHeight() const //获取高
{
    return mheight;
}

