method(namespace_Bullet, namespace_Custom,

    BodyBuilder := Object clone lexicalDo(

        appendProto(namespace_Bullet)
        appendProto(namespace_Custom)

        dynamicsWorld ::= nil
        shapeBuilder ::= nil

        buildBody := method(style,

            physShape := shapeBuilder create(style)
            shapeOffset := shapeBuilder getOffset(style)

            if (physShape == nil,
                return nil
            )

            mass := if(style isKinematic, 0, style mass)

            localInertia := btVector3 tmp(0,0,0)

            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            if (mass != 0,
                physShape calculateLocalInertia(style mass, localInertia)
            )

            // Location
            startTransform := btTransform tmp
            startTransform setIdentity()
            startTransform setOrigin(btVector3 tmp(style x, style y, style z))

            if (style axisX == 0 and style axisY == 0 and style axisZ == 0,
                rot := btQuaternion tmp(style yaw, style pitch, style roll)
            ,
                rot := btQuaternion tmp(btVector3 tmp(style axisX, style axisY, style axisZ), style angle)
            )

            startTransform setRotation(rot)

            if (style isKinematic,
                motionState := KinematicAnimator new(startTransform, shapeOffset)
            ,
                motionState := PhysicsAnimator new(startTransform, shapeOffset)
            )

            // This is done here rather than in ShapeBuilder because although bullet scales shapes, irrlicht scales nodes,
            // and the irrlicht node is only created in not in ShapeBuilder.
            // Also, some bullet shapes cannot be scaled anyway & have to be scaled here.
            physShape setLocalScaling(btVector3 tmp(style physScaleX, style physScaleY, style physScaleZ))

            rbInfo := btRigidBodyConstructionInfo tmp(mass, motionState, physShape, localInertia)
            rbInfo set_m_friction(style friction)

            rigidBody := btRigidBody new(rbInfo)

            if (style collisionGroup == nil,
                dynamicsWorld addRigidBody(rigidBody)
            ,
                dynamicsWorld addRigidBody(rigidBody, style collisionGroup, style collisionMask)
            )

            rigidBody setLinearFactor(btVector3 tmp(style linFactorX, style linFactorY, style linFactorZ))
            rigidBody setAngularFactor(btVector3 tmp(style angFactorX, style angFactorY, style angFactorZ))

            rigidBody setDamping(style linDamping, style angDamping)

            // Must set gravity after adding to dynamics world, or it gets overwritten with the default gravity.
            if (style gravityType == "none") then(
                rigidBody setGravity(btVector3 tmp(0,0,0))
            ) elseif(style gravityType == "custom") then(
                rigidBody setGravity(btVector3 tmp(style gravityX, style gravityY, style gravityZ))
            )

            rigidBody setLinearVelocity(btVector3 tmp(style xv, style yv, style zv))

            // Static mesh objects can be kinematic as well as rigid bodies.
            // I think this is safe for softbody too, although a kinematic softbody
            // doesn't really make a lot of sense.
            if (style isKinematic) then(
                CF_KINEMATIC_OBJECT := 2
                rigidBody setCollisionFlags(rigidBody getCollisionFlags | CF_KINEMATIC_OBJECT)
                DISABLE_DEACTIVATION := 4
                rigidBody setActivationState(DISABLE_DEACTIVATION)
            )

            if (style disableDeactivation,
                DISABLE_DEACTIVATION := 4
                rigidBody setActivationState(DISABLE_DEACTIVATION)
            )

            // Restitution applies to static mesh objects and to rigid bodies.
            if (style restitution != style default,
                rigidBody setRestitution(style restitution)
            )

            return Object clone lexicalDo(
                body := rigidBody
                anim := motionState
            )
        )
    )
)
