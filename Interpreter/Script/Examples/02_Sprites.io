
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
time := 0

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

// Loop until the window is closed.
while(device run,

    // The irrlicht device timer gives us real milliseconds elapsed, which
    // is independent of the game's graphics frame rate.  Note that this isn't
    // time elapsed since last frame, but rather total time elapsed since game start.
    time = device getTimer() getTime()

    // Now we'll change the wing state if the time delay has passed.
    // Note that we update lastTime when we do this.  wingState toggles between 0 and 1.
    if(time-lastTime1 >= wingDelay1) then(lastTime1 = time;  wingState1 = (wingState1 + 1) % 2)
    if(time-lastTime2 >= wingDelay2) then(lastTime2 = time;  wingState2 = (wingState2 + 1) % 2)

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
            vector2di newWithXY(164,125),
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


