method(namespace_irr, Constants,

Camera := Object clone lexicalDo(

    appendProto(namespace_irr)
    appendProto(namespace_irr core)
    appendProto(Constants)

    SColor := namespace_irr video SColor

	boxX := 0
	boxY := 0

	boxXSize := 7
	boxYSize := 7

	cameraNode ::= nil
	targetIrrAttrib ::= nil

    smgr ::= nil
    driver ::= nil

    distZ ::= 20
)

Camera createNode := method(

	cameraNode = smgr addCameraSceneNode(
		nil, // parent
		vector3df tmpWithXYZ(0, 0, distZ), // position
		vector3df tmpWithXYZ(0, -10, 0), // lookat
		-1, // id
		true  // makeActive
	)

    cameraNode setFOV(0.1*TAU)

    /*
	mayaCameraNode := smgr addCameraSceneNodeMaya(
        nil,    // parent
      -1000.0, // rotate speed
        200.0, // zoom speed
        150.0, // translation speed
        -1, // id
        false // makeActive
	)

	mayaCameraNode setPosition(vector3df tmp(0, 0, -350))
	*/

    self
)

Camera update := method(

    if (targetIrrAttrib != nil,

        target := targetIrrAttrib sceneNode getAbsolutePosition

        tx := target get_X
        ty := target get_Y

        if (tx < boxX - boxXSize/2, boxX = tx + boxXSize/2)
        if (ty < boxY - boxYSize/2, boxY = ty + boxYSize/2)
        if (tx > boxX + boxXSize/2, boxX = tx - boxXSize/2)
        if (ty > boxY + boxYSize/2, boxY = ty - boxYSize/2)

        cameraNode setPosition(vector3df tmp(boxX, boxY+5, distZ))
        cameraNode setTarget(vector3df tmp(boxX, boxY, 0))

        draw
    )
)

Camera draw := method(
	driver draw3DLine(
		vector3df tmp(boxX - boxXSize/2, boxY - boxYSize/2, 0),
		vector3df tmp(boxX - boxXSize/2, boxY + boxYSize/2, 0),
		SColor tmpWithARGB(255, 255, 255, 255)
	)

	driver draw3DLine(
		vector3df tmp(boxX + boxXSize/2, boxY - boxYSize/2, 0),
		vector3df tmp(boxX + boxXSize/2, boxY + boxYSize/2, 0),
		SColor tmpWithARGB(255, 255, 255, 255)
	)

	driver draw3DLine(
		vector3df tmp(boxX - boxXSize/2, boxY - boxYSize/2, 0),
		vector3df tmp(boxX + boxXSize/2, boxY - boxYSize/2, 0),
		SColor tmpWithARGB(255, 255, 255, 255)
	)

	driver draw3DLine(
		vector3df tmp(boxX - boxXSize/2, boxY + boxYSize/2, 0),
		vector3df tmp(boxX + boxXSize/2, boxY + boxYSize/2, 0),
		SColor tmpWithARGB(255, 255, 255, 255)
	)
)

return Camera

)
