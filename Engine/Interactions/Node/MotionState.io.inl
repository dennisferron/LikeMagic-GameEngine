
method(NodeInteraction, Node, Irrlicht, Bullet,

    MotionState := NodeInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("node") setTrigger(
            physRep : Bullet NodeAttribute,
            dispRep : Irrlicht NodeAttribute
        )

        enter := method(
            dispRep setMotionState(physRep motionState)
            self
        )
    )

    Node registerInteraction(MotionState)

    return MotionState
)
