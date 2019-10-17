#include "productionanalyzer.h"

#include <QFile>
#include <QJsonDocument>

/*************************************************************************
 * ProductionAnalyzer::ProductionAnalyzer
 *************************************************************************/
ProductionAnalyzer::ProductionAnalyzer()
{
#if DEBUG_PRODUCTION_ANALYZER
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * ProductionAnalyzer::getProductionData
 *************************************************************************/
QVector<ProductionData> ProductionAnalyzer::getProductionData() const
{
#if DEBUG_PRODUCTION_ANALYZER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return mProductionData;
}

/*************************************************************************
 * ProductionAnalyzer::setProductionData
 *************************************************************************/
void ProductionAnalyzer::setProductionData(const QVector<ProductionData> &productionData)
{
#if DEBUG_PRODUCTION_ANALYZER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mProductionData = productionData;
}

/*************************************************************************
 * ProductionAnalyzer::setFile
 *************************************************************************/
void ProductionAnalyzer::setFile(SaveFormat saveFormat, QString &fileName)
{
#if DEBUG_PRODUCTION_ANALYZER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mFileFormat = saveFormat;
    mFileName = fileName;
}

/*************************************************************************
 * ProductionAnalyzer::fileRead
 *************************************************************************/
bool ProductionAnalyzer::fileRead(void)
{
#if DEBUG_PRODUCTION_ANALYZER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    QFile loadFile(mFileName);

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(mFileFormat == Json
                          ? QJsonDocument::fromJson(saveData)
                          : QJsonDocument::fromBinaryData(saveData));

    jsonRead(loadDoc.object());

    return true;
}

/*************************************************************************
 * ProductionAnalyzer::fileWrite
 *************************************************************************/
bool ProductionAnalyzer::fileWrite(SaveFormat saveFormat, QString &fileName) const
{
#if DEBUG_PRODUCTION_ANALYZER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    QFile saveFile(fileName);

    if(!saveFile.open(QIODevice::ReadWrite))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject productionObject;
    jsonWrite(productionObject);

    QJsonDocument saveDoc(productionObject);
    saveFile.write(saveFormat == Json
                   ? saveDoc.toJson()
                   : saveDoc.toBinaryData());

    return true;
}

/*************************************************************************
 * ProductionAnalyzer::jsonRead
 *************************************************************************/
void ProductionAnalyzer::jsonRead(const QJsonObject &json)
{
#if DEBUG_PRODUCTION_ANALYZER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    ProductionData productionData;

    if(json.contains("productiondata") && json["productiondata"].isObject())
    {
        productionData.jsonRead(json["productiondata"].toObject());
    }

    mProductionData.append(productionData);

    while(mProductionData.size() > PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
    {
        mProductionData.removeFirst();
    }
}

/*************************************************************************
 * ProductionAnalyzer::jsonWrite
 *************************************************************************/
void ProductionAnalyzer::jsonWrite(QJsonObject &json) const
{
#if DEBUG_PRODUCTION_ANALYZER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    QJsonObject productionObject;

    if(!mProductionData.isEmpty())
    {
        mProductionData.last().jsonWrite(productionObject);
        json["productiondata"] = productionObject;
    }
}
