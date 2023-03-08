#include "GenerateMap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define N_ROOMS 3
#define N_ACTIVITIES 3
#define N_EXITS 4

struct Exit generateMap() {
   printf("HERE0\n");
   
   char line[MAX_LINE_LENGTH];
   char delim[2] = ",";
   
   // create rooms
   static struct Room rooms[N_ROOMS];
   FILE* roomcsv;
   roomcsv = fopen("Map/Rooms-Rooms.csv", "r");
   // Collumn headers do nothing
   fgets(line,MAX_LINE_LENGTH,roomcsv);

   for (int i=0;i<N_ROOMS;i++) {
     fgets(line,MAX_LINE_LENGTH,roomcsv);
     struct Room newRoom = {"","",0,0,{},{}};

     // ID do nothing
     strtok(line,delim);
     strcpy(newRoom.title, strtok(NULL,delim));
     strcpy(newRoom.description, strtok(NULL,delim));
     rooms[i] = newRoom;
   }  
   fclose(roomcsv);
   printf("HERE1\n");
   
   // create activities
   static struct Activity activities[N_ACTIVITIES];
   FILE* activitycsv;
   activitycsv = fopen("Map/Actvities-Actvities.csv", "r");
   // Collumn headers do nothing
   fgets(line,MAX_LINE_LENGTH,activitycsv);

   for (int i=0;i<N_ACTIVITIES;i++) {
     fgets(line,MAX_LINE_LENGTH,activitycsv);
     struct Activity newActivity = {"","",0,0,{},{}};

     // ID do nothing
     strtok(line,delim);
     strcpy(newActivity.title, strtok(NULL,delim));
     strcpy(newActivity.description, strtok(NULL,delim));
     activities[i] = newActivity;
   } 
   fclose(activitycsv);
   printf("HERE2\n");
   
   // create exits
   static struct Exit exits[N_EXITS];
   FILE* exitcsv;
   exitcsv = fopen("Map/Exits-Exits.csv", "r");
   fgets(line,MAX_LINE_LENGTH,exitcsv); // Collumn headers do nothing

   for (int i=0;i<N_EXITS;i++) {
     fgets(line,MAX_LINE_LENGTH,exitcsv);
     struct Exit newExit = {"",""};
     exits[i] = newExit;
     // ID do nothing
     strtok(line,delim);
     strcpy(newExit.title, strtok(NULL,delim));
     strcpy(newExit.description, strtok(NULL,delim));
     printf("desc %s\n",newExit.description);
     printf("title %s\n",newExit.title);
     int roomID = 0;
     sscanf(strtok(NULL,delim), "%d", &roomID);
     newExit.room = &rooms[roomID];
     exits[i] = newExit;
   }
   fclose(exitcsv);
   printf("HERE3\n");
   
   // add exits to rooms
   FILE* roomExitcsv = fopen("Map/RoomExits-RoomExits.csv", "r");
   fgets(line,MAX_LINE_LENGTH,roomExitcsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,roomExitcsv)) {
      strtok(line,delim); // ID do nothing
      int roomID = 0;
      sscanf(strtok(NULL,delim), "%d", &roomID);
      printf("room ID for exit: %d",roomID);
      int exitID = 0;
      sscanf(strtok(NULL,delim), "%d", &exitID);
      rooms[roomID].exits[rooms[roomID].n_exits] = &exits[exitID];
      rooms[roomID].n_exits++;
   }
   fclose(roomExitcsv);
   
   // add exits to activities
   FILE* activityExitcsv = fopen("Map/activityExits-activityExits.csv", "r");
   fgets(line,MAX_LINE_LENGTH,activityExitcsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,activityExitcsv)) {
      strtok(line,delim); // ID do nothing
      int activityID = 0;
      sscanf(strtok(NULL,delim), "%d", &activityID);
      int exitID = 0;
      sscanf(strtok(NULL,delim), "%d", &exitID);
      activities[activityID].exits[activities[activityID].n_exits] = &exits[exitID];
      activities[activityID].n_exits++;
   }
   fclose(activityExitcsv);
  
   // add activities to rooms
   FILE* roomActivitycsv = fopen("Map/RoomActivities-RoomActivities.csv", "r");
   fgets(line,MAX_LINE_LENGTH,roomActivitycsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,roomActivitycsv)) {
      strtok(line,delim); // ID do nothing
      int roomID = 0;
      sscanf(strtok(NULL,delim), "%d", &roomID);
      int activityID = 0;
      sscanf(strtok(NULL,delim), "%d", &activityID);
      printf("activity: %d title: %s\n",activityID,activities[activityID].title);
      rooms[roomID].activities[rooms[roomID].n_activities] = &activities[activityID];
      rooms[roomID].n_activities++;
   }
   fclose(roomActivitycsv);
 
   printf("HERE\n"); 
   printf("in func description: %s\n",exits[0].description);
   return exits[0];
}
