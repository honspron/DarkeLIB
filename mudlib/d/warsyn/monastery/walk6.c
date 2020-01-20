#include <std.h>

inherit "std/room";

void init()
   {
  :: init();
  add_action("do_drink","drink");
   }
void create() 
   {
     ::create();
     set_property("light", 2);
     set_property("outdoors", 1);
     set_property("no castle", 1);
     set_property("night light", 1);
     set("short","Center of the courtyard.");
     set("long","Here in the center of the courtyard stands a " +
           "fountain. Water sits quietly undisturbed in its basin." +
           "You can see a building further north and to both sides " +
           "of you are smaller buildings. This place could have " +
           "been beautiful once, but it is marred with chaos now.");
     add_item("building","This looks like it was a holy place once");
     add_item("buildings","These look like they once housed pilgrims.");
     add_item("fountain","It looks like the only thing untouched by chaos." +
           "It holds water that looks cold and unmoving.");
     add_item("water","This water looks cold and is very still");
     add_exit("/wizards/warsyn/monastery/walk5","south");
     add_exit("/wizards/warsyn/monastery/walk7","east");
     add_exit("/wizards/warsyn/monastery/walk8","west");
     add_exit("/wizards/warsyn/monastery/walk9","north");   
}

int do_drink(string str)
   {
  if(!str)
   {
    notify_fail("What do you want to drink?\n");
    return 0;
   }
  if(str!="water") 
   {
    return 0;
   }
   this_player()->add_poisoning(100);
  write("You drink the still water. It is tasteless but seems unlike water.");
  say(this_player()->query_cap_name()+" drinks the cool water.",
    this_player());
  return 1;
}
