#include "productionanalyzer.h"

#include <QFile>
#include <QJsonDocument>

ProductionAnalyzer::ProductionAnalyzer()
{

}

ProductionData ProductionAnalyzer::getProductionData() const
{
    return mProductionData;
}

void ProductionAnalyzer::setProductionData(ProductionData &productionData)
{
    mProductionData = productionData;
}

void ProductionAnalyzer::setFile(SaveFormat saveFormat, QString &fileName)
{
    mFileFormat = saveFormat;
    mFileName = fileName;
}

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

void ProductionAnalyzer::jsonRead(const QJsonObject &json)
{
    if(json.contains("productiondata") && json["productiondata"].isObject())
    {
        mProductionData.jsonRead(json["productiondata"].toObject());
    }
}

void ProductionAnalyzer::jsonWrite(QJsonObject &json) const
{
    QJsonObject productionObject;
    mProductionData.jsonWrite(productionObject);
    json["productiondata"] = productionObject;
}
