#ifndef FIRETURRECT_H
#define FIRETURRECT_H

#include "defetowerparent.h"

//火炮塔类，继承防御塔父类
class FireTurret : public DefeTowerParent
{
protected:

public:
    FireTurret(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
    virtual FireTurret* GetTypeid() ;

    virtual ~FireTurret() {}
};

#endif // FIRETURRECT_H
