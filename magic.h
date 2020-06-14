#ifndef MAGIC_H
#define MAGIC_H

#include "globalstruct.h"

class Magic
{
public:
    Magic(const QString);
    QString GetMagicImgPath() const;
    void SetMagicImgPath(const QString);

private:
    QString MagicImgPath;
};

#endif // MAGIC_H
