method(

    // Constraints have one or two mount points.
    MountStyle := Object clone lexicalDo(

        // Location (relative to the rigid body)
        x ::= 0
        y ::= 0
        z ::= 0

        // Set x,y,z all at once
        setPos := method(x, y, z,
            if(x==nil or y==nil or z==nil, Exception raise("mount setPos argument cannot be nil!"))
            setX(x) setY(y) setZ(z)
        )

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
    )
)
