#ifndef FACTORIO_ITEM_H
#define FACTORIO_ITEM_H

#include <QJsonObject>

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_ITEM             (1)

/*************************************************************************
 * FactorioItem Class
 *************************************************************************/
class FactorioItem
{
public:
                                        FactorioItem();

    void                                jsonRead(const QJsonObject &json);

private:
    QString                             mName;
    double                              mStackSize;
    QString                             mType;
};

#endif // FACTORIO_ITEM_H
