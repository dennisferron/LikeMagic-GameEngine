echo "Windows post-build steps"
copy ..\desteer\bindings\*.dll .
copy ..\LikeMagic\StdBindings\*.dll .
copy ..\GameBindings\*.dll .
copy ..\GameBindings\Deps\irrlicht\bin\Win32-gcc\*.dll .
