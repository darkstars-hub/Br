#include "ResourceManager.h"

#include "Helper.h"
#include "Sprite.h"


br::ResourceManager::ResourceManager() :
    _is_loaded(false),
    _mutex(),
    _textures(),
    _sprite_parts() {
}

br::ResourceManager::~ResourceManager() {
}

bool br::ResourceManager::IsLoaded(void) {
    std::lock_guard<std::mutex> lock(_mutex);
    return this->_is_loaded;
}

std::shared_ptr<Mof::CTexture> br::ResourceManager::GetTexture(const std::string& path) {
    std::shared_ptr<Mof::CTexture> tex = nullptr;

    auto it = _textures.find(path);
    if (it != _textures.end()) {
        tex = it->second;
    } // if
    else {
        tex = std::make_shared<Mof::CTexture>();
        if (tex->Load(path.c_str())) {
            _textures.emplace(path, tex);
        } // if
        else {
            tex.reset();
        } // else
    } // else
    return tex;
}

std::shared_ptr<br::SpritePart> br::ResourceManager::GetSpritePart(const std::string& path) {
    std::shared_ptr<br::SpritePart> spr = nullptr;

    auto it = _sprite_parts.find(path);
    if (it != _sprite_parts.end()) {
        spr = it->second;
    } // if
    else {
        spr = std::make_shared<br::SpritePart>();
        if (spr->Load(path.c_str(), *this)) {
            _sprite_parts.emplace(path, spr);
        } // if
        else {
            spr.reset();
        } // else
    } // else
    return spr;
}

bool br::ResourceManager::Load(void) {
    return true;
}

bool br::ResourceManager::Load(const char* path) {
    std::ifstream stream(path);
    std::vector<std::string> paths;

    // 読み込むファイルのパスを格納
    while (stream) {
        std::string buffer;
        std::getline(stream, buffer);
        paths.push_back(buffer);
    } // while

    // パスを参照し読み込む
    for (auto temp : paths) {
        auto path = temp.c_str();
        if (auto format = std::strstr(path, ".png"); format) {
            auto ptr = this->GetTexture(path);
            if (!ptr) {
                puts("failed");
            } // if
        } // if
        else if (auto format = std::strstr(path, ".sprite"); format) {
            auto ptr = this->GetSpritePart(path);
            if (!ptr) {
                puts("failed");
            } // if
        } // else if
    } // for

    _is_loaded = true;
    return true;
}

bool br::ResourceManager::Release(void) {
    for (auto spr : _sprite_parts) {
        if (!spr.second->Release()) {
            TRACE;
            DEBUG_PRINT("failed to release sprite part");
            return false;
        } // if
        spr.second.reset();
    } // for
    _sprite_parts.clear();

    for (auto tex : _textures) {
        if (!tex.second->Release()) {
            TRACE;
            DEBUG_PRINT("failed to release texture");
            return false;
        } // if
        tex.second.reset();
    } // for
    _textures.clear();
    return true;
}