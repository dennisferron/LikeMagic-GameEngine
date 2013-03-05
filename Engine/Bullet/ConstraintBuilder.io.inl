method(namespace_Bullet, ConstraintStyles,

    ConstraintBuilder := Object clone lexicalDo(
        appendProto(namespace_Bullet)
        appendProto(ConstraintStyles)

        none := method(Exception raise("No joint type specified."))

        mouseDrag := method(style, rbA, rbB,
            return point2point(Point2PointStyle clone, rbA, rbB)
        )

        slider := method(style, rbA, rbB,
            result := if (rbA == nil or style mountA == nil,
                btSliderConstraint new(rbB, getFrame(style mountB), style useLinearReferenceFrameA),
                btSliderConstraint new(rbA, rbB, getFrame(style mountA), getFrame(style mountB), style useLinearReferenceFrameA)
            )
            result setLowerLinLimit(style lowerLinLimit)
            result setUpperLinLimit(style upperLinLimit)
            result setLowerAngLimit(style lowerAngLimit)
            result setUpperAngLimit(style upperAngLimit)
            result
        )

        coneTwist := method(style, rbA, rbB,
            result := if (rbA == nil or style mountA == nil,
                btConeTwistConstraint new(rbB, getFrame(style mountB)),
                btConeTwistConstraint new(rbA, rbB, getFrame(style mountA), getFrame(style mountB))
            )
            result setLimit(style swingSpan1, style swingSpan2, style twistSpan, style softness, style biasFactor, style relaxationFactor)

            if (style damping != "none", result setDamping(style damping))

            result
        )

        hinge := method(style, rbA, rbB,
            result := if (rbA == nil or style mountA == nil,
                btHingeConstraint new(rbB, getFrame(style mountB), style useLinearReferenceFrameA),
                btHingeConstraint new(rbA, rbB, getFrame(style mountA), getFrame(style mountB), style useLinearReferenceFrameA)
            )

            result setLimit(style lowerAngLimit, style upperAngLimit, style softness, style biasFactor, style relaxationFactor)
            result
        )

        gear := method(style, rbA, rbB,
            result := GearConstraint new(rbA, rbB, style ratio)
            result
        )

        point2point := method(style, rbA, rbB,
            result := if( rbA == nil or style mountA == nil ,
                btPoint2PointConstraint new(rbB, getFrame(style mountB) getOrigin_c)
            ,
                btPoint2PointConstraint new(rbA, rbB, getFrame(style mountA) getOrigin_c, getFrame(style mountB) getOrigin_c)
            )
            result
        )

        generic := method(style, rbA, rbB,
            result := if (rbA == nil or style mountA == nil,
                btGeneric6DofConstraint new(rbB, getFrame(style mountB), style useLinearReferenceFrameA),
                btGeneric6DofConstraint new(rbA, rbB, getFrame(style mountA), getFrame(style mountB), style useLinearReferenceFrameA)
            )
            result setLinearLowerLimit(btVector3 tmp(style lowerLinLimitX, style lowerLinLimitY, style lowerLinLimitZ))
            result setLinearUpperLimit(btVector3 tmp(style upperLinLimitX, style upperLinLimitY, style upperLinLimitZ))
            result setAngularLowerLimit(btVector3 tmp(style lowerAngLimitX, style lowerAngLimitY, style lowerAngLimitZ))
            result setAngularUpperLimit(btVector3 tmp(style upperAngLimitX, style upperAngLimitY, style upperAngLimitZ))
            result
        )

        genericSpring := method(style, rbA, rbB,
            if (rbA == nil or style mountA == nil,
                Exception raise("generic spring constraint cannot be connected to world (mount A or rigid body A was null).")
            )
            result := btGeneric6DofSpringConstraint new(rbA, rbB, getFrame(style mountA), getFrame(style mountB), style useLinearReferenceFrameA)

            result setLinearLowerLimit(btVector3 tmp(style lowerLinLimitX, style lowerLinLimitY, style lowerLinLimitZ))
            result setLinearUpperLimit(btVector3 tmp(style upperLinLimitX, style upperLinLimitY, style upperLinLimitZ))
            result setAngularLowerLimit(btVector3 tmp(style lowerAngLimitX, style lowerAngLimitY, style lowerAngLimitZ))
            result setAngularUpperLimit(btVector3 tmp(style upperAngLimitX, style upperAngLimitY, style upperAngLimitZ))

            setProp := method(n, prop,
                result enableSpring(n, prop enabled)
                result setStiffness(n, prop stiffness)
                result setDamping(n, prop damping)
            )

            setProp(0, style transX)
            setProp(1, style transY)
            setProp(2, style transZ)
            setProp(3, style rotX)
            setProp(4, style rotY)
            setProp(5, style rotZ)

            result
        )
    )

    ConstraintBuilder create := method(style, objA, objB,
        slot := self getSlot(style jointType asString)
        if(slot != nil,
            result := slot call(style, objA ?rigidBody, objB ?rigidBody)
            result setDbgDrawSize(style debugDrawSize)
            ConstraintObj clone setStyle(style) setConstraint(result) setObjA(objA) setObjB(objB)
        ,
            return nil
        )
    )


    // Utility method
    ConstraintBuilder getFrame := method(mount,

        if (mount axisX == 0 and mount axisY == 0 and mount axisZ == 0,
            rot := btQuaternion tmp(mount yaw, mount pitch, mount roll)
        ,
            rot := btQuaternion tmp(btVector3 tmp(mount axisX, mount axisY, mount axisZ), mount angle)
        )

        btTransform tmp(
            rot, btVector3 tmp(mount x, mount y, mount z)
        )
    )

    return ConstraintBuilder
)
