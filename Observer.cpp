#include <iostream>
#include <vector>

class Observer; // Khai báo trước
class DisplayElement; // Khai báo trước

class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObserver() = 0;
};

class Observer {
public:
    virtual void update(const float& temp, const float& humidity, const float& pressure) = 0;
};

class DisplayElement {
public:
    virtual void display() = 0;
};

class WeatherData : public Subject {
private:
    std::vector<Observer*> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    void registerObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        //observers.erase(observer);
    }

    void notifyObserver() override {
        for (const auto& observer : observers) {
            observer->update(temperature, humidity, pressure);
        }
    }

    void measurementsChanged() {
        notifyObserver();
    }

    void setMeasurements(const float& temp, const float& hum, const float& press) {
        temperature = temp;
        humidity = hum;
        pressure = press;
        measurementsChanged();
    }
};

class CurrentConditionsDisplay : public Observer, public DisplayElement {
private:
    float temperature;
    float humidity;
    Subject* weatherData;

public:
    CurrentConditionsDisplay(Subject* weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }

    void update(const float& temp, const float& hum, const float& press) override {
        temperature = temp;
        humidity = hum;
        display();
    }

    void display() override {
        std::cout << "Current conditions: " << temperature << " F degrees and " << humidity << " % humidity" << std::endl;
    }
};

int main() {
    WeatherData* weatherData = new WeatherData();
    CurrentConditionsDisplay* currentDisplay = new CurrentConditionsDisplay(weatherData);

    // Simulate weather data changes
    weatherData->setMeasurements(80, 65, 30.4f);
    weatherData->setMeasurements(82, 70, 29.4f);

    // Clean up memory (not shown in the original code)
    delete currentDisplay;
    delete weatherData;

    return 0;
}
