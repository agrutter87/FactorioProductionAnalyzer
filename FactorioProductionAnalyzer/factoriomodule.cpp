#include "factoriomodule.h"

/*************************************************************************
 * FactorioModule::FactorioModule
 *************************************************************************/
FactorioModule::FactorioModule()
{
#if DEBUG_FACTORIO_MODULE
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * FactorioModule::jsonRead
 *************************************************************************/
void FactorioModule::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_MODULE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }
 }

