#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string exp_mesg;
int heal_bat;
int damage;
int perc;
int power;
int no_heal;

void check_heal();

void check_heal() {
  int roll, i;
  
  if(!who_shadowed) {
    remove();
    return;
  }
  if(no_heal) return;
  no_heal = 1;
  call_out("remove_no_heal", 2);
  if((100 * (int)who_shadowed->query_hp())/(int)who_shadowed->query_max_hp() <
    perc) {
    roll = 0;
    for(i = 1;i<=5;i++) roll += 1+random(4);
    roll *= power;
    damage += roll;
    who_shadowed->heal(roll);
    if(damage >= heal_bat) {
      if(exp_mesg) message("info", exp_mesg, who_shadowed);
      remove();
      return;
    } else {
      message("info", "%^CYAN%^The combat healing spell heals you.\n"+
        "%^BOLD%^Healing battery:%^RESET%^ "+
        sprintf("%d percent full.", (100*(heal_bat-damage))/heal_bat),
        who_shadowed);
    }
  }
  return;
} 

int query_auto_heal() { return 1; }

void remove_no_heal() {
  no_heal = 0;
  return;
}

void create() {
  power = 1;
  heal_bat = 0;
  damage = 0;
  no_heal = 0;
  perc = 1;
}

void set_perc(int x) { perc = x; }
void set_pow(int x) { power = x; }

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  heal_bat = dur;
  exp_mesg = mesg;
  return;
}

int do_damage(string limb, int amt) {
  int res;

  res = (int)next_shadow()->do_damage(limb, amt);
  check_heal();
  return amt;
}

void heal(int x) {
  next_shadow()->heal(x);
  if(x>=0) return;
  check_heal();
  return;
}

void add_hp(int x) {
  object prev;

  next_shadow()->add_hp(x);
  if(x >= 0) return;
  check_heal();
  return;
}


int can_exceed_max_hp() {return who_shadowed->query_property("allow_over_max");} 
