method(LinkInteraction, MouseDragLinkAttribute, IrrlichtNodeAttribute,

    IrrlichtMouseDrag := LinkInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("link") setTrigger(
            mouseAttr : MouseDragLinkAttribute
        )

        referent at("toNode") setTrigger(
            irrAttr : IrrlichtNodeAttribute
        )

        constraintAttr ::= nil

        enter := method(
            mouseAttr setOnDrag(block(pos,
                irrAttr setPos(pos)
            ))
        )

        leave := method(
            mouseAttr setOnDrag(nil)
        )
    )

    return IrrlichtMouseDrag
)
