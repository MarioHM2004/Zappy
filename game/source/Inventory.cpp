#include "Inventory.hpp"
#include <algorithm>

zappy::ResourceData &zappy::Inventory::get_all()
{
    return _data;
}

std::size_t zappy::Inventory::get_resource(zappy::ResourceType kind) const
{
    return _data.at(kind);
}

void zappy::Inventory::set_all(zappy::ResourceData data)
{
    _data = data;
}

void zappy::Inventory::set_resource(
    zappy::ResourceType kind, std::size_t amount)
{
    _data.at(kind) = amount;
}

void zappy::Inventory::add_resource(
    zappy::ResourceType kind, std::size_t amount)
{
    _data.at(kind) += amount;
}

void zappy::Inventory::remove_resource(
    zappy::ResourceType kind, std::size_t amount)
{
    _data.at(kind) -= amount;
}

void zappy::Inventory::clear_resource(zappy::ResourceType kind)
{
    set_resource(kind, 0);
}

void zappy::Inventory::clear_all()
{
    std::for_each(_data.begin(), _data.end(), [](std::size_t &resource) {
        resource = 0;
    });
}
