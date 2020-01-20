// level hacking put in by Valodin to enable necromancy
// Modified by Zortek to account for non-corporial beings
// Still under development....hmmm right now it is just a
// very fast decaying "corpse"

#include "/adm/include/std.h"
#include "/adm/include/move.h"

inherit BAG;

#define DECAY_TIME 20
string name;
int decay;
int level;
int old_hp;
int fingers;  /* indication of body type for the time being */
mapping body;
string *wielding_limbs;
string race;
string gender;
int player;

void init() {
  ::init();
  return;
}

void create() {
   set_name("noone");
   name = "noone";
   set_weight(1);
   decay = 2;
   set_id(({"vapor", "vapor of " + name, "remains"}));
   set_max_internal_encumbrance(0);
   level = 0;   
   old_hp = 0;                                                
   fingers = 0;
}

varargs void preserve_me(int time) {
  return;
}
  
int is_player() { return player; }

int is_corpse() { return 0; }
int query_level() {return level;}
void set_level(int lev){level = lev;}
int query_old_hp(){return old_hp;}
void set_old_hp(int num){old_hp = num;}
int query_decay(){return decay;}
void set_fingers(int num){fingers = num;}
int query_fingers(){return fingers;}

prevent_insert() {
   write("The mist is insubstancial.");
   return 1;
}
void set_name(string str) {
   ::set_name(str);
   name = str;
   set("long", "This is the mist of " + name + ".");
   set_id( ({"vapor", "vapor of " + lower_case(name), "remains" }));
   call_out("decay", DECAY_TIME);
}

void decay() {
  decay -= 1;
  if(decay > 0) {
    call_out("decay", 20);
    return;
  }
  remove();
}

int can_put_and_get() { return 1; }

string query_short() {
  if(decay == 2)
    return "the vapor of " + name;
  else
    return "The dispersing vapor of " + name;
}

int remove() {
  object *inv;
  object env, chambre;
  int i;
  
  if(!(env = environment(this_object()))) return ::remove();
  if(!(chambre = environment(env))) return ::remove();
  if(!(i=sizeof(inv=all_inventory(this_object())))) return ::remove();
  while(i--) {
    if(inv[i]->move(env)) {
      tell_object(env, "You drop "+(string)inv[i]->query_short()+" as "+
        query_short()+" disperses into nothing.");
      tell_room(chambre, (string)env->query_cap_name()+" drops "+
        (string)inv[i]->query_short()+" from a dispersing vapor.");
      if(inv[i]->move(chambre)){
        tell_object(chambre,"You cannot carry "+ inv[i]->query_short()+"!");
        tell_room(environment(chambre),(string)chambre->query_cap_name()+" drops "+
                 (string)inv[i]->query_short()+" from a dispersing vapor.",chambre);
         inv[i]->move(environment(chambre));
         return ::remove();
      }
      inv[i]->move(chambre);
      return ::remove();
    }
  }
  return ::remove();
}

int copy_body(object ob){
  string *limb_names;
  int i, lnsz;

  wielding_limbs = (string *)ob->query_wielding_limbs();
  body = ([]);
  limb_names = (string *)ob->query_limbs();
  for(i = 0, lnsz = sizeof(limb_names); i < lnsz; i++) {
    body[limb_names[i]] = ([
      "limb_ref": ob->query_reference(limb_names[i]),
      "max_dam": ob->query_max_dam(limb_names[i]),
      "damage": ob->query_dam(limb_names[i]), 
      "ac": ob->query_ac(limb_names[i])
    ]);
  }
  fingers = ob->query_fingers();
  old_hp = ob->query_max_hp();
  level = ob->query_level();
  player = ob->is_player();
  gender = ob->query_gender();
  race = ob->query("race");
}

int make_new_body(object ob){
  int i, lnsz;
  string *limb_names;

  ob->set_level(level);
  ob->set_max_hp(old_hp);
  ob->set_fingers(fingers);
  limb_names = keys(body);
  for(i = 0, lnsz = sizeof(limb_names); i < lnsz; i++){
    ob->add_limb(limb_names[i],
      body[limb_names[i]]["limb_ref"],
      body[limb_names[i]]["max_dam"], 
      body[limb_names[i]]["damage"],
      body[limb_names[i]]["ac"]
    );
  }
  ob->set_wielding_limbs(wielding_limbs);
  ob->set_zombie_name(name, decay);
  ob->set("race", race);
  ob->set_gender(gender);
}

