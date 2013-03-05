
method(ComponentInteraction, Model, Irrlicht, Avatar,

    IrrlichtKeyInput := ComponentInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("component") setTrigger(
            irrComp : Irrlicht Component,
            avComp  : Avatar Component
        )

        enter := method(
            avComp setEvents(irrComp events)
            self
        )
    )

    Model Graph registerInteraction(IrrlichtKeyInput)

    return IrrlichtKeyInput
)
