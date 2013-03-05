method(GameObjStyle,

    GameObjStyles := Module clone lexicalDo(

        EmptyStyle := GameObjStyle clone setShape("none")
        BoxStyle := GameObjStyle clone setShape("box")
        BallStyle := GameObjStyle clone setShape("ball")
        CylStyle := GameObjStyle clone setShape("cyl")
        CylXStyle := GameObjStyle clone setShape("cylX")
        CylZStyle := GameObjStyle clone setShape("cylZ")
        ConeStyle := GameObjStyle clone setShape("cone")
        ConeXStyle := GameObjStyle clone setShape("coneX")
        ConeZStyle := GameObjStyle clone setShape("coneZ")

        SkyboxStyle := GameObjStyle clone setShape("skybox") setPhysShape("none")

        HillStyle := GameObjStyle clone do(
            setShape("hills")
            setGameObjType("static")
            setMass(0)
            setSize(1.0f, 2.0f, 1.0f)
            xTiles ::= 15.0
            zTiles ::= 15.0
            xHills ::= 2
            zHills ::= 1
            xTextureRepeat ::= 1
            zTextureRepeat ::= 1
        )

        PlaneStyle := GameObjStyle clone do(
            setDispShape("plane")
            setPhysShape("mesh")
            setGameObjType("static")
            setMargin(0.1)
            setMass(0)
            setSize(1.0f, 0.0f, 1.0f)
            xTiles ::= 15.0
            zTiles ::= 15.0
            xTextureRepeat ::= 1
            zTextureRepeat ::= 1
        )

        WallStyle := GameObjStyle clone lexicalDo(
            prependProto(CylStyle)
            setColor(200, 60, 240)
            setMass(0)
            setRadius(10)
            setLength(1000)
        )

        GeneratorStyle := GameObjStyle clone lexicalDo(
            setIsKinematic(true)
            setPhysShape(none)
            setCollisionGroup(0)  // TODO:  make a group just for generators
            setCollisionMask(0)

            spawnStyle ::= BallStyle clone do(
                setVel(0, 30, 0)
            )
        )

        ClothStyle := PlaneStyle clone do(
            setDispShape("plane")
            setGameObjType("soft")
        )
    )
)
