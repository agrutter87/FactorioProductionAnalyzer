#include "factoriomodule.h"

/*************************************************************************
 * FactorioModule::FactorioModule
 *************************************************************************/
FactorioModule::FactorioModule()
{

}

/*************************************************************************
 * FactorioModule::jsonRead
 *************************************************************************/
void FactorioModule::jsonRead(const QJsonObject &json)
{
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }
 }

