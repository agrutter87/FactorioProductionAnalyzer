#ifndef PRODUCTIONANALYZER_H
#define PRODUCTIONANALYZER_H

#include "productiondata.h"

class ProductionAnalyzer
{
public:
    enum SaveFormat
    {
        Json, Binary
    };

    ProductionAnalyzer();

    ProductionData getProductionData() const;
    void setProductionData(ProductionData &productionData);

    void setFile(SaveFormat saveFormat, QString &fileName);

    bool fileRead(void);
    bool fileWrite(SaveFormat saveFormat, QString &fileName) const;

    void jsonRead(const QJsonObject &json);
    void jsonWrite(QJsonObject &json) const;

private:
    ProductionData mProductionData;
    QString mFileFormat;
    QString mFileName;
};

#endif // PRODUCTIONANALYZER_H
