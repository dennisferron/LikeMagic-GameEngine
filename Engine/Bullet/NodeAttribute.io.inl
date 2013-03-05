method(namespace_Bullet, namespace_Custom,

    NodeAttribute := Object clone lexicalDo(
        appendProto(namespace_Bullet)
        appendProto(namespace_Custom)

        style ::= nil

        physShape ::= nil
        rigidBody := nil
        constraintsA ::= nil
        constraintsB ::= nil
        motionState ::= nil

        setRigidBody := method(newRigidBody,
            if (rigidBody != nil, rigidBody setUserPointer(nil))
            rigidBody = newRigidBody
            rigidBody setUserPointer(self)
            return self
        )

        setLinearVelocity := method(xv, yv, zv,
            if (yv == nil,
                rigidBody setLinearVelocity(xv),
                rigidBody setLinearVelocity(btVector3 tmp(xv, yv, zv))
            )
        )

        setAngularVelocity := method(xv, yv, zv,
            rigidBody setAngularVelocity(btVector3 tmp(xv, yv, zv))
        )

        applyTorque := method(x, y, z,
            rigidBody applyTorque(btVector3 tmp(x, y, z))
        )

        getAngularVelocity := method(
            rigidBody getAngularVelocity
        )

        getLinearVelocity := method(
            rigidBody getLinearVelocity
        )

        addChild := method(otherObj,
            childObjs append(otherObj)
            node addChild(otherObj node)
        )

        disableSleepState := method(
            DISABLE_DEACTIVATION := 4
            rigidBody setActivationState(DISABLE_DEACTIVATION)
        )

        getRotZ := method(
            // For some reason getting this rotation from a Bullet rigid body is
            // *really freaking hard* to figure out & not much on google about it.
            // I solved it once for GearConstraints in C++ and be damned if I'm going to
            // try to solve it again in Io code, so I'm just going to "borrow"
            // the implementation from my gear constraint:
            GearConstraint getRotZ(rigidBody)
        )

        getPos := method(
            if (rigidBody != nil) then(
                p := rigidBody getCenterOfMassPosition
                o := Object clone
                o x := p getX; o y := p getY; o z := p getZ
                return o
            )
            else(
                return style getPos
            )
        )

        triggerAllGenerators := method(onTrigger,
            if (style hasSlot("spawnStyle"),
                s := style spawnStyle clone
                s setPos(s x + getX, s y + getY, s z + getZ)
                // TODO:  Set relative velocity as well as pos.
                obj := engine addObj(s)

                if(onTrigger != nil, onTrigger call(obj))
            )
            childObjs foreach(o, o triggerAllGenerators(onTrigger))
        )

        lockTo := method(otherObj,

            // In order to lock the object to another, we have to make it a kinematic body (i.e., directly animated not physically affected)
            CF_KINEMATIC_OBJECT := 2
            rigidBody setCollisionFlags(rigidBody getCollisionFlags | CF_KINEMATIC_OBJECT)
            DISABLE_DEACTIVATION := 4
            rigidBody setActivationState(DISABLE_DEACTIVATION)

            oldMotionState := motionState
            setMotionState(
                LockAnimator new(otherObj rigidBody getMotionState_c, namespace Bullet getIdentityTransform)
            )
            rigidBody setMotionState(motionState)

            if (node != nil,
                node addAnimator(motionState)
                node removeAnimator(oldMotionState)
            )

            oldMotionState drop

            motionState
        )

        applyForceTowards := method(targetPos, scalar, maxForce,
            p1 := targetPos
            p2 := getPos

            xdiff := p1 x - p2 x
            ydiff := p1 y - p2 y
            zdiff := p1 z - p2 z

            applyScaledForce(xdiff, ydiff, zdiff, scalar, maxForce)
        )

        applyScaledForce := method(xforce, yforce, zforce, scalar, maxForce, maxVerticalForce,

            if (maxVerticalForce == nil, maxVerticalForce = maxForce)

            xforce = xforce * scalar
            yforce = yforce * scalar
            zforce = zforce * scalar

            if (xforce > maxForce, xforce = maxForce)
            if (xforce < -maxForce, xforce = -maxForce)
            if (yforce > maxVerticalForce, yforce = maxVerticalForce)
            if (yforce < -maxVerticalForce, yforce = -maxVerticalForce)
            if (zforce > maxForce, zforce = maxForce)
            if (zforce < -maxForce, zforce = -maxForce)

            applyCentralForce(xforce, yforce, zforce)
        )

        applyCentralForce := method(x,y,z,
            rigidBody applyCentralForce(btVector3 tmp(x,y,z))
        )

        applyCentralImpulse := method(x,y,z,
            rigidBody applyCentralImpulse(btVector3 tmp(x,y,z))
        )

        applyTorque := method(x,y,z,
            rigidBody applyTorque(btVector3 tmp(x,y,z))
        )

        applyTorqueImpulse := method(x,y,z,
            rigidBody applyTorqueImpulse(btVector3 tmp(x,y,z))
        )

        fallApart := method(visited, removed,

            if (visited == nil,
                visited := list()
            )

            if (removed == nil,
                removed := list()
            )

            if (visited contains(self),
                return
            ,
                visited append(self)
            )

            consA := constraintsA clone
            consA foreach(c,
                if (c objB != nil,
                    c objB fallApart(visited, removed)
                )
                if (removed contains(c) not,
                    removed append(c)
                    engine removeConstraint(c)
                )
            )

            consB := constraintsB clone
            consB foreach(c,
                if (c objA != nil,
                    c objA fallApart(visited, removed)
                )
                if (removed contains(c) not,
                    removed append(c)
                    engine removeConstraint(c)
                )
            )

        )

        structureDoForEachObject := method(code, visited,

            if (visited == nil,
                visited := list()
            )

            if (visited contains(self),
                return
            ,
                visited append(self)
                code call(self)
            )

            consA := constraintsA clone
            consA foreach(c,
                if (c objB != nil,
                    c objB structureDoForEachObject(code, visited)
                )
            )

            consB := constraintsB clone
            consB foreach(c,
                if (c objA != nil,
                    c objA structureDoForEachObject(code, visited)
                )
            )
        )

        dispose := method(

            // If this is the left side of a constraint, delete not the constraint
            // but the object on the other side of the constraint.
            constraintsA foreach(v, v objB dispose)
            constraintsA empty

            // If this is the right side of a constraint, remove the constraint but not the A-side.
            constraintsB foreach(v, engine removeConstraint(v constraint); constraint delete)
            constraintsB empty

            if (rigidBody != nil,
                engine dynamicsWorld removeRigidBody(rigidBody)
                rigidBody delete
            )
        )
    )
)
