#ifndef FACTORIO_RESOURCE_H
#define FACTORIO_RESOURCE_H

#include <QJsonObject>

class FactorioResource
{
public:
    FactorioResource();

    void jsonRead(const QJsonObject &json);

private:
    QString mName;
};

#endif // FACTORIO_RESOURCE_H
