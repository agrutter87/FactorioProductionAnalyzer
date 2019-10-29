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
    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }
 }

