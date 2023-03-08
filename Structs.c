#ifndef STRUCTS_INCLUDED
#define STRUCTS_INCLUDED

struct Activity {
   char title[128];
   char description[128];
   int n_exits;
   int n_activities;
   struct Exit* exits[10];
   struct Activity* activities[10];
};

struct Exit {
   char title[128];
   char description[128];
   struct Room* room;
};

struct Room {
   char title[128];
   char description[128];
   int n_exits;
   int n_activities;
   struct Exit* exits[10];
   struct Activity* activities[10];
};

#endif
