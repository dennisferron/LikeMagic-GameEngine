
method(namespace_desteer, namespace_irr,

    Steering := Object clone lexicalDo(

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_desteer)
        appendProto(namespace_desteer entity)
        appendProto(namespace_desteer controller)

        gameObj ::= nil
        controller ::= nil
        entity ::= nil
        obstacles ::= nil
        forceScalar ::= 40
        maxHorizontalForce ::= 350
        maxVerticalForce ::= 200
        maxSpeed ::= 30

        getVector := method(x, y, z,
            gameObj node getAbsoluteTransformation getRotationDegrees rotationToDirection(vector3df tmp(x,y,z))
        )

        init := method(
            writeln("Steering init")
            //steerList append(self)
            setEntity(ScriptedMobileEntity new)
            entity appendProto(self)
            addBaseEntityBlocks(entity)
            addEntitySpaceBlocks(entity)
            addMobileEntityBlocks(entity)
            setController(SimpleSteeringController new(entity))
            // STILL getting a segfault on obstacles!
            //setObstacles(EntityGroup tmp)
            return self
        )

        addObstacleGameObj := method(gameObj,
            return nil;
            if (gameObj steering == nil,
                gameObj setSteering(Steering clone setGameObj(gameObj))
                //steerList append(gameObj)
            )
            obstacles push_back(gameObj steering entity)
            controller SetObstacles(obstacles)  // controller copies the vector by assignment
            setBehaviorFlag(EBF_AVOID, true)
        )

        setHideTarget := method(otherSteering,
            controller SetHideTarget(otherSteering entity)
            setBehaviorFlag(EBF_HIDE, otherSteering != nil)
        )

        setPursuitTarget := method(otherSteering,
            controller SetPursuitTarget(otherSteering entity)
            setBehaviorFlag(EBF_PURSUIT, otherSteering != nil)
        )

        setBehaviorFlag := method(flag, value,
            controller SetBehaviorFlag(flag, value)
        )

        update := method(timeElapsed,
            entity Update(timeElapsed)
        )

        addBaseEntityBlocks := method(entity,
            entity do(
                // IBaseEntity

                posBlock := block(
                    gameObj node getAbsolutePosition
                )

                //posList append(posBlock)
                //entList append(entity)

                set_OnPosition(posBlock)

                set_OnSetPosition(block(
                    Exception raise("SteeringEntity SetPosition not implemented.")
                ))

                set_OnRadius(block(
                    gameObj style radius + 0.5
                ))

                set_OnUpdate(block(
                    force := controller Calculate()
                    //writeln("Force is ", force get_X, ", ", force get_Y, ", ", force get_Z)
                    gameObj applyScaledForce(force get_X, force get_Y, force get_Z, forceScalar, maxHorizontalForce, maxVerticalForce)
                ))
            )
        )

        addEntitySpaceBlocks := method(entity,
            entity do(
                // IEntitySpace

                set_OnSideVector(block(
                    getVector(1,0,0)
                ))

                set_OnSetSideVector(block(
                    Exception raise("SteeringEntity SetSideVector not implemented.")
                ))

                set_OnForwardVector(block(
                    getVector(0,0,1)
                ))

                set_OnSetForwardVector(block(
                    Exception raise("SteeringEntity SetForwardVector not implemented.")
                ))

                set_OntransformWorldVectToLocal(block(vec,
                    tempValue := self Position
                    offset := vec - tempValue
                    up := getVector(0,1,0)
                    x := offset dotProduct(self SideVector)
                    y := offset dotProduct(up)
                    z := offset dotProduct(self ForwardVector)
                    return vector3df tmp(x, y, z)
                ))

                set_OntransformLocalVectToWorld(block(vec,
                    result := vector3df tmp
                    gameObj node getAbsoluteTransformation transformVect(result, vec)
                    return result
                ))
            )
        )

        addMobileEntityBlocks := method(entity,
            entity do(
                // IMobileEntity

                set_OnSetSteering(block(controller,
                    setController(controller)
                    return nil
                ))

                set_OnMass(block(
                    gameObj style mass
                ))

                set_OnSetMass(block(mass,
                    Exception raise("SteeringEntity SetMass not implemented.")
                ))

                set_OnMaxForce(block(
                    maxHorizontalForce
                ))

                set_OnSetMaxForce(block(
                    Exception raise("SteeringEntity SetMaxForce not implemented.")
                ))

                set_OnMaxSpeed(block(
                    return maxSpeed
                ))

                set_OnSetMaxSpeed(block(maxSpeed,
                    Exception raise("SteeringEntity SetMaxSpeed not implemented.")
                ))

                set_OnVelocity(block(
                    btVel := gameObj rigidBody getLinearVelocity
                    return vector3df tmp(btVel x, btVel y, btVel z)
                ))
            )
        )
    )
)
