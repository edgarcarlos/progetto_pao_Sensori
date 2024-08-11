#ifndef ENVSENSOR_H
#define ENVSENSOR_H

#include <string>
#include <vector>

#include "abstractsensor.h"

using namespace std;

class EnvSensor: public AbstractSensor {
    private:
        vector<double> dati;
        double valoreCorrente;

    public:
        EnvSensor(const string name,
                    const string description,
                    const unsigned int ID,
                    const vector<double> dati,
                    const double valoreCorrente);
        const vector<double> getDati()const ;
        double getValoreCorrente()const ;
        double media()const ;
        double valoreMin()const ;
        double valoreMax()const ;
        //void accept(IVisitor& visitor) override;
        //void accept(SConstVisitor& visitor) const override;

};

#endif // ENVSENSOR_H
