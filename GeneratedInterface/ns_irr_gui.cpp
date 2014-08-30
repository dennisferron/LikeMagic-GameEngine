#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_global.hpp"
#include "ns_irr_core.hpp"
#include "ns_irr_gui.hpp"
#include "ns_irr_video.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace gui
		{

auto IGUIFont::setKerningHeight(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setKerningHeight", args, 1) };
}
auto IGUIFont::setKerningWidth(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setKerningWidth", args, 1) };
}
auto IGUIFont::getKerningWidth(GameBindings::wchar_t_expr arg0, GameBindings::wchar_t_expr arg1) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getKerningWidth", args, 2) };
}
auto IGUIFont::getKerningHeight() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getKerningHeight", args, 0) };
}
auto IGUIFont::getDimension(GameBindings::wchar_t_expr arg0) -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getDimension", args, 1) };
}
auto IGUIFont::draw(GameBindings::irr::core::stringw arg0, GameBindings::irr::core::recti arg1, GameBindings::irr::video::SColor arg2, GameBindings::bool_expr arg3, GameBindings::bool_expr arg4, GameBindings::irr::core::recti arg5) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "draw", args, 6) };
}
auto IGUIFont::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGUIFont::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IGUIEnvironment::drawAll() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "drawAll", args, 0) };
}
auto IGUIEnvironment::addStaticText(GameBindings::wchar_t_expr arg0, GameBindings::irr::core::recti arg1, GameBindings::bool_expr arg2, GameBindings::bool_expr arg3, GameBindings::irr::gui::IGUIElement arg4, GameBindings::int_expr arg5, GameBindings::bool_expr arg6) -> GameBindings::irr::gui::IGUIStaticText
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "addStaticText", args, 7) };
}
auto IGUIEnvironment::addSpinBox(GameBindings::wchar_t_expr arg0, GameBindings::irr::core::recti arg1, GameBindings::bool_expr arg2, GameBindings::irr::gui::IGUIElement arg3, GameBindings::int_expr arg4) -> GameBindings::irr::gui::IGUISpinBox
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "addSpinBox", args, 5) };
}
auto IGUIEnvironment::addMenu(GameBindings::irr::gui::IGUIElement arg0, GameBindings::int_expr arg1) -> GameBindings::irr::gui::IGUIContextMenu
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "addMenu", args, 2) };
}
auto IGUIEnvironment::addToolBar(GameBindings::irr::gui::IGUIElement arg0, GameBindings::int_expr arg1) -> GameBindings::irr::gui::IGUIToolBar
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "addToolBar", args, 2) };
}
auto IGUIEnvironment::getBuiltInFont() -> GameBindings::irr::gui::IGUIFont
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBuiltInFont", args, 0) };
}
auto IGUIEnvironment::addEditBox(GameBindings::wchar_t_expr arg0, GameBindings::irr::core::recti arg1, GameBindings::bool_expr arg2, GameBindings::irr::gui::IGUIElement arg3, GameBindings::int_expr arg4) -> GameBindings::irr::gui::IGUIEditBox
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "addEditBox", args, 5) };
}
auto IGUIEnvironment::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGUIEnvironment::getRootGUIElement() -> GameBindings::irr::gui::IGUIElement
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRootGUIElement", args, 0) };
}
auto IGUIEnvironment::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IGUIEditBox::setWordWrap(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setWordWrap", args, 1) };
}
auto IGUIEditBox::setOverrideFont(GameBindings::irr::gui::IGUIFont arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOverrideFont", args, 1) };
}
auto IGUIEditBox::setOverrideColor(GameBindings::irr::video::SColor arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOverrideColor", args, 1) };
}
auto IGUIEditBox::setAutoScroll(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAutoScroll", args, 1) };
}
auto IGUIEditBox::setMultiLine(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMultiLine", args, 1) };
}
auto IGUIEditBox::setTextAlignment(GameBindings::irr::gui::EGUI_ALIGNMENT arg0, GameBindings::irr::gui::EGUI_ALIGNMENT arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setTextAlignment", args, 2) };
}
auto IGUIEditBox::isWordWrapEnabled() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isWordWrapEnabled", args, 0) };
}
auto IGUIEditBox::setMax(GameBindings::uint_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMax", args, 1) };
}
auto IGUIEditBox::isMultiLineEnabled() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isMultiLineEnabled", args, 0) };
}
auto IGUIEditBox::isAutoScrollEnabled() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isAutoScrollEnabled", args, 0) };
}
auto IGUIEditBox::setDrawBorder(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDrawBorder", args, 1) };
}
auto IGUIEditBox::getTextDimension() -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTextDimension", args, 0) };
}
auto IGUIEditBox::getMax() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMax", args, 0) };
}
auto IGUIEditBox::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGUIEditBox::setPasswordBox(GameBindings::bool_expr arg0, GameBindings::wchar_t_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setPasswordBox", args, 2) };
}
auto IGUIEditBox::isPasswordBox() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isPasswordBox", args, 0) };
}
auto IGUIEditBox::enableOverrideColor(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "enableOverrideColor", args, 1) };
}
auto IGUIEditBox::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IGUIStaticText::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGUIStaticText::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IGUIButton::setPressedImage(GameBindings::irr::video::ITexture arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setPressedImage", args, 1) };
}
auto IGUIButton::setPressedImage(GameBindings::irr::video::ITexture arg0, GameBindings::irr::core::recti arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setPressedImage", args, 2) };
}
auto IGUIButton::setUseAlphaChannel(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUseAlphaChannel", args, 1) };
}
auto IGUIButton::setSpriteBank(MissingType /* C++ irr::gui::IGUISpriteBank* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setSpriteBank", args, 1) };
}
auto IGUIButton::setSprite(MissingType /* C++ irr::gui::EGUI_BUTTON_STATE (end) */  arg0, GameBindings::int_expr arg1, GameBindings::irr::video::SColor arg2, GameBindings::bool_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "setSprite", args, 4) };
}
auto IGUIButton::setScaleImage(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setScaleImage", args, 1) };
}
auto IGUIButton::setOverrideFont(GameBindings::irr::gui::IGUIFont arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOverrideFont", args, 1) };
}
auto IGUIButton::setIsPushButton(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setIsPushButton", args, 1) };
}
auto IGUIButton::setDrawBorder(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDrawBorder", args, 1) };
}
auto IGUIButton::isPressed() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isPressed", args, 0) };
}
auto IGUIButton::setImage(GameBindings::irr::video::ITexture arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setImage", args, 1) };
}
auto IGUIButton::setImage(GameBindings::irr::video::ITexture arg0, GameBindings::irr::core::recti arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setImage", args, 2) };
}
auto IGUIButton::setPressed(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setPressed", args, 1) };
}
auto IGUIButton::isPushButton() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isPushButton", args, 0) };
}
auto IGUIButton::isAlphaChannelUsed() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isAlphaChannelUsed", args, 0) };
}
auto IGUIButton::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGUIButton::isScalingImage() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isScalingImage", args, 0) };
}
auto IGUIButton::isDrawingBorder() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isDrawingBorder", args, 0) };
}
auto IGUIButton::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IGUIElement::hasType(MissingType /* C++ irr::gui::EGUI_ELEMENT_TYPE (end) */  arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "hasType", args, 1) };
}
auto IGUIElement::getType() -> MissingType /* C++ irr::gui::EGUI_ELEMENT_TYPE */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getType", args, 0) };
}
auto IGUIElement::getParent() -> GameBindings::irr::gui::IGUIElement
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getParent", args, 0) };
}
auto IGUIElement::getID() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getID", args, 0) };
}
auto IGUIElement::getTypeName() -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTypeName", args, 0) };
}
auto IGUIElement::setText(GameBindings::wchar_t_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setText", args, 1) };
}
auto IGUIElement::setVisible(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setVisible", args, 1) };
}
auto IGUIElement::setMaxSize(GameBindings::irr::core::dimension2du arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMaxSize", args, 1) };
}
auto IGUIElement::getText() -> GameBindings::wchar_t_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getText", args, 0) };
}
auto IGUIElement::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGUIElement::setID(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setID", args, 1) };
}
auto IGUIElement::setMinSize(GameBindings::irr::core::dimension2du arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMinSize", args, 1) };
}
auto IGUIElement::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SUserEvent::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SUserEvent::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SLogEvent::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SLogEvent::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SKeyInput::set_Control(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Control", args, 1) };
}
auto SKeyInput::set_Shift(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Shift", args, 1) };
}
auto SKeyInput::get_Shift() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Shift", args, 0) };
}
auto SKeyInput::get_PressedDown() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_PressedDown", args, 0) };
}
auto SKeyInput::ref_Key() -> GameBindings::irr::gui::EKEY_CODE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Key", args, 0) };
}
auto SKeyInput::get_Key() -> GameBindings::irr::gui::EKEY_CODE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Key", args, 0) };
}
auto SKeyInput::set_Key(GameBindings::irr::gui::EKEY_CODE arg0) -> GameBindings::irr::gui::EKEY_CODE
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Key", args, 1) };
}
auto SKeyInput::ref_Char() -> GameBindings::wchar_t_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Char", args, 0) };
}
auto SKeyInput::set_PressedDown(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_PressedDown", args, 1) };
}
auto SKeyInput::get_Char() -> GameBindings::wchar_t_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Char", args, 0) };
}
auto SKeyInput::set_Char(GameBindings::wchar_t_expr arg0) -> GameBindings::wchar_t_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Char", args, 1) };
}
auto SKeyInput::get_Control() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Control", args, 0) };
}
auto SKeyInput::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SKeyInput::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SMouseInput::isLeftPressed() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isLeftPressed", args, 0) };
}
auto SMouseInput::isMiddlePressed() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isMiddlePressed", args, 0) };
}
auto SMouseInput::isRightPressed() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isRightPressed", args, 0) };
}
auto SMouseInput::get_Control() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Control", args, 0) };
}
auto SMouseInput::get_Shift() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Shift", args, 0) };
}
auto SMouseInput::set_Wheel(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Wheel", args, 1) };
}
auto SMouseInput::get_Wheel() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Wheel", args, 0) };
}
auto SMouseInput::ref_Y() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Y", args, 0) };
}
auto SMouseInput::set_Shift(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Shift", args, 1) };
}
auto SMouseInput::get_Y() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Y", args, 0) };
}
auto SMouseInput::ref_ButtonStates() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_ButtonStates", args, 0) };
}
auto SMouseInput::set_Y(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Y", args, 1) };
}
auto SMouseInput::ref_Event() -> GameBindings::irr::gui::EMOUSE_INPUT_EVENT
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Event", args, 0) };
}
auto SMouseInput::ref_X() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_X", args, 0) };
}
auto SMouseInput::set_Control(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Control", args, 1) };
}
auto SMouseInput::set_Event(GameBindings::irr::gui::EMOUSE_INPUT_EVENT arg0) -> GameBindings::irr::gui::EMOUSE_INPUT_EVENT
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Event", args, 1) };
}
auto SMouseInput::get_X() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_X", args, 0) };
}
auto SMouseInput::get_ButtonStates() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_ButtonStates", args, 0) };
}
auto SMouseInput::ref_Wheel() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Wheel", args, 0) };
}
auto SMouseInput::set_X(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_X", args, 1) };
}
auto SMouseInput::set_ButtonStates(GameBindings::uint_expr arg0) -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_ButtonStates", args, 1) };
}
auto SMouseInput::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto SMouseInput::get_Event() -> GameBindings::irr::gui::EMOUSE_INPUT_EVENT
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Event", args, 0) };
}
auto SMouseInput::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}

