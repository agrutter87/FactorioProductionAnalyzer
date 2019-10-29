#include "factorioproduct.h"

/*************************************************************************
 * FactorioProduct::FactorioProduct
 *************************************************************************/
FactorioProduct::FactorioProduct()
{
#if DEBUG_FACTORIO_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * FactorioProduct::FactorioProduct
 *************************************************************************/
FactorioProduct::FactorioProduct(const QJsonObject &json)
{
#if DEBUG_FACTORIO_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    jsonRead(json);
}

/*************************************************************************
 * FactorioProduct::jsonRead
 *************************************************************************/
void FactorioProduct::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Read the amount value if it exists */
    if(json.contains("amount") && json["amount"].isDouble())
    {
        mAmount = json["amount"].toDouble();
    }

    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }

    /* Read the type value if it exists */
    if (json.contains("type") && json["type"].isString())
    {
        mType = json["type"].toString();
    }
}

