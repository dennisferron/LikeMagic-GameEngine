
// This object receives key presses.
// It isn't used in this example, but it is needed
// to pass to createDevice.
events := ScriptedEventReceiver new

// Create an irrlicht device attached to a window.
// In LikeMagic, "CppFunc" is used to access static methods.
device := CppFunc createDevice(
    EDT_OPENGL,                  // 3d driver type
    dimension2du new(800, 600),  // window dimensions
    16,
    false,
    false,
    false,
    events  // event receiver
)

// Most of the 2d features are accessed through the irrlicht driver object.
driver := device getVideoDriver

// Irrlicht uses a funky custom string class for file system paths.
// LikeMagic doesn't have a built-in string conversion for it, but you
// can create the strings manually like this:
fsStr := irrFsStr newFromCStr("Media/IrrlichtExample/2ddemo.png")

// The images object just represents an image file loaded into a texture object.
// (In 3d engines, images are called textures.  Although textures are normally used
// for wrapping a skin on a 3d object, you also use the texture object just to
// hold your 2d graphics image when doing 2d programming.)
images := driver getTexture(fsStr)

// It's common for multiple pieces of game art to be stored in one image file.
// Each piece is sourced from a different 2d rectangle of pixels from the image.
// There are two imp images in the same irrlicht example png as the background image.
// Together, these two images make a simple wing flapping animation.
// These variables actually just store those source rectangle coordinates:
imp1 := recti newWithXYXY(349,15,385,78)
imp2 := recti newWithXYXY(387,15,423,78)

// This sets the transparent color for the background image.  It uses the pixel
// color at (0,0) to represent the transparent color.  If you comment out this
// line, you'll see bright purple everywhere it would normally be transparent.
driver makeColorKeyTextureAtPos(images, vector2di newWithXY(0,0), false)

// Window title, used to show FPS.
title := driver getName .. "  FPS: "

// The frame count is just used to only update FPS every 100 frames.
frames := 0

// This object is required by driver beginScene.
// I don't know what it does.
videoData := SExposedVideoData new

// Time is very important in game loops.
// In this example, it's used to flap the imp's wings.
// The time is number of milliseconds since the game started.
realTime := 0

// In order to use the time variable, you often have to remember the
// last time something happened to see how much time has elapsed.
// We'll use these two lastTimes to control the wing animation state.
lastTime1 := 0
lastTime2 := 0

// This will be the number of milliseconds to delay between flapping wings.
// We'll make the first imp flap his wings really fast, and the second
// imp will flap his wings more slowly.
wingDelay1 := 100
wingDelay2 := 500

// This is where we'll store which animation frame the wings are in.
// The values are just 0 or 1.
wingState1 := 0
wingState2 := 0

// Now for movement.  We'll track the position of one the imps with this:
xpos := 100
ypos := 100

// We also need to track the velocity, to know how much to update the position.
// This velocity will be considered a 60 FPS rate, regardless of graphics
// frame rate.  (More on that later.)
xvel := 5 * Random value + 1
yvel := 5 * Random value + 1

// We'll use the difference between physicsTime and wall clock time to
// keep the physics going at 60 FPS even when the graphics frame rate is different.
physicsTime := device getTimer() getTime()

// Loop until the window is closed.
while(device run,

    // The irrlicht device timer gives us real milliseconds elapsed, which
    // is independent of the game's graphics frame rate.  Note that this isn't
    // time elapsed since last frame, but rather total time elapsed since game start.
    realTime = device getTimer() getTime()

    // OK here's the explanation of how game loops work:
    // We make the assumption the physics movement of the objects goes at 60 FPS, but what
    // happens when the graphics frame rate is not 60 FPS?
    // One way to do it would be to scale the movement (the xvel and yvel variables)
    // according to the elapsed frame time, making bigger jumps if the graphics frame
    // rate is low and tinier jumps if the graphics frame rate is fast.
    // For various reasons, this isn't a good idea.  Suprisingly, it doesn't look very good,
    // but more importantly it kills determinism:  if you take different sized jumps
    // between frames, you can have strange bugs.  For instance you might take a big
    // jump and get stuck in a wall, but only when the graphics frame rate is slow.
    // Instead, what most games do is continue to assume everything is 60 FPS, but
    // if the graphics frame rate is actually slower, simply execute the physics loop
    // more than once, until the physics catches up with real time.
    while(physicsTime < realTime,

        // Each time through the loop advances physics by 1/60th of a second, times 1000 milliseconds.
        physicsTime = physicsTime + 1000*(1/60)

        // Update the position of the moving object.
        xpos = xpos + xvel
        ypos = ypos + yvel

        // Make the object bounce off walls by changing its velocity.
        if(xpos < 0) then(xvel = (xvel abs))
        if(xpos > 800) then(xvel = -(xvel abs))
        if(ypos < 0) then(yvel = (yvel abs))
        if(ypos > 600) then(yvel = -(yvel abs))
    )

    // Now we'll change the wing state if the time delay has passed.
    // Note that we update lastTime when we do this.  wingState toggles between 0 and 1.
    if(realTime-lastTime1 >= wingDelay1) then(lastTime1 = realTime;  wingState1 = (wingState1 + 1) % 2)
    if(realTime-lastTime2 >= wingDelay2) then(lastTime2 = realTime;  wingState2 = (wingState2 + 1) % 2)

    // This begins a frame.  Notably, it also sets the background color.
    driver beginScene(true, true, SColor newWithARGB(255,8,16,35), videoData, nil)

    // Draw a background image.
    driver draw2DImageFromRect(
            images, // source texture
            vector2di newWithXY(50,50), // dest pos
            recti newWithXYXY(0,0,342,224), // src rectangle
            nil, // clip rectangle pointer
            SColor newWithARGB(255,255,255,255), // color
            true); //useAlphaChannelofTexture

    // draw flying imp 1
    driver draw2DImageFromRect(
            images,
            vector2di newWithXY(xpos,ypos),
            if(wingState1 == 0, imp1, imp2),
            nil, // clip rectangle pointer
            SColor newWithARGB(255,255,255,255), // color
            true); //useAlphaChannelofTexture

    // draw flying imp2
    driver draw2DImageFromRect(
            images,
            vector2di newWithXY(270,105),
            if(wingState2 == 0, imp1, imp2),
            nil, // clip rectangle pointer
            SColor newWithARGB(255,255,255,255), // color
            true); //useAlphaChannelofTexture

    // This wraps up the frame.  I assume it also swaps the video pages,
    // if double bufferring is being used.
    driver endScene

    // Display frame rate.
    frames = frames + 1
    if (frames % 100 == 0,
        device setWindowCaption(title .. (driver getFPS asString))

    )
)

// When the window is closed, this does some clean up
// so that you can run another script without a crash.
device drop


