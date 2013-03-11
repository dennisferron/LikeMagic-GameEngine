
a := method(msg,
    b(msg)
)

b := method(msg,
    Exception raise(msg)
)

c := method(msg,
    d(msg)
)

d := method(msg,
    Exception raise(msg)
)

try(
    a("hello")
)

try(
    c("goodbye")
)

a("hello2")
