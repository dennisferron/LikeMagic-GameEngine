
#include "Bindings/Custom/SceneNodePtrTest.hpp"

#include <sstream>
#include <iostream>
using namespace std;

#include <irrlicht.h>

using namespace irr;
using namespace irr::scene;

namespace Bindings { namespace Custom {

void* SceneNodePtrTest::sceneNodePtrToVoidPtr(ISceneNode* node)
{
    return node;
}

ISceneNode* SceneNodePtrTest::voidPtrToSceneNodePtr(void* ptr)
{
    return reinterpret_cast<ISceneNode*>(ptr);
}

string SceneNodePtrTest::sceneNodePtrToString(ISceneNode const* p)
{
    stringstream ss;
    ss << p;
    return ss.str();
}

ISceneNode* SceneNodePtrTest::stringToSceneNodePtr(string hex_str)
{
    void* result = 0;
    std::stringstream ss;
    ss << std::hex << hex_str;
    ss >> result;
    return reinterpret_cast<ISceneNode*>(result);
}

void SceneNodePtrTest::printSceneNodePtr(ISceneNode const* node)
{
    cout << "Node ptr: " << node << endl;
}

void SceneNodePtrTest::addLightSceneNode(ISceneManager* smgr)
{
    smgr->addLightSceneNode(NULL);
}

}}
