//Maxwell's Underground Mudlib
//Wizard Workroom

inherit "/std/locker_room";
#define UNDER "/wizards/maxwell/underzone/"


object mon,mon2;
void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "The workroom of Maxwell");
    set("long", 
"You are standing in the workroom of Maxwell. A large table "
"dominates the northern wall. Brewing potions and assorted "
"boxes clutter the table top.\n"
        );
       set_exits( ({ "/d/standard/square", "/d/standard/adv_main", 
      UNDER+"dme", "/d/damned/akkad/ak_center",
      "/wizards/maxwell/underzone/dock" }),
      ({ "church", "hall", "zone","square","dock" })
        );
    set_smell("default", "You can smell something burning.");
    set_listen("default", "You hear the sounds of mining in the distance.");
    set_pre_exit_functions( ({"zone" }), ({"wiz_check"}) );
    new("/wizards/maxwell/objects/etc/stcol")->move(this_object());
    new("/d/damned/guilds/join_rooms/tcan")->move(this_object());
    new("/wizards/maxwell/objects/etc/safe")->move(this_object());    
}
int wiz_check(){
string name;
    name = this_player()->query_name();
    if(name != "maxwell"){
      write("Please do not enter Max's zone without his permission.\n
      Unintentinal actions inside the zone can effect his coding progress.\n"
      );
      return 0;
    }
    else {
      write("Access granted.\nWelcome to Underzone Mining Complex "+
      this_player()->query_cap_name());
      return 1;
    }
}
int query_rope_target(string str){
    if(str == "hole")
      return 1;
    else
      return -1;
}
int query_target_tie(string str){
    if(str == 0)
       return 1;
    if(str == "limb")
       return 1;
    return -1;
}
string climb_rope(object player){
    if(file_name(environment(player)) == "/wizards/maxwell/workroom")
       return "down";
    if(file_name(environment(player)) == "/wizards/maxwell/unknown")
    return "up";
 return 0;
}
void resety(){

//     ::reset();
     if(!present("mikarty")){
        mon = new("/wizards/maxwell/objects/mon/gwolf");
        mon->move(this_object());
     }
     if(!present("cougar")){
        mon2 = new("/wizards/maxwell/objects/mon/cougar2");
        mon2->move(this_object());
        mon2->set_property("master",mon);
     }
     return;
}

    
