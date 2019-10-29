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
 * FactorioProduct::jsonRead
 *************************************************************************/
void FactorioProduct::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }
 }

