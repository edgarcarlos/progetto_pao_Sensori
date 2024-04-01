#include "temperatura.h"

Temperatura::Temperatura(const string name,
                    const string descrizione,
                    const string logo_path,
                    const string ID,
                    const vector<double> dati,
                    const double valoreCorrente,
                    const string unita,
                    const double Tmin,
                    const double Tmax): EnvSensor(name,descrizione,logo_path,ID,dati,valoreCorrente,unita),
                                        Tmin(Tmin),
                                        Tmax(Tmax) {}

string Temperatura::stato(double valoreCorrente)const {

    if(valoreCorrente <= Tmin) return string("Basso");
    else if(Tmin < valoreCorrente < Tmax) return string("Normale");
    else if(valoreCorrente >= Tmax) return string("Elevato");
}
