method(namespace_Bullet, Constants,
    ShapeOffsets := Object clone lexicalDo(
        appendProto(namespace_Bullet)
        appendProto(Constants)

        none := method(
            namespace_Bullet getIdentityTransform
        )

        ball := method(
            namespace_Bullet getIdentityTransform
        )

        box := method(
            namespace_Bullet getIdentityTransform
        )

        cyl := method(style,
            axis := btVector3 tmp(0, 1, 0)
            angle := 0
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(0, -style length/2, 0)

            btTransform tmp(q, v)
        )

        cylX := method(style,
            axis := btVector3 tmp(0, 0, 1)
            angle := TAU/4
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(style length/2, 0, 0)
            //v := btVector3 tmp(0, 0, 0)

            btTransform tmp(q, v)
        )

        cylZ := method(style,
            axis := btVector3 tmp(1, 0, 0)
            angle := TAU/4
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(0, 0, -style length/2)
            //v := btVector3 tmp(0, 0, 0)

            btTransform tmp(q, v)
        )

        cone := method(style,
            axis := btVector3 tmp(0, 0, 1)
            angle := 0
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(0, -style length/2, 0)

            btTransform tmp(q, v)
        )

        coneX := method(style,
            axis := btVector3 tmp(0, 0, 1)
            angle := -TAU/4
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(-style length/2, 0, 0)
            //v := btVector3 tmp(0, 0, 0)

            btTransform tmp(q, v)
        )

        coneZ := method(style,
            axis := btVector3 tmp(1, 0, 0)
            angle := TAU/4
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(0, 0, -style length/2)
            //v := btVector3 tmp(0, 0, 0)

            btTransform tmp(q, v)
        )

        hills := method(
            namespace_Bullet getIdentityTransform
        )

        mesh := method(
            namespace_Bullet getIdentityTransform
        )

        cloth := method(
            namespace_Bullet getIdentityTransform
        )
    )

    ShapeOffsets namespace_Bullet := namespace_Bullet

    return ShapeOffsets
)
