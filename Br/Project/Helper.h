#ifndef BR_HELPER_H
#define BR_HELPER_H


#include <crtdbg.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <charconv>
#include <iterator>
#include <algorithm>
#include <random>

#include <Mof.h>

#include "../include/rapidjson/document.h"


#define DEBUG_PRINT(arg, ...)
#define TRACE
#if defined(_DEBUG)
#undef DEBUG_PRINT
#undef TRACE 
#define DEBUG_PRINT(arg, ...)\
{char str[256]; \
::sprintf_s(str, arg, __VA_ARGS__); \
::OutputDebugString(str);}
#define TRACE \
DEBUG_PRINT("%s %s %d \n", __FILE__, __func__, __LINE__);
#endif // defined (_DEBUG)

namespace def {
constexpr int kChipSize = 32;
constexpr int kPadding = 32;
constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;
constexpr int kColMax = kWindowWidth / kChipSize;
constexpr int kRowMax = kWindowHeight / kChipSize;

constexpr int kUIWindowOffsetCount = 5;
constexpr int kUIWindowOffset = kChipSize * kUIWindowOffsetCount;

constexpr const char* kPlayerTeam = "player";
constexpr const char* kEnemyTeam = "enemy";
struct Vector2i {
    int x = 0; int y = 0;
    int col = 0; int row = 0;


    bool operator==(const Vector2i& r) const {
        return col == r.col && row == r.row;
    }
    bool operator!=(const Vector2i& r) const {
        return col != r.col || row != r.row;
    }
    static Mof::CVector2 MofVec2(const Vector2i& r) {
        return Mof::CVector2(r.x, r.y);
    }
};

const Vector2i VUp = { 0,-1 };
const Vector2i VDown = { 0,1 };
const Vector2i VLeft = { -1, 0 };
const Vector2i VRight = { 1, 0 };
const Vector2i VDirection[] = {
    VUp,
    VDown,
    VLeft,
    VRight,
};

}

namespace ut {

inline void Zero(Mof::CVector2& v) {
    v.x = 0.0f;
    v.y = 0.0f;
}

inline def::Vector2i ToGridPos(Mof::CVector2 pos, int size = def::kChipSize) {
    auto v = def::Vector2i();
    v.x = pos.x;
    v.y = pos.y;
//    v.col = pos.x / size;
    v.col = pos.x * 0.03125f;
//    v.row = pos.y / size;
    v.row = pos.y * 0.03125f;

    return v;
}

template <typename T>
inline void CheckedDelete(T*& p) {
    typedef char type_must_be_complete
        [sizeof(T) ? 1 : -1];
    (void) sizeof(type_must_be_complete);
    delete p;
    p = nullptr;
}

inline int GenerateRandom(const int min, const int max) {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> random(min, max);
    return random(engine);
}
inline float GenerateRandomF(const int min, const int max) {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> random(min, max);
    return static_cast<float>(random(engine));
}

static bool LoadJsonDocument(const char* path, rapidjson::Document& document) {
    std::ifstream file(path);
    if (!file.is_open()) {
        TRACE;
        DEBUG_PRINT("failed to open file");
        return false;
    } // if
    std::stringstream stream;
    stream << file.rdbuf();
    std::string contents = stream.str();
    rapidjson::StringStream str(contents.c_str());
    document.ParseStream(str);

    return true;
}
}

#endif // !BR_HELPER_H