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
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }
 }

