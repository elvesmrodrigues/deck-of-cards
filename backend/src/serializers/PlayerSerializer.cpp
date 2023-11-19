#include "serializers/PlayerSerializer.hpp"

json PlayerSerializer::serialize(Player & player) {
    json data;

    data["id"] = player.get_id();
    data["name"] = player.get_name();
    data["cards"] = player.get_card_ids();

    if (player.is_playing())
        data["playing_game"] = player.get_game_playing();
    
    else
        data["playing_game"] = nullptr;

    return data;
}