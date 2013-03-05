
method(ComponentInteraction, Model, Avatar,

    AvatarTime := ComponentInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("component") setTrigger(
            avComp : Avatar Component,
            time : Model Time
        )

        enter := method(

            time beforePhysics append(
                block(timeStep,
                    avComp beforePhysics(timeStep)
                )
            )

            self
        )
    )

    Model Graph registerInteraction(AvatarTime)

    return AvatarTime
)
