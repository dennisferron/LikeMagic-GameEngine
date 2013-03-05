method(ConstraintStyle,

    ConstraintStyles := Module clone lexicalDo(

        SliderStyle := ConstraintStyle clone do(
            setJointType("slider")

            lowerLinLimit ::= 0
            upperLinLimit ::= 0
            lowerAngLimit ::= 0
            upperAngLimit ::= 0

            setLinRange := method(lower, upper, setLowerLinLimit(lower) if(upper == nil, setUpperLinLimit(lower), setUpperLinLimit(upper)))
            setAngRange := method(lower, upper, setLowerAngLimit(lower) if(upper == nil, setUpperAngLimit(lower), setUpperAngLimit(upper)))

            // I'm not really sure what this does, but some code I saw had a comment that seemed to say:
            // If true, use the frame in A as the reference frame for linear limits.
            // If false, use the frame in B as the reference frame for linear limits.
            // Now, what if we're using the B-only form of the constraint, then what does it mean if this is true??
            useLinearReferenceFrameA ::= true

        )

        ConeTwistStyle := ConstraintStyle clone do(
            setJointType("coneTwist")

            swingSpan1 ::= TAU * 0.10
            swingSpan2 ::= TAU * 0.10
            twistSpan ::= TAU * 0.25
            softness ::= 0.8
            biasFactor ::= 0.3
            relaxationFactor ::= 1.0
        )

        HingeStyle := ConstraintStyle clone do(
            setJointType("hinge")

            softness ::= 0.8
            biasFactor ::= 0.3
            relaxationFactor ::= 1.0

            lowerAngLimit ::= 0
            upperAngLimit ::= 0
            setAngRange := method(lower, upper, setLowerAngLimit(lower) if(upper == nil, setUpperAngLimit(lower), setUpperAngLimit(upper)))
            useLinearReferenceFrameA ::= false
        )

        GearStyle := ConstraintStyle clone do(
            setJointType("gear")
            ratio ::= 1.0
        )

        Point2PointStyle := ConstraintStyle clone do(
            setJointType("point2point")
        )

        Generic6DOFStyle := ConstraintStyle clone do(
            setJointType("generic")

            lowerLinLimitX ::= 0
            upperLinLimitX ::= 0
            lowerAngLimitX ::= 0
            upperAngLimitX ::= 0

            lowerLinLimitY ::= 0
            upperLinLimitY ::= 0
            lowerAngLimitY ::= 0
            upperAngLimitY ::= 0

            lowerLinLimitZ ::= 0
            upperLinLimitZ ::= 0
            lowerAngLimitZ ::= 0
            upperAngLimitZ ::= 0


            setLinRange := method(lowerX, upperX, lowerY, upperY, lowerZ, upperZ,

                list(lowerX, upperX, lowerY, upperY, lowerZ, upperZ) foreach(value,
                    if(value == nil, Exception raise("All values must be provided for setLinRange.")))

                setLowerLinLimitX(lowerX) setLowerLinLimitY(lowerY) setLowerLinLimitZ(lowerZ)
                setUpperLinLimitX(upperX) setUpperLinLimitY(upperY) setUpperLinLimitZ(upperZ)
            )

            setAngRange := method(lowerX, upperX, lowerY, upperY, lowerZ, upperZ,

                list(lowerX, upperX, lowerY, upperY, lowerZ, upperZ) foreach(value,
                    if(value == nil, Exception raise("All values must be provided for setAngRange.")))

                setLowerAngLimitX(lowerX) setLowerAngLimitY(lowerY) setLowerAngLimitZ(lowerZ)
                setUpperAngLimitX(upperX) setUpperAngLimitY(upperY) setUpperAngLimitZ(upperZ)
            )

            // I'm not really sure what this does, but some code I saw had a comment that seemed to say:
            // If true, use the frame in A as the reference frame for linear limits.
            // If false, use the frame in B as the reference frame for linear limits.
            // Now, what if we're using the B-only form of the constraint, then what does it mean if this is true??
            useLinearReferenceFrameA ::= true

        )

        Generic6DOFSpringStyle := Generic6DOFStyle clone do(
            setJointType("genericSpring")

            springProperty := Object clone do(
                enabled ::= true
                stiffness ::= 5
                damping ::= 0.9
            )

            // Default ranges so you know it's a spring
            setLinRange(-0.1,0.1,  -0.1,0.1,  -0.1,0.1)
            setAngRange(-TAU/10,TAU/10,  -TAU/10,TAU/10,  -TAU/10,TAU/10)

            transX := springProperty clone
            transY := springProperty clone
            transZ := springProperty clone
            rotX := springProperty clone
            rotY := springProperty clone
            rotZ := springProperty clone
        )

        // A "constraint" with no limitations, so it disables collisions
        // between the linked bodies without constraining their motion.
        DisableCollisionStyle := Generic6DOFStyle clone do(
            setDisableLinkedBodyCollisions(true)
            setLinRange(1,0, 1,0, 1,0)
            setAngRange(1,0, 1,0, 1,0)
            setDebugDrawSize(0)
        )

    )
)
