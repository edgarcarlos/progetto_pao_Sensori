#include "sensorspanel.h"

#include <QGridLayout>

SensorsPanel::SensorsPanel(QWidget* parent): QWidget(parent) {

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setBackgroundRole(QPalette::Dark);
    content = new QWidget(scrollArea);

    panelLayout = new QGridLayout(content);
    panelLayout->setAlignment(Qt::AlignTop);
    content->setLayout(panelLayout);
    scrollArea->setWidget(content);

    setLayout(panelLayout);


}


void SensorsPanel::addSensors(const std::vector<AbstractSensor*>& sensors){

    for(auto sensor : sensors){

        SensorWidget* sensorWidget = new SensorWidget(sensor, content);
        sensorWidgets.push_back(sensorWidget);
        panelLayout->addWidget(sensorWidget);
    }
    updateLayout();

}

void SensorsPanel::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateLayout();
}

void SensorsPanel::updateLayout() {
    int row = 0;
    int col = 0;
    int rowSize = initialRowSize;
    if (width() > 600) {
        rowSize = width() / 200;
    }

    if (rowSize == 0) {
        rowSize = 1;
    }

    for (SensorWidget* widget : sensorWidgets) {
        panelLayout->addWidget(widget, row, col);
        col++;
        if (col >= rowSize) {
            col = 0;
            row++;
        }
    }
}






