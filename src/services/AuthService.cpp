#include "services/AuthService.hpp"

void login(const httplib::Request &req, httplib::Response &res) {
    json data = Service::body_to_json(req);
    
    // std::list<std::string> required_values = {"player_id", "password"};
    // if (!Service::has_required_fields(req, res, required_values)) 
    //     return;

    // json::is_binary
}

void logout(const httplib::Request &req, httplib::Response &res) {

}