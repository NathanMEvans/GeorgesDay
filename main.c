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

#define NOTODO 255

struct Game game;
	
void borderLine(int x, int y, int width, char capl[4], char capr[4]) {
   gotoxy(x,y);
   printf("%s",capl);
   for (int i=2;i<width;i++) {
      printf("═");
   }
   printf("%s\n", capr);
}

void borderColumn(int x, int y, int height, char capu[4], char capd[4]) {
   gotoxy(x,y);
   printf("%s",capu);
   for (int i=1;i<height;i++) {
      gotoxy(x,i+y);
      printf("║\n");
   }
   gotoxy(x,y+height);
   printf("%s\n", capd);
}

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

   int divx = 2*w.ws_col/3;
   borderColumn(divx, 10, w.ws_row-12, "╦", "╩");
   //for (int i=10;i<w.ws_row-12;i++) {
   //   gotoxy(2*w.ws_col/3,i);
   //   printf("║\n");
   //}
   borderLine(1, 10, divx, "╠", "╦");
   borderLine(1, 12, divx, "╠", "╣");
   borderLine(1, 14, divx, "╠", "╣");
   borderLine(divx, 10, w.ws_col-divx, "╦", "╣");
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

void showOptions(struct Room* room, char* message) {
      gotoxy(1,11);
      printf("%4s%s: %s\n", "", room->title, room->description);
      printf("%4s%s\n\n","", message);
      for (int i = 0; i < room->n_activities; i++) {
         printf("%5d: %s\n",i+1,game.activities[room->activities[i]].title);
      }
      for (int i = 0; i < room->n_exits; i++) {
         printf("%5d: %s\n",i+room->n_activities+1,game.exits[room->exits[i]].title);
      }
}

void handleInput(struct Room* room, int inputI) {
    if (inputI > 0) {
        if (inputI <= room->n_activities) {
            struct Activity* activity = &game.activities[room->activities[inputI-1]];
            strcpy(game.lastMessage, activity->description);
            for  (int i = 0; i < activity->n_activities; i++) {
               room->activities[room->n_activities+i] = activity->activities[i];
               room->n_activities++;
            }
            for  (int i = 0; i < activity->n_exits; i++) {
               room->exits[room->n_exits+i] = activity->exits[i];
               room->n_exits++;
            }
            if (activity->todo != NOTODO) {
               game.todos[activity->todo].complete = 1;
            }
            // Remove activity from array
            room->activities[inputI-1] = room->activities[--room->n_activities];
        }
    }
}
void drawTodos() {
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
   int divx = 2*w.ws_col/3;
   gotoxy(w.ws_col-(divx/4)-3,11);
   printf("TODO");  
   for (int i=0; i<game.n_todos; i++) {
      gotoxy(divx+2,12+i);
      if (game.todos[i].complete) {
         printf("☒");
      } else {
         printf("□");
      }
      printf(" %s\n",game.todos[i].title);
   }
 
}
struct Exit* showRoom(struct Exit* exit) {
   printf("NEW ROOM\n");
   game.currentRoom = exit->room;
   strcpy(game.lastMessage, exit->description);
   struct Room* room = &game.rooms[game.currentRoom];
   char* input = malloc(sizeof(char)*10);
   int inputI = 0;
   while (1) {
      header();
      showOptions(room, game.lastMessage);
      drawTodos();
      border();
      gotoxy(5,22);
      fgets(input, 10, stdin);
      if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n')) {
         input[strlen (input) - 1] = '\0';
      }
      sscanf(input, "%d", &inputI);
      if (inputI > room->n_activities) {
         struct Exit* selectedExit = &game.exits[room->exits[inputI-1-room->n_activities]];
         return selectedExit;
      }
      handleInput(room, inputI);
   }
}

static void sig_handler(int sig)
{
  if (SIGWINCH == sig) {
    header();
    struct Room* room = &game.rooms[game.currentRoom];
    showOptions(room, game.lastMessage);
    drawTodos();
    border();
       
  }

} // sig_handler



int main() {
   signal(SIGWINCH, sig_handler);
   //static struct Todo todos[N_TODOS];
   
   //for (int i=0; i<N_TODOS; i++) {
   //  static struct Todo todo = {"", 0}; 
   //  todos[i] = todo;
   //}
  
   game = generateMap();
   struct Exit* nextExit = &game.exits[0];
   //return 0; 
   while (1) {
      nextExit = showRoom(nextExit);
   }
}

