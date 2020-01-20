#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
int    stat_mod;
int    mp_mod;

void create() {
  seteuid(getuid());
  stat_mod = 0;
  mp_mod = 0;
  return;
}

int start_shadow(object ob) {
  
  int dur;
  
  dur=14400; /* 4 hours (16 game); should not happen, sanity check.*/
  seteuid(UID_SHADOW);
  begin_shadow(ob);
  seteuid(getuid());
  who_shadowed = ob;
  ob->add_mp(mp_mod);	/* one time boost to mana */
 "/wizards/stryfe/control" -> add_pawn( file_name( this_object() ) );
  call_out("expire_power_bug", dur, this_object());
  return 1;
}

/* expire the shadow when the day is up */
/* should be called at the start of 'dawn' */
dawn_fun() {
  if(!remove()) return;
  message("info", "Your demonic powers fade with the comming of "
                   "the new day" , who_shadowed);
  return 1;
}

day_fun() { return 1; } 
night_fun() { return 1; } 
dusk_fun() { return 1; }

/* initialization of the strength of the  <demon type> demon power spell */
void set_power(int mp, int stat) { 
  mp_mod = mp; 
  stat_mod = stat; 
}

/* is the current object affected by demon power */
mixed query_property(string what) {
  if(what != "demon power") 
    return (int)next_shadow()->query_property(what); 
  return 1;
}

/* shadow the query_stats function, to increase the players stats */
query_stats(string stat) {

  if( stat == "strength" || stat == "constitution" || stat == "dexterity" ||
      stat == "wisdom" || stat == "intelligence" )
    return (int)next_shadow()->query_stats(stat) + stat_mod;
  else
    if( stat == "charisma" ) 
      return (int)next_shadow()->query_stats(stat) - stat_mod/2;
    else 
      return (int)next_shadow()->query_stats(stat);
}

/* increase the max mana for duration of the spell */
query_max_mp() { 
  return (int)next_shadow()->query_max_mp() + mp_mod; 
}

/* change the characters descriptions when power'd up */
string query_short() {
  return (string)next_shadow()->query_short() + " (demonic aura)";
}

string query_long() {
  return (string)next_shadow()->query_long() +
    	" The eyes and skin seem to pulse with a demonic power";
}

/* this is called via the call_out function in start shadow */
/* this will only be called if, for some reason, the spell */
/* did not terminate with the comming of a new day. */
void expire_power_bug() {
  if(!remove()) return;
  message("info", "For some unknown reason, your demonic powers fade",
          who_shadowed);
  message("bug","demon power is FUBAR'd again!!!",find_living("canute"));
  return;
}
