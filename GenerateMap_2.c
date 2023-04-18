#include "GenerateMap.h"
#include "MapC/exits.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NOTODO 255
#define THIS_ROOM 255
#define HELD_ACTIVITY 254
#define NO_HELD_ACTIVITY 255

struct Game generateMap() {
   struct Game game = {
     { // rooms
        {"Bedroom","A cosy bedroom with a big bed and a dog bed",1,3,{1},{0,1,7}},					// 0
        {"Hallway","A long hallway with a hard wood floor",3,1,{2,4,6},{2}},						// 1
        {"Street","Terraced houses go along the steep street",3,0,{7,8,12},{}},						// 2
        {"Living room","A room with a big sofa. There’s a dog bed on the floor and a tv on the wall",2,2,{1,5},{3,10}},	// 3
        {"Kitchen","Lot’s of food on the sides. There’s two dog bowls on the floor",1,2,{4},{4,5}},			// 4
        {"Study","Two desks with computers and a big comfy sofa",1,0,{1},{}},						// 5
        {"Little park","A small park with lots of climbing frames",1,0,{11},{}},					// 6
        {"Big park","A large park with trees and hills",2,0,{9,10},{}},							// 7
        {"Forest","A forest with lots of fallen down trees and muddy patches",2,1,{10,11},{15}},			// 8
        {"Green","An old bowling green",2,1,{9,11},{12}},								// 9
        {"Armstrong park","A long park with a few different paths through",0,0,{},{}},					// 10
        {"Jesmond dene","A long park with a river running through it",0,0,{},{}},					// 11
     }, // rooms
     0,
     { // activities
        {"Dog bed","You sleep for an hour",0,1,{},{0,THIS_ROOM},NOTODO},		// 0
        {"Big bed","You sleep for an hour",0,1,{},{1,THIS_ROOM},NOTODO},		// 1
        {"Front door","You bark at the front door",1,0,{3},{},NOTODO},			// 2
        {"TV","There is no dog on the TV",0,0,{},{},NOTODO},				// 3
        {"Water bowl","Slurp Slurp Slurp Slurp Slurp",0,0,{},{},1}, 			// 4
        {"Food bowl","You bark at the empty bowl",0,1,{},{6,THIS_ROOM},NOTODO},		// 5
        {"Food bowl","Chomp Chomp Chomp Chomp Chomp",0,1,{},{5,THIS_ROOM},0},		// 6
        {"Laundry basket","You find a sock",0,1,{},{8,HELD_ACTIVITY},2},		// 7
        {"Put down socks","You put down the socks",0,1,{},{9,THIS_ROOM},NOTODO},	// 8
        {"Socks","You pick up the socks",0,1,{},{8,HELD_ACTIVITY},NOTODO},		// 9
        {"Ball","You pick up the ball",0,1,{},{11,HELD_ACTIVITY},NOTODO},		// 10
        {"Put down ball","You drop the ball",0,1,{},{10,THIS_ROOM},NOTODO},		// 11
        {"Long grass","Smells like wee",0,1,{},{13,THIS_ROOM},NOTODO},			// 12
	{"Wee on long grass","It's your park now",0,1,{},{14,THIS_ROOM},3},		// 13
        {"Long grass","Smells like your wee",0,1,{},{14,THIS_ROOM},NOTODO},		// 14
        {"Bushes","You find a football",0,1,{},{16,HELD_ACTIVITY},NOTODO},		//15
        {"Drop football","You leave the footbll for your dad to pick up",0,1,{},{17,6},NOTODO},//16
        {"Chase football","Your dad kicks the football and you chase it",0,1,{},{16,HELD_ACTIVITY},4},//17
     }, // activities
     0,
     { // exits
        {"Wake up","You wake up in a big bed",0},			// 0
        {"Go to hallway","You walk into the hallway",1},		// 1
        {"Go to bedroom","You walk into the bedroom",0},		// 2
        {"Exit house","You put on your lead and walk into the street",2},//3
        {"Go to living room","You walk into the living room",3},	// 4
        {"Go to the kitchen","You walk into the kitchen",4},		// 5
        {"Go to the study","You walk into the study",5},		// 6
        {"Walk to little park","You walk into the little park",6},	// 7
        {"Walk to big park","You walk to the big park",7},		// 8
        {"Go to the forest","You run into the forest",8},		// 9
        {"Go to the green","You run to the green",9},			// 10
        {"Go to the street","You walk back to the street",2},		// 11
        {"Go home","You go back home",1}				// 12
     }, // exits
     0,
     { // todos
	{"Breakfast",0},	// 0
        {"Slurps",0},		// 1
        {"Steal socks",0},	// 2
        {"Claim bushes",0},	// 3
        {"Play football",0},	// 4
     }, // todos
     5,
     {}, // messages
     0,
     0,
     NO_HELD_ACTIVITY,
     7,
     0
   };
   
   return game;
}
