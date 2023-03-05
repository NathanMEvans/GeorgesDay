#include "GenerateMap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define N_ROOMS 3
struct Exit generateMap() {
   
   // create rooms
   static struct Room rooms[N_ROOMS];
   FILE* roomcsv;
   char line[MAX_LINE_LENGTH];
   roomcsv = fopen("Map/rooms-rooms.csv", "r");
   // Collumn headers do nothing
   fgets(line,MAX_LINE_LENGTH,roomcsv);

   char delim[2] = ",";
   for (int i=0;i<N_ROOMS;i++) {
     fgets(line,MAX_LINE_LENGTH,roomcsv);
     struct Room newRoom = {"","",0,0,{},{}};
     rooms[i] = newRoom;

     // ID do nothing
     strtok(line,delim);
     newRoom.title = strtok(line,delim);
     newRoom.description =  strtok(line,delim);
   }  
   fclose(roomcsv);

   static struct Activity dogBed = {"dog bed", "You sleep for an hour", 0, 0};
   static struct Activity bigBed = {"big bed", "You sleep for an hour", 0 ,0};
   static struct Activity frontDoor = {
      "front door",
      "You bark at the front door\n\"Time for your walk is it?\"",
      1,
      0,
      {},
      {}
   };
   rooms[1].activities[0] = &frontDoor;
   rooms[1].n_activities++;
   static struct Exit bedroomHallway = {"Go to hallway", "You walk into the hallway", &rooms[1]};
   rooms[0].exits[0] = &bedroomHallway;
   rooms[0].n_exits++;
   static struct Exit hallwayBedroom = {"Go to bedroom", "You walk into the bedroom", &rooms[0]};
   rooms[1].exits[0] = &hallwayBedroom;
   static struct Exit hallwayStreet = {"Exit house", "You put on your lead and walk into the street", &rooms[2]};
   frontDoor.exits[0] = &hallwayStreet;
   //char* input = malloc(sizeof(char)*10);
   //int inputI = 0;
   //fgets(input, 10, stdin);
   //if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n')) {
   //   input[strlen (input) - 1] = '\0';
   //}
   //sscanf(input, "%d", &inputI);
   //printf("inputI: %d", inputI); 
   //for (int i=0; i<inputI; i++) {
   //   static struct Exit exit = {"test", "test", &hallway};
   //   bedroom.exits[bedroom.n_exits] = &exit;
   //   bedroom.n_exits++;
   //}
   struct Exit nextExit = {"bedroom", "You wake up in a big bed", &rooms[0]};
   return nextExit;
}
