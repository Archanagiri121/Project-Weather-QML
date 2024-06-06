#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <api.h>
#include <QQmlContext>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Api>("WeatherApp", 1, 0, "Api");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/8thWeatherApi/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
