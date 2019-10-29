#ifndef FACTORIOPRODUCT_H
#define FACTORIOPRODUCT_H

#include <QJsonObject>

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_PRODUCT          (0)

/*************************************************************************
 * FactorioProduct Class
 *************************************************************************/
class FactorioProduct
{
public:
                                        FactorioProduct();

    void                                jsonRead(const QJsonObject &json);

private:
    double                              mAmount;
    QString                             mName;
    QString                             mType;
};

#endif // FACTORIOPRODUCT_H
