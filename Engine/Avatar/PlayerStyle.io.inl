
method(Styles,

    PlayerStyle := Styles CylZStyle clone do(
        setRadius(0.5)
        setLength(0.20)
        setMass(3)
        setColor(255, 255, 255)
        setTexture("Media/simpler-bronze-ratchet-gear.png")
        setAlternateTextureWrap(true)
        setPos(0,10,0)
        setFriction(4.0)
        //setRestitution(0.1)
        setMargin(0.1)
        setCollisionResponseTag("player")
        setLinearFactor(1,1,0)
        setAngularFactor(0,0,1)
        //setIsMouseDraggable(false)

        // For debugging:
        setGravity(0, -0.3, 0)
    )
)
