
method(namespace_Bullet,

    Sense := Object clone lexicalDo(
        appendProto(namespace_Bullet)

        engine ::= nil
        sourceObj ::= nil
        contactCallback ::= nil
        rayCallback ::= nil

        contactResponse ::= nil
        standOnResponse ::= nil
    )

    Sense create := method(engine, sourceObj,
        setEngine(engine)
        setSourceObj(sourceObj)

        setContactResponse(Map clone)
        setStandOnResponse(Map clone)

        setRayCallback(
            ScriptedClosestRayResultCallback tmp(
                block(rayResult, normalInWorldSpace,
                    isMe := rayCallback test_equals(rayResult get_m_collisionObject, sourceObj rigidBody)

                    if( isMe ) then(
                        return 1.0
                    )else(
                        other := io_vm castToIoObjectPointer(rayResult get_m_collisionObject getUserPointer)
                        if (other != nil,
                            rayCallback setOtherObj(other)
                        )
                        return rayCallback baseAddSingleResult(rayResult, normalInWorldSpace)
                    )
                )
            )
        )
        rayCallback otherObj ::= nil

        setContactCallback(
            ScriptedContactResultCallback tmp(
                block(cp, colObj0, partId0, index0, colObj1, partId1, index1,

                    objA := io_vm castToIoObjectPointer(colObj0 getUserPointer)
                    objB := io_vm castToIoObjectPointer(colObj1 getUserPointer)

                    if (objA == sourceObj) then(
                        contactCallback otherObjs append(objB)
                    ) elseif (objB == sourceObj) then(
                        contactCallback otherObjs append(objA)
                    ) else (
                        Exception raise("ContactCallback:  neither of the two contact objects equals the source object.")
                    )

                    return 0; // not sure if return value is used

                ),
                block(proxy, return true)
            )
        )
        contactCallback otherObjs := List clone

        return self
    )

    Sense contactTest := method(
        contactCallback otherObjs empty
        engine bltComp dynamicsWorld contactTest(sourceObj rigidBody, contactCallback)
        return contactCallback otherObjs
    )

    Sense contactWithResponse := method(
        result := contactTest
        result foreach(obj, if(obj style collisionResponseTag != nil, _tryResponse(contactResponse, obj)))
        return result
    )

    Sense rayTest := method(xOffset, yOffset, zOffset,

        xform := btTransform tmp
        sourceObj rigidBody getMotionState_c() getWorldTransform(xform)

        raySource := xform getOrigin_c()
        rayTarget := btVector3 tmp(raySource getX + xOffset, raySource getY + yOffset, raySource getZ + zOffset)

        rayCallback setOtherObj(nil)
        rayCallback set_m_closestHitFraction(1.0)
        engine bltComp dynamicsWorld rayTest(raySource, rayTarget, rayCallback)
        return rayCallback otherObj
    )

    // Note:  This only tests in a 2d arc in the x,y plane
    Sense arcTest := method(len, angle, sweep, count,
        result := List clone

        start := angle - sweep/2
        end := angle + sweep/2

        // A count of 1 does not increment.  Otherwise there are count - 1 segments.
        incr := if(count > 1, (end - start)/(count-1), 0)

        if (count == 1, start = angle)

        resultData := Object clone do(
            length ::= nil
            angle ::= nil
            x ::= nil
            y ::= nil
            obj ::= nil
        )

        for( i, 0, count-1,
            a := start + i*incr
            x := len * (a cos)
            y := len * (a sin)
            contactObj := rayTest(x, y, 0)
            result append(
                resultData clone setLength(len) setAngle(a) setX(x) setY(y) setObj(contactObj)
            )
        )

        return result
    )

    Sense standOnTest := method(len, sweep,

        center := -TAU/4

        hitList := arcTest(len, center, sweep, 9)

        standingOn := List clone

        hasHit := false
        angTotal := 0
        angCount := 0
        hitList foreach(arcResult,
            if(arcResult obj != nil,
                hasHit = true
                angTotal = angTotal + arcResult angle
                angCount = angCount + 1
                if(arcResult obj style collisionResponseTag != nil,
                    standingOn appendIfAbsent(arcResult obj)
                )
            )
        )

        avgAng := if(angCount > 0, angTotal/angCount, 0)

        resultData := Object clone do(
            hasHit ::= nil
            avgAng ::= nil
            standingOn ::= nil
        )
        return resultData clone setHasHit(hasHit) setAvgAng(avgAng) setStandingOn(standingOn)
    )

    Sense standOnWithResponse := method(len, sweep,
        resultData := standOnTest(len, sweep)
        resultData standingOn foreach(obj, _tryResponse(standOnResponse, obj))
        return resultData
    )

    Sense addStandOnResponse := method(responseTag, callback,
        _addResponse(standOnResponse, responseTag, callback)
    )

    Sense addContactResponse := method(responseTag, callback,
        _addResponse(contactResponse, responseTag, callback)
    )

    Sense _addResponse := method(map, responseTag, callback,
        map atIfAbsentPut(responseTag, List clone) appendIfAbsent(callback)
    )

    Sense _tryResponse := method(map, obj,
        map at(obj style collisionResponseTag, list()) foreach(cb, cb call(obj))
    )

    return Sense
)
