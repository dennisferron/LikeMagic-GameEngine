
method(NodeInteraction, Node, Avatar, Bullet, Time, Constants,

    PlayerPhysics := NodeInteraction clone lexicalDo(
        appendProto(Constants)

        setReferent(mapSubdomains)

        referent at("node") setTrigger(
            physBody : Bullet NodeAttribute,
            player : Avatar NodeAttribute
        )

        referent at("component") setTrigger(
            time : Time
        )

        jumpVel ::= 9
        vel := method(physBody getLinearVelocity)

        right := method(
            // Captured is a detail the player should resolve
            //if (player captured not,
                if (vel getX < 10, physBody applyCentralForce(100 - (vel getX)*(vel getX abs), 0, 0))
            //)
            physBody applyTorque(0, 0, -40)
        )

        left := method(
            //if (player captured not,
                if (vel getX > -10, physBody applyCentralForce(-100 - (vel getX)*(vel getX abs), 0, 0))
            //)
            physBody applyTorque(0, 0, 40)
        )

        dive := method(
            physBody applyCentralForce(0, -600 - (vel getY)*(vel getY abs), 0)
        )

        jump := method(

            // Jumping slows falling?
            physBody applyCentralForce(0, 15, 0)

//            if(player captured,
//                while(constraintsA size > 0, engine removeConstraint(constraintsA at(0)))
//                while(constraintsB size > 0, engine removeConstraint(constraintsB at(0)))
//                engine time setTimeout(1000, block(setCaptured(false); 0))
//            )

            if(true, // player canJump hasHit or player captured,

                //applyCentralImpulse(0, 35, 0)

                if (player captured,
                    jumpY := jumpVel
                    jumpX := 0
                ,

                    ang := TAU/4 // straight up
                /* TODO Put these jump angle adjustments back when we have Sense working again:
                    ang := canJump avgAng + TAU/2 // Apply force opposite the ground

                    // Adjust the jump angle to be closer to straight up than pure ground angle
                    ang := (ang + 2*TAU/4)/3
                */

                    jumpX := jumpVel * (ang cos)
                    jumpY := jumpVel * (ang sin)

                    //if( elevator != nil and elevator getLinearVelocity getY > 0,
                    //    jumpY = jumpY + 0.75 * elevator getLinearVelocity getY
                    //)
                )

                physBody setLinearVelocity(vel getX + jumpX, jumpY, 0)
                player setJustJumped(true)
                //time setTimeout(300, block(player setJustJumped(false); 0))
            )
        )

        enter := method(
            time beforePhysics append(
                block(
                    while(item := player actions removeFirst,
                        self perform(item)
                    )
                )
            )

            self
        )
    )

    Node registerInteraction(PlayerPhysics)

    return PlayerPhysics
)
