method(module,
    Link := Object clone lexicalDo(
        module := module

        style := nil
        fromNode := nil
        toNode := nil
        domain ::= nil
        graph := nil

        // This list is shared among all Link clones
        possibleInteractions := list()

        registerInteraction := method(interaction,
            possibleInteractions append(interaction)
        )

        init := method(
            setDomain(module Domain clone setSite(self))
        )

        with := method(newStyle,
            setStyle(newStyle)
        )

        setStyle := method(value, expectedInteraction,
            updateSlot("style", value)
            domain addObject("style", style, expectedInteraction)
            self
        )

        setFromNode := method(value,
            updateSlot("fromNode", value)
            // TODO:  Notify and remove old node value from domain.
            if(fromNode != nil,
                domain merge("fromNode", fromNode domain, "node")
            )
            self
        )

        setToNode := method(value,
            updateSlot("toNode", value)
            // TODO:  Notify and remove old node value from domain.
            if(toNode != nil,
                domain merge("toNode", toNode domain, "node")
            )
            self
        )

        setGraph := method(value,
            updateSlot("graph", value)
            // TODO:  Notify and remove old components from the domain.
            domain merge("component", graph domain, "component")
            self
        )

        addAttribute := method(attr, expectedInteraction,
            domain addObject("link", attr, expectedInteraction)
            self
        )

        findAttribute := method(attr,
            domain findObject("link", attr)
        )
    )
)
