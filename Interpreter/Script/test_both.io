
w := dimension2du clone do( set(800, 600) )

events := ScriptedEventReceiver new

device := CppFunc createDevice(EDT_OPENGL, w, 16, false, false, false, events)
//device := CppFunc createDevice(EDT_DIRECT3D9, w, 16, false, false, false, nil)
//device := CppFunc createDevice(EDT_BURNINGSVIDEO, w, 16, false, false, false, nil)

//device setWindowCaption("Test Title Change")

driver := device getVideoDriver

//mat2d := driver getMaterial2D
//texture := mat2d get_TextureLayer(0)
//texture set_BilinearFilter(true)


//fsStr := irrFsStr newFromCStr("Media/2ddemo.png")
//images := driver getTexture(fsStr)
//driver makeColorKeyTextureAtPos(images, vector2di newWithXY(0,0), false)

videoData := SExposedVideoData new

imp1 := recti newWithXYXY(349,15,385,78)
imp2 := recti newWithXYXY(387,15,423,78)

//driver getMaterial2D set_AntiAliasing(EAAM_FULL_BASIC)

smgr   := device getSceneManager

cameraNode := smgr addCameraSceneNode(
    nil, // parent
    vector3df newWithXYZ(0, 0, -200), // position
    vector3df newWithXYZ(0, 0, 0), // lookat
    -1, // id
    true  // makeActive
)

//smgr addCameraSceneNodeFPS(nil, 100, 0.005, -1, nil, 0, false, 0.010, false, true)

geometry := smgr getGeometryCreator

wallMesh :=  geometry createCylinderMesh(
    10, // radius
    1000, // length
    16, // tessellation (number of quads around)
    SColor newWithARGB(255, 200, 60, 240), // color
    false, // closeTop
    0 // oblique
)

wallNode1 := smgr addMeshSceneNode(
    wallMesh,  // mesh
    nil,        // parent
    -1,         // id
    vector3df newWithXYZ(-120,-120,0),    // position
    vector3df clone,    // rotation
    vector3df newWithXYZ(1,1,1), // scale
    false  // alsoAddIfMeshPointerZero
)

wallNode2 := smgr addMeshSceneNode(
    wallMesh,  // mesh
    nil,        // parent
    -1,         // id
    vector3df newWithXYZ(120,-120,0),    // position
    vector3df clone,    // rotation
    vector3df newWithXYZ(1,1,1), // scale
    false  // alsoAddIfMeshPointerZero
)

wallNode1 setMaterialFlag(EMF_LIGHTING, true)
wallNode2 setMaterialFlag(EMF_LIGHTING, true)

ballMesh := geometry createSphereMesh(
    2, // radius
    16, // polyCountX
    16 // polyCountY
)

ballNode := smgr addMeshSceneNode(
    ballMesh,  // mesh
    nil,        // parent
    -1,         // id
    vector3df newWithXYZ(60,30,0),    // position
    vector3df clone,    // rotation
    vector3df newWithXYZ(1,1,1), // scale
    false  // alsoAddIfMeshPointerZero
)

ballNode setMaterialFlag(EMF_LIGHTING, true)


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

// Gravity in feet per second per second
dynamicsWorld setGravity(LM btVector3 new(0,-32.174,0))

///create a few basic rigid bodies
groundShape := LM btBoxShape new(LM btVector3 new(5,5,5))

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
groundMotionState := LM PhysicsAnimator new(groundTransform, CppFunc getIdentityTransform)
rbInfo := LM btRigidBodyConstructionInfo new(mass,groundMotionState,groundShape,localInertia)
groundRigidBody := LM btRigidBody new(rbInfo)

//add the body to the dynamics world
dynamicsWorld addRigidBody(groundRigidBody)

groundMesh := geometry createCubeMesh(
    vector3df new(10, 10, 10)
)
groundNode := smgr addMeshSceneNode(
    groundMesh,  // mesh
    nil,        // parent
    -1,         // id
    vector3df new(0),    // position
    vector3df new,    // rotation
    vector3df new(1), // scale
    false  // alsoAddIfMeshPointerZero
)
groundNode addAnimator(groundMotionState)


