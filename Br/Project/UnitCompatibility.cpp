#include "UnitCompatibility.h"


br::UnitCompatibility::UnitCompatibility() :
    _reverse(false) {
}

br::UnitCompatibility::~UnitCompatibility() {
}

br::UnitCompatibility& br::UnitCompatibility::GetInstance() {
    static br::UnitCompatibility obj;
    return obj;
}

bool br::UnitCompatibility::IsReverse(void) {
    return this->_reverse;
}

void br::UnitCompatibility::Reverse(void) {
    _reverse = !_reverse;
}

br::UnitCompatibility::Effective br::UnitCompatibility::Compatibility(br::UnitType attacker, br::UnitType target) {
    using E = br::UnitCompatibility::Effective;
    E ret = E::NormalEffective;

    // äeëäê´ë„ì¸
    switch (attacker) {
        case br::UnitType::Lord:
            ret = E::SuperEffective;
            break;
        case br::UnitType::Cavalry:
            switch (target) {
                case br::UnitType::Lord:
                    //ret = E::NotVeryEffective;
                    break;
                case br::UnitType::Archer:
                    ret = E::SuperEffective;
                    break;
                case br::UnitType::Hoplite:
                    ret = E::NotVeryEffective;
                    break;
            } // switch
            break;
        case br::UnitType::Archer:
            switch (target) {
                case br::UnitType::Lord:
                    //ret = E::NotVeryEffective;
                    break;
                case br::UnitType::Cavalry:
                    ret = E::NotVeryEffective;
                    break;
                case br::UnitType::Hoplite:
                    ret = E::SuperEffective;
                    break;
            } // switch
            break;
        case br::UnitType::Hoplite:
            switch (target) {
                case br::UnitType::Lord:
                    //ret = E::NotVeryEffective;
                    break;
                case br::UnitType::Cavalry:
                    ret = E::SuperEffective;
                    break;
                case br::UnitType::Archer:
                    ret = E::NotVeryEffective;
                    break;
            } // switch
            break;
        default:
            ret = E::NormalEffective;
            break;
    } // switch


    // ëäê´ãtì]ÉtÉâÉOÇ™óßÇ¬Ç»ÇÁîΩì]Ç≥ÇπÇÈ
    if (_reverse) {
        switch (ret) {
            case E::SuperEffective:
                ret = E::NotVeryEffective;
                break;
            case E::NotVeryEffective:
                ret = E::SuperEffective;
                break;
        } // switch
    } // if
    return ret;
}