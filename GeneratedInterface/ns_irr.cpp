#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_global.hpp"
#include "ns_irr.hpp"
#include "ns_irr_scene.hpp"
#include "ns_irr_gui.hpp"
#include "ns_irr_video.hpp"
#include "ns_irr_custom.hpp"

namespace GameBindings
{
	namespace irr
	{

auto IrrlichtDevice::isDriverSupported(GameBindings::irr::video::E_DRIVER_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isDriverSupported", args, 1) };
}
auto IrrlichtDevice::yield() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "yield", args, 0) };
}
auto IrrlichtDevice::setWindowCaption(GameBindings::wchar_t_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setWindowCaption", args, 1) };
}
auto IrrlichtDevice::setInputReceivingSceneManager(GameBindings::irr::scene::ISceneManager arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setInputReceivingSceneManager", args, 1) };
}
auto IrrlichtDevice::setGammaRamp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "setGammaRamp", args, 5) };
}
auto IrrlichtDevice::getColorFormat() -> MissingType /* C++ irr::video::ECOLOR_FORMAT */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getColorFormat", args, 0) };
}
auto IrrlichtDevice::run() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "run", args, 0) };
}
auto IrrlichtDevice::sleep(GameBindings::uint_expr arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "sleep", args, 2) };
}
auto IrrlichtDevice::postEventFromUser(GameBindings::irr::gui::SEvent arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "postEventFromUser", args, 1) };
}
auto IrrlichtDevice::isWindowMinimized() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isWindowMinimized", args, 0) };
}
auto IrrlichtDevice::maximizeWindow() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "maximizeWindow", args, 0) };
}
auto IrrlichtDevice::getTimer() -> GameBindings::irr::ITimer
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTimer", args, 0) };
}
auto IrrlichtDevice::getVideoDriver() -> GameBindings::irr::video::IVideoDriver
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVideoDriver", args, 0) };
}
auto IrrlichtDevice::isWindowFocused() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isWindowFocused", args, 0) };
}
auto IrrlichtDevice::isFullscreen() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isFullscreen", args, 0) };
}
auto IrrlichtDevice::restoreWindow() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "restoreWindow", args, 0) };
}
auto IrrlichtDevice::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto IrrlichtDevice::getSceneManager() -> GameBindings::irr::scene::ISceneManager
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSceneManager", args, 0) };
}
auto IrrlichtDevice::setEventReceiver(GameBindings::irr::custom::IEventReceiver arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setEventReceiver", args, 1) };
}
auto IrrlichtDevice::setResizable(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setResizable", args, 1) };
}
auto IrrlichtDevice::getFileSystem() -> MissingType /* C++ irr::io::IFileSystem* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFileSystem", args, 0) };
}
auto IrrlichtDevice::getOSOperator() -> MissingType /* C++ irr::IOSOperator* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getOSOperator", args, 0) };
}
auto IrrlichtDevice::getVersion() -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVersion", args, 0) };
}
auto IrrlichtDevice::getType() -> MissingType /* C++ irr::E_DEVICE_TYPE */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getType", args, 0) };
}
auto IrrlichtDevice::getLogger() -> MissingType /* C++ irr::ILogger* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLogger", args, 0) };
}
auto IrrlichtDevice::getVideoModeList() -> MissingType /* C++ irr::video::IVideoModeList* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVideoModeList", args, 0) };
}
auto IrrlichtDevice::getEventReceiver() -> GameBindings::irr::custom::IEventReceiver
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getEventReceiver", args, 0) };
}
auto IrrlichtDevice::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IrrlichtDevice::getCursorControl() -> GameBindings::irr::gui::ICursorControl
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCursorControl", args, 0) };
}
auto IrrlichtDevice::getGUIEnvironment() -> GameBindings::irr::gui::IGUIEnvironment
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getGUIEnvironment", args, 0) };
}
auto IrrlichtDevice::closeDevice() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "closeDevice", args, 0) };
}
auto IrrlichtDevice::getGammaRamp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "getGammaRamp", args, 5) };
}
auto IrrlichtDevice::minimizeWindow() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "minimizeWindow", args, 0) };
}
auto IrrlichtDevice::isWindowActive() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isWindowActive", args, 0) };
}
auto IrrlichtDevice::clearSystemMessages() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "clearSystemMessages", args, 0) };
}
auto IrrlichtDevice::activateJoysticks(MissingType /* C++ irr::core::array<irr::SJoystickInfo, irr::core::irrAllocator<irr::SJoystickInfo> >& (end) */  arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "activateJoysticks", args, 1) };
}

auto IReferenceCounted::getReferenceCount() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getReferenceCount", args, 0) };
}
auto IReferenceCounted::grab() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "grab", args, 0) };
}
auto IReferenceCounted::getDebugName() -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDebugName", args, 0) };
}
auto IReferenceCounted::drop() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "drop", args, 0) };
}
auto IReferenceCounted::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IReferenceCounted::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ITimer::tick() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tick", args, 0) };
}
auto ITimer::isStopped() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isStopped", args, 0) };
}
auto ITimer::start() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "start", args, 0) };
}
auto ITimer::setSpeed(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setSpeed", args, 1) };
}
auto ITimer::setTime(GameBindings::uint_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setTime", args, 1) };
}
auto ITimer::getTime() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTime", args, 0) };
}
auto ITimer::getRealTime() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRealTime", args, 0) };
}
auto ITimer::stop() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "stop", args, 0) };
}
auto ITimer::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ITimer::getSpeed() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSpeed", args, 0) };
}
auto ITimer::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SKeyMap::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SKeyMap::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

	}
}
