//Maxwell's Underground Mudlib
//Inherited Equipment Loader
//Coded For DarkeMud By Maxwell
//@Copyright 1996

#include "/adm/include/std.h"
#define WEAP "/wizards/maxwell/objects/weapons/"
#define ARM  "/wizards/maxwell/objects/armour/"
#define VIRTA "d/damned/virtual/"

object mob;
string *armour_name,*armour_path,*weapon_single_name,*weapon_both_name,
*weapon_single_path,*weapon_both_path,wield_hand;
int i,x,type,num;

//Amour Code
int armour_code_midlevel(){
    armour_name = ({ "jacket","vest","pants","gloves" });
    armour_path = ({ VIRTA+"leather-jacket.armour",
                     VIRTA+"leather-vest.armour",
                     VIRTA+"leather-pants.armour",
                     ARM+"gloves" });
    i = random(sizeof(armour_name));
    if(!present(armour_name[i],environment(mob)) ){
          new( armour_path[i] )->move(mob);
          mob->force_me("wear "+armour_name[i]); }
    else{
         mob->force_me("get "+armour_name[i]);
         mob->force_me("wear "+armour_name[i]);
    }
}
//Weapon Code
int weapon_code_midlevel(){
    weapon_single_name = ({ "hand axe" });
    weapon_both_name = ({ "sledge","pick","pick-axe" });
    weapon_single_path = ({ WEAP+"handaxe"});
    weapon_both_path = ({ WEAP+"sledge",WEAP+"pick",WEAP+"pick-axe" });
    type = random(2);
    if(type == 0){
       x = random(sizeof(weapon_single_name));            
       if(!present(weapon_single_name[x],environment(mob)) ){
             new(weapon_single_path[x])->move(mob); }
       else{
           mob->force_me("get "+weapon_single_name[x]);
       }
       mob->force_me("wield "+weapon_single_name[x]+" in "+wield_hand);
    }
    if(type == 1){
       x = random(sizeof(weapon_both_name));
       if(!present(weapon_both_name[x],environment(mob)) ){
            new(weapon_both_path[x])->move(mob); }
       else{
          mob->force_me("get "+weapon_both_name[x]);
       }
       mob->force_me("wield "+weapon_both_name[x]+" in right hand and "
       "left hand");
    } 
    return 1;
}
