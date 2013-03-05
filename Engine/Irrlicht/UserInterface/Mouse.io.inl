
// TODO:  Add MouseDragLink attribute and possibly convert ConstraintStyles to LinkStyles or Styles.
method(namespace_Bullet, namespace_irr, namespace_Custom, PredefinedValues, Constants, ConstraintStyles,

    Mouse := Object clone lexicalDo(

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_irr custom)
        appendProto(namespace_Custom)
        appendProto(namespace_Bullet)
        appendProto(PredefinedValues)
        appendProto(Constants)

        ConstraintStyles := ConstraintStyles

        Constants := Constants

        graph ::= nil
        irrComp ::= nil
        gui ::= nil

        // Why do I need this?
        //cursor ::= nil

        collMan ::= nil
        hitTriangle ::= nil
        selectedSceneNode ::= nil
        collisionPoint ::= nil
        driver ::= nil

        draggingObj ::= nil
        mouseDragLink ::= nil
        wasDragging ::= false
        mouseX ::= nil
        mouseY ::= nil

        codeInputBoxes ::= nil
    )


    Mouse init := method(

        setCodeInputBoxes(list())
        setHitTriangle(triangle3df ref)
        setCollisionPoint(vector3df ref(1, 2, 3))
    )

    Mouse handle := method(event,

        mouseInput := event get_MouseInput
        if (mouseInput get_Event == EMIE_LMOUSE_PRESSED_DOWN or mouseInput get_Event == EMIE_RMOUSE_PRESSED_DOWN or mouseInput get_Event == EMIE_MOUSE_MOVED,
            mouseX = mouseInput get_X
            mouseY = mouseInput get_Y
            dragging(mouseX, mouseY, mouseInput)


            if(mouseInput get_Event == EMIE_RMOUSE_PRESSED_DOWN,
                codeInputBox := (gui addEditBox(
                    "",                     // text in box
                    recti tmpWithXYXY(
                        mouseX,                 // X1
                        mouseY,                 // Y1
                        mouseX+200,             // X2
                        mouseY+200              // Y2
                    ),                      // Rectangle
                    true,                   // show border
                    nil,                    // parent
                    333                     // ID
                ))
                codeInputBox setMultiLine(true)
                codeInputBox setWordWrap(false)
                codeInputBox setTextAlignment(
                    EGUIA_UPPERLEFT, // horizontal
                    EGUIA_UPPERLEFT  // vertical
                )
                codeInputBoxes append(codeInputBox)
            )

            return false
        )
    )

/*
    Mouse drawCursor := method(
        mousePos := cursor getPosition

        highlightTile(mousePos)

        //driver draw3DBox(aabbox3df newWithMinMaxXYZ(x-1, y-1, -1, x+1, y+1, 1), color)

        selectTriangle(mousePos get_X, mousePos get_Y)
        driver draw3DTriangle(hitTriangle, SColor tmp(0,255,0,0))
    )
*/

    Mouse highlightTile := method(mousePos,
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

    Mouse getTile := method(mousePos,
        ray := collMan getRayFromScreenCoordinates(mousePos, nil) // engine camera node)
        plane := plane3df newFromPointAndNormal(vector3df tmp, vector3df tmp(0, 0, -1))
        intersection := vector3df tmp
        plane getIntersectionWithLine(ray get_start, ray getVector, intersection)

        x := intersection get_X
        y := intersection get_Y

        return terrain getTile(x, y)
    )

    Mouse selectTriangle := method(X, Y,

        // This has been promoted to an object level slot so it can be displayed each frame.
        //hitTriangle := triangle3df ref

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

    Mouse handleMouse := method(X, Y, button,

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

    Mouse getPlaneIntersection := method(X, Y,
        mousePos := vector2di tmp(X, Y)
        ray := collMan getRayFromScreenCoordinates(mousePos, nil) // engine camera node)
        plane := plane3df newFromPointAndNormal(vector3df tmp, vector3df tmp(0, 0, -1))
        intersection := vector3df tmp
        plane getIntersectionWithLine(ray get_start, ray getVector, intersection)
        return intersection
    )


    Mouse dragging := method(X, Y, mouseInput,

        // Begin drag
        if( wasDragging not and mouseInput isLeftPressed,
            setWasDragging(true)
            setDraggingObj(selectNode(X, Y))
            if( draggingObj != nil ,
                style := LinkStyles MouseDragStyle clone
                setMouseDragLink(graph addLink(style, nil, draggingObj))
            ,
                if (mouseDragLink != nil,
                    graph removeLink(mouseDragLink)
                    setMouseDragLink(nil)
                )
            )
        )

        if (wasDragging,
            dragToScreenPos(X, Y)
        )

        // Cancel drag
        if( mouseInput isLeftPressed not,
            setWasDragging(false)
            setDraggingObj(nil)
            if (mouseDragLink != nil,
                graph removeLink(mouseDragLink)
                setMouseDragLink(nil)
            )
        )
    )

    Mouse dragToScreenPos := method(X, Y,
        // Move dragged obj
        obj := draggingObj
        if( (obj != nil) and (mouseDragLink != nil) ,
            pos := getPlaneIntersection(X, Y)
            attr := mouseDragLink findAttribute(MouseDragLinkAttribute)
            attr onDrag ?call(pos)
        )
    )

    Mouse selectNode := method(X, Y,

        writeln("Mouse selectNode self is ", self)

        selectedSceneNode := nil
        collisionPoint := vector3df ref(1, 2, 3)
        hitTriangle := triangle3df ref
        idBitMask := Constants mouseDraggableBitMask

        selectedSceneNode = collMan getSceneNodeFromScreenCoordinatesBB(
            vector2di tmp(X, Y),  // pos
            idBitMask,            // idBitMask
            true,                // bNoDebugObjects=false
            nil                   // root
        )

        if( selectedSceneNode != nil,
            writeln("selectedSceneNode = ", selectedSceneNode)
            pos := selectedSceneNode getPosition
            writeln("scene node pos = (", pos get_X, ", ", pos get_Y, ", ", pos get_Z, ")")
            writeln("node id = ", selectedSceneNode getID)

            // TODO: Why is nodeToGameObj STILL nil?
            gameObj := irrComp nodeToGameObj(selectedSceneNode)
            writeln("gameObj = ", gameObj)
            return gameObj
        ,
            writeln("No scene node")
            return nil
        )
    )

    return Mouse
)
