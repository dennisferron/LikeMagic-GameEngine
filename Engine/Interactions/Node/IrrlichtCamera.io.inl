
method(NodeInteraction, Node, Irrlicht, Avatar, Time,

    IrrlichtCamera := NodeInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("component") setTrigger(
            irrComp : Irrlicht Component,
            time : Time
        )

        referent at("node") setTrigger(
            avatarCamera  : Avatar Camera
        )

        enter := method(
            site addAttribute(irrComp camera)
            time beforeGraphics append(
                block(
                    irrComp camera update
                )
            )
            self
        )
    )

    Node registerInteraction(IrrlichtCamera)

    return IrrlichtCamera
)
