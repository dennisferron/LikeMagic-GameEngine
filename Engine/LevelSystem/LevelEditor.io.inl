method(namespace_Bullet, namespace_irr, namespace_Custom, Structure, Styles,

    LevelEditor := Structure clone lexicalDo(

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_irr custom)
        appendProto(namespace_Custom)
        appendProto(namespace_Bullet)

        SColor := namespace_irr video SColor

        engine ::= nil
        driver ::= nil
        gui ::= nil
        cursor ::= nil
        terrain ::= nil
        collMan ::= nil
        toolBar ::= nil

        inOutButton ::= nil
        zEquation ::= nil
        radiusKnob ::= nil

        hitTriangle ::= nil
        selectedSceneNode ::= nil
        collisionPoint ::= nil
    )

    LevelEditor create := method(engine,
        setEngine(engine)

        setGui(engine gui)
        setTerrain(engine terrain)
        setCollMan(engine collMan)
        setCursor(engine device getCursorControl)
        setDriver(engine driver)

        setToolBar(gui addToolBar(nil, 111))
        toolBar setMinSize(dimension2du tmp(1, 42))
        outImage := loadTexture("Media/button-push-out.png")
        inImage :=  loadTexture("Media/button-push-in.png")
        setInOutButton(toolBar addButton(112, "", "push in/out", outImage, inImage, true, true))
        gui addStaticText("Z(X,Y)=", recti tmpWithXYXY(50, 10, 80, 20), false, false, toolBar, 112, true)
        setZEquation(gui addEditBox("2", recti tmpWithXYXY(85, 5, 250, 38), true, toolBar, 113))
        zEquation setMultiLine(true)
        gui addStaticText("radius=", recti tmpWithXYXY(260, 10, 290, 20), false, false, toolBar, 114, true)
        setRadiusKnob(gui addSpinBox("1.0", recti tmpWithXYXY(300, 2, 350, 38), true, toolBar, 115))
        radiusKnob setDecimalPlaces(1)
        radiusKnob setStepSize(0.1)
        radiusKnob setRange(0.1, 1000)

        setHitTriangle(triangle3df tmp)
        setCollisionPoint(vector3df tmp(1, 2, 3))
    )

    LevelEditor loadTexture := method(fileName,
        fsStr := irrFsStr newFromCStr(WayUpDir(fileName))
        result := driver getTexture(fsStr)
        fsStr delete
        return result
    )

    LevelEditor drawCursor := method(
        mousePos := cursor getPosition

        highlightTile(mousePos)

        //driver draw3DBox(aabbox3df newWithMinMaxXYZ(x-1, y-1, -1, x+1, y+1, 1), color)

        selectTriangle(mousePos get_X, mousePos get_Y)
        driver draw3DTriangle(hitTriangle, SColor tmp(0,255,0,0))
    )

    LevelEditor highlightTile := method(mousePos,
        ray := collMan getRayFromScreenCoordinates(mousePos, nil) // engine camera node)
        plane := plane3df newFromPointAndNormal(vector3df tmp, vector3df tmp(0, 0, -1))
        intersection := vector3df tmp
        plane getIntersectionWithLine(ray get_start, ray getVector, intersection)

        x := intersection get_X
        y := intersection get_Y

        /*
        color := SColor tmp(10, 255, 0, 0)

        // Draw horizontal cross-hair at y position
        driver draw3DLine(vector3df tmp(x-20, y, 0), vector3df tmp(x+20, y, 0), color)

        // Draw vertical cross-hair at x position
        driver draw3DLine(vector3df tmp(x, y-20, 0), vector3df tmp(x, y+20, 0), color)
        */

        terrain highlight(x, y)
    )

    LevelEditor getTile := method(mousePos,
        ray := collMan getRayFromScreenCoordinates(mousePos, nil) // engine camera node)
        plane := plane3df newFromPointAndNormal(vector3df tmp, vector3df tmp(0, 0, -1))
        intersection := vector3df tmp
        plane getIntersectionWithLine(ray get_start, ray getVector, intersection)

        x := intersection get_X
        y := intersection get_Y

        return terrain getTile(x, y)
    )

    LevelEditor selectTriangle := method(X, Y,

        // This has been promoted to an object level slot so it can be displayed each frame.
        //hitTriangle := triangle3df tmp

        ray := collMan getRayFromScreenCoordinates(vector2di tmp(X, Y), nil) //engine camera node)

        selectedSceneNode = collMan getSceneNodeAndCollisionPointFromRay(
            ray,
            collisionPoint, // This will be the position of the collision
            hitTriangle,    // This will be the triangle hit in the collision
            0,              // Pickable flag (0 means ignore the flag)
            nil,            // root node
            false           // False means don't exclude debug objects
        )
    )

    LevelEditor handleMouse := method(X, Y, button,

        if (button == EMIE_LMOUSE_PRESSED_DOWN,
            pushIn := inOutButton isPressed
            ray := collMan getRayFromScreenCoordinates(vector2di tmp(X, Y), nil) // engine camera node)
            plane := plane3df newFromPointAndNormal(vector3df tmp, vector3df tmp(0, 0, -1))
            intersection := vector3df tmp
            plane getIntersectionWithLine(ray get_start, ray getVector, intersection)
            x := intersection get_X
            y := intersection get_Y
            z := if(pushIn, -10, 10)
            radius := radiusKnob getValue
            throwStyle := BallStyle clone setGravity(0) setPos(x,y,z) setVel(0, 0, 1.5 * -z) setMass(3*radius) setRadius(radius)
            thrownObj := engine addObj(throwStyle)
            engine time setTimeout(1200, block(engine removeObj(thrownObj); 0))
        )
    )

    LevelEditor selectNode := method(X, Y,

        selectedSceneNode := nil
        collisionPoint := vector3df tmp(1, 2, 3)
        hitTriangle := triangle3df tmp

        selectedSceneNode = collMan getSceneNodeFromScreenCoordinatesBB(
            vector2di tmp(X, Y),  // pos
            0,                    // idBitMask
            false,                // bNoDebugObjects=false
            nil                   // root
        )

        writeln(selectedSceneNode)

        if (selectedSceneNode != nil,
            pos := selectedSceneNode getPosition
            writeln("scene node pos = (", pos get_X, ", ", pos get_Y, ", ", pos get_Z, ")")

            writeln("node id = ", selectedSceneNode getID)
            writeln("node to game obj: ", nodeToGameObj(selectedSceneNode))
        ,
            writeln("No scene node")
        )
    )

    return LevelEditor
)
