LM := LikeMagic classes

broadphase := LM btDbvtBroadphase new
collisionConfiguration := LM btDefaultCollisionConfiguration new
dispatcher := LM btCollisionDispatcher new(collisionConfiguration)
solver := LM btSequentialImpulseConstraintSolver new

dynamicsWorld := LM btDiscreteDynamicsWorld new(dispatcher,broadphase,solver,collisionConfiguration)
dynamicsWorld setGravity(LM btVector3 new(0,-10,0))

//groundShape := LM btStaticPlaneShape new(LM btVector3 new(0,1,0),1)
groundShape := LM btBoxShape new(LM btVector3 new(1,1,1))


fallShape := LM btSphereShape new(1)

groundQuat := LM btQuaternion new(0,0,0,1)
groundVect := LM btVector3 new(0,-1,0)
groundXform := LM btTransform new(groundQuat, groundVect)
groundMotionState := LM btDefaultMotionState new(groundXform, CppFunc getIdentityTransform)

groundRigidBodyCI := LM btRigidBodyConstructionInfo new(0,groundMotionState,groundShape,LM btVector3 new)

groundRigidBody := LM btRigidBody new(groundRigidBodyCI)

dynamicsWorld addRigidBody(groundRigidBody)

fallXform := LM btTransform new(LM btQuaternion new(0,0,0,1), LM btVector3 new(0,50,0))
fallMotionState := LM btDefaultMotionState new(fallXform, CppFunc getIdentityTransform)
mass := 1
fallInertia := LM btVector3 new
fallShape calculateLocalInertia(mass,fallInertia)
fallRigidBodyCI := LM btRigidBodyConstructionInfo new(mass,fallMotionState,fallShape,fallInertia)
fallRigidBody := LM btRigidBody new(fallRigidBodyCI)
dynamicsWorld addRigidBody(fallRigidBody)

for(i, 0, 300,
    dynamicsWorld stepSimulation(1/60,10,1/60)
    trans := LM btTransform new
    fallRigidBody getMotionState_c() getWorldTransform(trans)
    spherePos := trans getOrigin_c()

    trans := LM btTransform new
    groundRigidBody getMotionState_c() getWorldTransform(trans)
    groundPos := trans getOrigin_c()

    writeln("sphere/ground: ", spherePos getY(), " / ", groundPos getY())
)

dynamicsWorld removeRigidBody(fallRigidBody)
dynamicsWorld removeRigidBody(groundRigidBody)

