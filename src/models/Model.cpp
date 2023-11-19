#include "models/Model.hpp"

std::string Model::name = "base_model";

Model::Model() {
    // need to be defined by the storage class
    id = -1;
}

unsigned int Model::get_id() {
    return this->id;
}

void Model::set_id(unsigned int id) {
    this->id = id;
}

std::string Model::get_class_name() {
    return name;
}