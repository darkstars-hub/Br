//!-----------------------------------------------------
//! @file : Builder.h
//! @brief : Actorの機能をまとめて持っておく ActorFactoryで使う
//! @date : 2020/06/04
//!-----------------------------------------------------


#ifndef BR_BUILDER_H
#define BR_BUILDER_H


#include <vector>


namespace br {
class Component;
class Builder {
    friend class Actor;
private:
    std::vector<Component*> _components;
public:
    Builder();
    ~Builder();

    void Release(void);

    void AddComponent(Component* component);
};
}
#endif // !BR_BUILDER_H