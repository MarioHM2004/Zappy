#include "World.hpp"
#include <string_view>

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
    return _map.at(x).at(y).at(resource);
}

void zappy::World::set_resource(
    std::size_t x, std::size_t y, ResourceType resource, std::size_t amount)
{
    _map.at(x).at(y).at(resource) = amount;
}

void zappy::World::add_resource(
    std::size_t x, std::size_t y, ResourceType resource, std::size_t amount)
{
    _map.at(x).at(y).at(resource) += amount;
}

void zappy::World::remove_resource(
    std::size_t x, std::size_t y, ResourceType resource, std::size_t amount)
{
    _map.at(x).at(y).at(resource) -= amount;
}

void zappy::World::clear_tile(std::size_t x, std::size_t y)
{
    get_tile(x, y) = {0, 0, 0, 0, 0, 0, 0};
}

void zappy::World::clear()
{
    std::for_each(_map.begin(), _map.end(), [](std::vector<TileData> &row) {
        std::for_each(row.begin(), row.end(), [](TileData &tile) {
            tile = {0, 0, 0, 0, 0, 0, 0};
        });
    });
}

std::string zappy::World::dump() const
{
    std::string result;
    for (const std::vector<TileData> &row : _map) {
        for (const TileData &tile : row) {
            for (std::size_t resource : tile) {
                result += std::to_string(resource) + " ";
            }
            result += "\n";
        }
    }
    return result;
}

std::string zappy::World::resource_to_string(ResourceType resource)
{
    switch (resource) {
        case FOOD: return "create_food";
        case LINEMATE: return "create_linemate";
        case DERAUMERE: return "create_deraumere";
        case SIBUR: return "create_sibur";
        case MENDIANE: return "create_mendiane";
        case PHIRAS: return "create_phiras";
        case THYSTAME: return "create_thystame";
        case EGGY: return "create_egg";
        default: return "";
    }
}
