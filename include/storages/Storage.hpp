#if !defined(DATA_STORAGE_H)
#define DATA_STORAGE_H

#include <iostream>
#include <list>
#include <map>
#include <algorithm>

#include "../utils/constants.hpp"
#include "../models/Model.hpp"
#include "../../libs/nlohmann/json.hpp"

class Storage {
    private:
        Storage();
        Storage(const Storage &) = delete;
        Storage & operator=(const Storage &) = delete;

        unsigned int _id_iterator = 0;
        model_name_to_data_ids_map _model_ids;

    public:
        id_to_model_map _data; 
        static Storage & get_instance();

        unsigned int save(Model * model);
        void update(unsigned int id, Model * model);
        
        Model * retrieve(unsigned int &id);
        model_list batch_retrieve(unsigned_list &ids);
        model_list retrieve_all(const std::string model_name);

        void remove(const std::string model_name, unsigned int &id);

        bool exists(const std::string & model_name, unsigned int &id);

};

#endif // DATA_STORAGE_H
