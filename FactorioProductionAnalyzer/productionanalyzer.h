#ifndef PRODUCTIONANALYZER_H
#define PRODUCTIONANALYZER_H

#include "productiondata.h"

#define PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX (10 * 60)
#define PRODUCTION_DATA_READ_PERIOD_MS          (1000)

class ProductionAnalyzer
{
public:
    enum SaveFormat
    {
        Json, Binary
    };

    ProductionAnalyzer();

    QVector<ProductionData> getProductionData() const;
    void setProductionData(const QVector<ProductionData> &productionData);

    void setFile(SaveFormat saveFormat, QString &fileName);

    bool fileRead(void);
    bool fileWrite(SaveFormat saveFormat, QString &fileName) const;

    void jsonRead(const QJsonObject &json);
    void jsonWrite(QJsonObject &json) const;

private:
    QVector<ProductionData> mProductionData;
    QString mFileFormat;
    QString mFileName;
};

#endif // PRODUCTIONANALYZER_H
