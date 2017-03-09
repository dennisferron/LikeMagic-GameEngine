#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace gui
		{

struct IGUIEditBox
{
    ::LM::ExprPtr expr;
    auto setWordWrap(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setOverrideColor(GameBindings::irr::video::SColor) -> GameBindings::void_expr;
    auto setMax(GameBindings::uint_expr) -> GameBindings::void_expr;
    auto setDrawBorder(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto isWordWrapEnabled() -> GameBindings::bool_expr;
    auto setMultiLine(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto isPasswordBox() -> GameBindings::bool_expr;
    auto setOverrideFont(GameBindings::irr::gui::IGUIFont) -> GameBindings::void_expr;
    auto setTextAlignment(GameBindings::irr::gui::EGUI_ALIGNMENT, GameBindings::irr::gui::EGUI_ALIGNMENT) -> GameBindings::void_expr;
    auto isMultiLineEnabled() -> GameBindings::bool_expr;
    auto setAutoScroll(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getMax() -> GameBindings::uint_expr;
    auto enableOverrideColor(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setPasswordBox(GameBindings::bool_expr, GameBindings::wchar_t_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto getTextDimension() -> GameBindings::irr::core::dimension2du;
    auto isAutoScrollEnabled() -> GameBindings::bool_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IGUIStaticText
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SKeyInput
{
    ::LM::ExprPtr expr;
    auto get_Control() -> GameBindings::bool_expr;
    auto set_Shift(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto set_PressedDown(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto set_Control(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto get_PressedDown() -> GameBindings::bool_expr;
    auto ref_Key() -> GameBindings::irr::gui::EKEY_CODE;
    auto get_Key() -> GameBindings::irr::gui::EKEY_CODE;
    auto get_Shift() -> GameBindings::bool_expr;
    auto get_Char() -> GameBindings::wchar_t_expr;
    auto ref_Char() -> GameBindings::wchar_t_expr;
    auto set_Char(GameBindings::wchar_t_expr) -> GameBindings::wchar_t_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto set_Key(GameBindings::irr::gui::EKEY_CODE) -> GameBindings::irr::gui::EKEY_CODE;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IGUIContextMenu
{
    ::LM::ExprPtr expr;
    auto setItemText(GameBindings::uint_expr, GameBindings::wchar_t_expr) -> GameBindings::void_expr;
    auto addItem(GameBindings::wchar_t_expr, GameBindings::int_expr, GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::uint_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SUserEvent
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct EGUI_EVENT_TYPE
{
    ::LM::ExprPtr expr;
    auto value() -> GameBindings::int_expr;
    auto asString() -> GameBindings::string_expr;
    auto operator ==(GameBindings::irr::gui::EGUI_EVENT_TYPE) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::irr::gui::EGUI_EVENT_TYPE) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ICursorControl
{
    ::LM::ExprPtr expr;
    auto setRelativePosition(GameBindings::irr::core::vector2df) -> GameBindings::void_expr;
    auto setRelativePosition(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setVisible(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setPosition(GameBindings::irr::core::vector2di) -> GameBindings::void_expr;
    auto setPosition(GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::void_expr;
    auto isVisible() -> GameBindings::bool_expr;
    auto getPosition() -> GameBindings::irr::core::vector2di;
    auto lm_delete() -> GameBindings::void_expr;
    auto setReferenceRect(GameBindings::irr::core::recti) -> GameBindings::void_expr;
    auto getRelativePosition() -> GameBindings::irr::core::vector2df;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct EMOUSE_INPUT_EVENT
{
    ::LM::ExprPtr expr;
    auto value() -> GameBindings::int_expr;
    auto asString() -> GameBindings::string_expr;
    auto operator ==(GameBindings::irr::gui::EMOUSE_INPUT_EVENT) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::irr::gui::EMOUSE_INPUT_EVENT) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SMouseInput
{
    ::LM::ExprPtr expr;
    auto isRightPressed() -> GameBindings::bool_expr;
    auto set_Control(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto isMiddlePressed() -> GameBindings::bool_expr;
    auto get_Control() -> GameBindings::bool_expr;
    auto set_Shift(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto get_Shift() -> GameBindings::bool_expr;
    auto ref_ButtonStates() -> GameBindings::uint_expr;
    auto isLeftPressed() -> GameBindings::bool_expr;
    auto ref_Wheel() -> GameBindings::float_expr;
    auto set_Wheel(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_Wheel() -> GameBindings::float_expr;
    auto set_Y(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_X() -> GameBindings::int_expr;
    auto set_X(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_Event() -> GameBindings::irr::gui::EMOUSE_INPUT_EVENT;
    auto get_Y() -> GameBindings::int_expr;
    auto ref_Y() -> GameBindings::int_expr;
    auto get_Event() -> GameBindings::irr::gui::EMOUSE_INPUT_EVENT;
    auto set_Event(GameBindings::irr::gui::EMOUSE_INPUT_EVENT) -> GameBindings::irr::gui::EMOUSE_INPUT_EVENT;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_ButtonStates() -> GameBindings::uint_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto set_ButtonStates(GameBindings::uint_expr) -> GameBindings::uint_expr;
    auto get_X() -> GameBindings::int_expr;
};struct IGUIEnvironment
{
    ::LM::ExprPtr expr;
    auto drawAll() -> GameBindings::void_expr;
    auto getRootGUIElement() -> GameBindings::irr::gui::IGUIElement;
    auto addStaticText(GameBindings::wchar_t_expr, GameBindings::irr::core::recti, GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::irr::gui::IGUIElement, GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::irr::gui::IGUIStaticText;
    auto addMenu(GameBindings::irr::gui::IGUIElement, GameBindings::int_expr) -> GameBindings::irr::gui::IGUIContextMenu;
    auto addSpinBox(GameBindings::wchar_t_expr, GameBindings::irr::core::recti, GameBindings::bool_expr, GameBindings::irr::gui::IGUIElement, GameBindings::int_expr) -> GameBindings::irr::gui::IGUISpinBox;
    auto addToolBar(GameBindings::irr::gui::IGUIElement, GameBindings::int_expr) -> GameBindings::irr::gui::IGUIToolBar;
    auto addEditBox(GameBindings::wchar_t_expr, GameBindings::irr::core::recti, GameBindings::bool_expr, GameBindings::irr::gui::IGUIElement, GameBindings::int_expr) -> GameBindings::irr::gui::IGUIEditBox;
    auto getBuiltInFont() -> GameBindings::irr::gui::IGUIFont;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IGUIFont
{
    ::LM::ExprPtr expr;
    auto setKerningHeight(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getKerningWidth(GameBindings::wchar_t_expr, GameBindings::wchar_t_expr) -> GameBindings::int_expr;
    auto setKerningWidth(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getKerningHeight() -> GameBindings::int_expr;
    auto getDimension(GameBindings::wchar_t_expr) -> GameBindings::irr::core::dimension2du;
    auto draw(GameBindings::irr::core::stringw, GameBindings::irr::core::recti, GameBindings::irr::video::SColor, GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::irr::core::recti) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct EEVENT_TYPE
{
    ::LM::ExprPtr expr;
    auto value() -> GameBindings::int_expr;
    auto asString() -> GameBindings::string_expr;
    auto operator ==(GameBindings::irr::gui::EEVENT_TYPE) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::irr::gui::EEVENT_TYPE) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SEvent
{
    ::LM::ExprPtr expr;
    auto ref_UserEvent() -> GameBindings::irr::gui::SUserEvent;
    auto ref_LogEvent() -> GameBindings::irr::gui::SLogEvent;
    auto set_LogEvent(GameBindings::irr::gui::SLogEvent) -> GameBindings::irr::gui::SLogEvent;
    auto ref_JoystickEvent() -> GameBindings::irr::gui::SJoystickEvent;
    auto set_JoystickEvent(GameBindings::irr::gui::SJoystickEvent) -> GameBindings::irr::gui::SJoystickEvent;
    auto ref_KeyInput() -> GameBindings::irr::gui::SKeyInput;
    auto set_KeyInput(GameBindings::irr::gui::SKeyInput) -> GameBindings::irr::gui::SKeyInput;
    auto ref_MouseInput() -> GameBindings::irr::gui::SMouseInput;
    auto get_LogEvent() -> GameBindings::irr::gui::SLogEvent;
    auto get_GUIEvent() -> GameBindings::irr::gui::SGUIEvent;
    auto set_GUIEvent(GameBindings::irr::gui::SGUIEvent) -> GameBindings::irr::gui::SGUIEvent;
    auto get_JoystickEvent() -> GameBindings::irr::gui::SJoystickEvent;
    auto ref_EventType() -> GameBindings::irr::gui::EEVENT_TYPE;
    auto ref_GUIEvent() -> GameBindings::irr::gui::SGUIEvent;
    auto set_MouseInput(GameBindings::irr::gui::SMouseInput) -> GameBindings::irr::gui::SMouseInput;
    auto set_UserEvent(GameBindings::irr::gui::SUserEvent) -> GameBindings::irr::gui::SUserEvent;
    auto get_EventType() -> GameBindings::irr::gui::EEVENT_TYPE;
    auto get_UserEvent() -> GameBindings::irr::gui::SUserEvent;
    auto get_KeyInput() -> GameBindings::irr::gui::SKeyInput;
    auto set_EventType(GameBindings::irr::gui::EEVENT_TYPE) -> GameBindings::irr::gui::EEVENT_TYPE;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_MouseInput() -> GameBindings::irr::gui::SMouseInput;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IGUIToolBar
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto addButton(GameBindings::int_expr, GameBindings::wchar_t_expr, GameBindings::wchar_t_expr, GameBindings::irr::video::ITexture, GameBindings::irr::video::ITexture, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::irr::gui::IGUIButton;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IGUIElement
{
    ::LM::ExprPtr expr;
    auto setVisible(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getTypeName() -> GameBindings::char_expr;
    auto getParent() -> GameBindings::irr::gui::IGUIElement;
    auto setID(GameBindings::int_expr) -> GameBindings::void_expr;
    auto hasType(MissingType /* C++ irr::gui::EGUI_ELEMENT_TYPE (end) */ ) -> GameBindings::bool_expr;
    auto getID() -> GameBindings::int_expr;
    auto setMaxSize(GameBindings::irr::core::dimension2du) -> GameBindings::void_expr;
    auto getText() -> GameBindings::wchar_t_expr;
    auto getType() -> MissingType /* C++ irr::gui::EGUI_ELEMENT_TYPE */ ;
    auto setText(GameBindings::wchar_t_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto setMinSize(GameBindings::irr::core::dimension2du) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SLogEvent
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IGUISpinBox
{
    ::LM::ExprPtr expr;
    auto setRange(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setValue(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setDecimalPlaces(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getValue() -> GameBindings::float_expr;
    auto getStepSize() -> GameBindings::float_expr;
    auto getMin() -> GameBindings::float_expr;
    auto getMax() -> GameBindings::float_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto setStepSize(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getEditBox() -> GameBindings::irr::gui::IGUIEditBox;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct EKEY_CODE
{
    ::LM::ExprPtr expr;
    auto value() -> GameBindings::int_expr;
    auto asString() -> GameBindings::string_expr;
    auto operator ==(GameBindings::irr::gui::EKEY_CODE) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::irr::gui::EKEY_CODE) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IGUIButton
{
    ::LM::ExprPtr expr;
    auto setPressedImage(GameBindings::irr::video::ITexture) -> GameBindings::void_expr;
    auto setPressedImage(GameBindings::irr::video::ITexture, GameBindings::irr::core::recti) -> GameBindings::void_expr;
    auto setImage(GameBindings::irr::video::ITexture) -> GameBindings::void_expr;
    auto setImage(GameBindings::irr::video::ITexture, GameBindings::irr::core::recti) -> GameBindings::void_expr;
    auto setScaleImage(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setOverrideFont(GameBindings::irr::gui::IGUIFont) -> GameBindings::void_expr;
    auto setPressed(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setUseAlphaChannel(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto isScalingImage() -> GameBindings::bool_expr;
    auto setDrawBorder(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto isPushButton() -> GameBindings::bool_expr;
    auto isPressed() -> GameBindings::bool_expr;
    auto isDrawingBorder() -> GameBindings::bool_expr;
    auto isAlphaChannelUsed() -> GameBindings::bool_expr;
    auto setSpriteBank(MissingType /* C++ irr::gui::IGUISpriteBank* (end) */ ) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto setIsPushButton(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setSprite(MissingType /* C++ irr::gui::EGUI_BUTTON_STATE (end) */ , GameBindings::int_expr, GameBindings::irr::video::SColor, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SJoystickEvent
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SGUIEvent
{
    ::LM::ExprPtr expr;
    auto ref_EventType() -> GameBindings::irr::gui::EGUI_EVENT_TYPE;
    auto set_EventType(GameBindings::irr::gui::EGUI_EVENT_TYPE) -> GameBindings::irr::gui::EGUI_EVENT_TYPE;
    auto get_Element() -> GameBindings::irr::gui::IGUIElement;
    auto set_Element(GameBindings::irr::gui::IGUIElement) -> GameBindings::irr::gui::IGUIElement;
    auto ref_Caller() -> GameBindings::irr::gui::IGUIElement;
    auto get_EventType() -> GameBindings::irr::gui::EGUI_EVENT_TYPE;
    auto get_Caller() -> GameBindings::irr::gui::IGUIElement;
    auto set_Caller(GameBindings::irr::gui::IGUIElement) -> GameBindings::irr::gui::IGUIElement;
    auto lm_delete() -> GameBindings::void_expr;
    auto ref_Element() -> GameBindings::irr::gui::IGUIElement;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct EGUI_ALIGNMENT
{
    ::LM::ExprPtr expr;
    auto value() -> GameBindings::int_expr;
    auto asString() -> GameBindings::string_expr;
    auto operator ==(GameBindings::irr::gui::EGUI_ALIGNMENT) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::irr::gui::EGUI_ALIGNMENT) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_MOUSE_BUTTON_STATE_MASK
{
    ::LM::ExprPtr expr;
    auto value() -> GameBindings::int_expr;
    auto asString() -> GameBindings::string_expr;
    auto operator ==(GameBindings::irr::gui::E_MOUSE_BUTTON_STATE_MASK) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::irr::gui::E_MOUSE_BUTTON_STATE_MASK) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

		}
	}
}