auto IGUISpinBox::setValue(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setValue", args, 1) };
}
auto IGUISpinBox::setStepSize(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setStepSize", args, 1) };
}
auto IGUISpinBox::setRange(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setRange", args, 2) };
}
auto IGUISpinBox::getValue() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getValue", args, 0) };
}
auto IGUISpinBox::getStepSize() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getStepSize", args, 0) };
}
auto IGUISpinBox::getMin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMin", args, 0) };
}
auto IGUISpinBox::getMax() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMax", args, 0) };
}
auto IGUISpinBox::setDecimalPlaces(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDecimalPlaces", args, 1) };
}
auto IGUISpinBox::getEditBox() -> GameBindings::irr::gui::IGUIEditBox
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getEditBox", args, 0) };
}
auto IGUISpinBox::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGUISpinBox::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SGUIEvent::get_EventType() -> GameBindings::irr::gui::EGUI_EVENT_TYPE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_EventType", args, 0) };
}
auto SGUIEvent::set_EventType(GameBindings::irr::gui::EGUI_EVENT_TYPE arg0) -> GameBindings::irr::gui::EGUI_EVENT_TYPE
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_EventType", args, 1) };
}
auto SGUIEvent::ref_Element() -> GameBindings::irr::gui::IGUIElement
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Element", args, 0) };
}
auto SGUIEvent::set_Element(GameBindings::irr::gui::IGUIElement arg0) -> GameBindings::irr::gui::IGUIElement
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Element", args, 1) };
}
auto SGUIEvent::ref_EventType() -> GameBindings::irr::gui::EGUI_EVENT_TYPE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_EventType", args, 0) };
}
auto SGUIEvent::ref_Caller() -> GameBindings::irr::gui::IGUIElement
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Caller", args, 0) };
}
auto SGUIEvent::get_Caller() -> GameBindings::irr::gui::IGUIElement
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Caller", args, 0) };
}
auto SGUIEvent::set_Caller(GameBindings::irr::gui::IGUIElement arg0) -> GameBindings::irr::gui::IGUIElement
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Caller", args, 1) };
}
auto SGUIEvent::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SGUIEvent::get_Element() -> GameBindings::irr::gui::IGUIElement
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Element", args, 0) };
}
auto SGUIEvent::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SEvent::set_UserEvent(GameBindings::irr::gui::SUserEvent arg0) -> GameBindings::irr::gui::SUserEvent
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_UserEvent", args, 1) };
}
auto SEvent::set_KeyInput(GameBindings::irr::gui::SKeyInput arg0) -> GameBindings::irr::gui::SKeyInput
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_KeyInput", args, 1) };
}
auto SEvent::set_JoystickEvent(GameBindings::irr::gui::SJoystickEvent arg0) -> GameBindings::irr::gui::SJoystickEvent
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_JoystickEvent", args, 1) };
}
auto SEvent::ref_UserEvent() -> GameBindings::irr::gui::SUserEvent
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_UserEvent", args, 0) };
}
auto SEvent::get_LogEvent() -> GameBindings::irr::gui::SLogEvent
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_LogEvent", args, 0) };
}
auto SEvent::get_KeyInput() -> GameBindings::irr::gui::SKeyInput
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_KeyInput", args, 0) };
}
auto SEvent::ref_JoystickEvent() -> GameBindings::irr::gui::SJoystickEvent
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_JoystickEvent", args, 0) };
}
auto SEvent::get_JoystickEvent() -> GameBindings::irr::gui::SJoystickEvent
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_JoystickEvent", args, 0) };
}
auto SEvent::ref_GUIEvent() -> GameBindings::irr::gui::SGUIEvent
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_GUIEvent", args, 0) };
}
auto SEvent::ref_MouseInput() -> GameBindings::irr::gui::SMouseInput
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_MouseInput", args, 0) };
}
auto SEvent::set_MouseInput(GameBindings::irr::gui::SMouseInput arg0) -> GameBindings::irr::gui::SMouseInput
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_MouseInput", args, 1) };
}
auto SEvent::get_MouseInput() -> GameBindings::irr::gui::SMouseInput
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_MouseInput", args, 0) };
}
auto SEvent::ref_EventType() -> GameBindings::irr::gui::EEVENT_TYPE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_EventType", args, 0) };
}
auto SEvent::ref_KeyInput() -> GameBindings::irr::gui::SKeyInput
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_KeyInput", args, 0) };
}
auto SEvent::get_GUIEvent() -> GameBindings::irr::gui::SGUIEvent
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_GUIEvent", args, 0) };
}
auto SEvent::set_GUIEvent(GameBindings::irr::gui::SGUIEvent arg0) -> GameBindings::irr::gui::SGUIEvent
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_GUIEvent", args, 1) };
}
auto SEvent::ref_LogEvent() -> GameBindings::irr::gui::SLogEvent
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_LogEvent", args, 0) };
}
auto SEvent::get_EventType() -> GameBindings::irr::gui::EEVENT_TYPE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_EventType", args, 0) };
}
auto SEvent::set_EventType(GameBindings::irr::gui::EEVENT_TYPE arg0) -> GameBindings::irr::gui::EEVENT_TYPE
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_EventType", args, 1) };
}
auto SEvent::get_UserEvent() -> GameBindings::irr::gui::SUserEvent
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_UserEvent", args, 0) };
}
auto SEvent::set_LogEvent(GameBindings::irr::gui::SLogEvent arg0) -> GameBindings::irr::gui::SLogEvent
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_LogEvent", args, 1) };
}
auto SEvent::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SEvent::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto EMOUSE_INPUT_EVENT::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto EMOUSE_INPUT_EVENT::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto EMOUSE_INPUT_EVENT::operator !=(GameBindings::irr::gui::EMOUSE_INPUT_EVENT arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto EMOUSE_INPUT_EVENT::operator ==(GameBindings::irr::gui::EMOUSE_INPUT_EVENT arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto EMOUSE_INPUT_EVENT::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto EMOUSE_INPUT_EVENT::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IGUIToolBar::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGUIToolBar::addButton(GameBindings::int_expr arg0, GameBindings::wchar_t_expr arg1, GameBindings::wchar_t_expr arg2, GameBindings::irr::video::ITexture arg3, GameBindings::irr::video::ITexture arg4, GameBindings::bool_expr arg5, GameBindings::bool_expr arg6) -> GameBindings::irr::gui::IGUIButton
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "addButton", args, 7) };
}
auto IGUIToolBar::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto EEVENT_TYPE::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto EEVENT_TYPE::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto EEVENT_TYPE::operator !=(GameBindings::irr::gui::EEVENT_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto EEVENT_TYPE::operator ==(GameBindings::irr::gui::EEVENT_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto EEVENT_TYPE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto EEVENT_TYPE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto EKEY_CODE::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto EKEY_CODE::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto EKEY_CODE::operator !=(GameBindings::irr::gui::EKEY_CODE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto EKEY_CODE::operator ==(GameBindings::irr::gui::EKEY_CODE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto EKEY_CODE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto EKEY_CODE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto EGUI_ALIGNMENT::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto EGUI_ALIGNMENT::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto EGUI_ALIGNMENT::operator !=(GameBindings::irr::gui::EGUI_ALIGNMENT arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto EGUI_ALIGNMENT::operator ==(GameBindings::irr::gui::EGUI_ALIGNMENT arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto EGUI_ALIGNMENT::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto EGUI_ALIGNMENT::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto E_MOUSE_BUTTON_STATE_MASK::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto E_MOUSE_BUTTON_STATE_MASK::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto E_MOUSE_BUTTON_STATE_MASK::operator !=(GameBindings::irr::gui::E_MOUSE_BUTTON_STATE_MASK arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto E_MOUSE_BUTTON_STATE_MASK::operator ==(GameBindings::irr::gui::E_MOUSE_BUTTON_STATE_MASK arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto E_MOUSE_BUTTON_STATE_MASK::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_MOUSE_BUTTON_STATE_MASK::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IGUIContextMenu::setItemText(GameBindings::uint_expr arg0, GameBindings::wchar_t_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setItemText", args, 2) };
}
auto IGUIContextMenu::addItem(GameBindings::wchar_t_expr arg0, GameBindings::int_expr arg1, GameBindings::bool_expr arg2, GameBindings::bool_expr arg3, GameBindings::bool_expr arg4, GameBindings::bool_expr arg5) -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "addItem", args, 6) };
}
auto IGUIContextMenu::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGUIContextMenu::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ICursorControl::setPosition(GameBindings::irr::core::vector2di arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setPosition", args, 1) };
}
auto ICursorControl::setPosition(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setPosition", args, 2) };
}
auto ICursorControl::setVisible(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setVisible", args, 1) };
}
auto ICursorControl::setReferenceRect(GameBindings::irr::core::recti arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setReferenceRect", args, 1) };
}
auto ICursorControl::isVisible() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isVisible", args, 0) };
}
auto ICursorControl::getRelativePosition() -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRelativePosition", args, 0) };
}
auto ICursorControl::getPosition() -> GameBindings::irr::core::vector2di
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getPosition", args, 0) };
}
auto ICursorControl::setRelativePosition(GameBindings::irr::core::vector2df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRelativePosition", args, 1) };
}
auto ICursorControl::setRelativePosition(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setRelativePosition", args, 2) };
}
auto ICursorControl::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ICursorControl::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SJoystickEvent::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SJoystickEvent::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto EGUI_EVENT_TYPE::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto EGUI_EVENT_TYPE::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto EGUI_EVENT_TYPE::operator !=(GameBindings::irr::gui::EGUI_EVENT_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto EGUI_EVENT_TYPE::operator ==(GameBindings::irr::gui::EGUI_EVENT_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto EGUI_EVENT_TYPE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto EGUI_EVENT_TYPE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

		}
	}
}
