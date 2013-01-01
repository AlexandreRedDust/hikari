#ifndef HIKARI_CORE_GAME_MAP_MAPLOADER
#define HIKARI_CORE_GAME_MAP_MAPLOADER

#include <hikari/core/Platform.hpp>
#include <hikari/core/geom/Rectangle2D.hpp>
#include <hikari/core/util/Service.hpp>
#include <hikari/core/util/TilesetCache.hpp>

#include <memory>
#include <json/value.h>
#include <string>

namespace hikari {

    class TilesetCache;
    class Map;
    class Room;
    class RoomTransition;
    class Spawner;

    typedef std::shared_ptr<Map> MapPtr;
    typedef std::shared_ptr<Room> RoomPtr;
    typedef std::shared_ptr<Spawner> SpawnerPtr;

    class HIKARI_API MapLoader : public Service {
    private:
        static const char* PROPERTY_NAME_TILESET;
        static const char* PROPERTY_NAME_ROOMS;
        static const char* PROPERTY_NAME_GRIDSIZE;
        static const char* PROPERTY_NAME_ROOM_ID;
        static const char* PROPERTY_NAME_ROOM_X;
        static const char* PROPERTY_NAME_ROOM_Y;
        static const char* PROPERTY_NAME_ROOM_WIDTH;
        static const char* PROPERTY_NAME_ROOM_HEIGHT;
        static const char* PROPERTY_NAME_ROOM_CAMERABOUNDS;
        static const char* PROPERTY_NAME_ROOM_CAMERABOUNDS_X;
        static const char* PROPERTY_NAME_ROOM_CAMERABOUNDS_Y;
        static const char* PROPERTY_NAME_ROOM_CAMERABOUNDS_WIDTH;
        static const char* PROPERTY_NAME_ROOM_CAMERABOUNDS_HEIGHT;
        static const char* PROPERTY_NAME_ROOM_TILE;
        static const char* PROPERTY_NAME_ROOM_TILEATTRIBUTES;
        static const char* PROPERTY_NAME_ROOM_ENEMIES;
        static const char* PROPERTY_NAME_ROOM_ENEMIES_TYPE;
        static const char* PROPERTY_NAME_ROOM_ENEMIES_POSITION;
        static const char* PROPERTY_NAME_ROOM_ENEMIES_POSITION_X;
        static const char* PROPERTY_NAME_ROOM_ENEMIES_POSITION_Y;
        static const char* PROPERTY_NAME_ROOM_ENEMIES_DIRECTION;
        static const char* PROPERTY_NAME_ROOM_ITEMS;
        static const char* PROPERTY_NAME_ROOM_TRANSITIONS;

        std::shared_ptr<TilesetCache> tilesetCache;

        MapPtr constructMap(const Json::Value &json) const;
        RoomPtr constructRoom(const Json::Value &json, const int &gridSize) const;
        const SpawnerPtr constructSpawner(const Json::Value &json) const;
        const RoomTransition constructTransition(const Json::Value &json) const;
        const Rectangle2D<int> constructCameraBounds(const Json::Value &json, 
                const int &roomX, const int &roomY, const int &gridSize) const;
        bool validateMapStructure(const Json::Value &json) const;
        bool validateRoomStructure(const Json::Value &json) const;

    public:
        MapLoader(const std::shared_ptr<TilesetCache> &tilesetCache);
        virtual ~MapLoader();
        MapPtr loadFromJson(const Json::Value &json) const;
    };

} // hikari

#endif // HIKARI_CORE_GAME_MAP_MAPLOADER