method(namespace_irr, namespace_Custom, namespace_TPS, Tile, Styles, ScriptUtil,

    Terrain := Object clone lexicalDo(
        appendProto(namespace_irr video)
        appendProto(namespace_irr core)
        appendProto(namespace_TPS)
        appendProto(namespace_Custom)

        ScriptUtil := ScriptUtil
        Styles := Styles GameObjStyles

        Tile := Tile

        graph ::= nil
        assets ::= nil
        meshMan ::= nil

        levelRect ::= nil
        tileDimensions ::= nil

        tileArray ::= nil
        numTilesX ::= 0
        numTilesY ::= 0

        tps ::= nil
        surface ::= nil

        initialSplit ::= 4

        pathMinZ ::= -2.0
        pathMaxZ ::= 2.0
        skyCutZ ::= -9.0

        minFitSizeLen ::= 0.5 + 0.01

        minFitSize ::= dimension2df tmp(minFitSizeLen, minFitSizeLen)
    )

    Terrain init := method(
        worldSizeX := 64
        worldSizeY := 64
        setLevelRect(
            rectf tmpPosSize(
                vector2df tmp(-worldSizeX/2, -worldSizeY/2),
                dimension2df tmp(worldSizeX, worldSizeY)
            )
        )
        setNumTilesX(4)
        setNumTilesY(4)

        setTileDimensions(dimension2df tmp(
            levelRect getWidth / numTilesX, levelRect getHeight / numTilesY))
    )

    Terrain load := method(

        setTileArray(list())
        tileArray setSize(numTilesX * numTilesY)

        // The num tiles in meshes and the surface need not be identical.
        surfaceCols := numTilesX
        surfaceRows := numTilesY
        surfaceMin := Vec tmp(levelRect get_UpperLeftCorner get_X, 0, levelRect get_UpperLeftCorner get_Y)
        surfaceMax := Vec tmp(levelRect get_LowerRightCorner get_X, 0, levelRect get_LowerRightCorner get_Y)

        setTps(
            ThinPlateQuilt tmp(surfaceCols, surfaceRows, surfaceMin, surfaceMax)
        )

        controlPointStyle := Styles BallStyle clone setPhysShape("none") setSize(0.5) setIsMouseDraggable(true)

        100 repeat(
            cpx := ScriptUtil get_random_float(
                    levelRect get_UpperLeftCorner get_X, levelRect get_LowerRightCorner get_X)
            cpy := ScriptUtil get_random_float(
                    levelRect get_UpperLeftCorner get_Y, levelRect get_LowerRightCorner get_Y)

            h := ScriptUtil get_random_float(-11.0, 5.0)

            tps addControlPoint(
                Vec tmp(cpx, h, cpy)
            )

            graph addNode(controlPointStyle clone setPos(cpx, cpy, h))
        )
        tps refresh

        setSurface(
            SurfaceQuadTree tmp(levelRect, tps, "Root")
        )

        // Initial grid placement
        surface split(initialSplit)

        // Split the grid to fit the path more closely
        surface fit(minFitSize, list(skyCutZ, pathMinZ, pathMaxZ))

        numTilesX repeat(x,
            //writeln("Loading terrain tile column ", x, " of ", numTilesX)
            numTilesY repeat(y,
                offset := 0.1 // this ensures right/bottom tile boundaries are triangulated.
                tilePos := vector2df tmp(x * tileDimensions get_Width + levelRect get_UpperLeftCorner get_X + offset,
                                         y * tileDimensions get_Height + levelRect get_UpperLeftCorner get_Y + offset)
                tileRect := rectf tmpPosSize(tilePos, tileDimensions)
                tileArray atPut(tileIndex(x,y),
                    Tile clone  setGraph(graph) setMeshMan(meshMan) setTileRect(tileRect) setSurface(surface) setPathMinZ(pathMinZ) setPathMaxZ(pathMaxZ) setSkyCutZ(skyCutZ) refresh
                )
            )
        )
    )

    Terrain tileIndex := method(x, y,

        if( x >= numTilesX,
            Exception raise("x out of bounds")
        )

        if( y >= numTilesY,
            Exception raise("y out of bounds")
        )

        result := return y*numTilesX + x

        if( result >= tileArray size,
            Exception raise("index out of bounds. index=" .. result asString .. " array size=" .. tileArray size asString .. " x=" .. x asString .. " y=" .. y asString)
        )

        return result
    )

    return Terrain
)
