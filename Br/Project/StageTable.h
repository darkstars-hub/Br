//!-----------------------------------------------------
//! @file : StageTable.h
//! @brief : Tile._type(éØï î‘çÜ)ÇÃëŒâûïtÇØÇíËã`
//!          â…Ç…Ç»Ç¡ÇΩÇÁäOïîÇ…à⁄Ç∑
//! @date : 2020/05/31
//!-----------------------------------------------------

#ifndef BR_STAGE_TABLE_H
#define BR_STAGE_TABLE_H


#include <string>
#include <unordered_map>
#include <Mof.h>

#include "Common.h"


struct TilePart {
    const char* name;
//    std::string name;
    std::string path;
    Mof::CRectangle render_rect;
    int cost = 1;
};

namespace def {
static const std::unordered_map<int, TilePart> tile_table = {
    { 0, { "road",      "Resource/textures/tiles.png", CRectangle(2.0f, 2.0f, 34.0f, 34.0f),        1 } },
    { 1, { "grass",     "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),     1 } },
    { 2, { "gravel",    "Resource/textures/tiles.png", CRectangle(2.0f, 206.0f, 34.0f, 238.0f),     1 } },
    { 3, { "meadow",    "Resource/textures/tiles.png", CRectangle(240.0f, 2.0f, 272.0f, 34.0f),     3 } },
    { 4, { "rock",      "Resource/textures/tiles.png", CRectangle(240.0f, 546.0f, 272.0f, 578.0f),  99 } },
    { 5, { "lake",      "Resource/textures/tiles.png", CRectangle(376.0f, 36.0f, 408.0f, 68.0f),    7 } },
    { 6, { "flower",    "Resource/textures/tiles.png", CRectangle(240.0f, 70.0f, 272.0f, 102.0f),   1 } },
    { 7, { "rock",      "Resource/textures/tiles.png", CRectangle(222.0f, 104.0f, 264.0f, 136.0f) } },
    { 8, { "rock",      "Resource/textures/tiles.png", CRectangle(222.0f, 104.0f, 264.0f, 136.0f) } },
    { 9, { "rock",      "Resource/textures/tiles.png", CRectangle(222.0f, 104.0f, 264.0f, 136.0f) } },

    { 10, { "road_0",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 11, { "road_1",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 12, { "road_2",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 13, { "road_3",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 14, { "road_4",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 15, { "road_5",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 16, { "road_6",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 17, { "road_7",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 18, { "road_8",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 19, { "road_9",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 20, { "road_10",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 21, { "road_11",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 22, { "road_12",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 23, { "road_13",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 24, { "grass_0",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 25, { "grass_1",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 26, { "grass_2",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 27, { "grass_3",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 28, { "grass_4",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 29, { "grass_5",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 30, { "grass_6",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 31, { "grass_7",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 32, { "grass_8",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 33, { "grass_9",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 34, { "grass_10",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 35, { "grass_11",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f),1 } },
    { 36, { "grass_12",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },
    { 37, { "grass_13",      "Resource/textures/tiles.png", CRectangle(2.0f, 104.0f, 34.0f, 136.0f) ,1} },



    { 38, { "grass2_0",      "Resource/textures/grass2.png", CRectangle(0.0f,   0.0f,   32.0f,  32.0f),    1 } },
    { 39, { "grass2_1",      "Resource/textures/grass2.png", CRectangle(32.0f,  0.0f,   64.0f,  32.0f),    1 } },
    { 40, { "grass2_2",      "Resource/textures/grass2.png", CRectangle(64.0f,  0.0f,   96.0f,  32.0f),    1 } },
    { 41, { "grass2_3",      "Resource/textures/grass2.png", CRectangle(96.0f,  0.0f,  128.0f,  32.0f),    1 } },
    { 42, { "grass2_4",      "Resource/textures/grass2.png", CRectangle(128.0f, 0.0f,  160.0f,  32.0f),    1 } },
    { 43, { "grass2_5",      "Resource/textures/grass2.png", CRectangle(32.0f,  32.0f,  64.0f,  64.0f),    1 } },
    { 44, { "grass2_6",      "Resource/textures/grass2.png", CRectangle(64.0f,  32.0f,  96.0f,  64.0f),    1 } },
    { 45, { "grass2_7",      "Resource/textures/grass2.png", CRectangle(96.0f,  32.0f, 128.0f,  64.0f),    1 } },
    { 46, { "grass2_8",      "Resource/textures/grass2.png", CRectangle(128.0f, 32.0f, 160.0f,  64.0f),    1 } },
    { 47, { "grass2_9",      "Resource/textures/grass2.png", CRectangle(32.0f,  64.0f,  64.0f,  96.0f),    1 } },
    { 48, { "grass2_10",     "Resource/textures/grass2.png", CRectangle(64.0f,  64.0f,  96.0f,  96.0f),    1 } },
    { 49, { "grass2_11",     "Resource/textures/grass2.png", CRectangle(96.0f,  64.0f, 128.0f,  96.0f),    1 } },
    { 50, { "grass2_12",     "Resource/textures/grass2.png", CRectangle(128.0f, 64.0f, 160.0f,  96.0f),    1 } },



    { 150, { "meadow_0",     "Resource/textures/meadow2.png", CRectangle(32.0f, 0.0f, 64.0f,  32.0f),    3 } },
    { 151, { "meadow_1",     "Resource/textures/meadow2.png", CRectangle(0.0f, 0.0f, 32.0f,  32.0f),    1 } },
    { 152, { "meadow_2",     "Resource/textures/meadow2.png", CRectangle(0.0f, 32.0f, 32.0f,  64.0f),    1 } },
    { 153, { "meadow_3",     "Resource/textures/meadow2.png", CRectangle(32.0f, 32.0f, 64.0f,  64.0f),    1 } },
    { 154, { "meadow_4",     "Resource/textures/meadow2.png", CRectangle(0.0f, 64.0f, 32.0f,  96.0f),    1 } },
    { 155, { "flower_0",     "Resource/textures/meadow2.png", CRectangle(32.0f, 64.0f, 64.0f,  96.0f),    1 } },
    { 156, { "vine_0",       "Resource/textures/meadow2.png", CRectangle(64.0f, 0.0f, 96.0f,  32.0f),    1 } },

    { 251, { "fence_1",     "Resource/textures/fence.png", CRectangle(32.0f, 0.0f, 64.0f,  32.0f),   99 } },



    { 300, { "lake_0",       "Resource/textures/lake.png", CRectangle(0.0f,  0.0f,   32.0f,  32.0f),    5 } },
    { 301, { "lake_1",       "Resource/textures/lake.png", CRectangle(32.0f, 0.0f,   64.0f,  32.0f),    5 } },
    { 302, { "lake_2",       "Resource/textures/lake.png", CRectangle(64.0f, 0.0f,   96.0f,  32.0f),    5 } },
    { 303, { "lake_3",       "Resource/textures/lake.png", CRectangle(0.0f,  32.0f,  32.0f,  64.0f),    5 } },
    { 304, { "lake_4",       "Resource/textures/lake.png", CRectangle(32.0f, 32.0f,  64.0f,  64.0f),    5 } },
    { 305, { "lake_5",       "Resource/textures/lake.png", CRectangle(64.0f, 32.0f,  96.0f,  64.0f),    5 } },
    { 306, { "lake_6",       "Resource/textures/lake.png", CRectangle(0.0f,  64.0f,  32.0f,  96.0f),    5 } },
    { 307, { "lake_7",       "Resource/textures/lake.png", CRectangle(32.0f, 64.0f,  64.0f,  96.0f),    5 } },
    { 308, { "lake_8",       "Resource/textures/lake.png", CRectangle(64.0f, 64.0f,  96.0f,  96.0f),    5 } },

    { 310, { "lake2_0",       "Resource/textures/lake.png", CRectangle(0.0f,  96.0f,   32.0f,  128.0f),    5 } },
    { 311, { "lake2_1",       "Resource/textures/lake.png", CRectangle(32.0f, 96.0f,   64.0f,  128.0f),    5 } },
    { 312, { "lake2_2",       "Resource/textures/lake.png", CRectangle(64.0f, 96.0f,   96.0f,  128.0f),    5 } },
    { 313, { "lake2_3",       "Resource/textures/lake.png", CRectangle(0.0f,  128.0f,  32.0f, 160.0f),    5 } },
    { 314, { "lake2_4",       "Resource/textures/lake.png", CRectangle(32.0f, 128.0f,  64.0f, 160.0f),    5 } },
    { 315, { "lake2_5",       "Resource/textures/lake.png", CRectangle(64.0f, 128.0f,  96.0f, 160.0f),    5 } },
    { 316, { "lake2_6",       "Resource/textures/lake.png", CRectangle(0.0f,  160.0f,  32.0f, 192.0f),    5 } },
    { 317, { "lake2_7",       "Resource/textures/lake.png", CRectangle(32.0f, 160.0f,  64.0f, 192.0f),    5 } },
    { 318, { "lake2_8",       "Resource/textures/lake.png", CRectangle(64.0f, 160.0f,  96.0f, 192.0f),    5 } },


    { 450, { "tree_0",      "Resource/textures/tree.png", CRectangle(0.0f,    0.0f,    32.0f,   32.0f),  99 } },
    { 451, { "tree_1",      "Resource/textures/tree.png", CRectangle(32.0f,   0.0f,    64.0f,   32.0f),  99 } },
    { 452, { "tree_2",      "Resource/textures/tree.png", CRectangle(64.0f,   0.0f,    96.0f,   32.0f),  99 } },
    { 453, { "tree_3",      "Resource/textures/tree.png", CRectangle(96.0f,   0.0f,    128.0f,   32.0f),  99 } },
    { 454, { "tree_4",      "Resource/textures/tree.png", CRectangle(0.0f,    32.0f,   32.0f, 64.0f),  99 } },
    { 455, { "tree_5",      "Resource/textures/tree.png", CRectangle(32.0f,   32.0f,   64.0f, 64.0f),  99 } },
    { 456, { "tree_6",      "Resource/textures/tree.png", CRectangle(64.0f,   32.0f,   96.0f, 64.0f),  99 } },
    { 457, { "tree_7",      "Resource/textures/tree.png", CRectangle(96.0f,   32.0f,   128.0f, 64.0f),  99 } },
    { 458, { "tree_8",      "Resource/textures/tree.png", CRectangle(0.0f,    64.0f,    32.0f,   96.0f),  99 } },
    { 459, { "tree_9",      "Resource/textures/tree.png", CRectangle(32.0f,   64.0f,    64.0f,   96.0f),  99 } },
    { 460, { "tree_10",     "Resource/textures/tree.png", CRectangle(64.0f,   64.0f,    96.0f,   96.0f),  99 } },
    { 461, { "tree_11",     "Resource/textures/tree.png", CRectangle(96.0f,   64.0f,   128.0f,   96.0f),  99 } },


    { 650, { "laboratory_0",     "Resource/textures/laboratory.png",  CRectangle(0.0f,    0.0f,   32.0f,   32.0f),  99 } },
    { 651, { "laboratory_1",     "Resource/textures/laboratory.png",  CRectangle(32.0f,   0.0f,   64.0f,   32.0f),  99 } },
    { 652, { "laboratory_2",     "Resource/textures/laboratory.png",  CRectangle(64.0f,   0.0f,   96.0f,   32.0f),  99 } },
    { 653, { "laboratory_3",     "Resource/textures/laboratory.png",  CRectangle(96.0f,   0.0f,   128.0f,   32.0f),  99 } },
    { 654, { "laboratory_4",     "Resource/textures/laboratory.png",  CRectangle(128.0f,  0.0f,   160.0f,   32.0f),  99 } },
    { 655, { "laboratory_5",     "Resource/textures/laboratory.png",  CRectangle(160.0f,  0.0f,   192.0f,   32.0f),  99 } },
    { 656, { "laboratory_6",     "Resource/textures/laboratory.png",  CRectangle(192.0f,  0.0f,   224.0f,   32.0f),  99 } },
    { 657, { "laboratory_7",     "Resource/textures/laboratory.png",  CRectangle(0.0f,    0.0f,   32.0f,   32.0f),  99 } },
    { 658, { "laboratory_8",     "Resource/textures/laboratory.png",  CRectangle(0.0f,    0.0f,   32.0f,   32.0f),  99 } },
    { 659, { "laboratory_9",     "Resource/textures/laboratory.png",  CRectangle(0.0f,    0.0f,   32.0f,   32.0f),  99 } },
    { 660, { "laboratory_10",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 661, { "laboratory_11",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 662, { "laboratory_12",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 663, { "laboratory_13",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 664, { "laboratory_14",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 665, { "laboratory_15",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 666, { "laboratory_16",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 667, { "laboratory_17",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 668, { "laboratory_18",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 669, { "laboratory_19",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 670, { "laboratory_20",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 671, { "laboratory_21",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 672, { "laboratory_22",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 673, { "laboratory_23",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 674, { "laboratory_24",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 675, { "laboratory_25",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 676, { "laboratory_26",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 677, { "laboratory_27",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 678, { "laboratory_28",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 679, { "laboratory_29",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 680, { "laboratory_30",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 681, { "laboratory_31",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 682, { "laboratory_32",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 683, { "laboratory_33",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },
    { 684, { "laboratory_34",     "Resource/textures/laboratory.png", CRectangle(0.0f,   0.0f,   32.0f,   32.0f),  99 } },




};

static const std::unordered_map<br::UnitType, std::string> kUnitKeys = {
    //{ type, "name" },
    { br::UnitType::Lord, "lord" },
    { br::UnitType::Cavalry, "cavalry" },
    { br::UnitType::Archer, "archer" },
    { br::UnitType::Hoplite, "hoplite" },
    { br::UnitType::Chariot, "chariot" },
    { br::UnitType::LightCavalry, "light_cavalry" },
    { br::UnitType::HeavyCavalry, "heavy_cavalry" },
    { br::UnitType::Sniper, "sniper" },
    { br::UnitType::Hunter, "hunter" },
    { br::UnitType::General, "general" },
    { br::UnitType::Healer, "healer" },
    { br::UnitType::Wizard, "wizard" },
};


}
#endif // !BR_STAGE_TABLE_H