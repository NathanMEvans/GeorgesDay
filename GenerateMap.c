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
           .n_activities = 0,
           .exits = {{.exit = 7, .time = {0, 24}}, {.exit = 8, .time = {0, 24}}, {.exit = 12, .time = {0, 24}}},
           .activities = {}},
          {.title = "Living room", // 3
           .description = "A room with a big sofa. There’s a dog bed on the floor and a tv on the wall",
           .n_exits = 2,
           .n_activities = 4,
           .exits = {{.exit = 1, .time = {0, 24}}, {.exit = 5, .time = {0, 24}}},
           .activities = {{.activity = 3, .time = {0, 8}}, {.activity = 3, .time = {9, 24}}, {.activity = 10, .time = {0, 24}}, {.activity = 18, .time = {8, 9}}}},                                                                                                            // 3
          {.title = "Kitchen", .description = "Lot’s of food on the sides. There’s two dog bowls on the floor", .n_exits = 1, .n_activities = 2, .exits = {{.exit = 4, .time = {0, 24}}}, .activities = {{.activity = 4, .time = {0, 24}}, {.activity = 5, .time = {0, 24}}}}, // 4
          {.title = "Study", .description = "Two desks with computers and a big comfy sofa", .n_exits = 1, .n_activities = 0, .exits = {{.exit = 1, .time = {0, 24}}}, .activities = {}},                                                                                      // 5
          {.title = "Little park", .description = "A small park with lots of climbing frames", .n_exits = 1, .n_activities = 0, .exits = {{.exit = 11, .time = {0, 24}}}, .activities = {}},                                                                                   // 6
          {.title = "Big park", .description = "A large park with trees and hills", .n_exits = 2, .n_activities = 0, .exits = {{.exit = 9, .time = {0, 24}}, {.exit = 10, .time = {0, 24}}}, .activities = {}},                                                                // 7
          {.title = "Forest", .description = "A forest with lots of fallen down trees and muddy patches", .n_exits = 2, .n_activities = 1, .exits = {{.exit = 10, .time = {0, 24}}, {.exit = 11, .time = {0, 24}}}, .activities = {{.activity = 15, .time = {0, 24}}}},        // 8
          {.title = "Green", .description = "An old bowling green", .n_exits = 2, .n_activities = 1, .exits = {{.exit = 9, .time = {0, 24}}, {.exit = 11, .time = {0, 24}}}, .activities = {{.activity = 12, .time = {0, 24}}}},                                               // 9
          {.title = "Armstrong park", .description = "A long park with a few different paths through", .n_exits = 0, .n_activities = 0, .exits = {}, .activities = {}},                                                                                                        // 10
          {.title = "Jesmond dene", .description = "A long park with a river running through it", .n_exits = 0, .n_activities = 0, .exits = {}, .activities = {}},                                                                                                             // 11
      },                                                                                                                                                                                                                                                                       // rooms
      .n_rooms = 0,
      .activities = {
          {.title = "Dog bed", .description = "You sleep for an hour", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {}, .todo = NOTODO, .keep = 1, .drop = 0},                               // 0
          {.title = "Big bed", .description = "You sleep for an hour", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {}, .todo = NOTODO, .keep = 1, .drop = 0},                              // 1
          {.title = "Front door", .description = "You bark at the front door", .n_exits = 1, .n_activities = 0, .exits = {{.exit = {.exit = 3, .time = {0, 24}}, THIS_ROOM}}, .activities = {}, .todo = NOTODO, .keep = 0, .drop = 0},                                       // 2
          {.title = "TV", .description = "There is no dog on the TV", .n_exits = 0, .n_activities = 0, .exits = {}, .activities = {}, .todo = NOTODO, .keep = 1, .drop = 0},                                                                                                 // 3
          {.title = "Water bowl", .description = "Slurp Slurp Slurp Slurp Slurp", .n_exits = 0, .n_activities = 0, .exits = {}, .activities = {}, .todo = 1, .keep = 0, .drop = 1},                                                                                          // 4
          {.title = "Food bowl", .description = "You bark at the empty bowl", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 6, .time = {0, 24}}, .room = THIS_ROOM}}, .todo = NOTODO, .keep = 0, .drop = 1},                        // 5
          {.title = "Food bowl", .description = "Chomp Chomp Chomp Chomp Chomp", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 5, .time = {0, 24}}, .room = THIS_ROOM}}, .todo = 0, .keep = 0, .drop = 1},                          // 6
          {.title = "Laundry basket", .description = "You find a sock", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 8, .time = {0, 24}}, .room = HELD_ACTIVITY}}, .todo = 2, .keep = 0, .drop = 0},                               // 7
          {.title = "Put down socks", .description = "You put down the socks", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 9, .time = {0, 24}}, .room = THIS_ROOM}}, .todo = NOTODO, .keep = 0, .drop = 0},                       // 8
          {.title = "Socks", .description = "You pick up the socks", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 8, .time = {0, 24}}, .room = HELD_ACTIVITY}}, .todo = NOTODO, .keep = 0, .drop = 1},                             // 9
          {.title = "Ball", .description = "You pick up the ball", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 11, .time = {0, 24}}, .room = HELD_ACTIVITY}}, .todo = NOTODO, .keep = 0, .drop = 1},                              // 10
          {.title = "Put down ball", .description = "You drop the ball", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 10, .time = {0, 24}}, .room = THIS_ROOM}}, .todo = NOTODO, .keep = 0, .drop = 0},                            // 11
          {.title = "Long grass", .description = "Smells like wee", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 13, .time = {0, 24}}, .room = THIS_ROOM}}, .todo = NOTODO, .keep = 0, .drop = 0},                                 // 12
          {.title = "Wee on long grass", .description = "It's your park now", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 14, .time = {0, 24}}, .room = THIS_ROOM}}, .todo = 3, .keep = 0, .drop = 0},                            // 13
          {.title = "Long grass", .description = "Smells like your wee", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {}, .todo = NOTODO, .keep = 1, .drop = 0},                            // 14
          {.title = "Bushes", .description = "You find a football", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 16, .time = {0, 24}}, .room = HELD_ACTIVITY}}, .todo = NOTODO, .keep = 0, .drop = 0},                             // 15
          {.title = "Drop football", .description = "You leave the footbll for your dad to pick up", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 17, .time = {0, 24}}, .room = 6}}, .todo = NOTODO, .keep = 0, .drop = 0},        // 16
          {.title = "Chase football", .description = "Your dad kicks the football and you chase it", .n_exits = 0, .n_activities = 1, .exits = {}, .activities = {{.activity = {.activity = 16, .time = {0, 24}}, .room = HELD_ACTIVITY}}, .todo = 4, .keep = 0, .drop = 0}, // 17
          {.title = "TV", .description = "There is a dog on the TV, they're acting", .n_exits = 0, .n_activities = 0, .exits = {}, .activities = {}, .todo = NOTODO, .keep = 1, .drop = 0},                                                                                  // 18
          {.title = "Cupboard", .description = "You can't get into the cupboard", .n_exits = 0, .n_activities = 0, .exits = {}, .activities = {}, .todo = NOTODO, .keep = 1, .drop = 0},                                                                                     // 19
      },                                                                                                                                                                                                                                                                     // activities
      .n_activities = 0,
      .exits = {
          // exits
          {.title = "Wake up", .description = "You wake up in a big bed", .room = 0},                         // 0
          {.title = "Go to hallway", .description = "You walk into the hallway", .room = 1},                  // 1
          {.title = "Go to bedroom", .description = "You walk into the bedroom", .room = 0},                  // 2
          {.title = "Exit house", .description = "You put on your lead and walk into the street", .room = 2}, // 3
          {.title = "Go to living room", .description = "You walk into the living room", .room = 3},          // 4
          {.title = "Go to the kitchen", .description = "You walk into the kitchen", .room = 4},              // 5
          {.title = "Go to the study", .description = "You walk into the study", .room = 5},                  // 6
          {.title = "Walk to little park", .description = "You walk into the little park", .room = 6},        // 7
          {.title = "Walk to big park", .description = "You walk to the big park", .room = 7},                // 8
          {.title = "Go to the forest", .description = "You run into the forest", .room = 8},                 // 9
          {.title = "Go to the green", .description = "You run to the green", .room = 9},                     // 10
          {.title = "Go to the street", .description = "You walk back to the street", .room = 2},             // 11
          {.title = "Go home", .description = "You go back home", .room = 1},                                 // 12
      },                                                                                                      // exits
      .n_exits = 0,
      .todos = {
          // todos
          {"Breakfast", 0},     // 0
          {"Slurps", 0},        // 1
          {"Steal socks", 0},   // 2
          {"Claim park", 0},    // 3
          {"Play football", 0}, // 4
      },                        // todos
      .n_todos = 5,
      .messages = {}, // messages
      .n_messages = 0,
      .currentRoom = 0,
      .heldActivity = NO_HELD_ACTIVITY,
      .hours = 7,
      .minutes = 0};

  return game;
}
