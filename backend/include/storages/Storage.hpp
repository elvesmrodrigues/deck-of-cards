#if !defined(DATA_STORAGE_H)
#define DATA_STORAGE_H

#include <iostream>
#include <list>
#include <map>

#include "../models/Model.hpp"
#include "../../libs/nlohmann/json.hpp"

class Storage {
    private:
        Storage();
        Storage(const Storage &) = delete;
        Storage & operator=(const Storage &) = delete;

        unsigned int _id_iterator = 0;
        std::map<unsigned int, Model *> _data; 
        std::map<std::string, std::list<unsigned int>> _model_ids;

    public:
        static Storage & get_instance();

        unsigned int save(Model * model);
        void update(unsigned int id, Model * model);
        
        Model * retrieve(unsigned int &id);
        std::list<Model *> batch_retrieve(std::list<unsigned int> &ids);
        std::list<Model *> retrieve_all(const std::string model_name);

        void remove(const std::string model_name, unsigned int &id);

        bool exists(unsigned int &id);

        ~Storage();
};

#endif // DATA_STORAGE_H
