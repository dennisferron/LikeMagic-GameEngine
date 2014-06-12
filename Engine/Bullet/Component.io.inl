
method(module, namespace_Bullet, namespace_Custom,

    Component := Object clone lexicalDo(

        module := module
        NodeAttribute := module NodeAttribute

        appendProto(namespace_Custom)
        appendProto(namespace_Bullet)

        fixedTimeStep := 1/60
        subframes := 30

        collisionConfiguration ::= nil
        dispatcher ::= nil  // This is a bullet physics thing, not associated with UI event dispatch
        overlappingPairCache ::= nil
        solver ::= nil
        dynamicsWorld ::= nil
        softBodyWorldInfo ::= nil
        scriptWorldMgr ::= nil
        debugDrawer ::= nil
        bodyBuilder ::= nil

        setDebugMode := method(debugMode,
            dynamicsWorld getDebugDrawer setDebugMode(debugMode)
        )

        addLink := method(link,
            if( link style jointType != "none" and module ConstraintBuilder hasSlot(link style jointType),
                attrA := link fromNode ?findAttribute(NodeAttribute)
                attrB := link toNode ?findAttribute(NodeAttribute)

                if( attrA == nil and attrB == nil,
                    writeln("Link style " .. (
                        link style jointType) .. (
                        " is supported by constraint builder, but both the from node (" ) .. (
                        if(link fromNode == nil, "nil", link fromNode style)) .. (
                        ") and the to node (") .. (
                        if(link toNode == nil, "nil", link toNode style)) .. (
                        ") do not have Bullet attributes attached.")
                    )
                ,
                    linkAttr := addConstraint(link style, attrA, attrB)
                    link addAttribute(linkAttr)
                )
            )
        )
    )

    Component init := method(

        writeln("Begin Bullet Component init")

        // Enable softbody collisions
        setCollisionConfiguration(btSoftBodyRigidBodyCollisionConfiguration new)

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        setDispatcher(btCollisionDispatcher new(collisionConfiguration))

        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        setOverlappingPairCache(btDbvtBroadphase new())

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        setSolver(btSequentialImpulseConstraintSolver new)

        //setDynamicsWorld(btDiscreteDynamicsWorld new(dispatcher,overlappingPairCache,solver,collisionConfiguration))
        setDynamicsWorld(btSoftRigidDynamicsWorld new(dispatcher, overlappingPairCache, solver, collisionConfiguration))

        // Gravity in approximate meters per second per second
        dynamicsWorld setGravity(btVector3 tmp(0, -9.81, 0))

        //setDebugMode(DBG_DrawConstraints)

        setScriptWorldMgr(ScriptedWorldManager tmp)

        scriptWorldMgr setOnTick(dynamicsWorld,
            block(worldptr, timeStep,
                nil
            )
        )

        scriptWorldMgr setOnPreTick(dynamicsWorld,
            block(worldptr, timeStep,
                nil
            )
        )

        // Created with tmp so don't need to delete
        setSoftBodyWorldInfo(btSoftBodyWorldInfo tmp)
        softBodyWorldInfo set_m_dispatcher(dispatcher)
        softBodyWorldInfo set_m_broadphase(overlappingPairCache)
        softBodyWorldInfo ref_m_sparsesdf Initialize(hashsize:=2383)
        //softBodyWorldInfo ref_m_sparsesdf Reset  // Initialize resets
        softBodyWorldInfo set_air_density(1.2)
        softBodyWorldInfo set_water_density(0)
        softBodyWorldInfo set_water_offset(0)
        softBodyWorldInfo set_water_normal(btVector3 tmp(0,0,0))
        softBodyWorldInfo set_m_gravity(btVector3 tmp(0,-9.81,0))
        //softBodyWorldInfo set_m_gravity(btVector3 tmp(0,0,0))

        shapeBuilder := module ShapeBuilder clone
        shapeBuilder setPhysicsShapes(
            module PhysicsShapes clone
        )
        shapeBuilder setShapeOffsets(
            module ShapeOffsets clone
        )

        setBodyBuilder(module BodyBuilder clone)
        bodyBuilder setDynamicsWorld(dynamicsWorld)
        bodyBuilder setShapeBuilder(shapeBuilder)
    )

    Component setDebugDrawer := method(drawer,
        dynamicsWorld setDebugDrawer(debugDrawer)
    )

    Component setOnTick := method(aBlock,
        scriptWorldMgr setOnTick(dynamicsWorld, block(worldptr, timeStep, aBlock call(timeStep)))
    )

    Component setOnPreTick := method(aBlock,
        scriptWorldMgr setOnPreTick(dynamicsWorld, block(worldptr, timeStep, aBlock call(timeStep)))
    )

    Component onPhysics := method(timeElapsed,
        dynamicsWorld stepSimulation(timeElapsed/1000.0, subframes, fixedTimeStep)
    )

    Component onGraphics := method(timeElapsed,
        // Enable this to see debug lines for all the physics objects.
        // If you suspect a physical object is out of sync with the graphical
        // object, you should enable this.
        //dynamicsWorld debugDrawWorld()
        nil
    )

    Component removeConstraint := method(constraint,
        if( constraint != nil,

            dynamicsWorld removeConstraint(constraint constraint)

            if(constraint attrA != nil, constraint attrA constraintsA remove(constraint))
            if(constraint attrB != nil, constraint attrB constraintsB remove(constraint))

            constraint attrA = nil
            constraint attrB = nil
        )
    )

    Component addConstraint := method(style, attrA, attrB,

        if (attrA == nil and attrB == nil, Exception raise("addConstraint attrA and attrB are both nil; style is " .. style asString))

        constraint := module ConstraintBuilder create(style, attrA, attrB)

        if (constraint == nil,
            return nil
        ,
            dynamicsWorld addConstraint(constraint constraint, style disableLinkedBodyCollisions)

            if(attrA != nil, attrA constraintsA append(constraint))
            if(attrB != nil, attrB constraintsB append(constraint))

            return constraint
        )
    )

    Component addNode := method(node,
        style := node style
        result := bodyBuilder buildBody(style)
        if( result != nil,
            body := result body
            motionState := result anim
            node addAttribute(
                NodeAttribute clone setStyle(style) setRigidBody(body) setMotionState(motionState)
            )
        )
    )

    return Component
)
