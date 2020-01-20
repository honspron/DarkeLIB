//    SoulChill Glyph
//    Based upon Diewarzau Runes
//    Zortek 960322
#define CRITS (["1":({"cold A"}),"2":({"cold A","cold A"}),\
  "3":({"cold B","cold A"}),"4":({"cold B","cold B"}),\
  "5":({"cold C","cold B"}),"6":({"cold C","cold C"})])
  
#include <move.h>
#include <rooms.h>
#include <daemons.h>

inherit "/std/Object";

string caster;
string my_file;
string *non_active;
int level;

void remove();
void preserve_me();
int query_level();

int is_glyph() { return 1; }
int query_level() { return level; }
void set_level(int l) { level = l; }

void create() {
  ::create();
  set_name("glyph");
  my_file = 0;
  level = 1;
  non_active = ({});
  set_id(({ "chilling glyph", "soulchill glyph", "glyph" }));
  set_short("%^BOLD%^MAGENTA%^A %^BLUE%^BOLD%^soulchill glyph%^MAGENTA%^BOLD%^");
  set_long(@GLYPH
This shimmering glyph is floating in the air. Potential
power, hidden within the meaning of its shape and movement,
reveal no hints to its function or power.
GLYPH
);
  return;
}

void do_freeze(object who) {
  int dmg, i;

  dmg = 0;
  for(i=1; i<=10; i++) dmg += 1+random(10);
  dmg *= query_level();
  who->do_damage((string)who->return_target_limb(), dmg);
  do_critical(this_object(), who, CRITS[sprintf("%d", query_level())], 0);
  return;
}


void remove() {
  object env;

  ::remove();
  return;
}

void set_dur(int dur) {
  call_out("remove_glyph", dur);
  return;
}

int detect_magic(object who) {
  if(!living(who)) return 0;
  if(caster == (string)who->query_name()) return 1;
  if(random(100) < (int)who->query_skill("detect magic")) return 1;
  if(random(100) < (int)who->query_skill("sense spell")) return 1;
  return 0;
}

void start_preserve() {
  remove_call_out("remove_rune");
  return;
}

void remove_glyph() {
  object *inv;

  inv = filter_array(all_inventory(environment()), "detect_magic", this_object());
  message("info", "%^BOLD%^MAGENTA%^A glyph of power fizzles.", inv);
  remove();
  return;
}

string query_cap_name() { return "Glyph"; }

void set_caster(string str) { caster = str; }

int move(mixed dest) {
  if(objectp(dest) && living(dest)) return MOVE_NOT_ALLOWED;
  return ::move(dest);
}


void preserve_me() {
  int spec;
  string *dir;

  seteuid(getuid());
  remove_call_out("remove_glyph");
  set_property("preserved", 1);
  return;
}

void init() {
  function go_off;
  int save;
  object who;
  
  ::init();
  if((string)this_player()->query_name() == caster) {
    add_action("erase_glyph", "erase");
    return;
  }
  if(query_property("can resist")) {
    if(stringp(query_property("save mod")))
      save = (int)this_player()->query_stats(query_property("save mod"));
    else save = 0;
    save += (int)this_player()->query_property("magic resistance");
    save -= 3 * query_level() - 30;
    if(random(100) < save) {
      message("info", "%^MAGENTA%^BOLD%^You shrug off the power of a glyph.", this_player());
      return;
    }
  }
  this_object()->do_freeze(this_player());
  return;
}

int delay_rune(int delay) {
  if(query("delay")) return 0;
  set("delay", 1);
  set("safe flag", 1);
  call_out("delay_action", delay);
  return 1;
}

int filter_living(object who) { return living(who); }

void delay_action() {
  object *inv, who;
  int i, save;
  function go_off;

  if(!environment()) {
    remove();
    return;
  }
  set("safe flag", 0);
  inv = filter_array(all_inventory(environment()), "filter_living",
      this_object());
  if(inv && (i=sizeof(inv)) && functionp(go_off=query("function"))) {
    while(i--) {
      if(query_property("can resist")) {
        if(stringp(query_property("save mod")))
          save = (int)inv[i]->query_stats(query_property("save mod"));
        else save = 0;
        save += (int)inv[i]->query_property("magic resistance");
        save -= 30 * query_level() - 45;
        if(random(100) < save) {
          message("info", "%^MAGENTA%^BOLD%^You shrug off the effects of a glyph.", inv[i]);
          continue;
        }
      }
      if(caster && (who=find_player(caster)) && !query_property("non-combat"))
        inv[i]->kill_ob(who, 1);
      (*go_off)(inv[i]);
    }
  }
  set("delay", 0);
  remove();
  return;
}

string query_short() {
/*  if(!this_player() || random(100) <
    (int)this_player()->query_skill("detect magic"))
*/
    return ::query_short();
//  return 0;
}

