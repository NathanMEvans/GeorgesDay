gcc -o GeorgesDay main.c GenerateMap.c
../emsdk/upstream/emscripten/emcc -o GeorgesDay.html  main.c GenerateMap_2.c  -sSTACK_SIZE=5MB -sEXIT_RUNTIME=1 -sEXPORTED_FUNCTIONS=_showRoom,_initiateGame -sEXPORTED_RUNTIME_METHODS=ccall,cwrap

../emsdk/upstream/emscripten/emcc -o GeorgesDay.html  main.c GenerateMap_2.c  -sSTACK_SIZE=5MB -sEXIT_RUNTIME=1 -sEXPORTED_FUNCTIONS=_showRoom,_initiateGame -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --js-library library.js -DJS                 

