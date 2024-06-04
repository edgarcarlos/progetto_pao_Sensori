#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QWidget>

class SensorWidget : public QWidget {
    Q_OBJECT

public:
    explicit SensorWidget(AbstractSensor* sensor, QWidget *parent = nullptr);
};

#endif // SENSORWIDGET_H
