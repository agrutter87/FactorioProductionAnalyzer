#include "factorioitem.h"

/*************************************************************************
 * FactorioItem::FactorioItem
 *************************************************************************/
FactorioItem::FactorioItem()
{
#if DEBUG_FACTORIO_ITEM
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * FactorioItem::jsonRead
 *************************************************************************/
void FactorioItem::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_ITEM
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }
 }

