
    LM := LikeMagic classes

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    collisionConfiguration := LM btDefaultCollisionConfiguration new

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher := LM btCollisionDispatcher new(collisionConfiguration)

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache := LM btDbvtBroadphase new()

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver := LM btSequentialImpulseConstraintSolver new

	dynamicsWorld := LM btDiscreteDynamicsWorld new(dispatcher,overlappingPairCache,solver,collisionConfiguration)

	dynamicsWorld setGravity(LM btVector3 new(0,-10,0))

	///create a few basic rigid bodies
	groundShape := LM btBoxShape new(LM btVector3 new(50,50,50))

	groundTransform := LM btTransform new
	groundTransform setIdentity
	groundTransform setOrigin(LM btVector3 new(0,-50,0))

        mass := 0

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		isDynamic := (mass != 0)

		localInertia := LM btVector3 new(0,0,0)
		
        if (isDynamic)
			groundShape calculateLocalInertia(mass,localInertia)

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		myMotionState := LM PhysicsAnimator new(groundTransform, CppFunc getIdentityTransform)
		rbInfo := LM btRigidBodyConstructionInfo new(mass,myMotionState,groundShape,localInertia)
		groundRigidBody := LM btRigidBody new(rbInfo)

		//add the body to the dynamics world
		dynamicsWorld addRigidBody(groundRigidBody)



		//create a dynamic rigidbody

		//btCollisionShape* colShape := LM btBoxShape new(LM btVector3 new(1,1,1))
		colShape := LM btSphereShape new(1)

		/// Create Dynamic Objects
		startTransform := LM btTransform new
		startTransform setIdentity()

		mass := 1

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		isDynamic := (mass != 0)

		localInertia := LM btVector3 new(0,0,0)
		if (isDynamic)
			colShape calculateLocalInertia(mass,localInertia)

		startTransform setOrigin(LM btVector3 new(2,10,0))
	
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		myMotionState := LM PhysicsAnimator new(startTransform, CppFunc getIdentityTransform)
		rbInfo := LM btRigidBodyConstructionInfo new(mass,myMotionState,colShape,localInertia)
		fallRigidBody := LM btRigidBody new(rbInfo)

		dynamicsWorld addRigidBody(fallRigidBody)



/// Do some simulation



	for(i, 0, 200,
		dynamicsWorld stepSimulation(1/60,10,1/60)

        trans := LM btTransform new
        fallRigidBody getMotionState_c() getWorldTransform(trans)
        spherePos := trans getOrigin_c()

        writeln("sphere: ", spherePos getY())

	)


dynamicsWorld removeRigidBody(fallRigidBody)
dynamicsWorld removeRigidBody(groundRigidBody)