//create a dynamic rigidbody

//btCollisionShape* colShape := LM btBoxShape new(LM btVector3 new(1,1,1))
colShape := LM btSphereShape new(2)

/// Create Dynamic Objects
startTransform := LM btTransform new
startTransform setIdentity()

mass := 1

//rigidbody is dynamic if and only if mass is non zero, otherwise static
isDynamic := (mass != 0)

localInertia := LM btVector3 new(0,0,0)
if (isDynamic)
        colShape calculateLocalInertia(mass,localInertia)

startTransform setOrigin(LM btVector3 new(0,50,0))

//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
ballMotionState := LM PhysicsAnimator new(startTransform, CppFunc getIdentityTransform)
rbInfo := LM btRigidBodyConstructionInfo new(mass, ballMotionState, colShape, localInertia)
fallRigidBody := LM btRigidBody new(rbInfo)

dynamicsWorld addRigidBody(fallRigidBody)


ballNode addAnimator(ballMotionState)


smgr addLightSceneNode(
    nil, // parent
    vector3df newWithXYZ(0, 0, -2000), // position
    SColorf newWithRGBA(1,1,1,1), // color
    1000, // radius
    -1 // id
)


title := driver getName .. "  FPS: "
frames := 0
time := 0
lasttime := 0
playerX := 0
playerY := 0
playerXV := 0
playerYV := 0
cameraY := 0
cameraZ := 0
cameraLookY := 0
while(device run,

    lasttime = time
    time = device getTimer() getTime()

    dynamicsWorld stepSimulation((time-lasttime)/1000,10,1/60)

    trans := LM btTransform new
    fallRigidBody getMotionState_c() getWorldTransform(trans)
    spherePos := trans getOrigin_c()

    //writeln("sphere: ", spherePos getY())

    if (events IsKeyDown(KEY_LEFT), playerXV = -3)
    if (events IsKeyDown(KEY_RIGHT), playerXV = 3)
    
    if (events IsKeyDown(KEY_UP), playerYV = 4)
    //if (events IsKeyDown(KEY_DOWN), playerY = playerY - 1)

    if (playerXV > 0, playerXV = playerXV - 0.05)
    if (playerXV < 0, playerXV = playerXV + 0.05)

    if (playerX < -100, playerXV = 3.5)
    if (playerX > 100, playerXV = -3.5)

    playerX = playerX + playerXV

    playerYV = playerYV - 0.1
    playerY = playerY + playerYV
    if (playerY < -100, playerY = -100; playerYV = 0)

    cameraYAdj := 0.5*(playerYV abs)

    targetY := playerY
    if (playerYV < 0 and cameraY < playerY, targetY = playerY + -10*playerYV; cameraYAdj = 2*playerYV abs)

    if (cameraY < targetY, cameraY = cameraY + cameraYAdj)
    if (cameraY > targetY, cameraY = cameraY - cameraYAdj)

    cameraZAdj := 0.5*(playerYV abs)

    if (cameraZ + 5 < (2*playerYV abs), cameraZ = cameraZ + cameraZAdj)
    if (cameraZ - 5 > (2*playerYV abs), cameraZ = cameraZ - cameraZAdj)

    cameraLookAdj := 0.5 + (playerYV abs)
    targetLookY := (cameraY + playerY)/2 + 200*playerYV
    if (cameraLookY < targetLookY, cameraLookY = cameraLookY + cameraLookAdj)
    if (cameraLookY > targetLookY, cameraLookY = cameraLookY - cameraLookAdj)

    cameraNode setPosition(vector3df newWithXYZ(0, 0, -150))
    cameraNode setTarget(vector3df newWithXYZ(0, 0, 0))

    driver beginScene(true, true, SColor newWithARGB(255,8,16,35), videoData, nil)

    smgr drawAll

    driver endScene

    // Set window caption should no longer act strange with the fixed string conversions in LikeMagic.
    frames = frames + 1
    if (frames % 100 == 0,
        device setWindowCaption(title .. (driver getFPS asString))

    )
)

device drop

dynamicsWorld removeRigidBody(fallRigidBody)
dynamicsWorld removeRigidBody(groundRigidBody)

