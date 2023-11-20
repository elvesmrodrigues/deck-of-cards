#if !defined(CONSTANTS_H)
#define CONSTANTS_H

#define string_list std::list<std::string>
#define unsigned_list std::list<unsigned int>
#define model_list std::list<Model *>
#define json_list std::list<json>
#define field_type_list std::list<std::pair<std::string, unsigned int>>
#define id_to_model_map std::map<unsigned int, Model *>
#define model_name_to_data_ids_map std::map<std::string, std::list<unsigned int>>

#endif // CONSTANTS_H
