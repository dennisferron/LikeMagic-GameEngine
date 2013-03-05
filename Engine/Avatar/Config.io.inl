method(namespace_Bullet, namespace_irr, namespace_Custom, Styles, PredefinedValues,
    Avatar := Module clone
    Avatar lexicalDo(
        scripts := self scripts
        Camera := scripts Camera()
        NodeAttribute := scripts NodeAttribute(namespace_Bullet, namespace_irr, namespace_Custom)
        KeyInputs := scripts KeyInputs(namespace_irr, namespace_Custom, PredefinedValues)
        PlayerStyle := scripts PlayerStyle(Styles GameObjStyles)
        Component := scripts Component(Avatar)
    )
)
