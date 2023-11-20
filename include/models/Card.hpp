#if !defined(CARD_MODEL_H)
#define CARD_MODEL_H

#include <string>

#include "./Model.hpp"

class Card: public Model {
    private:
        std::string _suit;
        std::string _face;
        int _value;
        
        void _calculate_value();

    public:
        static std::string name;

        Card(std::string suit, std::string face);

        std::string get_suit();
        std::string get_face();
        
        int get_value();
        std::string repr();

        std::string get_class_name() override;
};

#endif // CARD_MODEL_H
