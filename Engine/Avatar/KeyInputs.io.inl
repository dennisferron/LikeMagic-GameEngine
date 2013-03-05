method(namespace_irr, namespace_Custom, PredefinedValues,

    KeyInputs := Object clone lexicalDo(

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_Custom)
        appendProto(PredefinedValues)

        update := method(player, events,

            if (events isKeyDown(KEY_KEY_X),
                //if (engine hasSlot("robot"), engine robot fallApart)
                //if (engine hasSlot("tree"), engine tree fallApart)
                writeln("X key pressed")
                nil
            )

            if (events isKeyDown(KEY_KEY_Z),
                //props makeRobot
                nil
            )

            if (events isKeyDown(KEY_KEY_T),
                //props makeTree
                nil
            )

            if (events isKeyDown(KEY_DOWN),
                player dive
            )

            if (events isKeyDown(KEY_UP),
                player jump
            )

            if (events isKeyDown(KEY_RIGHT),
                player right
            )

            if (events isKeyDown(KEY_LEFT),
                player left
            )

            if (events isKeyDown(KEY_SPACE),
                //player attack
                nil
            )
        )
    )
)
