
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


fsStr := irrFsStr newFromCStr("Media/2ddemo.png")
images := driver getTexture(fsStr)
driver makeColorKeyTextureAtPos(images, vector2di newWithXY(0,0), false)

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
    8, // radius
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
playerX := 0
playerY := 0
playerXV := 0
playerYV := 0
cameraY := 0
cameraZ := 0
cameraLookY := 0
while(device run,

    time = device getTimer() getTime()

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

    ballNode setPosition(vector3df newWithXYZ(playerX, playerY, 0))

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

    cameraNode setPosition(vector3df newWithXYZ(0, cameraY, -150 - cameraZ))
    cameraNode setTarget(vector3df newWithXYZ(playerX/2, cameraLookY, 0))

    driver beginScene(true, true, SColor newWithARGB(255,8,16,35), videoData, nil)

    // draw background
    driver draw2DImageFromRect(
            images, // source texture
            vector2di newWithXY(50,50), // dest pos
            recti newWithXYXY(0,0,342,224), // src rectangle
            nil, // clip rectangle pointer
            SColor newWithARGB(255,255,255,255), // color
            true); //useAlphaChannelofTexture

    // draw flying imp
    driver draw2DImageFromRect(
            images,
            vector2di newWithXY(164,125),
            if( (time/500) % 2 < 1, imp1, imp2),
            nil, // clip rectangle pointer
            SColor newWithARGB(255,255,255,255), // color
            true); //useAlphaChannelofTexture

    smgr drawAll

    // draw second flying imp with colorcylce
    driver draw2DImageFromRect(
            images,
            vector2di newWithXY(270,105),
            if( (time/100) % 2 < 1, imp1, imp2),
            nil, // clip rectangle pointer
            SColor newWithARGB(255,255,255,255), // color
            true); //useAlphaChannelofTexture

    driver endScene

    // Set window caption should no longer act strange with the fixed string conversions in LikeMagic.
    frames = frames + 1
    if (frames % 100 == 0,
        device setWindowCaption(title .. (driver getFPS asString))

    )
)

device drop


