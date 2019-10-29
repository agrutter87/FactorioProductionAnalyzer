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
                                        FactorioProduct(const QJsonObject &json);

private:
    void                                jsonRead(const QJsonObject &json);

    double                              mAmount;
    QString                             mName;
    QString                             mType;
};

#endif // FACTORIOPRODUCT_H
