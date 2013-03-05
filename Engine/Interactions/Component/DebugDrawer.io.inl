method(ComponentInteraction, Model, Bullet, Irrlicht, namespace_Custom,

    DebugDrawer := ComponentInteraction clone lexicalDo(

        appendProto(namespace_Custom)

        setReferent(mapSubdomains)

        referent at("component") setTrigger(
            physComp : Bullet Component,
            dispComp : Irrlicht Component
        )

        motionState ::= nil

        enter := method(
            // Debug drawing will show phys objs, constraint limits and so forth.
            //physComp setDebugDrawer(IrrlichtBulletDebugDrawer new(dispComp driver))
            self
        )
    )

    Model Graph registerInteraction(DebugDrawer)

    return DebugDrawer
)

