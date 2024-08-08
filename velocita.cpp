#include "velocita.h"

Velocita::Velocita(const string name,
                        const string description,
                        const unsigned int ID,
                        const Localisation positionAttuale,
                        const vector<Localisation> dati,
                        const PositionSensor position,
                        const vector<double> altitudeDati): PositionSensor(name,description,ID,positionAttuale,dati),
                                                            position(position),
                                                            altitudeDati(altitudeDati) {}


vector<double> Velocita::velocitaDati(const vector<double> altitudeDati) const {
        vector<double> velocita;
        if (altitudeDati.size() < 2) {
            return velocita;
        }

        for (unsigned int i = 1; i < altitudeDati.size(); ++i) {
            double spazio = altitudeDati[i] - altitudeDati[i - 1];
            double tempo = 1.0; //tempo costante fra le misure
            double vel = spazio / tempo;
            velocita.push_back(vel);
        }

        return velocita;
}

double Velocita::velocitaMedia()const {

    double distanzaTotale = 0.0;
    
    for(unsigned int i=1; i<altitudeDati.size(); i++){
        double spazio = altitudeDati[i] - altitudeDati[i-1];
        distanzaTotale += spazio;
    }

    double tempoTot = altitudeDati.size()-1;
    
    return distanzaTotale/tempoTot;
}
 
double Velocita::accelerazione(vector<double> velocitaDati)const {
    double difTotale = 0.0;
    
    for(unsigned int i=1; i<velocitaDati.size(); i++){
        difTotale = velocitaDati[i] - velocitaDati[i-1];
         
    }

    double tempoTot = velocitaDati.size()-1;
    
    return difTotale/tempoTot;


}
