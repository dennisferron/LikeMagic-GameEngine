method(namespace, SharedTypes, PredefinedValues, Constants, ConstraintStyles,
    IrrlichtUserInterfaceModule := Module clone lexicalDo(
        scripts := self scripts
        EventDispatch := scripts EventDispatch(namespace irr, SharedTypes EnumMap)
        GuiEvents := scripts GuiEvents(SharedTypes, PredefinedValues)
        Keyboard := scripts Keyboard(namespace irr)
        Mouse := scripts Mouse(namespace Bullet, namespace irr, namespace Custom, PredefinedValues, Constants, ConstraintStyles)
        MouseDragLinkAttribute := scripts Mouse(namespace Bullet, namespace irr, namespace Custom, PredefinedValues, Constants, ConstraintStyles)
        Menu := scripts Menu(namespace irr)
        SceneNodeSelector := scripts SceneNodeSelector
    )
)
