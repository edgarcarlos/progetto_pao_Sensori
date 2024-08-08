#include "temperatura.h"

Temperatura::Temperatura(const string name,
                    const string description,
                    const unsigned int ID,
                    const vector<double> dati,
                    const double valoreCorrente,
                    const double Tmin,
                    const double Tmax): EnvSensor(name,description,ID,dati,valoreCorrente),
                                        Tmin(Tmin),
                                        Tmax(Tmax) {}

string Temperatura::stato(double valoreCorrente)const {

    if(valoreCorrente <= Tmin) return string("Basso");
    else if(Tmin < valoreCorrente < Tmax) return string("Normale");
    else if(valoreCorrente >= Tmax) return string("Elevato");
    else return string("errore");
}

const double& Temperatura::getTmin() const{
    return Tmin;
}
const double& Temperatura::getTmax() const{
    return Tmax;
}
