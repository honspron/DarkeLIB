//      From Maxwell's Underground mudlib
//        34th Room of Dwarf Mining Zone

#include "/adm/include/std.h"

inherit ROOM;
string *weapon_list;

void create() {
    ::create();
    set_property("light", 2);
    weapon_list = ({ "bob","tob" });
    set_property("indoors", 1);
    set("short", "You are crouched in a small crevice under the "
"breakdown.");
    set("long", 
"You are standing in some sort of ancient underground temple. The "
"walls are covered with huge murals depicting the history of the "
"Dwarves. In the center of the room is a stone column that is about "
"four feet high. Three corridors lead out of the room, each between "
"a set of massive stone pillars. In front of each corridor is another "
"column."
        );
    set_exits( ({ "/wizards/maxwell/underzone/dm33",
"/wizards/maxwell/underzone/dm35","/wizards/maxwell/underzone/dm36",
 "/wizards/maxwell/underzone/dm37" }),
      ({ "up","southwest","southeast","north" })
    );
    set_items( ([
       "wood" : "The moldy wood has DYNAMITE stamped on it.",
      ]) );
       set_smell("default", "The dust floating through the air is making "
"it hard to breathe.");
}
void init() {
    add_action("ted","ted");
    add_action("place","place");
    add_action("lay","lay");
}
int place(string str) {
        object sb;
     if(str == "silver blade on the silver column") {
            if(present("silver blade",this_player())) {
                   sb = ("silver blade");
                   write("You place the silver blade on the column. "
"The blade sinks down and locks into place. The column begins to "
"vibrate with small tremors.");
           sb->remove();
return 1;
}
             write("You don't have the silver blade");
             return 1;}
 }
int lay(string str) {
    string what,where;
if(sscanf(str,"%s on the %s",what,where) !=2) return 1;
  if(what == ("silver blade")){
       if(where == ("bed")) {
        write("You lay the blade on the bed.");
        return 1;
        }
      write("Where do you want to lay the blade?");
      return 1;
     }
    write("What are you doing Dave?");
}
int ted(string str) {
    string what;
   if(!str) {
     write("testy 1");
       return 1; }
    if(sscanf(str,"%s",what) !=1) return 1;
   if(member_array(what,weapon_list) == -1) {
      notify_fail("what are you doing dave?");
     return 0;}
     write("You're the man Dave..");
    return 1;
    }
void reset() {
   object sc,wc,gc;
   ::reset();
   if(present("silver column")) return;
   sc = new("/wizards/maxwell/objects/scol");
   sc->move(this_object());
   wc = new("/wizards/maxwell/objects/wcol");
   wc->move(this_object());
   gc = new("/wizards/maxwell/objects/gcol");
   gc->move(this_object());
   }

