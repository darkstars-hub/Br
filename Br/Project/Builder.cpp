#include "Builder.h"

#include "Component.h"


br::Builder::Builder() :
    _components() {
}

br::Builder::~Builder() {
}

void br::Builder::Release(void) {
    for (auto p : _components) {
        MOF_SAFE_DELETE(p);
    } // for
    _components.clear();
}

void br::Builder::AddComponent(Component* component) {
    _components.push_back(component);
}