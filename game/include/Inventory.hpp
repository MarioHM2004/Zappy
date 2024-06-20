#include "World.hpp"

#ifndef __INVENTORY
    #define __INVENTORY

namespace zappy
{
    using ResourceData = TileData;

    class Inventory {
      private:
        ResourceData _data;

      public:
        Inventory();
        ResourceData &get_all();
        std::size_t get_resource(ResourceType kind) const;

        void set_all(ResourceData data);
        void set_resource(ResourceType kind, std::size_t amount);
        void add_resource(ResourceType kind, std::size_t amount);
        void remove_resource(ResourceType kind, std::size_t amount);
        void clear_resource(ResourceType kind);
        void clear_all();
    };
} // namespace zappy

#endif /* __INVENTORY */
