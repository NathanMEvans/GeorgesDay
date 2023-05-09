#include "GenerateMap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOTODO 255
#define THIS_ROOM 255
#define HELD_ACTIVITY 254
#define NO_HELD_ACTIVITY 255

struct Game generateMap()
{
  struct Game game = {
      .rooms = {
          {.title = "Bedroom", // 0
           .description = "A cosy bedroom with a big bed and a dog bed",
           .n_exits = 1,
           .n_activities = 4,
           .exits = {
               {.exit = 1, .time = {0, 24}} // Hallway
           },
           .activities = {
               {.activity = 0, .time = {0, 24}},  // Dog bed
               {.activity = 1, .time = {20, 24}}, // Big bed
               {.activity = 7, .time = {0, 24}},  // Laundry basket
               {.activity = 19, .time = {0, 24}}  // Cupboard
           }},
          {.title = "Hallway", // 1
           .description = "A long hallway with a hard wood floor",
           .n_exits = 3,
           .n_activities = 1,
           .exits = {
               {.exit = 2, .time = {0, 24}}, // Bedroom
               {.exit = 4, .time = {0, 24}}, // Living room
               {.exit = 6, .time = {0, 24}}  // Study
           },
           .activities = {
               {.activity = 2, .time = {0, 24}} // Front door
           }},
          {.title = "Street", // 2
           .description = "Terraced houses go along the steep street",
           .n_exits = 3,
           .n_activities = 3,
           .exits = {
               {.exit = 7, .time = {11, 14}}, // little park
               {.exit = 8, .time = {0, 24}},  // big park
               {.exit = 12, .time = {0, 24}}  // home
           },
           .activities = {
               {.activity = 26, .time = {0, 11}},  // little park closed
               {.activity = 26, .time = {14, 24}}, // little park closed
               {.activity = 29, .time = {0, 24}},  // look for sticks, ok
           }},
          {.title = "Living room", // 3
           .description = "A room with a big sofa. There’s a dog bed on the floor and a tv on the wall",
           .n_exits = 2,
           .n_activities = 4,
           .exits = {{.exit = 1, .time = {0, 24}}, {.exit = 5, .time = {0, 24}}},
           .activities = {
               {.activity = 3, .time = {0, 19}},  // tv no dog
               {.activity = 3, .time = {20, 24}}, // tv no dog
               {.activity = 10, .time = {0, 24}}, // ball
               {.activity = 18, .time = {19, 20}} // tv dog
           }},
          {.title = "Kitchen", // 4
           .description = "Lot’s of food on the sides. There’s two dog bowls on the floor",
           .n_exits = 1,
           .n_activities = 4,
           .exits = {
               {.exit = 4, .time = {0, 24}} // living room
           },
           .activities = {
               {.activity = 4, .time = {0, 12}},   // water bowl morning
               {.activity = 23, .time = {12, 18}}, // water bowl day
               {.activity = 24, .time = {18, 24}}, // water bowl evening
               {.activity = 5, .time = {0, 24}},   // food bowl
               {.activity = 27, .time = {0, 24}}   // back door
           }},
          {.title = "Study", // 5
           .description = "Two desks with computers and a big comfy sofa",
           .n_exits = 1,
           .n_activities = 0,
           .exits = {{.exit = 1, .time = {0, 24}}},
           .activities = {}},
          {.title = "Little park", // 6
           .description = "A small park with lots of climbing frames",
           .n_exits = 1,
           .n_activities = 1,
           .exits = {{.exit = 11, .time = {0, 24}}},
           .activities = {
               {.activity = 33, .time = {0, 24}}, // look for sticks, great
           }},
          {.title = "Big park", // 7
           .description = "A large park with trees and hills",
           .n_exits = 2,
           .n_activities = 1,
           .exits = {{.exit = 9, .time = {0, 24}}, {.exit = 10, .time = {0, 24}}},
           .activities = {
               {.activity = 33, .time = {0, 24}}, // look for sticks, great
           }},
          {.title = "Forest", // 8
           .description = "A forest with lots of fallen down trees and muddy patches",
           .n_exits = 2,
           .n_activities = 2,
           .exits = {{.exit = 10, .time = {0, 24}}, {.exit = 11, .time = {0, 24}}},
           .activities = {
               {.activity = 15, .time = {0, 24}}, // bushes
               {.activity = 34, .time = {0, 24}}, // look for sticks, best
           }},
          {.title = "Green", // 9
           .description = "An old bowling green",
           .n_exits = 3,
           .n_activities = 2,
           .exits = {
               {.exit = 9, .time = {0, 24}}, {.exit = 11, .time = {0, 24}}, {.exit = 13, .time = {0, 24}} // Armstrong park
           },
           .activities = {
               {.activity = 12, .time = {0, 24}}, // long grass
               {.activity = 33, .time = {0, 24}}, // look for sticks, great
           }},
          {.title = "Armstrong park", // 10
           .description = "A long park with a few different paths through",
           .n_exits = 2,
           .n_activities = 1,
           .exits = {
               {.exit = 14, .time = {0, 24}}, // Jesmond Dene
               {.exit = 16, .time = {0, 24}}  // Green
           },
           .activities = {
               {.activity = 32, .time = {0, 24}}, // look for sticks, good
           }},
          {.title = "Jesmond Dene", // 11
           .description = "A long park with a river running through it",
           .n_exits = 1,
           .n_activities = 3,
           .exits = {
               {.exit = 15, .time = {0, 24}}, // Armstrong park
           },
           .activities = {
               {.activity = 35, .time = {0, 24}}, // Goats
               {.activity = 36, .time = {0, 24}}, // River
               {.activity = 37, .time = {0, 24}}, // Poodle
           }},
      }, // rooms
      .n_rooms = 0,
      .activities = {
          {.title = "Dog bed", // 0
           .description = "You sleep for an hour",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 60,
           .drop = 0},
          {.title = "Big bed", // 1
           .description = "You sleep for an hour",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 60,
           .drop = 0},
          {.title = "Front door", // 2
           .description = "You bark at the front door",
           .n_exits = 1,
           .n_activities = 0,
           .exits = {{.exit = {.exit = 3, .time = {0, 24}}, THIS_ROOM}},
           .activities = {},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "TV", // 3
           .description = "There is no dog on the TV",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Water bowl", // 4
           .description = "Slurp Slurp Slurp Slurp Slurp",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = 4,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Food bowl", // 5
           .description = "You bark at the empty bowl",
           .n_exits = 0,
           .n_activities = 4,
           .exits = {},
           .activities = {
               {.activity = {.activity = 6, .time = {7, 12}}, .room = THIS_ROOM},   // Breakfast
               {.activity = {.activity = 20, .time = {12, 16}}, .room = THIS_ROOM}, // Lunch
               {.activity = {.activity = 21, .time = {16, 20}}, .room = THIS_ROOM}, // Dinner
               {.activity = {.activity = 22, .time = {20, 22}}, .room = THIS_ROOM}, // Tea
           },
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Food bowl", // 6
           .description = "Chomp Chomp Chomp Chomp Chomp",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 23, .time = {7, 12}}, .room = THIS_ROOM}},
           .todo = 0,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Laundry basket", // 7
           .description = "You find a sock",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 8, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = 6,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Put down socks", // 8
           .description = "You put down the socks",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 9, .time = {0, 24}}, .room = THIS_ROOM}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Socks", // 9
           .description = "You pick up the socks",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 8, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Ball", // 10
           .description = "You pick up the ball",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 11, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Put down ball", // 11
           .description = "You drop the ball",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 10, .time = {0, 24}}, .room = THIS_ROOM}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Long grass", // 12
           .description = "Smells like wee",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 13, .time = {0, 24}}, .room = THIS_ROOM}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Wee on long grass", // 13
           .description = "It's your park now",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 14, .time = {0, 24}}, .room = THIS_ROOM}},
           .todo = 7,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Long grass", // 14
           .description = "Smells like your wee",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Bushes", // 15
           .description = "You find a football",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 16, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Drop football", // 16
           .description = "You leave the footbll for your dad to pick up",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 17, .time = {0, 24}}, .room = 6}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Chase football", // 17
           .description = "Your dad kicks the football and you chase it",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 16, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = 8,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "TV", // 18
           .description = "There is a dog on the TV, they're acting",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Cupboard", // 19
           .description = "You can't get into the cupboard",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Food bowl", // 20
           .description = "Chomp Chomp Chomp Chomp Chomp",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 23, .time = {12, 16}}, .room = THIS_ROOM}},
           .todo = 1,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Food bowl", // 21
           .description = "Chomp Chomp Chomp Chomp Chomp",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 23, .time = {16, 20}}, .room = THIS_ROOM}},
           .todo = 2,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Food bowl", // 22
           .description = "Chomp Chomp Chomp Chomp Chomp",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 23, .time = {20, 22}}, .room = THIS_ROOM}},
           .todo = 3,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Food bowl", // 23
           .description = "There's no food left",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Water bowl", // 24
           .description = "Slurp Slurp Slurp Slurp Slurp",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Water bowl", // 25
           .description = "Slurp Slurp Slurp Slurp Slurp",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = 5,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 1},
          {.title = "Walk to little park", // 26
           .description = "Not now, we'll play some football at lunch",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 0,
           .drop = 0},
          {.title = "Back door", // 27
           .description = "You whine for the back door to be open",
           .n_exits = 1,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 28, .time = {7, 12}}, .room = THIS_ROOM}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Sniff the fresh morning air", // 28
           .description = "Smells real good",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 10,
           .drop = 0},
          {.title = "Look for sticks", // 29
           .description = "You found an ok stick",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 30, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 10,
           .drop = 1},
          {.title = "Drop stick", // 30
           .description = "You put down the stick",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 31, .time = {0, 24}}, .room = THIS_ROOM}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Stick", // 31
           .description = "You pick up the stick",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 30, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 5,
           .drop = 0},
          {.title = "Look for sticks", // 32
           .description = "You found a good stick",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 30, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 10,
           .drop = 1},
          {.title = "Look for sticks", // 33
           .description = "You found a great stick",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 30, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = NOTODO,
           .keep = 0,
           .minutesTaken = 10,
           .drop = 1},
          {.title = "Look for sticks", // 34
           .description = "You found the best stick",
           .n_exits = 0,
           .n_activities = 1,
           .exits = {},
           .activities = {{.activity = {.activity = 30, .time = {0, 24}}, .room = HELD_ACTIVITY}},
           .todo = 9,
           .keep = 0,
           .minutesTaken = 10,
           .drop = 1},
          {.title = "Go see the goats", // 35
           .description = "There's some weird looking dogs",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 10,
           .drop = 0},
          {.title = "Swim in the river", // 36
           .description = "Splish splash",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 10,
           .drop = 0},
          {.title = "Look for other dogs", // 37
           .description = "You find a big poodle",
           .n_exits = 0,
           .n_activities = 0,
           .exits = {},
           .activities = {},
           .todo = NOTODO,
           .keep = 1,
           .minutesTaken = 10,
           .drop = 0},

      }, // activities
      .n_activities = 0,
      .exits = {
          // exits
          {.title = "Wake up", // 0
           .description = "You wake up in a big bed",
           .room = 0},
          {.title = "Go to hallway", // 1
           .description = "You walk into the hallway",
           .room = 1},
          {.title = "Go to bedroom", // 2
           .description = "You walk into the bedroom",
           .room = 0},
          {.title = "Exit house", // 3
           .description = "You put on your lead and walk into the street",
           .room = 2},
          {.title = "Go to living room", // 4
           .description = "You walk into the living room",
           .room = 3},
          {.title = "Go to the kitchen", // 5
           .description = "You walk into the kitchen",
           .room = 4},
          {.title = "Go to the study", // 6
           .description = "You walk into the study",
           .room = 5},
          {.title = "Walk to little park", // 7
           .description = "You walk into the little park",
           .room = 6},
          {.title = "Walk to big park", // 8
           .description = "You walk to the big park",
           .room = 7},
          {.title = "Go to the forest", // 9
           .description = "You run into the forest",
           .room = 8},
          {.title = "Go to the green", // 10
           .description = "You run to the green",
           .room = 9},
          {.title = "Go to the street", // 11
           .description = "You walk back to the street",
           .room = 2},
          {.title = "Go home", // 12
           .description = "You go back home",
           .room = 1},
          {.title = "Cross the road", // 13
           .description = "You go across the road to Armstrong park",
           .room = 10},
          {.title = "Cross the bridge", // 14
           .description = "You go across the bridge into Jesmond Dene",
           .room = 11},
          {.title = "Cross the bridge", // 15
           .description = "You go across the bridge into Armstrong park",
           .room = 10},
          {.title = "Cross the road", // 16
           .description = "You cross the road back to big park",
           .room = 7},
      }, // exits
      .n_exits = 0,
      .todos = {
          // todos
          {"Breakfast", 0},       // 0
          {"Lunch", 0},           // 1
          {"Dinner", 0},          // 2
          {"Tea", 0},             // 3
          {"Morning slurps", 0},  // 4
          {"Evening slurps", 0},  // 5
          {"Steal socks", 0},     // 6
          {"Claim park", 0},      // 7
          {"Play football", 0},   // 8
          {"Find best stick", 0}, // 9
      },                          // todos
      .n_todos = 10,
      .messages = {}, // messages
      .n_messages = 0,
      .currentRoom = 0,
      .heldActivity = NO_HELD_ACTIVITY,
      .hours = 7,
      .minutes = 0};

  return game;
}
