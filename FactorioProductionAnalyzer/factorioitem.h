#ifndef FACTORIO_ITEM_H
#define FACTORIO_ITEM_H

#include <QJsonObject>

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_ITEM             (0)

/*************************************************************************
 * FactorioItem Class
 *************************************************************************/
class FactorioItem
{
public:
                                        FactorioItem();
                                        FactorioItem(const QJsonObject &json);

    QString                             getName() const;

private:
    void                                jsonRead(const QJsonObject &json);

    QString                             mName;
    double                              mStackSize;
    QString                             mType;
};

#endif // FACTORIO_ITEM_H
