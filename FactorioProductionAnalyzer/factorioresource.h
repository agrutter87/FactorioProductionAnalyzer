#ifndef FACTORIO_RESOURCE_H
#define FACTORIO_RESOURCE_H

#include <QJsonObject>
#include "factorioproduct.h"

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_RESOURCE         (1)

/*************************************************************************
 * FactorioResource Class
 *************************************************************************/
class FactorioResource
{
public:
                                        FactorioResource();

    void                                jsonRead(const QJsonObject &json);

private:
    QString                             mName;
};

#endif // FACTORIO_RESOURCE_H
