#include "Api.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Api::Api(QObject *parent) : QObject(parent), m_weatherInfo(new WeatherInfo(this)), networkManager(new QNetworkAccessManager(this))
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &Api::replyFinished);
}

WeatherInfo* Api::weatherInfo() const
{
    return m_weatherInfo;
}

void Api::fetchWeather(double latitude, double longitude)
{
    QString apiUrl = "https://api.openweathermap.org/data/2.5/weather?lat=" +
                     QString::number(latitude) +
                     "&lon=" +
                     QString::number(longitude) +
                     "&appid=d150de1e47c122cda60ea28992ba1b57";

    networkManager->get(QNetworkRequest(QUrl(apiUrl)));
}

void Api::replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        double temperature = jsonObject["main"].toObject()["temp"].toDouble() - 273.15;
        QString iconId = jsonObject["weather"].toArray()[0].toObject()["icon"].toString();
        //qDebug()<<" Icon printing <<<<<<"iconId;

        m_weatherInfo->setTemperature(temperature);
        m_weatherInfo->setIconId(iconId);

        // temperatureInfo.temperature = temperature;
        // temperatureInfo.iconId = iconId;
        emit weatherInfoChanged();
    }
    else
    {
        qDebug() << "Error ----->401" << reply->errorString();
    }

    reply->deleteLater();
}
