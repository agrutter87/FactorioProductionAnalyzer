#include "factoriominer.h"

/*************************************************************************
 * FactorioMiner::FactorioMiner
 *************************************************************************/
FactorioMiner::FactorioMiner()
{
#if DEBUG_FACTORIO_MINER
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * FactorioMiner::jsonRead
 *************************************************************************/
void FactorioMiner::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_MINER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }
 }

