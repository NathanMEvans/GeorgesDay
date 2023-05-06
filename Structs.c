#ifndef STRUCTS_INCLUDED
#define STRUCTS_INCLUDED

struct TimeRange {
   int start;
   int end;
};

struct ActivityTime {
   int activity;
   struct TimeRange time;
};

struct ExitTime {
   int exit;
   struct TimeRange time;
};

struct ActivityRoom {
   struct ActivityTime activity;
   int room;
};

struct ExitRoom {
   struct ExitTime exit;
   int room;
};

struct Activity {
   char title[128];
   char description[128];
   int n_exits;
   int n_activities;
   struct ExitRoom exits[10];
   struct ActivityRoom activities[10];
   int todo;
   int drop;
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
   struct ExitTime exits[10];
   struct ActivityTime activities[10];
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
