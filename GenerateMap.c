#include "GenerateMap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define NOTODO 255
#define NO_HELD_ACTIVITY 255

struct Game generateMap() {
   struct Game game = {{}, 0, {}, 0, {}, 0, {}, 0, {}, 0, 0, NO_HELD_ACTIVITY };
   char line[MAX_LINE_LENGTH];
   char delim[2] = ",";
   
   // create rooms
   FILE* roomcsv;
   roomcsv = fopen("Map/Rooms-Rooms.csv", "r");
   fgets(line,MAX_LINE_LENGTH,roomcsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,roomcsv)) {
     struct Room newRoom = {"","",0,0,{},{}};
     strtok(line,delim); // ID do nothing
     strcpy(newRoom.title, strtok(NULL,delim));
     strcpy(newRoom.description, strtok(NULL,delim));
     game.rooms[game.n_rooms++] = newRoom;
   }  
   fclose(roomcsv);
   
   // create activities
   FILE* activitycsv;
   activitycsv = fopen("Map/Actvities-Actvities.csv", "r");
   fgets(line,MAX_LINE_LENGTH,activitycsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,activitycsv)) {
     struct Activity newActivity = {"","",0,0,{},{},NOTODO};
     strtok(line,delim); // ID do nothing
     strcpy(newActivity.title, strtok(NULL,delim));
     strcpy(newActivity.description, strtok(NULL,delim));
     game.activities[game.n_activities++] = newActivity;
   } 
   fclose(activitycsv);
   
   // create exits
   FILE* exitcsv;
   exitcsv = fopen("Map/Exits-Exits.csv", "r");
   fgets(line,MAX_LINE_LENGTH,exitcsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,exitcsv)) {
     struct Exit newExit = {"","", 0};
     strtok(line,delim); // ID do nothing
     strcpy(newExit.title, strtok(NULL,delim));
     strcpy(newExit.description, strtok(NULL,delim));
     sscanf(strtok(NULL,delim), "%d", &newExit.room);
     game.exits[game.n_exits++] = newExit;
   }
   fclose(exitcsv);
   
   // create TODOS
   FILE* todocsv;
   todocsv = fopen("Map/Todo-Todo.csv", "r");
   fgets(line,MAX_LINE_LENGTH,todocsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,todocsv)) {
      struct Todo todo = {"", 0};
      strtok(line,delim); // ID do nothing
      strcpy(todo.title, strtok(NULL,delim));
      todo.complete = 0;
      int activityID = 0;
      sscanf(strtok(NULL,delim), "%d", &activityID);
      game.activities[activityID].todo = game.n_todos;
      game.todos[game.n_todos++] = todo;
   }
 
   // add exits to rooms
   FILE* roomExitcsv = fopen("Map/RoomExits-RoomExits.csv", "r");
   fgets(line,MAX_LINE_LENGTH,roomExitcsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,roomExitcsv)) {
      strtok(line,delim); // ID do nothing
      int roomID = 0;
      sscanf(strtok(NULL,delim), "%d", &roomID);
      int exitID = 0;
      sscanf(strtok(NULL,delim), "%d", &exitID);
      struct Room* room = &game.rooms[roomID];
      room->exits[room->n_exits++] = exitID;
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
      struct Activity* activity = &game.activities[activityID];
      activity->exits[activity->n_exits++] = exitID;
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
      struct Room* room = &game.rooms[roomID];
      room->activities[room->n_activities++] = activityID;
   }
   fclose(roomActivitycsv);

   // add activities to activities
   FILE* activityActivitycsv = fopen("Map/ActivityActivities-ActivityActivities.csv", "r");
   fgets(line,MAX_LINE_LENGTH,activityActivitycsv); // Collumn headers do nothing
   while(fgets(line,MAX_LINE_LENGTH,activityActivitycsv)) {
      struct ActivityRoom actRoom;
      strtok(line,delim); // ID do nothing
      int activityID1 = 0;
      sscanf(strtok(NULL,delim), "%d", &activityID1);
      int activityID2 = 0;
      sscanf(strtok(NULL,delim), "%d", &actRoom.activity);
      sscanf(strtok(NULL,delim), "%d", &actRoom.room);
      struct Activity* activity = &game.activities[activityID1];
      activity->activities[activity->n_activities++] = actRoom;
   }
   fclose(activityActivitycsv);
   
   return game;
}
