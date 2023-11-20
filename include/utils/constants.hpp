#if !defined(CONSTANTS_H)
#define CONSTANTS_H

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

#define string_list std::list<std::string>
#define unsigned_list std::list<unsigned int>
#define model_list std::list<Model *>
#define json_list std::list<json>
#define field_type_list std::list<std::pair<std::string, unsigned int>>
#define id_to_model_map std::map<unsigned int, Model *>
#define model_name_to_data_ids_map std::map<std::string, std::list<unsigned int>>

#endif // CONSTANTS_H
