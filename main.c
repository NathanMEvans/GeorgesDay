#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define clear() printf("\033[H\033[J")

struct Activity {
   char* title;
   char* description;
};

struct Exit {
   char* title;
   char* description;
   struct Room* room;
};

struct Room {
   int n_exits;
   int n_activities;
   struct Exit* exits[10];
   struct Activity* activities[10];
};

struct Exit* showRoom(struct Exit* exit) {
   struct Room* room = exit->room;
   char* intro = exit->description;
   clear();
   char* input = malloc(sizeof(char)*10);
   int inputI = 0;
   while (1) {
      if (inputI > 0) {
         if (inputI <= room->n_activities) {
            printf("%s\n", room->activities[inputI-1]->description);
         } else {
            return room->exits[inputI-1-room->n_activities];
         } 
      } else {
          printf("%s\n",intro);
      }
      for (int i = 0; i < room->n_activities; i++) {
         printf("%d: %s\n",i+1,room->activities[i]->title);
      }
      for (int i = 0; i < room->n_exits; i++) {
         printf("%d: go to %s\n",i+room->n_activities+1,room->exits[i]->title);
      }
      
      fgets(input, 10, stdin);
      if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n')) {
         input[strlen (input) - 1] = '\0';
      }
      sscanf(input, "%d", &inputI);
      clear();
   }
}

int main() {
   struct Activity dogBed = {"dog bed", "You sleep for an hour"};
   struct Activity bigBed = {"big bed", "You sleep for an hour"};
   struct Room bedroom = {
      1,
      2,
      {},
      {&dogBed, &bigBed}
   };
   struct Activity frontDoor = {"front door", "You bark at the front door"};
   struct Room hallway = {
      1,
      1,
      {},
      &frontDoor
   };
   struct Exit bedroomHallway = {"hallway", "You walk into the hallway", &hallway};
   bedroom.exits[0] = &bedroomHallway;
   struct Exit hallwayBedroom = {"bedroom", "You walk into the bedroom", &bedroom};
   hallway.exits[0] = &hallwayBedroom;
   struct Exit nextExit = {"bedroom", "You wake up in a big bed", &bedroom};
   while (1) {
      nextExit = *showRoom(&nextExit);
   }
}


