#ifndef BIGTURRET_H
#define BIGTURRET_H

#include "defetowerparent.h"

//大炮防御塔类
class BigTurret : public DefeTowerParent
{
protected:

public:
    BigTurret(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
    virtual BigTurret* GetTypeid();

    virtual ~BigTurret() {}
};

#endif // BIGTURRET_H
