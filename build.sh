../emsdk/upstream/emscripten/emcc -o GeorgesDay.js main.c GenerateMap.c -sSTACK_SIZE=5MB -sEXIT_RUNTIME=1 -sEXPORTED_FUNCTIONS=_showRoom,_initiateGame -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --js-library library.js -DJS    

rm georges.day
gcc -o GeorgesDay main.c GenerateMap.c                                                        