
method(namespace_irr, namespace_Custom, Constants,

    NodeAttribute := Object clone lexicalDo(
        appendProto(namespace_irr)
        appendProto(namespace_irr scene)
        appendProto(namespace_Custom)

        Constants := Constants

        style ::= nil
        texture ::= nil
        sceneNode ::= nil

        motionState := nil
        setMotionState := method(value,
            motionState = value
            if(motionState != nil,
                if(sceneNode != nil,
                    sceneNode addAnimator(motionState)
                )
            )
        )

        dispShape ::= nil
        flagBits ::= nil

        isMouseDraggable := nil
        setIsMouseDraggable := method(state,
            if(state==nil,
                state = (style mass != 0)
            )
            isMouseDraggable = state
            if(flagBits != nil and sceneNode != nil,
                flagBits setBit(Constants mouseDraggableBitPos, state)
            )
            self
        )

        setFlagBit := method(pos, state,
            flagBits setBit(pos, state)
            self
        )

        addKinematicAnimator := method(anim,
            animators append(anim)
            sceneNode addAnimator(anim)
        )

        addChild := method(otherObj,
            sceneNode addChild(otherObj sceneNode)
        )

        getPos := method(
            if (sceneNode != nil) then(
                p := sceneNode getAbsolutePosition
                o := Object clone
                o x := p get_X; o y := p get_Y; o z := p get_Z
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

            oldMotionState := motionState
            setMotionState(
                LockAnimator new(otherObj rigidBody getMotionState_c, namespace Bullet getIdentityTransform)
            )

            if (sceneNode != nil,
                sceneNode addAnimator(motionState)
                sceneNode removeAnimator(oldMotionState)
            )

            oldMotionState drop

            motionState
        )

        dispose := method(
            sceneNode remove
            //sceneNode drop
        )
    )
)
