#ifndef STRUCTS_INCLUDED
#define STRUCTS_INCLUDED

struct ActivityRoom {
   int activity;
   int room;
};

struct Activity {
   char title[128];
   char description[128];
   int n_exits;
   int n_activities;
   int exits[10];
   struct ActivityRoom activities[10];
   int todo;
};

struct Exit {
   char title[128];
   char description[128];
   int room;
};

struct Room {
   char title[128];
   char description[128];
   int n_exits;
   int n_activities;
   int exits[10];
   int activities[10];
};

struct Todo {
   char title[128];
   int complete;
};

struct Game {
   struct Room rooms[256];
   int n_rooms;
   struct Activity activities[256];
   int n_activities;
   struct Exit exits[256];
   int n_exits;
   struct Todo todos[256];
   int n_todos;
   char messages[128][128];
   int n_messages;
   int currentRoom;
   int heldActivity;
   int hours;
   int minutes;
};
#endif
