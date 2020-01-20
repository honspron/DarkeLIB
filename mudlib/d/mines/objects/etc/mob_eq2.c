//Maxwell's Underground Mudlib
//Inherited Equipment Loader
//Coded For DarkeMud By Maxwell
//@Copyright 1996

#include <std.h>
#define WEAP "/wizards/maxwell/objects/weapons/"
#define ARM  "/wizards/maxwell/objects/armour/"
#define VIRTA "d/damned/virtual/"
#define UNDER "/wizards/maxwell/underzone/"

mixed  *names_armour,*paths_armour;
string *armour_name,*armour_path;
string *weapon_single_name,*weapon_both_name;
string *weapon_single_path,*weapon_both_path,wield_hand;
//string *names_armour,*paths_armour;
string *helmet_name,*helmet_path,*glove_name,*glove_path,*pants_name;
string *pants_path,*arm_name,*arm_path,*bodyar_name,*bodyar_path;
int i,x,y,type,num,array_size;
object mob,monster;

//Amour Code
int armour_total_midlevel(){

    helmet_name = ({"leather hat","bandanna","miner hat"});
    helmet_path = ({ARM+"lhat.c",ARM+"bandanna.c",ARM+"mhat.c"});
    glove_name  = ({"leather gloves"});
    glove_path  = ({ARM+"lgloves.c"});
    pants_name  = ({"leather pants","leg guards","corduroy pants"});
    pants_path  = ({ARM+"lpants.c",ARM+"lguards.c",ARM+"pants.c"});
    arm_name    = ({"leather shirt"});
    arm_path    = ({ARM+"lshirt.c"});
    bodyar_name = ({"vest","cloak"});
    bodyar_path = ({ARM+"vest.c",ARM+"cloak.c"});

    names_armour = ({ helmet_name,glove_name,pants_name,arm_name,
                      bodyar_name });
    paths_armour = ({ helmet_path,glove_path,pants_path,arm_path,
                      bodyar_path });
    array_size = sizeof(names_armour);
    y = 0;
    while(y < array_size){
//     armour_name = ({});
//     armour_path = ({});
//     armour_name = current_name;
     armour_name = names_armour[y];
     armour_path = paths_armour[y];
     tell_player(find_player("maxwell"),"Pass "+y+" size array is "+
                array_size);
     i = random(sizeof(armour_name));
     if(!present(armour_name[i],environment(mob)) ){
        tell_player(find_player("maxwell")," equip is "
           +armour_path[i]+" Mob is "+mob->query_name()+"\n");
//           new( armour_path[i] )->move(mob);           
          new( armour_path[i] )->move(find_player("maxwell"));
//          mob->force_me("wear "+armour_name[i]);
     }
     else{
          mob->force_me("get "+armour_name[i]);
          mob->force_me("wear "+armour_name[i]);
     }
     y = y + 1;
   }

}
//Weapon Code
int weapon_code_midlevel(){
    weapon_single_name = ({ "hand axe","crystal dagger","stiletto" });
    weapon_both_name = ({ "sledge","pick","pick-axe","longsword",
      "club","spear" });
    weapon_single_path = ({ WEAP+"handaxe",WEAP+"dagger",WEAP+"stiletto"});
    weapon_both_path = ({ WEAP+"sledge",WEAP+"pick",WEAP+"pick-axe",
      WEAP+"longs",WEAP+"sp-club",WEAP+"spear" });
    type = random(2);
    if(type == 0){
       x = random(sizeof(weapon_single_name));            
       if(!present(weapon_single_name[x],environment(mob))
}
