
method(module,

    Node := Object clone lexicalDo(

        module := module

        graph := nil
        setGraph := method(value,
            self graph = value
            graph components foreach(c,
                domain addObject("component", c)
            )
        )

        style ::= nil
        domain ::= nil

        // This list is shared among all Node clones
        possibleInteractions := list()

        init := method(
            setDomain(
                module Domain clone setSite(self)
            )
        )

        with := method(style,
            setStyle(style)
        )

        registerInteraction := method(interaction,
            possibleInteractions append(interaction)
        )

        addAttribute := method(attr, expectedInteraction,
            domain addObject("node", attr, expectedInteraction)
            self
        )

        findAttribute := method(attr,
            domain findObject("node", attr)
        )
    )

    Node getPos := method(
        Exception raise("TODO: Define Model Node getPos")
    )

    Node do(
        getX := method(getPos x)
        getY := method(getPos y)
        getZ := method(getPos z)
    )

    Node dispose := method(nil)

    return Node
)
