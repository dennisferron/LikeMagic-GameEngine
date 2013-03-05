method(namespace_irr, namespace_Custom, namespace_TPS, Styles, ScriptUtil,

    Tile := Object clone lexicalDo(
        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_Custom)
        appendProto(Styles GameObjStyles)

        ScriptUtil := ScriptUtil

        graph ::= nil
        meshMan ::= nil

        tileRect ::= nil

        pathMinZ ::= nil
        pathMaxZ ::= nil
        skyCutZ ::= nil

        backGameObj     ::= nil
        walkwayGameObj  ::= nil
        foreGameObj     ::= nil

        surface ::= nil
    )

    Tile refresh := method(

        tolerance := 0.05

        splitForWalkway := MeshTools createHillMesh(surface, tileRect, pathMinZ-tolerance, pathMaxZ+tolerance)

        tileStyle := EmptyStyle setGameObjType("static") setDispShape("mesh") setMass(0) setPos(0, 0, 0) setIsMouseDraggable(false)

        // For debugging
        //tileStyle setWireframe(true)

        // Temporary
        walkwayDepth := 4.0
        repeatAmt := 1.0 / 2.0
        s := repeatAmt/walkwayDepth
        t := repeatAmt/walkwayDepth

        meshMan makePlanarTextureMapping(
            splitForWalkway getMeshBuffer(0),    // buffer
            s,  // resolutionS
            t,  // resolutionT
            1,  // axis
            vector3df tmp(-tileRect getWidth/2.0, walkwayDepth/2.0, (walkwayDepth/2.0)/repeatAmt)  // offset
        )

        walkStyle := tileStyle clone setTexture("Media/boardwalk.png") setPhysShape("mesh") setMesh(splitForWalkway)
        setWalkwayGameObj(graph addNode(walkStyle))
        walkwayGameObj addAttribute(self)

        repeatAmt := 1.0/2.0

        s := repeatAmt / tileRect getWidth
        t := repeatAmt / tileRect getHeight

        splitBackFromSky := MeshTools createHillMesh(surface, tileRect, skyCutZ-tolerance, pathMinZ+tolerance)

        meshMan makePlanarTextureMapping(
            splitBackFromSky getMeshBuffer(0),    // buffer
            s,  // resolutionS
            t,  // resolutionT
            2,  // axis
            vector3df tmp(0, 0, 0)  // offset
        )

        backStyle := tileStyle clone setTexture("Media/mountaintop.jpg") setMesh(splitBackFromSky) setPhysShape("none")
        setBackGameObj(graph addNode(backStyle))
        backGameObj addAttribute(self)

        splitFront := MeshTools createHillMesh(surface, tileRect, pathMaxZ-tolerance, 1000000)

        meshMan makePlanarTextureMapping(
            splitFront getMeshBuffer(0),    // buffer
            s,  // resolutionS
            t,  // resolutionT
            2,  // axis
            vector3df tmp(0, 0, 0)  // offset
        )

        foreStyle := tileStyle clone setTexture("Media/irrlicht2_dn.jpg") setMesh(splitFront) setPhysShape("none")
        setForeGameObj(graph addNode(foreStyle))
        foreGameObj addAttribute(self)

        return self
    )

    return Tile
)
