#ifndef PRODUCTIONANALYZER_H
#define PRODUCTIONANALYZER_H

#include "productiondata.h"

/*************************************************************************
 * Defines
 *************************************************************************/
#define PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX     (1 * 60)
#define PRODUCTION_DATA_READ_PERIOD_MS              (1000)
#define DEBUG_PRODUCTION_ANALYZER                   (0)

/*************************************************************************
 * ProductionAnalyzer Class
 *************************************************************************/
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

private:
    void jsonRead(const QJsonObject &json);
    void jsonWrite(QJsonObject &json) const;

    QVector<ProductionData> mProductionData;
    QString mFileFormat;
    QString mFileName;
};

#endif // PRODUCTIONANALYZER_H
