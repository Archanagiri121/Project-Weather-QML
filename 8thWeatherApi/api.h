#ifndef API_H
#define API_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include "WeatherInfo.h"

class Api : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WeatherInfo* weatherInfo READ weatherInfo NOTIFY weatherInfoChanged)

public:
    explicit Api(QObject *parent = nullptr);

    WeatherInfo* weatherInfo() const;



signals:
    void weatherInfoChanged();



public slots:
    void fetchWeather(double latitude, double longitude);
    void replyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    WeatherInfo *m_weatherInfo;
};

#endif // API_H
