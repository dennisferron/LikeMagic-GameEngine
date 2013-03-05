
method(ComponentInteraction, Model, Irrlicht,

    IrrlichtTime := ComponentInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("component") setTrigger(
            irrComp : Irrlicht Component,
            time : Model Time
        )

        enter := method(

            time setDeviceTimer(
                block(
                    irrComp deviceTimer getTime
                )
            )

            time setShouldRun(
                block(
                    irrComp shouldRun
                )
            )

            time beforeGraphics append(
                block(
                    irrComp beforeGraphics
                )
            )

            time onGraphics append(
                block(timeStep,
                    irrComp onGraphics(timeStep)
                )
            )

            time afterGraphics append(
                block(
                    irrComp afterGraphics
                )
            )

            self
        )
    )

    Model Graph registerInteraction(IrrlichtTime)

    return IrrlichtTime
)
