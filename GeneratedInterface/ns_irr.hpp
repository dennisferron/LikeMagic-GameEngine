#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace irr
	{

struct IrrlichtDevice
{
    ::LM::ExprPtr expr;
    auto isDriverSupported(GameBindings::irr::video::E_DRIVER_TYPE) -> GameBindings::bool_expr;
    auto yield() -> GameBindings::void_expr;
    auto setWindowCaption(GameBindings::wchar_t_expr) -> GameBindings::void_expr;
    auto setInputReceivingSceneManager(GameBindings::irr::scene::ISceneManager) -> GameBindings::void_expr;
    auto setGammaRamp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::bool_expr;
    auto getColorFormat() -> MissingType /* C++ irr::video::ECOLOR_FORMAT */ ;
    auto run() -> GameBindings::bool_expr;
    auto sleep(GameBindings::uint_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto postEventFromUser(GameBindings::irr::gui::SEvent) -> GameBindings::bool_expr;
    auto isWindowMinimized() -> GameBindings::bool_expr;
    auto maximizeWindow() -> GameBindings::void_expr;
    auto getTimer() -> GameBindings::irr::ITimer;
    auto getVideoDriver() -> GameBindings::irr::video::IVideoDriver;
    auto isWindowFocused() -> GameBindings::bool_expr;
    auto isFullscreen() -> GameBindings::bool_expr;
    auto restoreWindow() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto getSceneManager() -> GameBindings::irr::scene::ISceneManager;
    auto setEventReceiver(GameBindings::irr::custom::IEventReceiver) -> GameBindings::void_expr;
    auto setResizable(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getFileSystem() -> MissingType /* C++ irr::io::IFileSystem* */ ;
    auto getOSOperator() -> MissingType /* C++ irr::IOSOperator* */ ;
    auto getVersion() -> GameBindings::char_expr;
    auto getType() -> MissingType /* C++ irr::E_DEVICE_TYPE */ ;
    auto getLogger() -> MissingType /* C++ irr::ILogger* */ ;
    auto getVideoModeList() -> MissingType /* C++ irr::video::IVideoModeList* */ ;
    auto getEventReceiver() -> GameBindings::irr::custom::IEventReceiver;
    auto lm_delete() -> GameBindings::void_expr;
    auto getCursorControl() -> GameBindings::irr::gui::ICursorControl;
    auto getGUIEnvironment() -> GameBindings::irr::gui::IGUIEnvironment;
    auto closeDevice() -> GameBindings::void_expr;
    auto getGammaRamp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::bool_expr;
    auto minimizeWindow() -> GameBindings::void_expr;
    auto isWindowActive() -> GameBindings::bool_expr;
    auto clearSystemMessages() -> GameBindings::void_expr;
    auto activateJoysticks(MissingType /* C++ irr::core::array<irr::SJoystickInfo, irr::core::irrAllocator<irr::SJoystickInfo> >& (end) */ ) -> GameBindings::bool_expr;
};struct IReferenceCounted
{
    ::LM::ExprPtr expr;
    auto getReferenceCount() -> GameBindings::int_expr;
    auto grab() -> GameBindings::void_expr;
    auto getDebugName() -> GameBindings::char_expr;
    auto drop() -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ITimer
{
    ::LM::ExprPtr expr;
    auto tick() -> GameBindings::void_expr;
    auto isStopped() -> GameBindings::bool_expr;
    auto start() -> GameBindings::void_expr;
    auto setSpeed(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setTime(GameBindings::uint_expr) -> GameBindings::void_expr;
    auto getTime() -> GameBindings::uint_expr;
    auto getRealTime() -> GameBindings::uint_expr;
    auto stop() -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto getSpeed() -> GameBindings::float_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SKeyMap
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

	}
}
