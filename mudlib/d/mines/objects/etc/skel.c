//   Maxwell's Underground Mud Library   
//              Skeleton   

inherit "/std/container";

void create() {
    set_id( ({"skeleton"}) );
    set_name("skeleton");
    set_short("A rotting skeleton");
    set_long("A rotting skeleton is laying against one of the crates. "
    "It is still clothed in tatered rags, the original material rotted "
    "away long ago. The miner must have died while waiting for the "
"dwarves to break through the rubble. Sticking out from some of the old "
"garments and blocked by a bone is a strange looking wooden shaft. It "
"looks like you could free it by moving the bone.");
    set_weight(2000000);
    set_value(50);
    set_max_internal_encumbrance(500);
}
void init(){
    add_action("bob", "move");
}
int get() { 
    if(query("get message")) write(query("get message"));
    return 0;
}
int look() {
    write("Hey stupid");
    return 0;
}
int bob(string str){
   object shaft,bones;
     if(str == "bone"){
       shaft = new("/wizards/maxwell/objects/etc/shaft.c");
       shaft->move(this_object());
       bones = new("/wizards/maxwell/objects/etc/bones.c");     
       bones->move(this_object());
// call_other("wizards/maxwell/objects/bones", "droppy");
       write("You pull the bone to the side and the object drops to "
"the ground. The corpse collaspes beneath your fingers in a cloud of "
"dust.");
say(this_player()->query_cap_name()+ " moves a bone in the skeleton " +
"and the corpse collaspes."
       );
       remove();
       return 1;}
}
int dis(string fun){
   remove();
}

