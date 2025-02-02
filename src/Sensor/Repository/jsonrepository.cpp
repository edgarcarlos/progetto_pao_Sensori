#include "jsonrepository.h"
#include "../Converter/Json/reader.h"
#include "../Converter/Json/json.h"

//#include <stdexcept>

namespace Sensor {
namespace Repository {



JsonRepository::JsonRepository(DataMapper::JsonFile data_mapper)
    : data_mapper(data_mapper)
{
    std::vector<AbstractSensor*> sensor(data_mapper.load());
    for (auto it = sensor.begin(); it != sensor.end(); ++it){
        repository[(*it)->getID()] = *it;
    }

}

JsonRepository::~JsonRepository(){
    for (auto it = repository.begin(); it != repository.end(); ++it){
        delete it->second;
    }
}

JsonRepository JsonRepository::fromPath(const std::string path){
    Converter::Json::Reader reader;
    Converter::Json::Json converter(reader);
    DataMapper::JsonFile data_mapper(path, converter);
    JsonRepository repository(data_mapper);
    return repository;
}

const DataMapper::JsonFile& JsonRepository::getDataMapper() const{
    return data_mapper;
}
const std::map<unsigned int, AbstractSensor*>& JsonRepository::getRepository() const{
    return repository;
}
const std::string& JsonRepository::getPath() const{
    return data_mapper.getPath();
}
JsonRepository& JsonRepository::setPath(std::string path){
    data_mapper.setPath(path);
    return *this;
}

JsonRepository& JsonRepository::create(AbstractSensor* sensor){
    if (!sensor) {
        qDebug() << "Error: Trying to create a sensor with a null pointer.";
        return *this;
    }

    repository[sensor->getID()] = sensor;
    return *this;
}

AbstractSensor* JsonRepository::read(const unsigned int identifier) const{
    auto it = repository.find(identifier);
    if (it != repository.end()) {   // nel caso non venga ritrovato
        return it->second;
    } else {
        return nullptr;
    }
}

JsonRepository& JsonRepository::update(AbstractSensor* item){

    return create(item);
}

JsonRepository& JsonRepository::remove(const unsigned int identifier) {
    std::map<unsigned int, AbstractSensor*>::const_iterator it = repository.find(identifier);
    if (it != repository.end()) {
        delete it->second;
        repository.erase(it);
    }
    return *this;
}

JsonRepository& JsonRepository::erase(const unsigned int identifier) {
    std::map<unsigned int, AbstractSensor*>::const_iterator it = repository.find(identifier);
    if (it != repository.end()) {
        repository.erase(it);
    }
    return *this;
}

std::vector<AbstractSensor*> JsonRepository::readAll() const{
    std::vector<AbstractSensor*> sensors;
    for (auto it = repository.begin(); it != repository.end(); ++it ) {
        sensors.push_back(it->second);
    }
    return sensors;
}

JsonRepository& JsonRepository::store(){
    data_mapper.store(readAll());
    return *this;
}

bool JsonRepository::empty() const{
    return repository.empty();
}


}
}



