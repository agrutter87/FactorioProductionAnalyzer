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
 * FactorioItem::FactorioItem
 *************************************************************************/
FactorioItem::FactorioItem(const QJsonObject &json)
{
#if DEBUG_FACTORIO_ITEM
    qDebug() << __PRETTY_FUNCTION__;
#endif
    jsonRead(json);
}

/*************************************************************************
 * FactorioItem::getName
 *************************************************************************/
QString FactorioItem::getName() const
{
#if DEBUG_FACTORIO_ITEM
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return mName;
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

    /* Read the stack_size value if it exists */
    if (json.contains("stack_size") && json["stack_size"].isDouble())
    {
        mStackSize = json["stack_size"].toDouble();
    }

    /* Read the type value if it exists */
    if (json.contains("type") && json["type"].isString())
    {
        mType = json["type"].toString();
    }
}

