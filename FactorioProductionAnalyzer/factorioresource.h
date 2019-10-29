#ifndef FACTORIO_RESOURCE_H
#define FACTORIO_RESOURCE_H

#include <QJsonObject>
#include "factorioproduct.h"

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_RESOURCE         (0)

/*************************************************************************
 * FactorioResource Class
 *************************************************************************/
class FactorioResource
{
public:
                                        FactorioResource();

    void                                jsonRead(const QJsonObject &json);

private:
    bool                                mInfinite;
    double                              mMinimum;
    double                              mMiningTime;
    QString                             mName;
    QVector<FactorioProduct>            *mProducts;
    QString                             mResourceCategory;
};

#endif // FACTORIO_RESOURCE_H
