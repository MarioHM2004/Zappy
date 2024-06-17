#include <string_view>

#ifndef __COMMON
    #define __COMMON

namespace zappy
{
    class Constants {
      public:
        static constexpr std::string_view TEAM_NAME = "GRAPHIC";
        class Commands {
          public:
            static constexpr std::string_view BAD_PARAMETER = "sbp";
            static constexpr std::string_view BROADCAST = "pbc";
            static constexpr std::string_view ECHO = "echo";
            static constexpr std::string_view END_GAME = "seg";
            static constexpr std::string_view END_INCANTATION = "pie";
            static constexpr std::string_view EGG_CONNECTION = "ebo";
            static constexpr std::string_view EGG_DEATH = "edi";
            static constexpr std::string_view EGG_LAID = "enw";
            static constexpr std::string_view EGG_LAYING = "pfk";
            static constexpr std::string_view MAP_CONTENT = "mct";
            static constexpr std::string_view MAP_SIZE = "msz";
            static constexpr std::string_view PLAYER_DEATH = "pdi";
            static constexpr std::string_view PLAYER_EXPULSION = "pex";
            static constexpr std::string_view PLAYER_INVENTORY = "pin";
            static constexpr std::string_view PLAYER_JOINED = "pnw";
            static constexpr std::string_view PLAYER_LEVEL = "plv";
            static constexpr std::string_view PLAYER_POSITION = "ppo";
            static constexpr std::string_view RESOURCE_COLLECTING = "pgt";
            static constexpr std::string_view RESOURCE_DROPPING = "pdr";
            static constexpr std::string_view SERVER_KO = "ko";
            static constexpr std::string_view SERVER_MESSAGE = "smg";
            static constexpr std::string_view SERVER_OPEN = "welcome";
            static constexpr std::string_view START_INCANTATION = "pic";
            static constexpr std::string_view TEAM_NAMES = "tna";
            static constexpr std::string_view TILE_CONTENT = "bct";
            static constexpr std::string_view TIME_UNIT_MODIFICATION = "sst";
            static constexpr std::string_view TIME_UNIT_REQUEST = "sgt";
            static constexpr std::string_view UNKNOWN_COMMAND = "suc";
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
