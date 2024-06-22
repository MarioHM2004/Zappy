#include "Team.hpp"
#include <algorithm>
#include <format>
#include <godot_cpp/variant/color.hpp>

zappy::Team::Team(std::string name) : _name(name)
{
    std::string randomHex = "#";
    for (int i = 0; i < 6; i++) {
        randomHex += std::format("{:x}", rand() % 16);
    }

    _color = godot::Color(randomHex.c_str());
}

std::string zappy::Team::get_name() const
{
    return _name;
}

std::size_t zappy::Team::get_max_count() const
{
    return _count;
}

std::size_t zappy::Team::get_size() const
{
    return _players.size();
}

void zappy::Team::set_max_count(std::size_t count)
{
    _count = count;
}

const zappy::Player &zappy::Team::get_player_at(std::size_t index)
{
    return *_players.at(index);
}

void zappy::Team::add_player(std::shared_ptr<zappy::Player> player)
{
    if (_players.size() >= _count) {
        return godot::UtilityFunctions::print(
            std::format(("Team `{}` is full"), _name).c_str());
    }

    _count += 1;
    player->lay_egg();
    player->set_accent_color(_color);
    _players.push_back(std::move(player));
}

void zappy::Team::remove_player(std::size_t id)
{
    std::erase_if(_players, [id](const std::shared_ptr<Player> &player) {
        return player->get_number() == id;
    });
}

void zappy::Team::clear_players()
{
    std::for_each(_players.begin(), _players.end(),
        [](const std::shared_ptr<Player> &player) {
            player->destroy();
        });
    _players.clear();
}
