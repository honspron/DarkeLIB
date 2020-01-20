//    Maxwell's Underground Mudlib 
//          Dynamite Crate

inherit "/std/bag_logic";
object player; 
string what;
void create() {
  ::create();
    set_name("wooden crate");
    set_id( ({ "wooden crate","crate","dynocrate" }) );
   set_short("an old wooden crate" );
    set_long("This old wooden crate is covered in mold and dust. The sides "
    "of the crate busted long ago, leaving huge cracks behind.\n"
    "Stamped on the side of the crate is 'DANGER EXPLOSIVE ZIKERT WITHIN "
"DO NOT TAMPER WITH!! \nProperty of Mine Equipment Foreman'");
    set_weight(100);
    set_value(70);
    set_possible_to_close(1);
    set_max_internal_encumbrance(500);
//    new("/wizards/maxwell/objects/weapons/dblock")->move(this_object());
    toggle_closed();
    set_lock("locked");
    set_key("ababababab");
    set_property("magic hold", 500);
}
void init() {
    ::init();
    add_action("open_crate", "open");
    add_action("detect_trap","use");
}
int detect_trap(string str){
int level;
    if(str == "detect trap at crate"){
       level = this_player()->query_skill("detect trap");
       if(level >= 75){
        say(this_player()->query_cap_name()+" inspects the crate for traps "
         "and locates one!");
         write("You find an explosive device!\nDue to the complexity of "
         "the device there is no way to disarm it without setting it off.\n"
         "It is set to trigger when the object is opened");
         return 1;
       }
   }
}  
void open_crate(string str){
   if(str == "crate") write("You carefully try to lift the wooden lid.");
   player = this_player();
   call_out("test_trap",2,this_object());
}
int test_trap(){
object here;
string limb;
int lmd,lcd;
   if(this_object()->receive_objects()){
      tell_object(player,"The chest explodes into flames and bits of "
      "burning splinters!!\nYou are thrown back several feet and by "
      "the force of the blast!");
      here = environment(this_object());
      limb = player->return_target_limb();
      lmd =  player->query_max_dam(limb);
      lcd =  player->query_dm(limb);
      player->do_damage(limb,((lmd-lcd)/2));
      tell_object(player,"Your "+limb+" is severely damaged in the "
      "explosion!!");
  if(here->is_player())
   tell_room(environment(here),player->query_cap_name()+
   " is thrown back as the chest explodes into flames and hot splinters!\n"
+player->query_cap_name()+"'s "+limb+" is severely damaged by the blast!",
   player);
  else
   tell_room(environment(this_object()),player->query_cap_name()+
   " is thrown back as the chest explodes into flames and hot splinters!\n"
+player->query_cap_name()+"'s "+limb+" is severely damaged by the blast!",
   player);
//  if(here->is_player())
// environment(here)->set_long(environment(here)->query_long()+"\nThere "
//"are splinters of wood scattered on the floor and signs of a recent "
//"chemical explosion.\n");
//  else
//      here->set_long(here->query_long()+"\nThere are splinters of wood "
//      "scattered on the floor and signs of a recent chemical explosion.\n");
      remove();
   }
}
//int get() { 
//    if(query("get message")) write(query("get message"));
//    return 0;
//}
