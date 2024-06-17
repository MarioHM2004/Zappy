#include "Team.hpp"

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

void zappy::Team::add_player(std::size_t number, godot::Vector3 position)
{
    if (_players.size() >= _count) {
        return;
    }

    _count += 1;
    _players.push_back(std::make_unique<Player>(number, position));
}
