#include "GenerateMap.h"

struct Exit generateMap() {
   static struct Activity dogBed = {"dog bed", "You sleep for an hour", 0, 0};
   static struct Activity bigBed = {"big bed", "You sleep for an hour", 0 ,0};
   static struct Room bedroom = {
      1,
      2,
      {},
      {&dogBed, &bigBed}
   };
   static struct Activity frontDoor = {
      "front door",
      "You bark at the front door\n\"Time for your walk is it?\"",
      1,
      0,
      {},
      {}
   };
   static struct Room hallway = {
      1,
      1,
      {},
      &frontDoor
   };
   static struct Exit bedroomHallway = {"Go to hallway", "You walk into the hallway", &hallway};
   bedroom.exits[0] = &bedroomHallway;
   static struct Exit hallwayBedroom = {"Go to bedroom", "You walk into the bedroom", &bedroom};
   hallway.exits[0] = &hallwayBedroom;
   static struct Room street = {
      1,
      0,
      {},
      {},
   };
   static struct Exit hallwayStreet = {"Exit house", "You put on your lead and walk into the street", &street};
   frontDoor.exits[0] = &hallwayStreet;

   struct Exit nextExit = {"bedroom", "You wake up in a big bed", &bedroom};
   return nextExit;
}
