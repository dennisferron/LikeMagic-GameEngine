
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

// Loop until the window is closed.
while(device run,

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


