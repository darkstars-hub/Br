//!-----------------------------------------------------
//! @file : BezierCurve.h
//! @brief : ベジエ曲線のデータを取得する
//! @date : 2020/07/18
//!-----------------------------------------------------


#ifndef BR_BEZIER_CURVE_H
#define BR_BEZIER_CURVE_H


#include <Mof.h>


namespace br {
enum class EaseType {
    Linear,
    EaseIn,
    EaseOut,
    EaseInOut,
};
struct AnimData {
    float value;
    float time;
    EaseType ease_type;
};

class BezierCurve {
private:
public:
    // timeは正規化されているものとする 
    float Interpolation(float time, float prev, float next,
                        br::EaseType type = br::EaseType::Linear) {
        //int phase;
        //for (phase = 1; phase < cnt; phase++) {
        //    if (AnimTime < AnimData[phase].Time) {
        //        break;
        //    } // if
        //} // for
        //phase = MOF_MIN(phase, cnt - 1);
        //float nt = AnimTime - AnimData[phase - 1].Time;
        //float at = AnimData[phase].Time - AnimData[phase - 1].Time;
        //float t = nt / at; // 配合率
        //t = MOF_CLIPING(t, 0.0f, 1.0f);
        //switch (AnimData[phase].EasingType) {
        //    case EASING_TYPE::EASE_IN_SINE:
        //        t = 1.0f - MOF_COS(MOF_MATH_HALFPI * t);
        //        break;
        //    case EASING_TYPE::EASE_OUT_SINE:
        //        t = MOF_SIN(MOF_MATH_HALFPI * t);
        //        break;
        //    case EASING_TYPE::EASE_INOUT_SINE:
        //        t = 0.5f - 0.5f * MOF_COS(MOF_MATH_PI * t);
        //        break;
        //    default:
        //        break;
        //} // switch

        if (time < 0.5f) {
        } // if

        switch (type) {
            case br::EaseType::EaseInOut:
                time = 0.5f - 0.5f * MOF_COS(MOF_MATH_PI * time);
                break;
        } // switch


        float from = prev;
        float to = next;
        return from + (to - from) * time;
    }

    //!-----------------------------------------------------
    //! @brief : 補間計算
    //! @param : [in](float normalized) アニメーションさせたい時間で割った値
    //!                                 最大値が1.0f
    //! @param : [in](std::vector<float>& poistion) コントロールポイントの位置 
    //! @param : [in](br::EaseType type) イージングのタイプ
    //! @return : none
    //!-----------------------------------------------------
    float InterpolationAnimData(float normalized,
                                std::vector<float>& control,
                                br::EaseType type = br::EaseType::Linear) {
        _ASSERT_EXPR(0.0 <= normalized && normalized <= 1.0f,
                     L"アニメーションの時間の閾値を超えています");
        if (control.size() > 2) {
            std::vector<float> anim_data;
            for (int i = 1; i < control.size(); i++) {
                float value = Interpolation(normalized,
                                            control.at(i - 1),
                                            control.at(i),
                                            type);
                anim_data.push_back(value);
            } // for
            return InterpolationAnimData(normalized, anim_data);
        } // if
        else if (control.size() == 2) {
            return Interpolation(normalized,
                                 control.at(0),
                                 control.at(1),
                                 type);
        } // else if
        return 0.0f;
    }
};
}
#endif // !BR_BEZIER_CURVE_H