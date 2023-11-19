#if !defined(CARD_MODEL_H)
#define CARD_MODEL_H

// suits
#define CARD_SUIT_HEARTS "HEARTS"
#define CARD_SUIT_SPADES "SPADES"
#define CARD_SUIT_CLUBS "CLUBS"
#define CARD_SUIT_DIAMONDS "DIAMONDS"

#define CARD_FACE_ACE "ACE"
#define CARD_FACE_2 "2"
#define CARD_FACE_3 "3"
#define CARD_FACE_4 "4"
#define CARD_FACE_5 "5"
#define CARD_FACE_6 "6"
#define CARD_FACE_7 "7"
#define CARD_FACE_8 "8"
#define CARD_FACE_9 "9"
#define CARD_FACE_10 "10"
#define CARD_FACE_JACK "JACK"
#define CARD_FACE_QUEEN "QUEEN"
#define CARD_FACE_KING "KING"

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

        std::string get_class_name() override;
        std::string repr();
};

#endif // CARD_MODEL_H
