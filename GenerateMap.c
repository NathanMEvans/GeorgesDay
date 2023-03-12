#include "GenerateMap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define N_ROOMS 6
#define N_ACTIVITIES 7
#define N_EXITS 7

struct Exit generateMap() {
   
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
   
   // create exits
   static struct Exit exits[N_EXITS];
   FILE* exitcsv;
   exitcsv = fopen("Map/Exits-Exits.csv", "r");
   fgets(line,MAX_LINE_LENGTH,exitcsv); // Collumn headers do nothing

   for (int i=0;i<N_EXITS;i++) {
     fgets(line,MAX_LINE_LENGTH,exitcsv);
     struct Exit newExit = {"",""};
     // ID do nothing
     strtok(line,delim);
     strcpy(newExit.title, strtok(NULL,delim));
     strcpy(newExit.description, strtok(NULL,delim));
     int roomID = 0;
     sscanf(strtok(NULL,delim), "%d", &roomID);
     newExit.room = &rooms[roomID];
     printf("newExit Title: %s\n", newExit.title);
     exits[i] = newExit;
   }
   fclose(exitcsv);
   
   // add exits to rooms
   FILE* roomExitcsv = fopen("Map/RoomExits-RoomExits.csv", "r");
   fgets(line,MAX_LINE_LENGTH,roomExitcsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,roomExitcsv)) {
      strtok(line,delim); // ID do nothing
      int roomID = 0;
      sscanf(strtok(NULL,delim), "%d", &roomID);
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
      rooms[roomID].activities[rooms[roomID].n_activities] = &activities[activityID];
      rooms[roomID].n_activities++;
   }
   fclose(roomActivitycsv);

   // add activities to rooms
   FILE* activityActivitycsv = fopen("Map/ActivityActivities-ActivityActivities.csv", "r");
   fgets(line,MAX_LINE_LENGTH,activityActivitycsv); // Collumn headers do nothing

   while(fgets(line,MAX_LINE_LENGTH,activityActivitycsv)) {
      strtok(line,delim); // ID do nothing
      int activityID1 = 0;
      sscanf(strtok(NULL,delim), "%d", &activityID1);
      int activityID2 = 0;
      sscanf(strtok(NULL,delim), "%d", &activityID2);

      activities[activityID1].activities[activities[activityID1].n_activities] = &activities[activityID2];
      activities[activityID1].n_activities++;
   }
   fclose(activityActivitycsv);

   return exits[0];
}
