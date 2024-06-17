#include "Team.hpp"
#include <format>

zappy::Team::Team(std::string name) : _name(name)
{
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

void zappy::Team::add_player(std::unique_ptr<zappy::Player> player)
{
    if (_players.size() >= _count) {
        return godot::UtilityFunctions::print(
            std::format(("Team `{}` is full"), _name).c_str());
    }

    _count += 1;
    _color = _color * (1.0f - 0.1f * _players.size());
    player->tint(_color);
    _players.push_back(std::move(player));
}
