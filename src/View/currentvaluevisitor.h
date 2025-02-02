#ifndef CURRENTVALUEVISITOR_H
#define CURRENTVALUEVISITOR_H

#include <QString>

#include "../Sensor/svisitor.h"
#include "sensorwidget.h"

#include "../Sensor/carburante.h"
#include "../Sensor/pressione.h"
#include "../Sensor/temperatura.h"
#include "../Sensor/positionsensor.h"

namespace View {

class CurrentValueVisitor: public Sensor::SVisitor

{
public:
    CurrentValueVisitor(SensorWidget* widget);

    void visit(Sensor::Carburante& carburante) override;
    void visit(Sensor::Pressione& pressione) override;
    void visit(Sensor::Temperatura& temperatura) override;
    void visit(Sensor::PositionSensor& positionsensor) override;

private:
    SensorWidget* widget;
};

}
#endif // CURRENTVALUEVISITOR_H
