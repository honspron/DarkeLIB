inherit "std/room";

int tower();
int read(string str);

void create() {
   object ob;
  ::create();
    set_property("light",3);
    set_property("night light", 3);
    set_property("no scry",1);
    set_property("no attack",1);
    set_property("no spell",1);
    set_property("vote",1);
    
    set("short","Council Vote Room");
    set("long",@TEXT
TEXT
);
    add_exit("/d/damned/akkad/council_v_room", "vote");
    ob=new("/d/damned/akkad/voteboard");
}

void init() {
   ::init();
}
