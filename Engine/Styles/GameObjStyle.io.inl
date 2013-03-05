method(Constants, Structure, SColor,


    // Inspired by cascading style sheets used in websites, this is "CSS for 3d game objects".

    // Style proto for 3d objects.
    // Creates defaults for all possible object properties.
    // No single object uses all of these properties; different combinations
    // will be used determined by what shape it is (which is itself a property).
    // Note:  Instead of prop ::= value, use setProp(value) in derived styles.
    //
    // Example:  myStyle := GameObjStyle clone prependProto(BallStyle) setPos(10, 20, 30) setColor(200, 100, 50)
    //           engine addObj(myStyle)
    //
    GameObjStyle := Structure clone lexicalDo(

        TAU := Constants TAU
        SColor := SColor // method arg

        none := "none"
        default := "default"
        custom := "custom"

        // Location
        x ::= 0
        y ::= 0
        z ::= 0

        // Set x,y,z all at once
        setPos := method(x, y, z,
            if(x==nil or y==nil or z==nil, Exception raise("GameObjStyle setPos argument cannot be nil!"))
            setX(x) setY(y) setZ(z)
        )

        getPos := method(Object clone do(x := self x; y := self y; z := self z))

        // Velocity
        xv ::= 0
        yv ::= 0
        zv ::= 0

        // Set xv, yv, zv all at once
        setVel := method(xv, yv, zv, setXv(xv) setYv(yv) setZv(zv))

        // Physical properties
        mass ::= 1
        friction ::= 0.5
        restitution ::= default
        margin ::= default

        // Set to true to make the physics body take its position
        // from the irrilicht node.  Collisions from physics objects
        // won't affect it but it will affect other objects.
        isKinematic ::= false

        // Set to true to cause the object never to deactivate.
        // This is important if the object might be moved by means
        // other than something colliding with it.  (Note: isKinematic also disables deactivation.)
        disableDeactivation ::= false

        gravityType := default
        gravityX := nil
        gravityY := nil
        gravityZ := nil
        setGravity := method(x, y, z,
            if(y == nil,
                // setGravity(0) is a synonym for setGravity(none)
                gravityType = if(x==0, none, x); gravityX = nil; gravityY = nil; gravityZ = nil
            ,
                gravityType = "custom"; gravityX = x; gravityY = y; gravityZ = z
            )
            return self
        )

        // 1 gives no damping and 0 is fully damped.
        linDamping ::= 0
        angDamping ::= 0
        setDamping := method(lin, ang, setLinDamping(lin) setAngDamping(ang))

        // Collision properties
        collisionGroup ::= -1 ^ Constants CameraFilter //DefaultFilter
        collisionMask ::= Constants AllFilter
        collisionResponseTag ::= nil

        // Dimensions - sphere/cylinder/cone
        radius ::= 1
        length ::= 1
        closeEnds ::= true  // for cylinder

        // Dimensions - box
        xSize ::= 1
        ySize ::= 1
        zSize ::= 1

        // Set xSize,ySize,zSize all at once
        setSize := method(xSize, ySize, zSize,
            if (ySize == nil,
                setXSize(xSize) setYSize(xSize) setZSize(xSize)
            ,
                setXSize(xSize) setYSize(ySize) setZSize(zSize)
            )
            self
        )

        // Physical shape
        physShape ::= "box"

        // Display shape
        dispShape ::= "box"

        // Set physical and display shape at once.
        setShape := method(s, setPhysShape(s) setDispShape(s))

        // Appearance properties
        color := SColor tmpWithARGB(255, 255, 255, 255)

        // Note:  This method puts alpha last as opposed to SColor which has it first.
        setColor := method(r,g,b,a,
            if(g==nil) then(color=r) elseif(a==nil) then(color = SColor tmpWithARGB(255, r, g, b)) else(color = SColor tmpWithARGB(a, r, g, b))
            return self
        )

        // Map of texture name keys to texture files
        // Generalizes style texture to include more than one in a style,
        // e.g. for things like skybox.
        textureMap ::= nil

        // Set to a file name to load the texture.
        texture := nil
        setTexture := method(value,
            texture = value
            textureMap atPut("primary", value)
            self
        )

        // Change the way TCoords wrap for e.g. cylinder or cone
        alternateTextureWrap ::= false

        // New method of changing texture wrap:  pass a block to execute
        onTextureWrap ::= nil

        // Set one or the other of the following two rotation styles but not both.
        // Yaw, Roll, Pitch are used iff axisX==axisY==axisZ==0.

        // Rotation by axis and angle (better for first person view? might be useful for space ship game -?)
        axisX ::= 0
        axisY ::= 0
        axisZ ::= 0
        angle ::= 0
        setAxis := method(x, y, z, setAxisX(x) setAxisY(y) setAxisZ(z))

        // Rotation by yaw, pitch, roll (better if your frame of reference is outside the object -?)
        yaw ::= 0
        pitch ::= 0
        roll ::= 0

        // Linear factor lets you constrain the object to 0 in X, Y or Z to keep the object on a 2D plane
        // 1 == normal, 0 == force 0
        linFactorX ::= 1
        linFactorY ::= 1
        linFactorZ ::= 1
        setLinearFactor := method(x, y, z, setLinFactorX(x) setLinFactorY(y) setLinFactorZ(z))

        // Angular factor lets you disable certain rotations of the object (useful for 2D game)
        angFactorX ::= 1
        angFactorY ::= 1
        angFactorZ ::= 1
        setAngularFactor := method(x, y, z, setAngFactorX(x) setAngFactorY(y) setAngFactorZ(z))

        // Scale the bullet and irrlicht shapes
        dispScaleX ::= 1
        dispScaleY ::= 1
        dispScaleZ ::= 1
        physScaleX ::= 1
        physScaleY ::= 1
        physScaleZ ::= 1
        setDispScale := method(x,y,z, setDispScaleX(x) setDispScaleY(y) setDispScaleZ(z))
        setPhysScale := method(x,y,z, setPhysScaleX(x) setPhysScaleY(y) setPhysScaleZ(z))
        setScale := method(x,y,z, setDispScale(x,y,z) setPhysScale(x,y,z))

        gameObjType ::= "rigid"

        wireframe ::= false

        // Default is an object is draggable iff it's not static
        isMouseDraggable ::= method(mass != 0)

        // If set to an Irrlicht mesh, display shape will use this mesh instead of the dispshape name.
        // (And if physShape name is "mesh", then physShape will be built from this mesh object.)
        // I will probably remove this field in a future version of the engine, because
        // this field breaks the property of GameObjStyles that they describe 3D objects rather
        // than contain pieces of them (and that propery is desirable e.g. for things like
        // serialization of game objects).
        mesh ::= nil

        init := method(
            setTextureMap(Map clone)
        )
    )
)
