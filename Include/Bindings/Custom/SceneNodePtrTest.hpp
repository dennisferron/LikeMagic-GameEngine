
namespace irr { namespace scene { class ISceneNode; class ISceneManager; } }
#include <string>

namespace Bindings { namespace Custom {

class SceneNodePtrTest
{
public:
    static void* sceneNodePtrToVoidPtr(irr::scene::ISceneNode* node);
    static irr::scene::ISceneNode* voidPtrToSceneNodePtr(void* ptr);
    static std::string sceneNodePtrToString(irr::scene::ISceneNode const* p);
    static irr::scene::ISceneNode* stringToSceneNodePtr(std::string hex_str);
    static void printSceneNodePtr(irr::scene::ISceneNode const* node);
    static void addLightSceneNode(irr::scene::ISceneManager* smgr);
};

}}
