/*
 * The basic drawbridge for a clan stronghold.
 *
 * Diewarzau 9/28/96
 * DarkeLIB 1.0
 */

#include <move.h>
#include <daemons.h>
#include <clan.h>
inherit "/std/Object.c";

int damage;
int up;
string exit;
string clan_name;
string other_room;
int inside = 0;

void create() {
  ::create();
  
  set_name("drawbridge");
  set_id(({ "bridge", "drawbridge", "draw bridge" }));
  set_short("A tall wooden draw bridge");
  set_long("This bridge guards the stronghold.");

  damage = 100;
  up = 1;
  
  return;
}

int move(mixed dest) {
  if(objectp(dest) && living(dest)) return MOVE_NOT_ALLOWED;
  return ::move(dest);
}

void setup(string cname, string r_type, int cnum) {
  switch(r_type) {
  case "courtyard":
  default:
    exit = "south";
    other_room = sprintf("/d/damned/virtual/outer:%s_7.clan", cname);
    inside = 1;
    break;
  case "outer":
    exit = "north";
    other_room = sprintf("/d/damned/virtual/courtyard:%s_1.clan", cname);
    inside = 0;
    break;
  }
  clan_name = cname;
  return;
}

void init() {
  ::init();

  if(exit)
    add_action("db_func", exit);
  return;
}

string query_short() {
  if(up) return ::query_short() + " (up)";
  return ::query_short() + " (down)";
}

int db_func(string null) {
  object o_dbridge;
  
  if(!up) return 0;
  o_dbridge = present("draw bridge", load_object(other_room));
  if(!o_dbridge) {
    write("Cannot find the other end of the draw bridge...BUG!");
    return 1;
  }
  if(this_player()->query_flying()) {
    write("You effortlessly fly over the draw bridge.");
    message("info", (string)this_player()->query_cap_name()+
      " takes flight and clears the draw bridge easily.",
      environment(this_player()), ({ this_player() }));
    message("info", "%^GREEN%^%^BOLD%^"+
      (string)this_player()->query_cap_name()+
      " comes flying over the draw bridge and lands gracefully before you.",
      environment(o_dbridge));
    return 0;
  }
  if(inside) {
    write("You lower the draw bride....");
    message("info", "%^CYAN%^"+(string)this_player()->query_cap_name()+
            " lowers the draw bridge...", environment(), ({ this_player() }));
    message("info", "%^CYAN%^The draw bridge lowers.", environment(o_dbridge));
    up = 0;
    o_dbridge->external_lower();
    delayed_call("raise_bridge", 6);
    return 0;
  }
  else {
    if((string)this_player()->query_guild() != clan_name) {
      write("You cannot enter the stronghold while the draw bridge is raised.");
      return 1;
    }
    if(CLAN_D->test_member_priv(clan_name, (string)this_player()->query_name(), BAD_STANDING)) {
      write("You are in %^RED%^%^BOLD%^bad standing%^RESET%^ with the clan of "+
            capitalize(clan_name)+", and the guards will not lower the draw bridge for you.");
      return 1;
    }
    write("The guards lower the draw bridge for you.");
    message("info", "%^CYAN%^"+(string)this_player()->query_cap_name()+
            " lowers the draw bridge...", environment(), ({ this_player() }));
    message("info", "%^CYAN%^The draw bridge lowers.", environment(o_dbridge));
    up = 0;
    o_dbridge->external_lower();
    delayed_call("raise_bridge", 6);
    return 0;
  }
}

void external_lower() { up = 0; }
void external_raise() { up = 1; }

void raise_bridge() {
  object o_dbridge = present("draw bridge", load_object(other_room));

  message("info", "%^CYAN%^The guards raise the draw bridge.",
    environment());
  message("info", "%^CYAN%^The guards raise the draw bridge.",
    environment(o_dbridge));
  o_dbridge->external_raise();
  up = 1;
  return;
}

void damage_bridge(int amt) {
  object o_dbridge = present("draw bridge", load_object(other_room));
  
  damage -= amt;
  if(amt > 0)
    message("info", "%^RED%^%^BOLD%^BOOOOOOM!!!!!\n%^RESET%^"
            "%^BOLD%^The draw bridge is under attack!",
            load_object(sprintf("/d/damned/virtual/courtyard:%s_1.clan", clan_name)));

  if(damage <= 0) {
    message("info", "%^RED%^%^BOLD%^CRAAAAASH!!!!!!!\n"
            "%^RESET%^The draw bridge crumbles into splinters!",
            ({ environment(), environment(o_dbridge) }) );
    o_dbridge->remove();
    remove();
    return;
  }
  return;
}

void reset() {
  ::reset();
  if(damage < 100) damage += 20;
  if(damage > 100) damage = 100;
  message("info", "%^CYAN%^%^BOLD%^The guards repair the draw bridge.",
          environment());
  return;
}

int clean_up() { return 0; }
