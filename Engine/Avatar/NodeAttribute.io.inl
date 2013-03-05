// TODO:  Implement only left and right and the interaction TODO from the bottom of this file.

method(namespace_Bullet, namespace_irr, namespace_Custom,

    NodeAttribute := Object clone lexicalDo(

        appendProto(namespace_Bullet)
        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_Custom)

        sense ::= nil
        canJump ::= true
        justJumped ::= false
        captured ::= false
        onPlatform ::= false
        elevator ::= nil
        addedVelX ::= 0
        jumpVel ::= 9

        physBody ::= nil

        actions ::= nil

        init := method(
            setActions(list())
        )

/*
        create := method(

            setSteering(Steering clone setGameObj(self))

            setSense(Sense create(engine, self))

            sense addStandOnResponse("elevator",
                block(obj,
                    setElevator(obj)
                )
            )

            sense addContactResponse("gearSlot",
                block(obj,
                    if (justJumped not and captured not,
                        setCaptured(true)
                        gearAxle := obj constraintsB at(0)
                        carBody := gearAxle objA
                        engine addConstraint(gearAxle style, carBody, self)

                        wheel := carBody constraintsA at(0) objB

                        gear := GearStyle clone do(
                            setRatio(0.5)
                        )

                        engine addConstraint(gear, self, wheel)
                    )
                )
            )

            //rigidBody setLinearFactor(btVector3 tmp(1,1,0))
            //rigidBody setAngularFactor(btVector3 tmp(0,0,1))

            self
        )
*/

        canJump := method(

            //setCanJump(testCanJump)
            //sense standOnWithResponse(style radius + 0.2, TAU/3)
            //sense contactWithResponse
            true
        )

        dive := method(
            actions append("dive")
        )

        jump := method(
            actions append("jump")
        )

        right := method(
            actions append("right")
        )

        left := method(
            actions append("left")
        )

        /*
        TODO:  Is this fully implemented in Sense instead?
        testCanJump := method(

            if (justJumped, return false)

            xform := btTransform tmp
            rigidBody getMotionState_c() getWorldTransform(xform)

            raySource := xform getOrigin_c()
            rayTarget := btVector3 tmp(raySource getX, raySource getY - (0.5 + 0.5), raySource getZ)

            rayCallback := ScriptedClosestRayResultCallback tmp(
                block(rayResult, normalInWorldSpace,
                    isMe := rayCallback test_equals(rayResult get_m_collisionObject, rigidBody)

                    if( isMe ) then(
                        return 1.0
                    )else(
                        other := io_vm castToIoObjectPointer(rayResult get_m_collisionObject getUserPointer)
                        if (other != nil,
                            setOnPlatform(other style isPlatform)
                            //writeln("onPlatform == ", onPlatform)
                        )
                        return rayCallback baseAddSingleResult(rayResult, normalInWorldSpace)
                    )
                )
            )

            setOnPlatform(false)
            rayCallback set_m_closestHitFraction(1.0)
            engine dynamicsWorld rayTest(raySource, rayTarget, rayCallback)

            return rayCallback hasHit
        )
    */
    )
)
