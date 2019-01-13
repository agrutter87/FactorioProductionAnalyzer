#include "productionanalyzer.h"

#include <QFile>
#include <QJsonDocument>
#include <QTextStream>

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

bool ProductionAnalyzer::fileRead(SaveFormat saveFormat)
{
    QFile loadFile(saveFormat == Json
                             ? QStringLiteral("production_data.json")
                             : QStringLiteral("production_data.dat"));

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(saveFormat == Json
                          ? QJsonDocument::fromJson(saveData)
                          : QJsonDocument::fromBinaryData(saveData));

    jsonRead(loadDoc.object());

    QTextStream(stdout) << "Loaded save for production data using "
                        << (saveFormat != Json ? "binary " : "") << "JSON...\n";

    return true;
}

bool ProductionAnalyzer::fileWrite(SaveFormat saveFormat) const
{
    QFile saveFile(saveFormat == Json
                             ? QStringLiteral("production_data.json")
                             : QStringLiteral("production_data.dat"));

    if(!saveFile.open(QIODevice::ReadOnly))
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
