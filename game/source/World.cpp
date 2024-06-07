#include "World.hpp"

zappy::World::World(std::size_t x, std::size_t y)
    : _map(x, std::vector<TileData>(y))
{
}

std::pair<std::size_t, std::size_t> zappy::World::get_size() const
{
    return {_map.at(0).size(), _map.size()};
}

zappy::TileData &zappy::World::get_tile(std::size_t x, std::size_t y)
{
    return _map.at(y).at(x);
}

const zappy::TileData &zappy::World::get_tile(
    std::size_t x, std::size_t y) const
{
    return _map.at(y).at(x);
}

std::size_t zappy::World::get_resource(
    std::size_t x, std::size_t y, ResourceType resource) const
{
    return _map.at(x).at(y).at(static_cast<std::size_t>(resource));
}

void zappy::World::set_resource(
    std::size_t x, std::size_t y, ResourceType resource, std::size_t amount)
{
    _map.at(x).at(y).at(static_cast<std::size_t>(resource)) = amount;
}

void zappy::World::add_resource(
    std::size_t x, std::size_t y, ResourceType resource, std::size_t amount)
{
    _map.at(x).at(y).at(static_cast<std::size_t>(resource)) += amount;
}

void zappy::World::remove_resource(
    std::size_t x, std::size_t y, ResourceType resource, std::size_t amount)
{
    _map.at(x).at(y).at(static_cast<std::size_t>(resource)) -= amount;
}

void zappy::World::clear_tile(std::size_t x, std::size_t y)
{
    get_tile(x, y) = {0, 0, 0, 0, 0, 0, 0};
}

void zappy::World::clear()
{
    for (std::size_t y = 0; y < _map.size(); ++y) {
        for (std::size_t x = 0; x < _map.at(0).size(); ++x) {
            clear_tile(x, y);
        }
    }
}
