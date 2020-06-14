#include "magic.h"

Magic::Magic(const QString MagicImgPath)
{
    this->MagicImgPath = MagicImgPath;
}

QString Magic::GetMagicImgPath() const
{
    return this->MagicImgPath;
}

void Magic::SetMagicImgPath(const QString path)
{
    this->MagicImgPath = path;
}
