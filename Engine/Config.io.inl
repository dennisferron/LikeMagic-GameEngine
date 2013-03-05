method(rootModule, LikeMagicModule, Constants, FileSystem,

    rootModule lexicalDo(

        scripts := self scripts
        namespace := LikeMagicModule LikeMagic namespace

        SharedTypes := scripts SharedTypes             requiredConfig( namespace std )
        Model := scripts Model                   requiredConfig( namespace std )
        Styles := scripts Styles                  requiredConfig( Constants, Model Structure, namespace irr video SColor )
        Avatar := scripts Avatar                  requiredConfig( namespace Bullet, namespace irr, namespace Custom, Styles, LikeMagicModule PredefinedValues )
        UserInterface := scripts UserInterface           requiredConfig
        Desteer := scripts Desteer                 optionalConfig( namespace irr, namespace desteer )
        Bullet := scripts Bullet                  optionalConfig( namespace Bullet, namespace Custom, Constants, LikeMagicModule PredefinedValues, Styles )
        Irrlicht := scripts Irrlicht                optionalConfig( namespace, SharedTypes, UserInterface MainWindow, LikeMagicModule PredefinedValues, Constants, namespace ScriptUtil, Styles )
        EditorGUI := scripts EditorGUI               requiredConfig( namespace irr )

        Subsystems := Module clone

        Subsystems Time := scripts requiredSlot("Time",     Model Time)
        Subsystems Bullet := scripts optionalSlot("Bullet",   Bullet )
        Subsystems Irrlicht := scripts optionalSlot("Irrlicht", Irrlicht )
        Subsystems Desteer := scripts optionalSlot("Desteer",  Desteer )
        Subsystems Avatar := scripts requiredSlot("Avatar",   Avatar)
        Subsystems EditorGUI := scripts optionalSlot("EditorGUI", EditorGUI)

        Interactions := scripts Interactions            requiredConfig( namespace, Model, Subsystems, Constants, Styles )
        LevelSystem := scripts LevelSystem             optionalConfig( namespace Bullet, namespace irr, namespace Custom, namespace TPS, Model Structure, Styles, namespace ScriptUtil )

        UnitTests := scripts UnitTests requiredConfig(namespace, Model, Interactions, Subsystems, Styles)
    )
)
