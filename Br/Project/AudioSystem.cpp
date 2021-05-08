#include "AudioSystem.h"

#include <fstream>

#include "Helper.h"



br::AudioSystem::AudioSystem() :
    _is_loaded(false),
    _mutex(),
    _sound_buffers() {
}

br::AudioSystem::~AudioSystem() {
}

bool br::AudioSystem::IsLoaded(void) {
    std::lock_guard<std::mutex> lock(_mutex);
    return this->_is_loaded;
}

bool br::AudioSystem::Load(const char* path) {
    std::ifstream stream(path);
    std::vector<std::string> paths;

    // 読み込むファイルのパスを格納
    while (stream) {
        std::string buffer;
        std::getline(stream, buffer);
        paths.push_back(buffer);
    } // while

    // パスを参照し読み込む
    for (auto& path : paths) {
        std::shared_ptr<Mof::CSoundBufferBase> sound = nullptr;
        if (_sound_buffers.find(path.c_str()) !=
            _sound_buffers.end()) {
            continue;
        } // if

        // BGMかSEか分ける
        if (path.find("Resource/sound") != std::string::npos) {
            sound = std::make_shared<Mof::CSoundBuffer>();
        } // if
        else if (path.find("Resource/bgm") != std::string::npos) {
            sound = std::make_shared<Mof::CStreamingSoundBuffer>();
        } // else if

        if (path.find("Resource/") != std::string::npos &&
            sound->Load(path.c_str())) {
            _sound_buffers.emplace(path, sound);
        } // if
        else {
            sound.reset();
            //return false;
        } // else
    } // for

    _is_loaded = true;
    return true;
}

void br::AudioSystem::Update(void) {
    for (auto& sound : _sound_buffers) {
        sound.second->Update();
    } // for
}

bool br::AudioSystem::Release(void) {
    for (auto& sound : _sound_buffers) {
        if (!sound.second->Release()) {
            return false;
        } // if
        sound.second.reset();
    } // for
    _sound_buffers.clear();
    return true;
}

void br::AudioSystem::Play(const std::string path) {
    auto it = _sound_buffers.find(path);
    if (it != _sound_buffers.end()) {
        (*it).second->Play();
    } // if
}

void br::AudioSystem::Stop(const std::string path) {
    auto it = _sound_buffers.find(path);
    if (it != _sound_buffers.end()) {
        (*it).second->Stop();
    } // if
}

bool br::AudioSystem::IsPlay(const std::string path) {
    auto it = _sound_buffers.find(path);
    if (it != _sound_buffers.end()) {
        return (*it).second->IsPlay();
    } // if
    return false;
}

void br::AudioSystem::AddSound(const char* name, const std::shared_ptr<Mof::CSoundBufferBase>& sound) {
        _sound_buffers.emplace(name, sound);
}
