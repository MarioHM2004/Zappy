#include <memory>
#include <string>
#include <vector>
#include "Player.hpp"

#ifndef __TEAM
    #define __TEAM

namespace zappy
{
    class Team {
      private:
        std::string _name;
        std::size_t _count = 6; // TODO(jabolo): Use the correct value
        std::vector<std::unique_ptr<Player>> _players;

      public:
        Team(std::string name);

        std::string get_name() const;
        std::size_t get_max_count() const;
        std::size_t get_size() const;

        void set_max_count(std::size_t count);
        const Player &get_player_at(std::size_t index);
        void add_player(std::size_t number, godot::Vector3 position);
    };
} // namespace zappy

#endif /* __TEAM */