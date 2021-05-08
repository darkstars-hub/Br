//!-----------------------------------------------------
//! @file : SelectInfomation.h
//! @brief : ëIëÇµÇΩèÓïÒÇì‡ïÔÇ∑ÇÈ
//! @date : 2020/07/09
//!-----------------------------------------------------


#ifndef BR_SELECT_INFOMATION_H
#define BR_SELECT_INFOMATION_H


#include "SceneInfomation.h"


namespace br {
struct SelectInfomation : public br::SceneInfomation {
    bool select = false;
    const char* stage_data_path = "";
    const char* unit_data_path = "";
    const char* start_text_path = "";
    const char* clear_text_path = "";
    
    void Initialize() {
        select = false;
        stage_data_path = "";
        unit_data_path = "";
        start_text_path = "";
        clear_text_path = "";
    }
    void SetData(const char* stage, const char* unit, const char* start_text, const char* clear_text) {
        select = true;
        stage_data_path = stage;
        unit_data_path = unit;
        start_text_path = start_text;
        clear_text_path = clear_text;
    }
    bool ExistData(void) {
        return select;
    }
};
}
#endif // !BR_SELECT_INFOMATION_H