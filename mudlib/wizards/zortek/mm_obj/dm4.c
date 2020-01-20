//      From Maxwell's Underground mudlib
//         4th Room of Dwarf Mining Zone

#include <std.h>
#define UNDER "/wizards/maxwell/underzone/dm"
#define MY_DAEMON "/wizards/maxwell/underzone/test_daemon"
inherit ROOM;

void init() {
  add_action("mod_foo", "foomod");
}
int mod_foo(string str) {
  MY_DAEMON->set_foo(str);
  return 1;
}
void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "You are standing in an mining tunnel");
    set("long", 
"The tunnel begins to bend to the southwest here. It appears that it "+
"is leading deeper underground. The track begins to slope down and the "+
"tunnel size has expanded. You notice large piles of granite dust along "+
"the side of the tracks. The miners must have to sweep the dust off the "+
"tracks so the carts can roll over them.\n"+ 
"The test daemon variable of foo is:  "+MY_DAEMON->query_foo()
       );
    add_exit("/wizards/maxwell/underzone/dm3","southeast");
    add_exit("/wizards/maxwell/underzone/dm5","southwest");
//    set_exits( ({ "/wizards/maxwell/underzone/dm3", 
//"/wizards/maxwell/underzone/dm5" }),
//      ({ "southeast", "southwest" })
//    );
    set_items( ([
       "track" : "The steel track makes a sharp bend here.",
       "dust" : "The dust is thick and filled with shattered peices of granite.",
      ]) );
       
//    set_smell("default", "It smells like a new immortal in here.");
//    set_listen("default", "You hear the sounds of code creation.");
}
void reset() {
 object mon,mon2,itm;

 ::reset();
   if(!present("mikarty")) {
     mon = new("/wizards/maxwell/objects/mon/gwolf");
     mon->move(this_object());
     mon->weapon_code_midlevel();
     mon->armour_code_midlevel();
     new("/wizards/maxwell/objects/etc/chain")->move(mon);
   }
   if(!present("wolf")) {    
     mon2 = new("/wizards/maxwell/objects/mon/wolf");
     mon2->move(this_object());
     itm = new("/wizards/maxwell/objects/etc/chain");
     itm->move(mon2);
//     new("/wizards/maxwell/objects/etc/gems")->move(bag);            
   }   
}
