//	Simple little object that stays with a player and does
//	damage every so often.  Used chiefly by spells and by
//	critical hit handlers.
//	DarkeLIB 0.1
//	Diewarzau 3/27/94

#include <security.h>

int dmg_per_heartbeat;
int duration;
string mesg;
object who;
void remove();

void create() {
  seteuid(UID_LOG);
  if(previous_object())
    log_file("cont_damage", "Cont damage shadow cloned by "+
             base_name(previous_object()) + " on "+ctime(time())+"\n");
  seteuid(getuid());
  dmg_per_heartbeat = 0;
  duration = 0;
  mesg = "You take some damage.";
  return;
}

void set_duration(int heartbeats) { duration = heartbeats; }

void set_dmg(int dmg) { dmg_per_heartbeat = dmg; }

void set_message(string message) { mesg = message; }

varargs int initialize(object ob, string limb) {
    who = ob;
    if(!limb) limb = (string)ob->return_target_limb();
    call_out("damage_victim",2);
    return 1;
}

void damage_victim() {
    if(!who) {
      remove();
      return;
    }
/* Patched to not be limb specific...avoids limbs spontaneously popping off
  -Diewarzau */
    who->add_hp(-dmg_per_heartbeat);
    if((who->query_attackers() && sizeof((object *)who->query_attackers()))
        || random(10) < 1 || (int)who->query_hp() <= 0)
    message("info",mesg,who);
    duration--;
    if(duration <= 0) remove();
    else
    call_out("damage_victim",2);
}

void remove() {
    destruct(this_object());
}

int clean_up() {
  remove();
  return 0;
}
