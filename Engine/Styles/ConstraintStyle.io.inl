method(Constants, MountStyle, LinkStyle,

    ConstraintStyle := LinkStyle clone lexicalDo(

        TAU := Constants TAU

        // Mount styles.  If the constraint is mounted "to the world" then set mountA to nil.
        mountA ::= MountStyle clone
        mountB ::= MountStyle clone

        jointType ::= "none"

        damping ::= "none"

        // Set to true if you don't want the joined bodies to collide.
        disableLinkedBodyCollisions ::= false

        // how big to draw the constraint debug wireframe
        debugDrawSize ::= 1
    )

    ConstraintStyle init := method(
        setMountA(mountA clone)
        setMountB(mountB clone)
        self
    )

    return ConstraintStyle
)
