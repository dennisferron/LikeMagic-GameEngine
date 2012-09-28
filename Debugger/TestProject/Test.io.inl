
testA := "AAA"
testB := 2
testC := Object clone

m := method(
    writeln("in method 1")
    writeln("in method 2")
    writeln("in method 3")
)

writeln("one")
writeln("two")
m()
writeln("three")
writeln("four")
m()
writeln("five")
writeln("six")
