#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Structs.c"
#include "GenerateMap.h"

#define clear() printf("\033[H\033[J")

struct Exit* showRoom(struct Exit* exit) {
   struct Room* room = exit->room;
   char* intro = exit->description;
   clear();
   char* input = malloc(sizeof(char)*10);
   int inputI = 0;
   while (1) {
      if (inputI > 0) {
         if (inputI <= room->n_activities) {
            struct Activity* activity = room->activities[inputI-1];
            printf("%s\n", activity->description);
            for  (int i = 0; i < activity->n_activities; i++) {
               room->activities[room->n_activities+i] = activity->activities[i];
               room->n_activities++;// = room->n_activities + 1;
            }
            activity->n_activities = 0;
            for  (int i = 0; i < activity->n_exits; i++) {
               room->exits[room->n_exits+i] = activity->exits[i];
               room->n_exits++;// = room->n_exits + 1;
            }
            activity->n_exits = 0;
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
         printf("%d: %s\n",i+room->n_activities+1,room->exits[i]->title);
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
   struct Exit nextExit = generateMap();
   while (1) {
      nextExit = *showRoom(&nextExit);
   }
}

