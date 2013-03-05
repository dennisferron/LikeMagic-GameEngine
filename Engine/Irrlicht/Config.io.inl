method(namespace, SharedTypes, MainWindow, PredefinedValues, Constants, ScriptUtil, Styles,
    IrrlichtModule := Module clone
    IrrlichtModule lexicalDo(
        scripts := self scripts

        UserInterface := scripts UserInterface requiredConfig( namespace, SharedTypes, PredefinedValues, Constants, Styles ConstraintStyles )

        Camera := scripts Camera(namespace irr, Constants)

        Assets := scripts Assets(namespace irr core)

        DisplayShapes := scripts DisplayShapes(namespace irr, namespace Custom, PredefinedValues)
        ShapeBuilder := scripts ShapeBuilder(namespace irr, namespace Custom, PredefinedValues)
        SceneNodes := scripts SceneNodes(namespace irr, PredefinedValues)
        SceneNodeBuilder := scripts SceneNodeBuilder(namespace irr, namespace Custom, PredefinedValues)

        Component := scripts Component(IrrlichtModule, namespace irr, namespace Custom, MainWindow, PredefinedValues, ScriptUtil )

        NodeAttribute := scripts NodeAttribute(namespace irr, namespace Custom, Constants)
    )
)
