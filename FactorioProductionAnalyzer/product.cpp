#include "product.h"

#include <QJsonArray>

Product::Product()
{

}

QString Product::getName() const
{
    return mName;
}

void Product::setName(const QString &name)
{
    mName = name;
}

double Product::getValue() const
{
    return mValue;
}

void Product::setValue(double value)
{
    mValue = value;
}

Product::ProductType Product::getProductType() const
{
    return mProductType;
}

void Product::setProductType(ProductType productType)
{
    mProductType = productType;
}

void Product::jsonRead(const QJsonObject &json)
{
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }

    /* Find "value" section in JSON object and ensure it is set to a Double */
    if (json.contains("value") && json["value"].isDouble())
    {
        /* Set mValue to value in JSON */
        mValue = json["value"].toDouble();
    }
 }

void Product::jsonWrite(QJsonObject &json) const
{
    /* Set the JSON data for "name" to mName */
    json["name"] = mName;

    /* Set the JSON data for "value" to mValue */
    json["value"] = mValue;
}
