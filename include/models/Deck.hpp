#if !defined(DECK_MODEL_H)
#define DECK_MODEL_H

#include <list>
#include <cstdlib>

#include "./Model.hpp"

class Deck: public Model {
    private:
        std::list<unsigned int> * _card_ids;

    public:
        static std::string name;

        Deck(std::list<unsigned int> * card_ids);

        std::list<unsigned int> get_card_ids();

        std::string get_class_name() override;
        ~Deck();
};

#endif // DECK_MODEL_H
