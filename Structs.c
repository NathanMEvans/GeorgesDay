#ifndef STRUCTS_INCLUDED
#define STRUCTS_INCLUDED

struct Activity {
   char* title;
   char* description;
   int n_exits;
   int n_activities;
   struct Exit* exits[10];
   struct Activity* activities[10];
};

struct Exit {
   char* title;
   char* description;
   struct Room* room;
};

struct Room {
   char* title;
   char* description;
   int n_exits;
   int n_activities;
   struct Exit* exits[10];
   struct Activity* activities[10];
};

#endif
