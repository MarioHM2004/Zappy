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
        class ArgCount {
          public:
            static constexpr int BAD_PARAMETER = 1;
            static constexpr int BROADCAST = 3;
            static constexpr int ECHO = 1;
            static constexpr int END_GAME = 2;
            static constexpr int END_INCANTATION = 4;
            static constexpr int EGG_CONNECTION = 2;
            static constexpr int EGG_DEATH = 2;
            static constexpr int EGG_LAID = 5;
            static constexpr int EGG_LAYING = 2;
            static constexpr int MAP_SIZE = 3;
            static constexpr int PLAYER_DEATH = 2;
            static constexpr int PLAYER_EXPULSION = 2;
            static constexpr int PLAYER_INVENTORY = 11;
            static constexpr int PLAYER_JOINED = 7;
            static constexpr int PLAYER_LEVEL = 3;
            static constexpr int PLAYER_POSITION = 5;
            static constexpr int RESOURCE_COLLECTING = 3;
            static constexpr int RESOURCE_DROPPING = 3;
            static constexpr int SERVER_KO = 1;
            static constexpr int SERVER_MESSAGE = 2;
            static constexpr int SERVER_OPEN = 1;
            static constexpr int START_INCANTATION = 5;
            static constexpr int TEAM_NAMES = 2;
            static constexpr int TILE_CONTENT = 10;
            static constexpr int TIME_UNIT_MODIFICATION = 2;
            static constexpr int TIME_UNIT_REQUEST = 2;
            static constexpr int UNKNOWN_COMMAND = 1;
        };
    };

    #define CHECK_ARGCOUNT(key, count)                                 \
        if (count < zappy::Constants::ArgCount::key) {                 \
            emit_signal("error",                                       \
                std::format("Invalid argument count for command '{}'", \
                    zappy::Constants::Commands::key)                   \
                    .c_str());                                         \
            return;                                                    \
        }
} // namespace zappy

#endif /* __COMMON */
