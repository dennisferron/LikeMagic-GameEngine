#!/bin/bash
find ./obj/Debug/Source -type f \( -name "*.o" -o -name "*.a" -o -name "*.exe" -o -name "*.dll" \) -fprintf filesizes.txt '%CY %Cm %Cd %CH:%CM\t%s\t%f\t%h\t<null>\n'
# Then use SqliteStudio to CSV import filesizes.txt with tab delimts and Null = "<null>"
# Finally use update statement to set Build FK where build is null