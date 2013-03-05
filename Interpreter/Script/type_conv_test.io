LM := LikeMagic classes

for( c, 0, 10,
    v := LM btVector3 new(1, 2, 3)
    v delete
    s := LM irrFsStr newFromCStr("hello!")
    s delete
    a := LM ArrayOfVector3df new
    for (i, 1, 10,
        v = LM vector3df new(i, i, i)
        a push_back(v)
    )
    t := 0
    for (i, 1, 10,
        t = t + a[i-1] get_X
    )
    a delete
    writeln(c, ": ", t)
)
