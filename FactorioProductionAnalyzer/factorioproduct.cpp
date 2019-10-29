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
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }
 }

