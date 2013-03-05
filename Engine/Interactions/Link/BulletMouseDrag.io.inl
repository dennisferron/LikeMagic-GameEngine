method(LinkInteraction, Node, MouseDragLinkAttribute, LinkStyles, BulletComponent,

    BulletMouseDrag := LinkInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("link") setTrigger(
            mouseAttr : MouseDragLinkAttribute
        )

        referent at("component") setTrigger(
            bulletComp : BulletComponent
        )

        referent at("toNode") setTrigger(
            toNode : Node
        )

        constraintAttr ::= nil

        enter := method(
            setConstraintAttr(bulletComp addLink(Point2PointStyle, nil, toNode))
            mouseAttr setOnDrag(block(pos,
                constraintAttr constraint setPivotB(btVector3 tmp(pos get_X, pos get_Y, 0))
            ))
        )

        leave := method(
            mouseAttr setOnDrag(nil)
            site removeAttribute(constraintAttr)
            setConstraintAttr(nil)
        )
    )

    return BulletMouseDrag
)
