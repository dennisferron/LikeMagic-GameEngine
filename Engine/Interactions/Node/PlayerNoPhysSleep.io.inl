
method(NodeInteraction, Node, Avatar, Bullet,

    PlayerNoPhysSleep := NodeInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("node") setTrigger(
            physRep : Bullet NodeAttribute,
            playerRep : Avatar NodeAttribute
        )

        enter := method(
            physRep disableSleepState
            self
        )
    )

    Node registerInteraction(PlayerNoPhysSleep)

    return PlayerNoPhysSleep
)
