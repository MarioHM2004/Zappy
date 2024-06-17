#include <string_view>

#ifndef __COMMON
    #define __COMMON

namespace zappy
{
    class Constants {
      public:
        class Commands {
          public:
            static constexpr std::string_view MAP_SIZE = "msz";
            static constexpr std::string_view TILE_CONTENT = "bct";
            static constexpr std::string_view MAP_CONTENT = "mct";
            static constexpr std::string_view TEAM_NAMES = "tna";
            static constexpr std::string_view PLAYER_POSITION = "ppo";
            static constexpr std::string_view PLAYER_LEVEL = "plv";
            static constexpr std::string_view PLAYER_INVENTORY = "pin";
            static constexpr std::string_view TIME_UNIT_REQUEST = "sgt";
            static constexpr std::string_view TIME_UNIT_MODIFICATION = "sst";
            static constexpr std::string_view ECHO = "echo";
        };
        class Signals {
          public:
            static constexpr std::string_view SERVER_INACCESSIBLE = "soff";
            static constexpr std::string_view SERVER_CONNECTED = "scon";
            static constexpr std::string_view WORLD_SIZE = "wsize";
        };
    };
} // namespace zappy

#endif /* __COMMON */
