#include "AIParam.h"

#include "Unit.h"
#include "UnitAIManager.h"


br::AIParam::AIParam() :
    _owner(nullptr),
    _weights() {
}

br::AIParam::AIParam(br::Unit* owner) :
    _owner(owner),
    _weights() {
}

br::AIParam::~AIParam() {
}

br::Unit* br::AIParam::GetTargetUnit(void) {
    int index = 0;
    int weight = 0;

    // 重みが最大のもののインデックスを格納
    for (int i = 0; i < _weights.size(); i++) {
        if (weight < _weights.at(i).second) {
            weight = _weights.at(i).second;
            index = i;
        } // if
    } // for
    // 重みが最大のユニットを返す
    return _weights.at(index).first;
}
/*
void br::AIParam::Initialize(std::vector<br::Unit*>& players) {
    _weights.clear();

    for (auto u : players) {
        _weights.push_back(std::make_pair(u, 0));
    } // for
}
*/
void br::AIParam::AddUnit(br::Unit* player) {
    _weights.push_back(std::make_pair(player, 0));
}

void br::AIParam::AddWeight(br::Unit* player, int value) {
    // ユニットを持つペアを探す
    auto it = std::find_if(_weights.begin(), _weights.end(), [&player]
    (std::pair<br::Unit*, int>pair) {
        return pair.first == player;
    });

    _ASSERT_EXPR(it != _weights.end(), L"ユニットは追加されているべき");

    // 探したペアの重みに入力値を加算する
    it->second += value;
}

/*
void br::AIParam::Reset(void) {
    _weights.clear();
}
*/