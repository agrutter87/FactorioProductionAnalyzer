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

    bool fileRead(SaveFormat saveFormat);
    bool fileWrite(SaveFormat saveFormat) const;

    void jsonRead(const QJsonObject &json);
    void jsonWrite(QJsonObject &json) const;

private:
    ProductionData mProductionData;
};

#endif // PRODUCTIONANALYZER_H
