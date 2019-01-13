#include "productiondata.h"

#include <QJsonArray>

ProductionData::ProductionData()
{

}

QVector<Product> ProductionData::getInputs() const
{
    return mInputs;
}

void ProductionData::setInputs(const QVector<Product> &products)
{
    mInputs = products;
}

QVector<Product> ProductionData::getOutputs() const
{
    return mOutputs;
}

void ProductionData::setOutputs(const QVector<Product> &products)
{
    mOutputs = products;
}

void ProductionData::jsonRead(const QJsonObject &json)
{
    /* Find "inputs" section in JSON object and ensure it is set to an array */
    if (json.contains("inputs") && json["inputs"].isArray())
    {
        /* Initialize a local array to hold the data in the JSON array */
        QJsonArray inputArray = json["inputs"].toArray();

        /* Clear the existing data */
        mInputs.clear();

        /* Reserve memory for the incoming data*/
        mInputs.reserve(inputArray.size());

        /* Loop through the members of the JSON array */
        for(int inputIndex = 0; inputIndex < inputArray.size(); ++inputIndex)
        {
            /* Initialize a local object to hold the data of the JSON member */
            QJsonObject inputObject = inputArray[inputIndex].toObject();

            /* Initialize a local product with the data of the JSON member */
            Product product;
            product.jsonRead(inputObject);

            /* Append the local product to the mInputs array */
            mInputs.append(product);
        }
    }

    /* Find "outputs" section in JSON object and ensure it is set to an array */
    if (json.contains("outputs") && json["outputs"].isArray())
    {
        /* Initialize a local array to hold the data in the JSON array */
        QJsonArray outputArray = json["outputs"].toArray();

        /* Clear the existing data */
        mOutputs.clear();

        /* Reserve memory for the incoming data*/
        mOutputs.reserve(outputArray.size());

        /* Loop through the members of the JSON array */
        for(int outputIndex = 0; outputIndex < outputArray.size(); ++outputIndex)
        {
            /* Initialize a local object to hold the data of the JSON member */
            QJsonObject outputObject = outputArray[outputIndex].toObject();

            /* Initialize a local product with the data of the JSON member */
            Product product;
            product.jsonRead(outputObject);

            /* Append the local product to the mOutputs array */
            mOutputs.append(product);
        }
    }
  }

void ProductionData::jsonWrite(QJsonObject &json) const
{
    /* Create a local JSON array for "inputs" data */
    QJsonArray inputArray;

    /* Create a local JSON array for "outputs" data */
    QJsonArray outputArray;

    /* Loop through members of mInputs */
    foreach (const Product product, mInputs)
    {
        /* Create a local JSON object */
        QJsonObject inputObject;

        /* Write the product data to the JSON object */
        product.jsonWrite(inputObject);

        /* Append the JSON object to the JSON array */
        inputArray.append(inputObject);
    }

    /* Loop through members of mOutputs */
    foreach (const Product product, mOutputs)
    {
        /* Create a local JSON object */
        QJsonObject outputObject;

        /* Write the product data to the JSON object */
        product.jsonWrite(outputObject);

        /* Append the JSON object to the JSON array */
        inputArray.append(outputObject);
    }

    /* Set the JSON data for "inputs" to the JSON array */
    json["inputs"] = inputArray;

    /* Set the JSON data for "outputs" to the JSON array */
    json["outputs"] = outputArray;
}
