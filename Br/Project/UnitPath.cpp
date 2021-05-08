#include "UnitPath.h"

#include "Unit.h"


bool br::UnitPath::ConputePath(br::Tile* tile, br::Tile* destination, std::vector<br::PathDataPointer>& path) {
    std::vector<AStarDataPointer> open_list;
    AStarDataPointer ap = std::make_shared<AStarData>(tile);
    open_list.push_back(ap);
    std::vector<AStarDataPointer> release_list; // AStar�f�[�^����������Tile�̃��X�g ���̏����𔲂���Ƃ��Ƀ��Z�b�g����
    release_list.push_back(ap);

    while (!open_list.empty()) {
        // �J�n�ʒu����̃R�X�g�ƃq���[���X�e�B�b�N�R�X�g���ŏ��̂��̂�I��
        auto it = std::min_element(open_list.begin(), open_list.end(),
                                   [](AStarDataPointer a, AStarDataPointer b) {
            int ac = a->from_start; float ah = a->heuristic;
            int bc = b->from_start; float bh = b->heuristic;
            return ac + ah < bc + bh;
        });
        auto current = *it;
        open_list.erase(it); // open_list�Ɋ܂܂�Ă����S�Ẵ^�C������������Ă�����܏��H�ɓ����Ă���

        if (current->_tile->Equal(destination)) {
            // �o�H�����쐬����
            this->GeneratePath(current, release_list, path);
            return true;
        } // if
        else {
            // current�ɗאڂ���^�C��
            for (auto a : current->_tile->GetAdjacents()) {
                if (!a) { // Stage�ɂ́u�ӂ��v������㉺���E ���Âꂩ���אڂ��Ă��Ȃ����̂�����
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
            //�אڂ���^�C���𒲂ׂ��̂Ō��݂̃^�C���͒�������
            current->is_closed = true;
        } // else
    } // while
    return false;
}