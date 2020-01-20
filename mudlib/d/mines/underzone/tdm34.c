//      From Maxwell's Underground mudlib
//        34th Room of Dwarf Mining Zone

#include <std.h>
#define UNDER "/wizards/maxwell/underzone/"
inherit ROOM;

string *weapon_names,*columns,*placed_pieces;
 
void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "You are standing in some sort of underground temple.\n");
    set("long", 
     "You are standing in some sort of ancient underground temple. The "
     "walls are covered with huge murals depicting the history of the "
     "Dwarves. In the center of the room is a stone column that is about "
     "four feet high. Three corridors lead out of the room, each between "
     "a set of massive stone pillars. In front of each corridor is another "
     "column.\n");
    set_exits( ({ UNDER+"dm44",UNDER+"dm35",UNDER+"dm36",UNDER"dm37" }),
               ({ "up","southwest","southeast","north" }) );
    set_items( ([
       "wood" : "The moldy wood has DYNAMITE stamped on it.",]));
    set_smell("default", "The dust floating through the air is making "
                "it hard to breathe.");
//Quest Code
    columns = ({"silver column","gold column","wooden column"});
    weapon_names = ({"silver blade","gold blade","shaft"});
    placed_pieces = ({});

    new("/wizards/maxwell/objects/etc/scol")->move(this_object());
    new("/wizards/maxwell/objects/etc/wcol")->move(this_object());
    new("/wizards/maxwell/objects/etc/gcol")->move(this_object());   
    new("/wizards/maxwell/objects/etc/gong")->move(this_object());
}
void init() {
   ::init();
    add_action("place","place");
}
int place(string str) {
string what,where;

 if(!str) {
   write("Place what? Where?");
   return 1;
 }
 if(str == "blade"){
    write("Place which blade where?");
    return 1;
 }
  if(sscanf(str,"%s on %s",what,where));
      { 
      if(member_array(what,weapon_names) != -1){
        if(!present(what,this_player())){
           write("You don't have the " + what+"!");
           return 1;
         }                         
         if(member_array(where,columns) != -1){
            if(member_array(what,placed_pieces) != -1){
             write("That piece has already been placed!");
             return 1;
           }
           if(member_array(where,columns)==member_array(what,weapon_names)){ 
              write("You place the "+what+" on the "+where+". It "
              "slides down inside the column and locks in place");
             say(this_player()->query_cap_name()+ " places the "+what+
                "on the "+where+". It slides down and locks in place.");
             tell_room(UNDER+"dm34","The column begins to shake and hum");
            (present(what, this_player()))->remove();
             placed_pieces += ({what});
             (present("silver column"))->desc();
              call_out("quest",1,this_player());
           }
           else {
             write("It doesn't seem to fit there.");
             say(this_player()->query_cap_name()+" tries to put the "+what
                +" on the "+where+". However it doesn't fit.");
           }
           return 1;
 
         }
         else
            write("Where do you want to place the " + what + "?");
         return 1;
      }         
  }
}
void quest(){
  if(sizeof(placed_pieces) == 2) {
     tell_room(UNDER+"dm34","The colunms begin to vibrate and a low "
        "pulsing sound fills the room. A layer of dark colored mist "
        "slowly forms above the stone floor. The mist slowly swirls "
        "around your feet.\n");
     call_out("quest2",8,this_object()); 
  }  
  return;
}

void quest2(){
  tell_room(UNDER+"dm34","Crack! Three bright beams of light suddenly "
      "radiate out of the columns! The beams stretch out and connect "
      "together in the center of the room. A bright green orb of light "
      "forms where the beams collide. It slowly begins to rotate as tiny "
      "bolts of electricity shoot off its surface.\n");
   call_out("quest3",8,this_object());
   return;
}
void quest3(){
  tell_room(UNDER+"dm34","The orb begins to rotate faster and you can "
      "see an object forming inside. The object becomes more solid as "
      "huge bursts of energy pulsate out of the columns. After another "
      "few seconds the object becomes a spining axe. The orb shatters in "
      "a flash of intense light and the axe slowly lowers to the ground!\n"
      "The three columns quickly sink down into the stone floor.\n");
    (present("silver column",this_object()))->remove();
    (present("gold column",this_object()))->remove();
    (present("wooden column",this_object()))->remove();
  new("/wizards/maxwell/objects/weapons/daxe.c")->move(this_object());
  return;
}

