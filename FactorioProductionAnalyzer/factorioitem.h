#ifndef FACTORIO_ITEM_H
#define FACTORIO_ITEM_H

#include <QJsonObject>

class FactorioItem
{
public:
    FactorioItem();

    void jsonRead(const QJsonObject &json);

private:
    QString mName;
};

#endif // FACTORIO_ITEM_H
