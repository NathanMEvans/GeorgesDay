#include "../Structs.c"    


struct Exit* generateExits() {
static struct Exit exits[256] = {
{"Wake up","You wake up in a big bed",0},
{"Go to hallway","You walk into the hallway",1},
{"Go to bedroom","You walk into the bedroom",0},
{"Exit house","You put on your lead and walk into the street",2},
{"Go to living room","You walk into the living room",3},
{"Go to the kitchen","You walk into the kitchen",4},
{"Go to the study","You walk into the study",5},
{"Walk to little park","You walk into the little park",6},
{"Walk to big park","You walk to the big park",7},
{"Go to the forest","You run into the forest",8},
{"Go to the green","You run to the green",9},
{"Go to the street","You walk back to the street",2},
{"Go home","You go back home",1}
};
return exits;
}
