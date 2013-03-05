method(namespace_Bullet, namespace_irr, namespace_Custom, Structure, Styles,

    Props := Object clone lexicalDo(

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_Bullet)
        appendProto(namespace_Custom)

        Styles := Styles GameObjStyles

        graph ::= nil
    )

    Props makeStage := method(

        graph addNode(WallStyle clone setPos(-50, -40, 0))
        graph addNode(WallStyle clone setPos( 50, -40, 0) setFriction(0.07))
        graph addNode(BoxStyle clone setPos(0, -5.01, 0) setSize(100, 10, 20) setMass(0) setTexture("Media/testpattern.png"))

    )

    Props makeTree := method(

        base := ConeStyle clone do(
            setPos(0, 0.5, 0)
            setLength(1.1)
            setRadius(1)
            setPitch(0)

            // Don't allow the base to tip or twist
            setAngularFactor(0,0,0)

            // Don't allow base to move except to fall to the ground
            //setLinearFactor(0,1,0)
            setLinearFactor(1,1,0)

            setAlternateTextureWrap(true)
            setTexture("Media/palmbark.png")
        )

        joint := Generic6DOFStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(0, 0.3, 0)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0, -0.3, 0)
                )
            )

            setDisableLinkedBodyCollisions(true)
            setLinRange(0, 0, 0, 0, 0, 0)
            setAngRange(0, 0, 0, 0, 0, 0)
        )

        trunk := CylStyle clone do(
            setLength(0.8)
            setRadius(0.4)
            setTexture("Media/palmbark.png")
        )

        top := CylStyle clone do(
            setRadius(2.5)
            setLength(0.4)
            setColor(0, 255, 0)
            setTexture("Media/palmtop.png")
            setAlternateTextureWrap(true)
        )

        treeStructure := Structure build(
            base
            joint
            trunk setPos(0, 1.0, 0)
            joint
            trunk setPos(0, 1.5, 0)
            joint
            trunk setPos(0, 2.0, 0)
            joint
            trunk setPos(0, 2.5, 0)
            joint
            trunk setPos(0, 3.0, 0)
            joint
            trunk setPos(0, 3.5, 0)
            joint
            trunk setPos(0, 4.0, 0)
            joint
            top setPos(0, 4.5, 0)
        )

        tree := graph addStructure(treeStructure)

        // TODO:  Replace the line above with the code below
        // when I'm finished with changes to style/structure mechanics.
        //tree := GameObject clone with(treeStructure)
        //graph addGameObject(tree)

        return tree
    )

    Props makeSnake := method(
        segmentStyle := CylXStyle clone do(
            setLength(1)
            setRadius(0.5)
            setMass(0.1)
            setGravity(0, -3, 0)
        )

        jointStyle := HingeStyle clone do(
            setDisableLinkedBodyCollisions(true)
            setAngRange(-TAU/8, TAU/8)
            mountA do(
                setPos(0.5, 0, 0)
            )
            mountB do(
                setPos(-0.5, 0, 0)
            )
        )

        leftJointStyle := jointStyle clone do(
            setDisableLinkedBodyCollisions(true)
            setAngRange(-TAU/32, 0)
        )

        rightJointStyle := jointStyle clone do(
            setDisableLinkedBodyCollisions(true)
            setAngRange(0, TAU/2+TAU/32)
        )

        headStyle := BallStyle clone do(
            setPos(0, 0, -1)
            setGravity(0, -3, 0)
        )

        noseHeadJoint := Point2PointStyle clone do(
            setDisableLinkedBodyCollisions(true)
            mountB setPos(0, 0.1, -1)
        )

        noseStyle := BallStyle clone do(
            setRadius(0.5)
            setMass(0.1)
            setGravity(0, -3, 0)
        )

        writeln("snake jointStyle: ", jointStyle)

        snakeStructure := Structure build(
            noseStyle (
                noseHeadJoint headStyle
            ,
                leftJointStyle do( mountA setPos(-0.4, -0.4, 0); mountB setPos(1.00/2, 0.1, 0) )
                    segmentStyle setPos(-0.5, -0.3, 0) setRadius(0.5) setLength(1.00)
                jointStyle do( mountA setPos(-1.00/2, 0.1, 0); mountB setPos(0.75/2, 0, 0) )
                    segmentStyle setPos(-1.5, -0.3, 0) setRadius(0.4) setLength(0.75)
                jointStyle do( mountA setPos(-0.75/2, 0, 0); mountB setPos(0.50/2, 0, 0) )
                    segmentStyle setPos(-2.5, -0.3, 0) setRadius(0.3) setLength(0.50)
                jointStyle do( mountA setPos(-0.5/2, 0, 0); mountB setPos(0.40/2, 0, 0) )
                    segmentStyle setPos(-3.5, -0.3, 0) setRadius(0.2) setLength(0.40)
            ,
                rightJointStyle do( mountA setPos(0.4, -0.4, 0); mountB setPos(-1.00/2, 0.1, 0) )
                    segmentStyle setPos( 0.5, -0.3, 0) setRadius(0.5) setLength(1.00)
                jointStyle do( mountA setPos(1.00/2, 0.1, 0); mountB setPos(-0.75/2, 0, 0) )
                    segmentStyle setPos( 1.5, -0.3, 0) setRadius(0.4) setLength(0.75)
                jointStyle do( mountA setPos(0.75/2, 0, 0); mountB setPos(-0.50/2, 0, 0) )
                    segmentStyle setPos( 2.5, -0.3, 0) setRadius(0.3) setLength(0.50)
                jointStyle do( mountA setPos(0.5/2, 0, 0); mountB setPos(-0.40/2, 0, 0) )
                    segmentStyle setPos( 3.5, -0.3, 0) setRadius(0.2) setLength(0.40)
            )
        )

        snakeStructure move(-2, 3, 0)

        nose := graph addStructure(snakeStructure)
        nose rigidBody setLinearFactor(btVector3 tmp(1,1,0))
        nose rigidBody setAngularFactor(btVector3 tmp(0,0,1))

        head := nose constraintsA at(0) objB
        head rigidBody setAngularFactor(btVector3 tmp(0,0,0))

        leftStache := nose constraintsA at(1) objB
        rightStache := nose constraintsA at(2) objB

        leftStache rigidBody setLinearFactor(btVector3 tmp(1,1,0))
        leftStache rigidBody setAngularFactor(btVector3 tmp(0,0,1))
        rightStache rigidBody setLinearFactor(btVector3 tmp(1,1,0))
        rightStache rigidBody setAngularFactor(btVector3 tmp(0,0,1))

        leftRound := graph addNode(BallStyle clone do(setIsKinematic(true) setPhysShape(none) setPos(0, 0, 0) setRadius(0.5)))
        leftStache addChild(leftRound)

        rightRound := graph addNode(BallStyle clone do(setIsKinematic(true) setPhysShape(none) setPos(0, 1.0, 0) setRadius(0.5)))
        rightStache addChild(rightRound)

        graph addConstraint(DisableCollisionStyle, head, leftStache)
        graph addConstraint(DisableCollisionStyle, head, rightStache)
        graph addConstraint(DisableCollisionStyle, leftStache, rightStache)

        setMotors := method(segment, count,
            if (segment constraintsA size > 0,
                constraint := segment constraintsA at(0) constraint
                v := 10
                graph time setTimeout(500, block(v = -v; constraint enableAngularMotor(true, v, 5); 100+100*count))
                setMotors(segment constraintsA at(0) objB, count + 1)
            )
        )

        setMotors(leftStache, 0)
        setMotors(rightStache, 0)

        /*
            block
            (
                //v = -v
                //constraint enableAngularMotor(true, v, 5)
                500
            )
        )
        */

        /*
        motor := constraint getRotationalLimitMotor(0)
        motor set_m_enableMotor(true)
        motor set_m_loLimit(0)
        motor set_m_hiLimit(0)
        motor set_m_maxMotorForce(5)
        motor set_m_maxLimitForce(5)
        motor set_m_targetVelocity(1)
        */

    )

    Props makeRobot := method(

        shoulderBall := BallStyle clone do(
            setRadius(0.75)
            setPos(9, 2, 0)
        )

        shoulderToUpperArm := Generic6DOFStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(0.6,0,0)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0,0,0)
                )
            )

            setDisableLinkedBodyCollisions(true)
            setLinRange(0, 0, 0, 0, 0, 0)
            setAngRange(0, 0, 0, 0, 0, 0)

        )

        upperArm := CylXStyle clone do(
            setLength(1.2)
            setRadius(0.4)
            setPos(7, 2, 0)
        )

        upperArmToElbow := Point2PointStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(0.9,0,0)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0,0,0)
                )
            )

            setDisableLinkedBodyCollisions(true)
        )

        elbowBall := BallStyle clone do(
            setPos(4.5, 2, 0)
            setRadius(0.56)
            setFriction(0.3)
        )

        elbowToForeArm := Generic6DOFStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(0.9,0,0)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0,0,0)
                )
            )

            setDisableLinkedBodyCollisions(true)
            setLinRange(0, 0, 0, 0, 0, 0)
            setAngRange(0, 0, 0, 0, 0, 0)

        )

        foreArm := ConeXStyle clone do(
            setPos(3, 2, 0)
            setLength(1.2)
            setRadius(0.5)
            setFriction(0.3)
        )

        torso := ConeStyle clone do(
            setPos(0, 5, 0)
            setLength(2)
            setRadius(0.8)
            setPitch(TAU/2)
            setTexture("Media/security.png")

            // Alternate texture wrap for cone, relying on knowledge center top and center bottom nodes are added last,
            // and first N-2 vertices are around the bottom of the cone in order with equal spacing.
            setOnTextureWrap(block(mesh,
                buf := mesh getMeshBuffer(0)

                tesselation := buf getVertexCount - 2
                xStep := 1.0 / tesselation

                for(i, 0, tesselation - 1,
                    tCoords := buf getTCoords_nc(i)
                    tCoords set_X(i*xStep)
                    tCoords set_Y(0.0)
                )

                atTip := buf getVertexCount - 2
                atBase := buf getVertexCount - 1

                buf getTCoords_nc(atTip)  do( set_X(0.0); set_Y(1.0) )
                buf getTCoords_nc(atBase) do( set_X(0.0); set_Y(1.0) )

                buf setDirty(EBT_VERTEX)
            ))
        )

        torsoToLeftShoulder := Point2PointStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(1.2, -1, 0)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0,0,0)
                )
            )

            setDisableLinkedBodyCollisions(true)
        )

        torsoToRightShoulder := Point2PointStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(-1.2, -1, 0)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0,0,0)
                )
            )

            setDisableLinkedBodyCollisions(true)
        )

        torsoToBase := HingeStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(0,0.5,0)
                    setPitch(TAU/4)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0,0,0)
                    setPitch(-TAU/4)
                )
            )

            setDisableLinkedBodyCollisions(true)
            //setLinRange(0, 0, 0, 0, 0, 0)
            //setAngRange(0, 0, 1, 0, 0, 0)

            setAngRange(1, 0)

        )

        base := CylStyle clone do(
            setPos(0,5,0)
            setRadius(0.4)
            setLength(0.8)
            // Don't allow the base to tip sideways or rotate
            setAngularFactor(0,0,1)
            //setAngularFactor(0,0,0)
            setLinearFactor(1,1,0)
            setMass(2)
        )

        head := BallStyle clone do(
            setCollisionGroup(0)
            setCollisionMask(0)
            setRadius(0.75)
            setPos(0,0,0.5)
        )

        headToTorso := Generic6DOFStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(0,1.1,0)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0,0,0)
                )
            )

            setDisableLinkedBodyCollisions(true)
            setLinRange(0, 0, 0, 0, 0, 0)
            setAngRange(0, 0, 0, 0, 0, 0)

        )

        leftAxle := HingeStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(0,0,0.6)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0,0,0)
                )
            )

            setDisableLinkedBodyCollisions(true)
            //setLinRange(0, 0, 0, 0, 0, 0)
            //setAngRange(0, 0, 0, 0, 1, 0)

            setAngRange(1, 0)
        )

        rightAxle := HingeStyle clone do(
            setMountA(
                MountStyle clone do(
                    setPos(0,0,-0.6)
                )
            )

            setMountB(
                MountStyle clone do(
                    setPos(0,0,0)
                )
            )

            setDisableLinkedBodyCollisions(true)
            //setLinRange(0, 0, 0, 0, 0, 0)
            //setAngRange(0, 0, 0, 0, 1, 0)

            setAngRange(1, 0)
        )

        leftWheel := CylZStyle clone do(
            setRadius(0.65)
            setLength(0.25)
            setPos(0, 5, 0.6)
            setTexture("Media/bronze-ratchet-gear.png")
            setAlternateTextureWrap(true)
            setMass(2)
            setFriction(3)
        )

        rightWheel := CylZStyle clone do(
            setRadius(0.65)
            setLength(0.25)
            setPos(0, 5, -0.6)
            setTexture("Media/bronze-ratchet-gear.png")
            setAlternateTextureWrap(true)
            setMass(2)
            setFriction(3)
        )

        robotStructure := Structure build(
            head headToTorso torso(
                torsoToLeftShoulder shoulderBall shoulderToUpperArm upperArm upperArmToElbow elbowBall elbowToForeArm foreArm
            ,
                torsoToRightShoulder shoulderBall shoulderToUpperArm upperArm upperArmToElbow elbowBall elbowToForeArm foreArm
            ) torsoToBase base(leftAxle leftWheel, rightAxle rightWheel)
        )

        robot := graph addStructure(robotStructure)

        torsoObj := robot constraintsA at(0) objB

        shoulderObj1 := torsoObj constraintsA at(0) objB
        shoulderObj2 := torsoObj constraintsA at(1) objB

        upperArmObj1 := shoulderObj1 constraintsA at(0) objB
        upperArmObj2 := shoulderObj2 constraintsA at(0) objB

        elbowObj1 := upperArmObj1 constraintsA at(0) objB
        elbowObj2 := upperArmObj2 constraintsA at(0) objB

        foreArmObj1 := elbowObj1 constraintsA at(0) objB
        foreArmObj2 := elbowObj2 constraintsA at(0) objB

        baseObj := torsoObj constraintsA at(2) objB
        writeln("baseObj is ", baseObj)

        constraint1 := baseObj constraintsA at(0) constraint
        constraint2 := baseObj constraintsA at(1) constraint

        foreArmObj1 setSteering(Steering clone setGameObj(foreArmObj1))
        foreArmObj1 steering setPursuitTarget(graph player steering)

        // Do this before adding the obstacle object because addObstacleGameObj creates a steering obj.
        foreArmObj2 setSteering(Steering clone setGameObj(foreArmObj2))
        foreArmObj2 steering setPursuitTarget(graph player steering)

        foreArmObj1 steering addObstacleGameObj(baseObj)
        foreArmObj1 steering addObstacleGameObj(torsoObj)
        foreArmObj1 steering addObstacleGameObj(foreArmObj2)
        foreArmObj1 steering addObstacleGameObj(robot)

        foreArmObj2 steering addObstacleGameObj(baseObj)
        foreArmObj2 steering addObstacleGameObj(torsoObj)
        foreArmObj2 steering addObstacleGameObj(foreArmObj1)
        foreArmObj2 steering addObstacleGameObj(robot)


        graph time setTimeout(2000,
            block(
                angle := baseObj getRotZ

                vel := -angle * 30
                torque := (50 * angle) abs

                constraint1 enableAngularMotor(true, vel, torque)
                constraint2 enableAngularMotor(true, vel, torque)

                foreArmObj1 steering update(100)
                foreArmObj2 steering update(100)

                return 100
            )
        )

    /*
        state := true

        graph time setTimeout(2100,
            block(
                state = state not
                foreArmObj1 steering setBehaviorFlag(EBF_PURSUIT, state)
                foreArmObj2 steering setBehaviorFlag(EBF_PURSUIT, state not)
                return 3000
            )
        )
    */

        return robot
    )



    Props makeCannon := method(

        hub := BallStyle clone do(
            setPos(0, -15, 0)
            setIsKinematic(true)
            setRadius(0.5)
        )

        barrel := CylStyle clone do(
            setIsKinematic(true)
            setLength(2.5)
            setRadius(0.4)
        )

        tip := GeneratorStyle clone do(
            setPos(0, 2.5, 0)
            setSpawnStyle(
                BallStyle clone do(
                    setRadius(0.5)
                    setVel(0, 20, 0)
                    setMass(20)
                )
            )
        )


        CannonStructure := Structure build(
            hub(
                barrel setPos(   1, 0,  0) tip,

                barrel setPos( 0.5, 0,  0.866) tip,

                barrel setPos(-0.5, 0,  0.866) tip,

                barrel setPos(  -1, 0,  0) tip,

                barrel setPos( 0.5, 0, -0.866) tip,

                barrel setPos(-0.5, 0, -0.866) tip
            )
        )

        cannon := graph addStructure(CannonStructure)
        rot := vector3df clone do(set(0, 0.4, 0))
        anim := graph smgr createRotationAnimator(rot)

        graph time setTimeout(1500,
            block(
                cannon triggerAllGenerators(
                    block(obj,
                        graph time setTimeout(2500,
                            block(
                                graph playSound(WayUpDir("Media/explosion.wav"))
                                obj dispose
                                0
                            )
                        )
                    )
                )
                1500
            )
        )
    )


    Props makeCar := method(

        leftWheel := CylZStyle clone do(
            setPos(2, -5, 0)
            setRadius(0.75)
            setLength(0.2)
            setFriction(5.0)
            setMass(1)
        )

        leftAxle := Point2PointStyle clone do(
            mountA setPos(-1, 0, 0)
            setDisableLinkedBodyCollisions(true)
        )


        rightWheel := CylZStyle clone do(
            setPos( 4, -5, 0)
            setRadius(0.5)
            setLength(0.2)
            setFriction(5.0)
            setMass(0.2)
        )

        rightAxle := Point2PointStyle clone do(
            mountA setPos(4, 0, 0)
            setDisableLinkedBodyCollisions(true)
        )

        carBody := BoxStyle clone do(
            setPos( 3, -5, 0)
            setSize(7, 0.50, 0.25)
            //setCollisionGroup(0)
        )

        gearAxle := Point2PointStyle clone do(
            mountA setPos(0, 1, 0)
            mountB setPos(0, 0, 0)
            setDisableLinkedBodyCollisions(true)
        )

        gearSlotStyle := BoxStyle clone do(
            setPos(0, 1, 0)
            setCollisionMask(0)
            setDispShape(none)
            setGravity(none)
            setCollisionResponseTag("gearSlot")
        )

        carStructure := Structure build(
            carBody	(
                leftAxle leftWheel,
                gearAxle gearSlotStyle,
                rightAxle rightWheel
            )
        )

        car := graph addStructure(carStructure)

        car rigidBody setLinearFactor(btVector3 tmp(1,1,0))
        car rigidBody setAngularFactor(btVector3 tmp(0,0,1))


        car constraintsA foreach(a,
            a objB rigidBody setLinearFactor(btVector3 tmp(1,1,0))
            a objB rigidBody setAngularFactor(btVector3 tmp(0,0,1))
        )

    )

    Props makeElevator := method(x, y,

        elevatorStyle := CylXStyle clone do(
            setIsKinematic(true)
            setPos(x, y, 0)
            setLength(6)
            setRadius(0.5)
            setFriction(1)
            //setCollisionGroup(0)
            setCollisionResponseTag("elevator")
            setTexture("Media/testpattern.png")

            //setRestitution(0)
            //setMargin(0.05)
        )

        elevator := graph addNode(elevatorStyle)

        elevator points := ArrayOfVector3df tmp  // const core::array< core::vector3df > &
        elevator points push_back(vector3df tmp(x-10, y-4, 0))
        elevator points push_back(vector3df tmp(x-5,  y+4, 0))
        elevator points push_back(vector3df tmp(  x,  y-4, 0))
        elevator points push_back(vector3df tmp(x+5,  y+4, 0))
        elevator points push_back(vector3df tmp(x+10, y-4, 0))


        anim := graph smgr createFollowSplineAnimator(
            startTime := graph time currentTime,
            elevator points,  // const core::array< core::vector3df > &
            speed := 0.75,
            tightness := 0.5,
            loop := true,
            pingpong := true
        )

        elevator addKinematicAnimator(anim)

        standOnElevator := Generic6DOFStyle clone do(
            mountA setPos(0, 0.5+0.5-0.1, 0)
            mountB setPos(0, 0, 0)
            setLinRange(-2.5,2.5,   0.1,0.1,   1,0)
            setAngRange(0,0,   0,0,   1,0)
        )

        //elevator standOnElevator := standOnElevator

        //graph addConstraint(standOnElevator, elevator, graph player)

        //graph player elevator := elevator
        //graph elevator := elevator

        /*
        graph time setTimeout(1.0/60,
            block(
                velE := elevator getLinearVelocity
                velP := graph player getLinearVelocity
                //graph player setLinearVelocity(velE + velP)
                1.0/60
            )
        )
        */
    )

    Props makeBox := method(
        box := graph addNode(BoxStyle clone do( setPos(-7, 0, 0) setMass(100) setSize(5, 3, 1) ))
        box rigidBody setLinearFactor(btVector3 tmp(1,1,0))
        box rigidBody setAngularFactor(btVector3 tmp(0,0,1))
    )

    Props makeDwarf := method(

        smgr := graph smgr

        //fsStr := irrFsStr newFromCStr(WayUpDir("Media/dwarf.x"))
        fsStr := irrFsStr newFromCStr(WayUpDir("Media/earth.x"))
        mesh := smgr getMeshFromPath(fsStr)
        fsStr delete

        /*

        anode := smgr addAnimatedMeshSceneNode(
            mesh,                   // IAnimatedMesh * mesh
            nil,                    // ISceneNode * 	parent = 0,
            -1,                     // s32 	id = -1,
            vector3df tmp(0, 0, 0), // const core::vector3df & 	position = core::vector3df(0, 0, 0),
            vector3df tmp(0, 0, 0), // const core::vector3df & 	rotation = core::vector3df(0, 0, 0),
            vector3df tmp(0.1f, 0.1f, 0.1f),    // const core::vector3df & 	scale = core::vector3df(1.0f, 1.0f, 1.0f),
            false // bool 	alsoAddIfMeshPointerZero = false
        )

        anode setPosition(vector3df tmp(0, 0, 0))

        */

        meshBuf := mesh getMeshBuffer(0)  // frame 0

        if (meshBuf getVertexType != EVT_STANDARD, Exception raise("The mesh's vertex data not in the standard format."))

        bulletMesh := btIndexedMesh tmp

        bulletMesh set_m_numTriangles(meshBuf getIndexCount / 3)

        triangleIndexBase := meshBuf getIndices_nc
        triangleIndexBaseCasted := triangleIndexBase unsafe_ptr_cast

        bulletMesh set_m_triangleIndexBase(triangleIndexBaseCasted)

        vertexBase := meshBuf getVertices_nc
        vertexBaseCasted := vertexBase unsafe_ptr_cast
        bulletMesh set_m_vertexBase(vertexBaseCasted)


        indexSize := 2 // 16 bits, 2 bytes
        bulletMesh set_m_triangleIndexStride(3 * indexSize)
        bulletMesh set_m_numVertices(meshBuf getVertexCount)
        bulletMesh set_m_vertexStride(S3DVertex get_class get_size)

        // This will be set when the bullet mesh buf is added to the triangle index vertex array object
        //bulletMesh set_m_indexType(PHY_SHORT)

        // This defaults to whatever bullet is built with (floats or doubles).  For Irrlicht I'm sure we want only floats.
        bulletMesh set_m_vertexType(PHY_FLOAT)

        // Cant' figure out how to set the indexType properly here, and a comment indicates this constructor is only for backwards compatibility.
        // Best to use the default constructor and addIndexedMesh where you can specify the index type.
        //meshInterface := btTriangleIndexVertexArray new(numTriangles, indices unsafe_ptr_cast, indexStride, numVertices, vertices unsafe_ptr_cast, vertexStride)

        meshInterface := btTriangleIndexVertexArray new()
        meshInterface addIndexedMesh(bulletMesh, PHY_SHORT)

        meshShape := btBvhTriangleMeshShape new(meshInterface, true, true)

        style := GameObjStyle clone
        style setScale(10) setMass(0) setPos(11, 6, 7)
        obj := GameObject create(style, graph, mesh, meshShape)
        graph objList append(obj)
    )


    Props loadL3DTMesh := method(

        smgr := graph smgr

        //fsStr := irrFsStr newFromCStr(WayUpDir("Media/dwarf.x"))
        fsStr := irrFsStr newFromCStr(WayUpDir("Media/L3DT.x"))
        mesh := smgr getMeshFromPath(fsStr)
        fsStr delete

        /*

        anode := smgr addAnimatedMeshSceneNode(
            mesh,                   // IAnimatedMesh * mesh
            nil,                    // ISceneNode * 	parent = 0,
            -1,                     // s32 	id = -1,
            vector3df tmp(0, 0, 0), // const core::vector3df & 	position = core::vector3df(0, 0, 0),
            vector3df tmp(0, 0, 0), // const core::vector3df & 	rotation = core::vector3df(0, 0, 0),
            vector3df tmp(0.1f, 0.1f, 0.1f),    // const core::vector3df & 	scale = core::vector3df(1.0f, 1.0f, 1.0f),
            false // bool 	alsoAddIfMeshPointerZero = false
        )

        anode setPosition(vector3df tmp(0, 0, 0))

        */

        /*

        meshBuf := mesh getMeshBuffer(0)  // frame 0

        if (meshBuf getVertexType != EVT_STANDARD, Exception raise("The mesh's vertex data not in the standard format."))

        bulletMesh := btIndexedMesh tmp

        bulletMesh set_m_numTriangles(meshBuf getIndexCount / 3)

        triangleIndexBase := meshBuf getIndices_nc
        triangleIndexBaseCasted := triangleIndexBase unsafe_ptr_cast

        bulletMesh set_m_triangleIndexBase(triangleIndexBaseCasted)

        vertexBase := meshBuf getVertices_nc
        vertexBaseCasted := vertexBase unsafe_ptr_cast
        bulletMesh set_m_vertexBase(vertexBaseCasted)

        indexSize := 2 // 16 bits, 2 bytes
        bulletMesh set_m_triangleIndexStride(3 * indexSize)
        bulletMesh set_m_numVertices(meshBuf getVertexCount)
        bulletMesh set_m_vertexStride(S3DVertex get_class get_size)

        // This will be set when the bullet mesh buf is added to the triangle index vertex array object
        //bulletMesh set_m_indexType(PHY_SHORT)

        // This defaults to whatever bullet is built with (floats or doubles).  For Irrlicht I'm sure we want only floats.
        bulletMesh set_m_vertexType(PHY_FLOAT)

        // Cant' figure out how to set the indexType properly here, and a comment indicates this constructor is only for backwards compatibility.
        // Best to use the default constructor and addIndexedMesh where you can specify the index type.
        //meshInterface := btTriangleIndexVertexArray new(numTriangles, indices unsafe_ptr_cast, indexStride, numVertices, vertices unsafe_ptr_cast, vertexStride)

        meshInterface := btTriangleIndexVertexArray new()
        meshInterface addIndexedMesh(bulletMesh, PHY_SHORT)

        meshShape := btBvhTriangleMeshShape new(meshInterface, true, true)
        */

        style := GameObjStyle clone
        style setScale(0.01) setMass(0) setPos(-26, -30, 0)
        //obj := GameObject create(style, graph, mesh, meshShape)
        obj := GameObject createClone(style, graph, mesh)
        graph objList append(obj)
    )


    Props loadLevel := method(
        terrain := Terrain clone setEngine(graph) load("Media/beach-heightmap.png")
    )

    Props loadLevelOld := method(

        //graph editor terrain getTile(0,0)

        fsStr1 := irrFsStr tmpFromCStr(WayUpDir("Media/beach-heightmap.png"))
        image := graph driver createImageFromFileWithPath(fsStr1)

        loadTile := method(x, y, xsize, ysize, scale, zscale,

            xStart := -150
            yStart := -100

            rawShape := MeshTools createMeshFromHeightmap(
                image,                      // IIMage object
                dimension2du tmp(xsize, ysize),    // tileSizeInPixels
                vector2di tmp(x, y),      // tilePosInTiles
                true // extraStripsOnEdges
            )

            if(rawShape != nil,

                zInsert := 3.0f

                splitResult := MeshTools splitMeshZ(
                    rawShape,   // mesh
                    0.0f,       // zCut
                    zInsert,    // zInsert (width of added strip)
                    false,      // marginalTrisInLeft
                    true        // marginalTrisInRight
                )

                back := graph addNode(
                    EmptyStyle clone setTexture("Media/mountaintop.jpg") setScale(scale,scale,zscale) setGameObjType("static") setPos(x*xsize*scale+xStart, y*ysize*scale+yStart, 0)
                ,
                    splitResult get_left
                )

                // For some strange reason a NULL IMesh* is not converting to nil as it should (NULLs of other types are converting to nil, just not this one)
                if( ScriptUtil get_void_ptr(splitResult get_middle) != nil,
                    writeln("path not nil")
                    meshMan := graph smgr getMeshManipulator
                    repeatAmt := 1.0/2.0
                    xScale := (repeatAmt/zInsert)
                    yScale := (repeatAmt/zInsert)
                    meshMan makePlanarTextureMapping(splitResult get_middle getMeshBuffer(0), xScale, yScale, 1, vector3df tmp(-xsize/2.0, zInsert/2.0, (zInsert/2.0)/repeatAmt))
                    walk := graph addNode(
                        EmptyStyle clone setTexture("Media/boardwalk.png") setScale(scale,scale,1.0) setGameObjType("static") setPos(x*xsize*scale+xStart, y*ysize*scale+yStart, 0) setPhysShape("mesh")
                    ,
                        splitResult get_middle
                    )
                )

                fore := graph addNode(
                    EmptyStyle clone setTexture("Media/irrlicht2_dn.jpg") setScale(scale,scale,zscale) setGameObjType("static") setPos(x*xsize*scale+xStart, y*ysize*scale+yStart, 0)
                ,
                    splitResult get_right
                )
            )
        )

        for( x, 0, 6,
            for( y, 0, 2,
                loadTile(x, y, 100, 100, 1.0, 1.0)
            )
        )
    )

    Props loadSkybox := method(

        dawn := "Media/dawnsky.png"
        night := "Media/NightMoon.png"
        dummy1 := "Media/grass.jpg"
        dummy2 := "Media/irrlicht2_dn.jpg"
        dummy3 := "Media/mountaintop.jpg"

        style := Styles SkyboxStyle clone lexicalDo(
            textureMap atPut("back", dawn)
            textureMap atPut("front", night)
            textureMap atPut("up", dummy1)
            textureMap atPut("down", dummy2)
            textureMap atPut("left", dummy3)
            textureMap atPut("right", dummy1)
        )

        skybox := graph addNode(style)

    )

    Props testSoftBody := method(

        // Set gravity to make the cloth "fall up"
        graph softBodyWorldInfo set_m_gravity(btVector3 tmp(0, -9.8, 0))

        /*
        cloth := graph addNode(ClothStyle clone setDispShape("ball") setRadius(3) setPos(6, 4, 0) setMargin(0.2) setXTiles(8) setZTiles(8) setTexture("Media/irrlicht2_dn.jpg"))

        // We want the ground to be plastic rather than elastic so set the softbody damping coefficient

        // Get the softbody
        softBody := cloth softBody

        // m_cfg is the Config object of the softbody
        // Using ref_ instead of get_ so we can change the settings.
        config := softBody ref_m_cfg

        // kDP is the damping coefficient in a range 0 to 1.0
        config set_kDP(0.001)

        config set_kDF(1)
        config set_kPR(25)

        // I read that kLST sets the spring strength.
        // It's not a property of the config but rather a material property.
        // (Softbody has array of materials.)


        graph time setTimeout(6000, block(
            writeln("removing cloth")
            graph dynamicsWorld removeSoftBody(cloth rigidBody)
            cloth node setVisible(false)
            6000
        ))

        graph time setTimeout(9000, block(
            writeln("adding cloth")
            graph dynamicsWorld addSoftBody(cloth rigidBody, cloth style collisionGroup, cloth style collisionMask)
            cloth node setVisible(true)
            6000
        ))
        */

        //cloth node setVisible(false)

        sphere := graph addNode(BallStyle clone setPhysShape("none") setRadius(3))
        sphere node setVisible(false)

        topMesh := MeshTools sliceMesh(sphere dispShape, aabbox3df tmp( -100, -100,-100, 1,100,100 ) )
        topMeshStyle := EmptyStyle clone setPos(0, 3.2, 0) setTexture("Media/mountaintop.jpg") // setWireframe(true)
        topObj := graph addNode(topMeshStyle, topMesh)

        botMesh := MeshTools sliceMesh(sphere dispShape, aabbox3df tmp( 1, -100 ,-100, 100, 100, 100 ) )
        botMeshStyle := EmptyStyle clone setPos(0, 3.2, 0) setTexture("Media/grass.jpg") // setWireframe(true)
        botObj := graph addNode(botMeshStyle, botMesh)

        //graph addNode(BoxStyle clone setPos(1, 3.2, 0) setSize(0.02, 6, 6) setMass(0))

        graph time setTimeout(100, block(
            if (graph events isKeyDown(KEY_KEY_A),
                topObj node setVisible(false)
            )
            if (graph events isKeyDown(KEY_KEY_S),
                topObj node setVisible(true)
            )
            if (graph events isKeyDown(KEY_KEY_D),
                botObj node setVisible(false)
            )
            if (graph events isKeyDown(KEY_KEY_F),
                botObj node setVisible(true)
            )
            100
        ))
    )

    return Props
)
