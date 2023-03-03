#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define clear() printf("\033[H\033[J")

struct Activity {
   char* title;
   char* description;
};

struct Room {
   char* intro;
   int n_exits;
   int n_activities;
   char* exits[10];
   struct Activity* activities[10];
};

char* showRoom(struct Room room) {
   clear();
   char* input = malloc(sizeof(char)*10);
   int inputI = 0;
   while (1) {
      if (inputI > 0) {
         if (inputI <= room.n_activities) {
            printf("%s\n", room.activities[inputI-1]->description);
         } else {
            return room.exits[inputI-1-room.n_activities];
         } 
      } else {
          printf("%s\n",room.intro);
      }
      for (int i = 0; i < room.n_activities; i++) {
         printf("%d: %s\n",i+1,room.activities[i]->title);
      }
      for (int i = 0; i < room.n_exits; i++) {
         if (inputI == i+room.n_activities+1)  {
            return room.exits[i];
         }
         printf("%d: go to %s\n",i+room.n_activities+1,room.exits[i]);
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
      "You wake up in the bedroom",
      1,
      2,
      {"hallway"},
      {&dogBed, &bigBed}
   };
   struct Activity frontDoor = {"front door", "You bark at the front door"};
   struct Room hallway = {
      "You walk into the hallway",
      2,
      1,
      {"bedroom", "living room"},
      &frontDoor
   };
   showRoom(bedroom);
   showRoom(hallway);
}


