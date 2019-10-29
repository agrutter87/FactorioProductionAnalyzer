#include "factorioresource.h"

/*************************************************************************
 * FactorioResource::FactorioResource
 *************************************************************************/
FactorioResource::FactorioResource()
{
#if DEBUG_FACTORIO_RESOURCE
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * FactorioResource::jsonRead
 *************************************************************************/
void FactorioResource::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_RESOURCE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }
 }

