#ifndef GREENTURRET_H
#define GREENTURRET_H

#include "defetowerparent.h"

//绿色炮塔类，继承防御塔父类
class GreenTurret : public DefeTowerParent
{
protected:

public:
    GreenTurret(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
    virtual GreenTurret* GetTypeid();

    virtual ~GreenTurret() {}
};

#endif // GREENTURRET_H
