#if !defined(MODEL_H)
#define MODEL_H

#include <string>

class Model {
    public:
        static std::string name;
        unsigned int id;
        
        Model();
        
        unsigned int get_id();
        void set_id(unsigned int id);

        virtual std::string get_class_name();
};

#endif // MODEL_H
