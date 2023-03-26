#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <ncurses.h>
#include <sys/ioctl.h> 
#include <unistd.h> //STDOUT_FILENO

#include "Structs.c"
#include "GenerateMap.h"

#define clear() printf("\033[H\033[J")

void border() {
   clear();
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

   for (int i=0;i<w.ws_col;i++) {
      printf("-");
   }
   printf(
"|   _____                           _           _                |\n"
"|  / ____|                         ( )         | |               |\n"
"| | |  __  ___  ___  _ __ __ _  ___|/ ___    __| | __ _ _   _    |\n"
"| | | |_ |/ _ \\/ _ \\| '__/ _` |/ _ \\ / __|  / _` |/ _` | | | |   |\n"
"| | |__| |  __/ (_) | | | (_| |  __/ \\__ \\ | (_| | (_| | |_| |   |\n"
"|  \\_____|\\___|\\___/|_|  \\__, |\\___| |___/  \\__,_|\\__,_|\\__, |   |\n"
"|                         __/ |                          __/ |   |\n"
"|                        |___/                          |___/    |\n"
);
 for (int i=0;i<w.ws_col;i++) {
      printf("-");
   }
}


struct Exit* showRoom(struct Exit* exit) {
   struct Room* room = exit->room;
   char* intro = exit->description;
   border();
   char* input = malloc(sizeof(char)*10);
   int inputI = 0;
   while (1) {
      if (inputI > 0) {
         if (inputI <= room->n_activities) {
            struct Activity* activity = room->activities[inputI-1];
            printf("%s\n", activity->description);
            for  (int i = 0; i < activity->n_activities; i++) {
               room->activities[room->n_activities+i] = activity->activities[i];
               room->n_activities++;
            }
            for  (int i = 0; i < activity->n_exits; i++) {
               room->exits[room->n_exits+i] = activity->exits[i];
               room->n_exits++;
            }

            // Remove activity from array
            room->activities[inputI-1] = room->activities[--room->n_activities];
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
      border();
   }
}



int main() {
   struct Exit nextExit = generateMap();
   while (1) {
      nextExit = *showRoom(&nextExit);
   }
}

