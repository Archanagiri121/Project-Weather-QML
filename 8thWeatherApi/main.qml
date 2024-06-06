import QtQuick
import QtQuick.Controls
import WeatherApp 1.0

Window {
    visible: true
    width: 400
    height: 200
    title: "Weather App"
    color: "lightblue"

    Api
    {
        id: api
    }

    Text {
        id: weatherText
        anchors.centerIn: parent
        text: "Current Temp..."

    }

    Image
    {
        id: weatherImg
        width: 50
        height: 50
        anchors.bottom: weatherText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Component.onCompleted:
    {
        var latitude = 18.5204;
        var longitude = 73.8567;
        api.fetchWeather(latitude, longitude);


        api.weatherInfoChanged.connect(updateWeatherInfo);
    }

    function updateWeatherInfo()
    {
        weatherText.text = "Temperature: " + api.weatherInfo.temperature.toFixed(2) + "°C";
        weatherImg.source = "http://openweathermap.org/img/wn/" + api.weatherInfo.iconId + "@2x.png";
    }
}

