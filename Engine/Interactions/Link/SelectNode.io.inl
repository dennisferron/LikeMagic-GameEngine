method(LinkInteraction, Link, Irrlicht,

    SelectNode := LinkInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("fromNode") setTrigger(
            selector : Irrlicht UserInterface SceneNodeSelector
        )

        referent at("toNode") setTrigger(
            dispAttr : Irrlicht NodeAttribute
        )

        enter := method(
            selector select(dispAttr)
            self
        )

        leave := method(
            selector deselect(dispAttr)
            self
        )
    )

    Link registerInteraction(SelectNode)

    return SelectNode
)
