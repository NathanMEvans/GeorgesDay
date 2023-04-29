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
#define THIS_ROOM 255
#define HELD_ACTIVITY 254
#define NO_HELD_ACTIVITY 255

struct Game game;

void increaseTime(int hours, int minutes) {
   game.minutes += minutes;
   game.hours += hours;
   game.hours += game.minutes / 60;
   game.minutes = game.minutes % 60;
   game.hours = game.hours % 24;
}
	
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
   borderLine(1, 14, divx, "╠", "╣");
   borderLine(1, 19, divx, "╠", "╣");
   borderLine(divx, 10, w.ws_col-divx, "╦", "╣");
   
   // clock outline
   borderColumn(w.ws_col-7, 1, 2, "╦", "╚");
   borderLine(w.ws_col-7, 3, 7, "╚", "╣");
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

int inRange(struct TimeRange timeRange) {
  return timeRange.start <= game.hours && game.hours < timeRange.end;
}

void showOptions(struct Room* room) {
      struct winsize w;
      ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
      int divx = 2*w.ws_col/3;
      
      // clock
      gotoxy(w.ws_col - 6, 2);
      printf("%02d:%02d", game.hours, game.minutes); 
      
      gotoxy(1,11);
      int titleLen = strlen(room->title);
      printf("%4s%s: ", "", room->title);
      int lineLength = 0;
      char description[128];
      strcpy(description, room->description);
      char* token = strtok(description, " ");
      int line = 11;
      while ( token != NULL ) {
          if (lineLength + strlen(token) + 20 + titleLen > divx) {
             lineLength = 0;
             gotoxy(7+titleLen,++line);
          }
          lineLength += strlen(token);
          printf( "%s ", token);
          token = strtok(NULL, " ");
      }
      gotoxy(1,15);
      for (int i=0; i<4; i++) {
          if (game.n_messages-4+i < 0) {
             continue;
          }
          char* message = game.messages[game.n_messages-4+i];
         printf("%4s%s\n","", message);
      }
      gotoxy(1,20);
      int count = 1;
      for (int i = 0; i < room->n_activities; i++) {
         struct Activity* activity = &game.activities[room->activities[i]];
         if (inRange(activity->timeRange)) {
#ifdef DEBUG
            printf("%5d activity: %s exits: %d activities: %d \n",count++, activity->title, activity->n_exits, activity->n_activities);
#else
            printf("%5d %s\n",count++, activity->title);
#endif
         }
      }
      for (int i = 0; i < room->n_exits; i++) {
         struct Exit* exit = &game.exits[room->exits[i]];
         if (inRange(exit->timeRange)) {
#ifdef DEBUG
            printf("%5d exit: %s\n",count++,exit->title);
#else
            printf("%5d %s\n",count++,exit->title);
#endif
         }
      }
      if (game.heldActivity != NO_HELD_ACTIVITY) {
#ifdef DEBUG
         printf("%5d held activity: %s\n",count++,game.activities[game.heldActivity].title);
#else 
         printf("%5d %s\n",count++,game.activities[game.heldActivity].title);
#endif
      }
}

void selectActivity(struct Activity* activity) {
    for  (int i = 0; i < activity->n_activities; i++) {
        struct ActivityRoom actRoom = activity->activities[i];
        if (actRoom.room == THIS_ROOM) {
            struct Room* room = &game.rooms[game.currentRoom];
            room->activities[room->n_activities++] = actRoom.activity;
        } else if (actRoom.room == HELD_ACTIVITY) {
            if (game.heldActivity != NO_HELD_ACTIVITY) {
                struct Activity* oldHeldActivity = &game.activities[game.heldActivity];
                game.heldActivity = NO_HELD_ACTIVITY;
                selectActivity(oldHeldActivity); 
            }
            game.heldActivity = actRoom.activity;
         } else {
            struct Room* room = &game.rooms[actRoom.room];
            room->activities[room->n_activities++] = actRoom.activity;
         }
     }
     strcpy(game.messages[game.n_messages++], activity->description);
     // Exits currently placed in this room - might update this same as activities
     struct Room* room = &game.rooms[game.currentRoom];
     
     for  (int i = 0; i < activity->n_exits; i++) {
         room->exits[room->n_exits++] = activity->exits[i];
     }
     if (activity->todo != NOTODO) {
        game.todos[activity->todo].complete = 1;
     }
}

void handleInput(struct Room* room, int inputI) {
    int count = 0;
    int offset = 0;
    if (inputI > 0) {
	int offset = 0;
        for (int i=1;i<=room->n_activities+room->n_exits+1;i++) {
           if (i <= room->n_activities) {
              struct Activity* activity = &game.activities[room->activities[i-1]];
              if (!inRange(activity->timeRange)) {
                 inputI++;
              } else if (i==inputI) {
                 selectActivity(activity);
                 // Remove activity from array
                 room->activities[inputI-1] = room->activities[--room->n_activities];
              }
           } else if (i <= room->n_activities + room->n_exits) {
             struct Exit* selectedExit = &game.exits[room->exits[i-1-room->n_activities]];
             if (!inRange(selectedExit->timeRange)) {
                 inputI++;
             } else if (i==inputI) {
                 game.currentRoom = selectedExit->room;
                 strcpy(game.messages[game.n_messages++], selectedExit->description);
             }
           } else if (i == room->n_activities + room->n_exits + 1) {
                 if (i == inputI && game.heldActivity != NO_HELD_ACTIVITY) {
                    struct Activity* oldHeldActivity = &game.activities[game.heldActivity];
                    game.heldActivity = NO_HELD_ACTIVITY;
                    selectActivity(oldHeldActivity);
               }
           } 
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

void showRoom(int inputI) {
  struct Room* room = &game.rooms[game.currentRoom];
  if (inputI > 0) {
    handleInput(room, inputI);
    increaseTime(0,10);
  }
  room = &game.rooms[game.currentRoom];
  header();
  showOptions(room);
  drawTodos();
  border();
  gotoxy(5,30);
  printf("What do you want to do next?: ");
}

static void sig_handler(int sig)
{
  if (SIGWINCH == sig) {
    header();
    struct Room* room = &game.rooms[game.currentRoom];
    showOptions(room);
    drawTodos();
    border();
    gotoxy(5,30);
    printf("What do you want to do next?: \n");
    gotoxy(38,40);
  }

} // sig_handler


int main( int argc, char *argv[] )  {
    char* fname = "georges.day";
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
       fread(&game, sizeof(struct Game), 1, file);
       fclose(file);
       if (argc == 2) {
          if (strcmp(argv[1],"--interactive") == 0) {
             showRoom(0);
             char* input = malloc(sizeof(char)*10);
             int inputI = 0;
             while (1) {
               fgets(input, 10, stdin);
               if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n')) {
                  input[strlen (input) - 1] = '\0';
               }
             
               sscanf(input, "%d", &inputI);
               showRoom(inputI);
               file = fopen(fname, "w");
               fwrite(&game, sizeof(struct Game), 1, file);
               fclose(file);
             }
          }
          int inputI;
          sscanf(argv[1],"%d",&inputI);
          showRoom(inputI);
       } else {
          showRoom(0);
       }
       file = fopen(fname, "w");
       fwrite(&game, sizeof(struct Game), 1, file);
       fclose(file);
    } else {
      file = fopen(fname, "w");
      printf("0\n");
      game = generateMap();
      struct Exit* nextExit = &game.exits[0];
      strcpy(game.messages[game.n_messages++], nextExit->description);
      showRoom(0);
      fwrite(&game, sizeof(struct Game), 1, file);
      fclose(file);
   }
   return 0;
}
