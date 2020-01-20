//Maxwell's Underground Mudlib
//Inherited Equipment Loader
//Coded For DarkeMud By Maxwell
//@Copyright 1996

#include "/adm/include/std.h"
#define WEAP "/wizards/maxwell/objects/weapons/"
#define ARM  "/wizards/maxwell/objects/armour/"
#define VIRTA "d/damned/virtual/"


mixed  *names_armour,*paths_armour;
mixed  *armour_name,*armour_path,*Types_name,*Types_path;
string *weapon_single_name,*weapon_both_name;
string *weapon_single_path,*weapon_both_path,wield_hand;
string *helmet_name,*helmet_path,*glove_name,*glove_path,*pants_name;
string *pants_path,*bodylo_name,*bodylo_path,*leggin_name,*leggin_path;
string *hat_name,*hat_path,*gaunt_name,*gaunt_path;
string *bodyhi_name,*bodyhi_path,*Types;

int i,x,y,type,num,array_size;
object mob,monster;

//Amour Code
int armour_total_midlevel(string incoming){
string *requested_types;

    hat_name     = ({"leather hat","bandanna","helmet",});
    hat_path     = ({ARM+"lhat",ARM+"bandanna",ARM+"mhelmet",});
    helmet_name  = ({"steel helmet","spiked helmet",});
    helmet_path  = ({ARM+"shelmet",ARM+"sphelmet",});
    glove_name   = ({"leather gloves",});
    glove_path   = ({ARM+"lgloves",});
    gaunt_name   = ({"steel gauntlets","spiked gauntlets",});
    gaunt_path   = ({ARM+"sgaunt",ARM+"spgaunt",});
    pants_name   = ({"leather pants","leg guards","corduroy pants",});
    pants_path   = ({ARM+"lpants",ARM+"lguard",ARM+"pants",});
    leggin_name  = ({"plated pants","leg plates","riveted pants",});
    leggin_path  = ({ARM+"stpants",ARM+"apants",ARM+"rpants",});
    bodylo_name  = ({"vest","cloak","leather shirt",});
    bodylo_path  = ({ARM+"vest",ARM+"cloak",ARM+"lshirt",});
    bodyhi_name  = ({"chain mail","breast plate","body armour",});
    bodyhi_path  = ({ARM+"cmail",ARM+"brstplt",ARM+"bodyar",});

    names_armour = ({});
    paths_armour = ({});

    Types      = ({ "hat","helmet","glove","gaunt","pants","leggin",
                 "bodylo","bodyhi", });
    Types_name = ({hat_name,helmet_name,glove_name,gaunt_name,
                 pants_name,leggin_name,bodylo_name,bodyhi_name,});

    Types_path = ({hat_path,helmet_path,glove_path,gaunt_path,
                 pants_path,leggin_path,bodylo_path,bodyhi_path,});
 
   if(incoming == 0){
    names_armour = ({ hat_name,glove_name,pants_name,bodylo_name });
    paths_armour = ({ hat_path,glove_path,pants_path,bodylo_path });
   }
   else {
     y = 0;
     requested_types = explode(incoming,",");
     while( y < sizeof(Types) ){
       if(member_array(Types[y],requested_types) != -1){
          names_armour += ({ Types_name[y] });
          paths_armour += ({ Types_path[y] });
       }
       y = y + 1;
     }    
   }
   array_size = sizeof(names_armour);
   y = 0;
   while(y < array_size){
      armour_name = names_armour[y];
      armour_path = paths_armour[y];
      i = random(sizeof(armour_name));
//      if(!present(armour_name[i],environment(mob)) ){
      if(!present(armour_name[i]) ){
        if(stringp(armour_path[i]))
           new( armour_path[i] )->move(mob);           
        mob->force_me("wear "+armour_name[i]);
      }
      else {
          mob->force_me("get "+armour_name[i]);
          mob->force_me("wear "+armour_name[i]);
      }
      y = y + 1;
   }
  
}
//Weapon Code
int weapon_code_midlevel(string wep){
    weapon_single_name = ({ "hand axe","crystal dagger","stiletto" });
    weapon_both_name = ({ "sledge","pick","pick-axe",
                          "club","spear" });
    weapon_single_path = ({ WEAP+"handaxe",WEAP+"dagger",WEAP+"stiletto"});
    weapon_both_path = ({ WEAP+"sledge",WEAP+"pick",WEAP+"pick-axe",
                          WEAP+"sp-club",WEAP+"spear" });
    if(wep != 0){
      if(wep == "single")
         type = 0;
      if(wep == "double")
         type = 1;
    }
    else      
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
int weapon_code_highlevel(){
     weapon_single_name = ({ "double dagger","steel dagger","katar"});
     weapon_both_name = ({ "bastard sword","axe","mace","pick-hammer" });
     weapon_single_path = ({ WEAP+"dbl-dg",WEAP+"sdagger",
       WEAP+"katar-dg"});
     weapon_both_path = ({ WEAP+"bs-sword",WEAP+"dhd-axe",WEAP+"sp-mace",
       WEAP+"pick-hammer" });
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
