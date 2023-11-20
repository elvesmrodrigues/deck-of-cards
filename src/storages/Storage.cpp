#include <iostream>
#include "storages/Storage.hpp"

Storage::Storage() {
    this->_id_iterator = 1;
}

Storage & Storage::get_instance() {
    static Storage instance;
    return instance;
}

unsigned int Storage::save(Model * model) {
    unsigned int data_id = this->_id_iterator;
    
    model->set_id(data_id);
    this->_data[data_id] = model;
    
    this->_model_ids[model->get_class_name()].push_back(data_id);

    this->_id_iterator++;
    return data_id;
}

void Storage::update(unsigned int id, Model * model) {
    this->_data[id] = model;
}

Model * Storage::retrieve(unsigned int &id) {
    return this->_data[id];
}

model_list Storage::batch_retrieve(unsigned_list &ids) {
    model_list data;
    unsigned_list::iterator iter = ids.begin();

    unsigned int id;

    while(iter != ids.end()) {
        id = *iter;
        data.push_back(this->_data[id]);
        iter++;
    }
    return data;
}

model_list Storage::retrieve_all(const std::string model_name) {
    return this->batch_retrieve(this->_model_ids[model_name]);
}

void Storage::remove(const std::string model_name, unsigned int &id) {
    std::map<unsigned int, Model *>::iterator iter = this->_data.find(id);
    if (iter != this->_data.end())
        this->_data.erase(iter);

    this->_model_ids[model_name].remove(id);  
}

bool Storage::exists(const std::string & model_name, unsigned int &id) {
    std::list<unsigned int>::iterator it = std::find(this->_model_ids[model_name].begin(), this->_model_ids[model_name].end(), id);
    return it != this->_model_ids[model_name].end();
}

Storage::~Storage() {
    for (auto &pair : this->_data) {
        delete pair.second;
    }
}