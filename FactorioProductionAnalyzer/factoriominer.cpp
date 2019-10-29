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
    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }
 }

