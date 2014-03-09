method(rootModule, namespace, Constants, FileSystem,

    writeln("About to reference namespace std")
    msg := namespace std type
    writeln(msg)
    writeln("Done referencing namespace std")

    rootModule lexicalDo(

        scripts := self scripts

        SharedTypes := scripts SharedTypes             requiredConfig( namespace std )
        Model := scripts Model                   requiredConfig( namespace std )
        Styles := scripts Styles                  requiredConfig( Constants, Model Structure, namespace irr video SColor )
        Avatar := scripts Avatar                  requiredConfig( namespace Bullet, namespace irr, namespace Custom, Styles, namespace )
        UserInterface := scripts UserInterface           requiredConfig( namespace irr )
        Desteer := scripts Desteer                 optionalConfig( namespace irr, namespace desteer )
        Bullet := scripts Bullet                  optionalConfig( namespace Bullet, namespace Custom, Constants, namespace, Styles )
        Irrlicht := scripts Irrlicht                optionalConfig( namespace, SharedTypes, UserInterface MainWindow, namespace, Constants, namespace ScriptUtil, Styles )
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
