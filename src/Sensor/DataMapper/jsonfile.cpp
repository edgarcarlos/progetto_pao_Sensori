#include "jsonfile.h"
#include "../Converter/Json/reader.h"

//#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

namespace Sensor{
namespace DataMapper{

JsonFile::JsonFile(const std::string& path, Converter::Json::Json& converter): path(path), converter(converter) {}

JsonFile JsonFile::fromPath(const std::string& path) {
    Converter::Json::Reader reader;
    Converter::Json::Json converter(reader);
    JsonFile data_mapper(path, converter);
    return data_mapper;
}

const std::string& JsonFile::getPath() const {
    return path;
}

JsonFile& JsonFile::setPath(const std::string& path) {
    this->path = path;
    return *this;
}

const Converter::Json::Json& JsonFile::getConverter() const {
    return converter;
}

JsonFile& JsonFile::store(const std::vector<AbstractSensor*> sensors){
    QJsonArray json_sensors;
    for ( auto it = sensors.begin(); it != sensors.end(); it++ ) {
        json_sensors.push_back(converter.fromObject(**it));
    }
    QJsonDocument document(json_sensors);
    QFile json_file(path.c_str());
    json_file.open(QFile::WriteOnly);
    json_file.write(document.toJson());
    json_file.close();
    return *this;
}

std::vector<AbstractSensor*> JsonFile::load() {
    std::vector<AbstractSensor*> sensors;
    QFile json_file(path.c_str());

    // Vérification de l'ouverture du fichier
    if (!json_file.open(QFile::ReadOnly)) {
        throw std::ios_base::failure("Failed to open file for reading.");
    }

    QByteArray data = json_file.readAll();
    json_file.close();

    try {
        QJsonDocument document = QJsonDocument::fromJson(data);
        if (document.isNull()) {
            throw std::invalid_argument("Invalid JSON format.");
        }

        QJsonArray json_sensors = document.array();
        for (const QJsonValue& value: json_sensors) {
            QJsonObject json_object = value.toObject();
            sensors.push_back(converter.toObject(json_object));
        }
    } catch (const std::exception& e) {
        qDebug() << "Error parsing JSON:" << e.what();
        // Vous pouvez également enregistrer l'erreur ou effectuer une action corrective
    } catch (...) {
        qDebug() << "An unknown error occurred while parsing JSON.";
    }

    return sensors;
}

}
}


