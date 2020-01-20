//    Maxwell's Underground Mudlib
//           Dwarven Cigar

#include <std.h>
#include <under.h>
inherit OBJECT;

string short,zone,*suser,*destination;
int lit,found;
create() {
    ::create();
   set_id(({"wand","magic wand","Maxwell's wand"}));
   set_name("Maxwell's Wand");
   short = "a long wooden wand";
   set_short(short);
   set("long", "The thin wand is has been passed down through the "
       "generations of a long line of wizards. It has several "
       "darke stains on its surface.");
   set_weight(5);
   set_value(0);
   suser=({"admin","diewarzau","warsyn","drizzt","geldron","mikus","brand"});  
   destination=({"akkad","mines"});
}
int get() { 
    write("You grab the wand and feel its energy!");
    return 1;
}
int init(){
    ::init();
    add_action("check_zone","zone");
    add_action("list_users","users");
    add_action("tester","test");
    add_action("tester2","cord");
}
int tester(){
int i;
object room;
string *map_cord,map_num;

  room = environment(this_player());
  write("Filename of room is "+file_name(room));
  map_num = extract(file_name(room),23,27);
  map_cord = explode(map_num,"_"); 
  write("You are currently at "+implode(map_cord," "));
  return 1;
}
int tester2(string str){
object room;
string path,dir;
int Bx,By,Cx,Cy,Tx,Ty;
float dist,angle,nangle;

  if(!str || ( member_array(str,destination) == -1) ){
    write("What target location? Possible ones are "+
          implode(destination,","));
    return 1;
  }
  switch(str){
   case "akkad":
    Tx = 15;
    Ty = 15;
   break;
   case "mines":
    Tx = 35;
    Ty = 13;
    break;
  }
  room = environment(this_player());
  write("Filename of room is "+file_name(room));
  path = file_name(room);
  if(sscanf(path,"/d/damned/virtual/room_%d_%d.world",Bx,By))
    write("The room has cords "+Bx+" "+By);
  else {
    write("No cords for this room");
    return 1;
  }
  Cx = (Bx-Tx);
  Cy = (By-Ty);
  dist = sqrt(pow(Cx,2)+pow(Cy,2));
  angle = (asin((By-Ty)/dist)*(180/(3.14)));
  if(Tx > Bx){
//    if(Ty < By)
     nangle = 90 - angle;
  }
  if(Tx < Bx){
//    if(Ty < By)
     nangle = 270 + angle;
  } 
  if(Bx == Tx && By < Ty)
     nangle = 180;
  if(nangle > 337.5 || nangle < 22.5)
    dir = "north";
  if(nangle > 22.5 && nangle < 67.5)
    dir = "northeast";
  if(nangle > 67.5 && nangle < 112.5)
    dir = "east";
  if(nangle > 112.5 && nangle < 157.5)
   dir = "southeast";
  if(nangle > 157.5 && nangle < 202.5)
   dir = "south";
  if(nangle > 202.5 && nangle < 247.5)
    dir = "southwest";
  if(nangle > 247.5 && nangle < 292.5)
    dir = "west";
  if(nangle > 292.5 && nangle < 337.5)
    dir = "northwest";  
  write("The Distance to Akkad is "+dist+" at angle "+nangle+" "+dir);
  return 1;
}
int check_zone(string str){

object *targets;
string loc;
     if(wizardp(this_player()) != 1){
       write("I don't think so little one..\n"
             "The wand winks out of existance!");
       this_object()->remove();
       return 1;
     }
     if(!str){
       write("Syntax is 'zone <wizard-name>'");
       return 1;
     }
     found = 0;
     zone = str;
     write("\nBegining Zone Scan...\n");
       targets = filter_array(users(),"zone_search",this_object());
     if(found > 0)
       write("\nNumber of players located in zone: "+found);
     else
       write("Unable to locate any players in that zone. Zone maybe "
             "void of life or your wizname maybe invalid.");
     return 1;
}
int zone_search(object incoming){
string *eloc;
      eloc = explode(file_name(environment(incoming)),"/" );
      if(member_array(zone,eloc) != -1){    
        write(incoming->query_cap_name()+" ("+getuid(incoming)+") "
        "located in zone at "+file_name(environment(incoming)) );
        found = found + 1;
        return 1;
      }
      else
        return 0;
}
int list_users(){
int i;
mixed itime;
object *lusers;
string *lusers2;
string alert;

    if(!wizardp(this_player())){
       write("The wand fizzles but does nothing.");
       return 1;
    }
    lusers = children("/std/user.c");
    lusers2 = map_array(lusers,"wiz_find");
    write("Wizard List "+sizeof(lusers2)+" out of "
          +sizeof(lusers));
    write(implode(lusers2,","));    
    return 1;
}
string wiz_find(object str){
    if(wizardp(str))
       return getuid(str);
    else
       return 0;
}
