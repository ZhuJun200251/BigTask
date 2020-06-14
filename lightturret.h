#ifndef LIGHTTURRET_H
#define LIGHTTURRET_H

#include "defetowerparent.h"
//光炮类
class LightTurret : public DefeTowerParent
{
protected:

public:
    LightTurret(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
    virtual LightTurret* GetTypeid() ;

    virtual ~LightTurret() {}
};

#endif // LIGHTTURRET_H
