#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <ncurses.h>
#include <sys/ioctl.h> 
#include <unistd.h> //STDOUT_FILENO
#include <signal.h>

#include "Structs.c"
#include "GenerateMap.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

char* intro;
int inputI;
struct Room* room;
	
void border() {
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
   gotoxy(1,1);
   printf("╔");
   for (int i=2;i<w.ws_col-1;i++) {
      printf("═");
   }
   printf("╗");
   for (int i=2;i<w.ws_row-2;i++) {
      gotoxy(1,i);
      printf("║\n");
      gotoxy(w.ws_col-1,i);
      printf("║\n");
   }
   printf("╚");
   for (int i=2;i<w.ws_col-1;i++) {
      printf("═");
   }
   printf("╝\n");
}


void header() {
   clear();
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

   gotoxy(1,2);
   if (w.ws_col > 68) {
   printf(
"%1$*2$s   _____                           _           _                \n"
"%1$*2$s  / ____|                         ( )         | |               \n"
"%1$*2$s | |  __  ___  ___  _ __ __ _  ___|/ ___    __| | __ _ _   _    \n"
"%1$*2$s | | |_ |/ _ \\/ _ \\| '__/ _` |/ _ \\ / __|  / _` |/ _` | | | |   \n"
"%1$*2$s | |__| |  __/ (_) | | | (_| |  __/ \\__ \\ | (_| | (_| | |_| |   \n"
"%1$*2$s  \\_____|\\___|\\___/|_|  \\__, |\\___| |___/  \\__,_|\\__,_|\\__, |   \n"
"%1$*2$s                         __/ |                          __/ |   \n"
"%1$*2$s                        |___/                          |___/    \n"
,"",(w.ws_col-68)/2
);
} else {
printf(
"%1$*2$s   _____ _           _             \n"
"%1$*2$s  / ____( )         | |            \n"
"%1$*2$s | |  __|/ ___    __| | __ _ _   _ \n"
"%1$*2$s | | |_ | / __|  / _` |/ _` | | | |\n"
"%1$*2$s | |__| | \\__ \\ | (_| | (_| | |_| |\n"
"%1$*2$s  \\_____| |___/  \\__,_|\\__,_|\\__, |\n"
"%1$*2$s                              __/ |\n"
"%1$*2$s                             |___/ \n"
,"",(w.ws_col-35)/2
);
}
   //for (int i=0;i<w.ws_col;i++) {
   //   printf("-");
   //}
}

void options(struct Room* room, char* intro, int inputI) {
      gotoxy(1,12);
      printf("%4s%s: %s\n", "", room->title, room->description);
      if (inputI > 0) {
         if (inputI <= room->n_activities) {
            struct Activity* activity = room->activities[inputI-1];
            printf("%5s\n", activity->description);
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
         }
      } else {
          printf("%4s%s\n\n","", intro);
      }
      for (int i = 0; i < room->n_activities; i++) {
         printf("%5d: %s\n",i+1,room->activities[i]->title);
      }
      for (int i = 0; i < room->n_exits; i++) {
         printf("%5d: %s\n",i+room->n_activities+1,room->exits[i]->title);
      }
}

struct Exit* showRoom(struct Exit* exit) {
   printf("NEW ROOM\n");
   room = exit->room;
   intro = exit->description;
   char* input = malloc(sizeof(char)*10);
   inputI = 0;
   while (1) {
      header();
      options(room, intro, inputI);
      
      border();
      gotoxy(10,12);
      fgets(input, 10, stdin);
      if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n')) {
         input[strlen (input) - 1] = '\0';
      }
      sscanf(input, "%d", &inputI);
      if (inputI > room->n_activities) {
         struct Exit* selectedExit = room->exits[inputI-1-room->n_activities];
         return selectedExit;
      }
   }
}

static void sig_handler(int sig)
{
  if (SIGWINCH == sig) {
    header();
    options(room, intro, inputI);
    border();    
  }

} // sig_handler



int main() {
   signal(SIGWINCH, sig_handler);

   struct Exit nextExit = generateMap();
   while (1) {
      nextExit = *showRoom(&nextExit);
   }
}

