#ifndef BR_CAMERA_H
#define BR_CAMERA_H
#include <Mof.h>
#include "Scene.h"
namespace br {
class Camera {
private:
    Mof::CVector2 _scroll;
    br::Scene* _scene;
    class Cursor* _cursor;
public:
    Camera(br::Scene* scene);
    ~Camera();

    void SetCursor(class Cursor* cursor);

    void Initialize(void);
    void Update(void);
    Mof::CVector2& GetScroll(void);
};
}
#endif // !BR_CAMERA_H
