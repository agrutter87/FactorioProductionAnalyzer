#include "factorioassembler.h"

/*************************************************************************
 * FactorioAssembler::FactorioAssembler
 *************************************************************************/
FactorioAssembler::FactorioAssembler()
{

}

/*************************************************************************
 * FactorioAssembler::jsonRead
 *************************************************************************/
void FactorioAssembler::jsonRead(const QJsonObject &json)
{
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }
 }

