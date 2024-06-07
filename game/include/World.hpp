#include <array>
#include <vector>

#ifndef __WORLD
    #define __WORLD

namespace zappy
{
    constexpr std::size_t RESOURCE_COUNT = 7;
    using TileData = std::array<std::size_t, RESOURCE_COUNT>;

    enum class ResourceType {
        FOOD = 0,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };

    class World {
      private:
        std::vector<std::vector<TileData>> _map;

      public:
        World(std::size_t x, std::size_t y);
        ~World() = default;

        World(const World &) = delete;
        World &operator=(const World &) = delete;

        World(World &&) = default;
        World &operator=(World &&) = default;

        std::pair<std::size_t, std::size_t> get_size() const;
        TileData &get_tile(std::size_t x, std::size_t y);
        const TileData &get_tile(std::size_t x, std::size_t y) const;
        std::size_t get_resource(
            std::size_t x, std::size_t y, ResourceType resource) const;
        void set_resource(std::size_t x, std::size_t y, ResourceType resource,
            std::size_t amount);
        void add_resource(std::size_t x, std::size_t y, ResourceType resource,
            std::size_t amount);
        void remove_resource(std::size_t x, std::size_t y,
            ResourceType resource, std::size_t amount);
        void clear_tile(std::size_t x, std::size_t y);
        void clear();
    };
} // namespace zappy

#endif /* __WORLD */
