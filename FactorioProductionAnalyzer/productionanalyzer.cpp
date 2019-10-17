#include "productionanalyzer.h"

#include <QFile>
#include <QJsonDocument>

/*************************************************************************
 * ProductionAnalyzer::ProductionAnalyzer
 *************************************************************************/
ProductionAnalyzer::ProductionAnalyzer()
{

}

/*************************************************************************
 * ProductionAnalyzer::getProductionData
 *************************************************************************/
QVector<ProductionData> ProductionAnalyzer::getProductionData() const
{
    return mProductionData;
}

/*************************************************************************
 * ProductionAnalyzer::setProductionData
 *************************************************************************/
void ProductionAnalyzer::setProductionData(const QVector<ProductionData> &productionData)
{
    mProductionData = productionData;
}

/*************************************************************************
 * ProductionAnalyzer::setFile
 *************************************************************************/
void ProductionAnalyzer::setFile(SaveFormat saveFormat, QString &fileName)
{
    mFileFormat = saveFormat;
    mFileName = fileName;
}

/*************************************************************************
 * ProductionAnalyzer::fileRead
 *************************************************************************/
bool ProductionAnalyzer::fileRead(void)
{
    qDebug("ProductionAnalyzer::fileRead");

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
    QJsonObject productionObject;

    if(!mProductionData.isEmpty())
    {
        mProductionData.last().jsonWrite(productionObject);
        json["productiondata"] = productionObject;
    }
}
