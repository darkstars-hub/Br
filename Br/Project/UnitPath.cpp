#include "UnitPath.h"

#include "Unit.h"


bool br::UnitPath::ConputePath(br::Tile* tile, br::Tile* destination, std::vector<br::PathDataPointer>& path) {
    std::vector<AStarDataPointer> open_list;
    AStarDataPointer ap = std::make_shared<AStarData>(tile);
    open_list.push_back(ap);
    std::vector<AStarDataPointer> release_list; // AStarデータをいじったTileのリスト この処理を抜けるときにリセットする
    release_list.push_back(ap);

    while (!open_list.empty()) {
        // 開始位置からのコストとヒューリスティックコストが最小のものを選ぶ
        auto it = std::min_element(open_list.begin(), open_list.end(),
                                   [](AStarDataPointer a, AStarDataPointer b) {
            int ac = a->from_start; float ah = a->heuristic;
            int bc = b->from_start; float bh = b->heuristic;
            return ac + ah < bc + bh;
        });
        auto current = *it;
        open_list.erase(it); // open_listに含まれていた全てのタイルが調査されていたら袋小路に入っている

        if (current->_tile->Equal(destination)) {
            // 経路情報を作成する
            this->GeneratePath(current, release_list, path);
            return true;
        } // if
        else {
            // currentに隣接するタイル
            for (auto a : current->_tile->GetAdjacents()) {
                if (!a) { // Stageには「ふち」があり上下左右 いづれかが隣接していないものがある
                    continue;
                } // if
                if (a->GetOnUnit() &&
                    a->GetOnUnit()->GetTeam() !=
                    destination->GetOnUnit()->GetTeam()) {
                    continue;
                } // if
                if (a->IsBlocked()) {
                    continue;
                }
                auto result = std::find_if(release_list.begin(), release_list.end(),
                                           [&](AStarDataPointer ap) {return ap->_tile == a; });
                AStarDataPointer add = ((result == release_list.end()) ? std::make_shared<AStarData>(a) : *result);
                if (!add->is_open && !add->is_closed) {
                    this->InsertOpenList(add, current, destination, open_list);
                    release_list.push_back(add);
                } // if
            } // for
            //隣接するタイルを調べたので現在のタイルは調査完了
            current->is_closed = true;
        } // else
    } // while
    return false;
}