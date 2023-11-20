#if !defined(DECK_MODEL_H)
#define DECK_MODEL_H

#include <list>
#include <cstdlib>

#include "./Model.hpp"

class Deck: public Model {
    private:
        unsigned_list * _card_ids;

    public:
        static std::string name;

        Deck(unsigned_list * card_ids);

        unsigned_list get_card_ids();

        std::string get_class_name() override;
        
        ~Deck();
};

#endif // DECK_MODEL_H
