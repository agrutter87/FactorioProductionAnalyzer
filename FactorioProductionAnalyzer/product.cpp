#include "product.h"

#include <QJsonArray>

/*************************************************************************
 * Product::Product
 *************************************************************************/
Product::Product()
{

}

/*************************************************************************
 * Product::getName
 *************************************************************************/
QString Product::getName() const
{
    return mName;
}

/*************************************************************************
 * Product::setName
 *************************************************************************/
void Product::setName(const QString &name)
{
    mName = name;
}

/*************************************************************************
 * Product::getValue
 *************************************************************************/
double Product::getValue() const
{
    return mValue;
}

/*************************************************************************
 * Product::setValue
 *************************************************************************/
void Product::setValue(double value)
{
    mValue = value;
}

/*************************************************************************
 * Product::getProductType
 *************************************************************************/
Product::ProductType Product::getProductType() const
{
    return mProductType;
}

/*************************************************************************
 * Product::setProductType
 *************************************************************************/
void Product::setProductType(ProductType productType)
{
    mProductType = productType;
}

/*************************************************************************
 * Product::jsonRead
 *************************************************************************/
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

/*************************************************************************
 * Product::jsonWrite
 *************************************************************************/
void Product::jsonWrite(QJsonObject &json) const
{
    /* Set the JSON data for "name" to mName */
    json["name"] = mName;

    /* Set the JSON data for "value" to mValue */
    json["value"] = mValue;
}
