// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/IrrlichtValues.hpp"

#include <irrlicht.h>

#include "LikeMagic/Lang/LangInterpreter.hpp"

#include "LikeMagic/BindingMacros.hpp"
#include "Bindings/Irrlicht/ScriptedSceneNode.hpp"
#include "Bindings/Irrlicht/ScriptedEventReceiver.hpp"

using namespace std;
using namespace LM;
using namespace irr;
using namespace irr::video;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;

namespace Bindings { namespace Irrlicht {

void add_values()
{
    auto& ns = type_system->global_namespace();

    typedef core::string<fschar_t> irrFsStr;
    LM_CREATE_VALUE(ns, irrFsStr)

    LM_CREATE_VALUES(ns, (dimension2du)(recti)(vector2df)(vector2di)(vector3df)(aabbox3df))

    LM_CREATE_VALUES(ns, (u16)(SColor)(SColorf)(SMaterial)(S3DVertex)(SExposedVideoData))

    LM_ADD_VECTORS(ns, (u16)(S3DVertex)(vector3df))

    LM_CREATE_VALUE(ns, ScriptedSceneNode, 0, 0, 0)
    //LM_ADD_VALUE(ns, ScriptedEventReceiver)

    LM_ENUM_VALUES(ns, (EDT_DIRECT3D9)(EDT_DIRECT3D8)(EDT_OPENGL)(EDT_SOFTWARE)(EDT_BURNINGSVIDEO)(EDT_NULL))

    LM_ENUM_VALUES(ns, (ETPS_17))

    LM_ENUM_VALUES(ns, (EMF_WIREFRAME)(EMF_POINTCLOUD)(EMF_GOURAUD_SHADING)(EMF_LIGHTING)(EMF_ZBUFFER)(EMF_ZWRITE_ENABLE)
            (EMF_BACK_FACE_CULLING)(EMF_FRONT_FACE_CULLING)(EMF_BILINEAR_FILTER)(EMF_TRILINEAR_FILTER)(EMF_ANISOTROPIC_FILTER)
            (EMF_FOG_ENABLE)(EMF_NORMALIZE_NORMALS)(EMF_TEXTURE_WRAP)(EMF_ANTI_ALIASING)(EMF_COLOR_MASK)(EMF_COLOR_MATERIAL))

    LM_ENUM_VALUES(ns, (ETS_VIEW)(ETS_WORLD)(ETS_PROJECTION)(ETS_TEXTURE_0)(ETS_TEXTURE_1)(ETS_TEXTURE_2)(ETS_TEXTURE_3))

    LM_ENUM_VALUES(ns, (EVT_STANDARD)(EVT_2TCOORDS)(EVT_TANGENTS))

    LM_ENUM_VALUES(ns, (EMT_SOLID)(EMT_SOLID_2_LAYER)(EMT_LIGHTMAP)(EMT_LIGHTMAP_ADD)(EMT_LIGHTMAP_M2)(EMT_LIGHTMAP_M4)(EMT_LIGHTMAP_LIGHTING)(EMT_LIGHTMAP_LIGHTING_M2)
        (EMT_LIGHTMAP_LIGHTING_M4)(EMT_DETAIL_MAP)(EMT_LIGHTMAP_LIGHTING)(EMT_LIGHTMAP_LIGHTING_M2)(EMT_LIGHTMAP_LIGHTING_M4)(EMT_DETAIL_MAP)(EMT_SPHERE_MAP)(EMT_REFLECTION_2_LAYER)
        (EMT_TRANSPARENT_ADD_COLOR)(EMT_TRANSPARENT_ALPHA_CHANNEL)(EMT_TRANSPARENT_ALPHA_CHANNEL_REF)(EMT_TRANSPARENT_VERTEX_ALPHA)(EMT_TRANSPARENT_REFLECTION_2_LAYER)(EMT_NORMAL_MAP_SOLID)
        (EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR)(EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA)(EMT_PARALLAX_MAP_SOLID)(EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR)
        (EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA)(EMT_ONETEXTURE_BLEND)
    )

    LM_ENUM_VALUES(ns, (EHM_NEVER)(EHM_STATIC)(EHM_DYNAMIC)(EHM_STREAM) )

    LM_ENUM_VALUES(ns, (EBT_NONE)(EBT_VERTEX)(EBT_INDEX)(EBT_VERTEX_AND_INDEX) )

    LM_ENUM_VALUES(ns,
        (ECM_NONE)
        (ECM_DIFFUSE)
        (ECM_AMBIENT)
        (ECM_EMISSIVE)
        (ECM_SPECULAR)
        (ECM_DIFFUSE_AND_AMBIENT)
    )

    LM_ENUM_VALUES(ns,
        (ISREL3D_FRONT)
        (ISREL3D_BACK)
        (ISREL3D_PLANAR)
        (ISREL3D_SPANNING)
        (ISREL3D_CLIPPED)
    )

    LM_ENUM_VALUES(ns, (EAAM_FULL_BASIC))

    LM_ENUM_VALUES(ns,
		(KEY_LBUTTON)  // Left mouse button
		(KEY_RBUTTON)  // Right mouse button
		(KEY_CANCEL)  // Control-break processing
		(KEY_MBUTTON)  // Middle mouse button (three-button mouse)
		(KEY_XBUTTON1)  // Windows 2000/XP: X1 mouse button
		(KEY_XBUTTON2)  // Windows 2000/XP: X2 mouse button
		(KEY_BACK)  // BACKSPACE key
		(KEY_TAB)  // TAB key
		(KEY_CLEAR)  // CLEAR key
		(KEY_RETURN)  // ENTER key
		(KEY_SHIFT)  // SHIFT key
		(KEY_CONTROL)  // CTRL key
		(KEY_MENU)  // ALT key
		(KEY_PAUSE)  // PAUSE key
		(KEY_CAPITAL)  // CAPS LOCK key
		(KEY_KANA)  // IME Kana mode
		(KEY_HANGUEL)  // IME Hanguel mode (maintained for compatibility use (KEY_HANGUL)
		(KEY_HANGUL)  // IME Hangul mode
		(KEY_JUNJA)  // IME Junja mode
		(KEY_FINAL)  // IME final mode
		(KEY_HANJA)  // IME Hanja mode
		(KEY_KANJI)  // IME Kanji mode
		(KEY_ESCAPE)  // ESC key
		(KEY_CONVERT)  // IME convert
		(KEY_NONCONVERT)  // IME nonconvert
		(KEY_ACCEPT)  // IME accept
		(KEY_MODECHANGE)  // IME mode change request
		(KEY_SPACE)  // SPACEBAR
		(KEY_PRIOR)  // PAGE UP key
		(KEY_NEXT)  // PAGE DOWN key
		(KEY_END)  // END key
		(KEY_HOME)  // HOME key
		(KEY_LEFT)  // LEFT ARROW key
		(KEY_UP)  // UP ARROW key
		(KEY_RIGHT)  // RIGHT ARROW key
		(KEY_DOWN)  // DOWN ARROW key
		(KEY_SELECT)  // SELECT key
		(KEY_PRINT)  // PRINT key
		(KEY_EXECUT)  // EXECUTE key
		(KEY_SNAPSHOT)  // PRINT SCREEN key
		(KEY_INSERT)  // INS key
		(KEY_DELETE)  // DEL key
		(KEY_HELP)  // HELP key
		(KEY_KEY_0)  // 0 key
		(KEY_KEY_1)  // 1 key
		(KEY_KEY_2)  // 2 key
		(KEY_KEY_3)  // 3 key
		(KEY_KEY_4)  // 4 key
		(KEY_KEY_5)  // 5 key
		(KEY_KEY_6)  // 6 key
		(KEY_KEY_7)  // 7 key
		(KEY_KEY_8)  // 8 key
		(KEY_KEY_9)  // 9 key
    )
    LM_ENUM_VALUES(ns,
		(KEY_KEY_A)  // A key
		(KEY_KEY_B)  // B key
		(KEY_KEY_C)  // C key
		(KEY_KEY_D)  // D key
		(KEY_KEY_E)  // E key
		(KEY_KEY_F)  // F key
		(KEY_KEY_G)  // G key
		(KEY_KEY_H)  // H key
		(KEY_KEY_I)  // I key
		(KEY_KEY_J)  // J key
		(KEY_KEY_K)  // K key
		(KEY_KEY_L)  // L key
		(KEY_KEY_M)  // M key
		(KEY_KEY_N)  // N key
		(KEY_KEY_O)  // O key
		(KEY_KEY_P)  // P key
		(KEY_KEY_Q)  // Q key
		(KEY_KEY_R)  // R key
		(KEY_KEY_S)  // S key
		(KEY_KEY_T)  // T key
		(KEY_KEY_U)  // U key
		(KEY_KEY_V)  // V key
		(KEY_KEY_W)  // W key
		(KEY_KEY_X)  // X key
		(KEY_KEY_Y)  // Y key
		(KEY_KEY_Z)  // Z key
		(KEY_LWIN)  // Left Windows key (Microsoft� Natural� keyboard)
		(KEY_RWIN)  // Right Windows key (Natural keyboard)
		(KEY_APPS)  // Applications key (Natural keyboard)
		(KEY_SLEEP)  // Computer Sleep key
		(KEY_NUMPAD0)  // Numeric keypad 0 key
		(KEY_NUMPAD1)  // Numeric keypad 1 key
		(KEY_NUMPAD2)  // Numeric keypad 2 key
		(KEY_NUMPAD3)  // Numeric keypad 3 key
		(KEY_NUMPAD4)  // Numeric keypad 4 key
		(KEY_NUMPAD5)  // Numeric keypad 5 key
		(KEY_NUMPAD6)  // Numeric keypad 6 key
		(KEY_NUMPAD7)  // Numeric keypad 7 key
		(KEY_NUMPAD8)  // Numeric keypad 8 key
		(KEY_NUMPAD9)  // Numeric keypad 9 key
		(KEY_MULTIPLY)  // Multiply key
		(KEY_ADD)  // Add key
		(KEY_SEPARATOR)  // Separator key
		(KEY_SUBTRACT)  // Subtract key
		(KEY_DECIMAL)  // Decimal key
		(KEY_DIVIDE)  // Divide key
		(KEY_F1)  // F1 key
		(KEY_F2)  // F2 key
		(KEY_F3)  // F3 key
		(KEY_F4)  // F4 key
		(KEY_F5)  // F5 key
		(KEY_F6)  // F6 key
		(KEY_F7)  // F7 key
		(KEY_F8)  // F8 key
		(KEY_F9)  // F9 key
		(KEY_F10)  // F10 key
		(KEY_F11)  // F11 key
		(KEY_F12)  // F12 key
		(KEY_F13)  // F13 key
		(KEY_F14)  // F14 key
		(KEY_F15)  // F15 key
		(KEY_F16)  // F16 key
		(KEY_F17)  // F17 key
		(KEY_F18)  // F18 key
		(KEY_F19)  // F19 key
		(KEY_F20)  // F20 key
		(KEY_F21)  // F21 key
		(KEY_F22)  // F22 key
		(KEY_F23)  // F23 key
		(KEY_F24)  // F24 key
		(KEY_NUMLOCK)  // NUM LOCK key
		(KEY_SCROLL)  // SCROLL LOCK key
		(KEY_LSHIFT)  // Left SHIFT key
		(KEY_RSHIFT)  // Right SHIFT key
		(KEY_LCONTROL)  // Left CONTROL key
		(KEY_RCONTROL)  // Right CONTROL key
		(KEY_LMENU)  // Left MENU key
		(KEY_RMENU)  // Right MENU key
		(KEY_PLUS)  // Plus Key   (+)
		(KEY_COMMA) // Comma Key  (,)
		(KEY_MINUS)  // Minus Key  (-)
		(KEY_PERIOD)  // Period Key (.)
		(KEY_ATTN)  // Attn key
		(KEY_CRSEL)  // CrSel key
		(KEY_EXSEL)  // ExSel key
		(KEY_EREOF)  // Erase EOF key
		(KEY_PLAY)  // Play key
		(KEY_ZOOM)  // Zoom key
		(KEY_PA1)  // PA1 key
		(KEY_OEM_CLEAR)   // Clear key

		(KEY_KEY_CODES_COUNT)  // this is not a key, but the amount of keycodes there are.
        )

    LM_ENUM_VALUES(ns, (EET_KEY_INPUT_EVENT)(EET_MOUSE_INPUT_EVENT)(EET_GUI_EVENT))


	//EMOUSE_INPUT_EVENT
    LM_ENUM_VALUES(ns,

		// Left mouse button was pressed down.
		(EMIE_LMOUSE_PRESSED_DOWN)

		// Right mouse button was pressed down.
		(EMIE_RMOUSE_PRESSED_DOWN)

		// Middle mouse button was pressed down.
		(EMIE_MMOUSE_PRESSED_DOWN)

		// Left mouse button was left up.
		(EMIE_LMOUSE_LEFT_UP)

		// Right mouse button was left up.
		(EMIE_RMOUSE_LEFT_UP)

		// Middle mouse button was left up.
		(EMIE_MMOUSE_LEFT_UP)

		// The mouse cursor changed its position.
		(EMIE_MOUSE_MOVED)

		// The mouse wheel was moved. Use Wheel value in event data to find out
		// in what direction and how fast.
		(EMIE_MOUSE_WHEEL)

		// Left mouse button double click.
		// This event is generated after the second (EMIE_LMOUSE_PRESSED_DOWN event.
		(EMIE_LMOUSE_DOUBLE_CLICK)

		// Right mouse button double click.
		// This event is generated after the second (EMIE_RMOUSE_PRESSED_DOWN event.
		(EMIE_RMOUSE_DOUBLE_CLICK)

		// Middle mouse button double click.
		// This event is generated after the second (EMIE_MMOUSE_PRESSED_DOWN event.
		(EMIE_MMOUSE_DOUBLE_CLICK)

		// Left mouse button triple click.
		// This event is generated after the third (EMIE_LMOUSE_PRESSED_DOWN event.
		(EMIE_LMOUSE_TRIPLE_CLICK)

		// Right mouse button triple click.
		// This event is generated after the third (EMIE_RMOUSE_PRESSED_DOWN event.
		(EMIE_RMOUSE_TRIPLE_CLICK)

		// Middle mouse button triple click.
		// This event is generated after the third (EMIE_MMOUSE_PRESSED_DOWN event.
		(EMIE_MMOUSE_TRIPLE_CLICK)

		// No real event. Just for convenience to get number of events
		(EMIE_COUNT)
    )

    LM_ENUM_VALUES(ns, (EGUIA_UPPERLEFT)(EGUIA_LOWERRIGHT)(EGUIA_CENTER)(EGUIA_SCALE))

    LM_ENUM_VALUES(ns, (EGET_BUTTON_CLICKED)(EGET_TREEVIEW_NODE_DESELECT)(EGET_TREEVIEW_NODE_SELECT)(EGET_TREEVIEW_NODE_EXPAND)(EGET_TREEVIEW_NODE_COLLAPS))
}

}}

