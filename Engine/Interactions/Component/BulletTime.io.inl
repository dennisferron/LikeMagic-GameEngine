
method(ComponentInteraction, Model, Bullet,

    BulletTime := ComponentInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("component") setTrigger(
            bltComp : Bullet Component,
            time : Model Time
        )

        enter := method(

            time onPhysics append(
                block(timeStep,
                    bltComp onPhysics(timeStep)
                )
            )

            time onGraphics append(
                block(timeStep,
                    bltComp onGraphics(timeStep)
                )
            )

            self
        )
    )

    Model Graph registerInteraction(BulletTime)

    return BulletTime
)
