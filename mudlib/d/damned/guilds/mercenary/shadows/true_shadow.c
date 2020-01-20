#include <security.h>
 
inherit "/std/spells/shadows/shadow";
 
object who_shadowed;
mapping skills, sk_bonus;
mapping spells, sp_bonus;
string exp_mesg;
 
void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  exp_mesg = mesg;
  if(dur) call_out("expire_skill", dur, this_object());
  return;
}
 
void create() {
 
  sk_bonus = ([]);
  sp_bonus = ([]);
  spells = ([]);
  skills = ([]);
  return;
}
 
void add_skill(string skill, int lev) {
  skills[skill] = lev;
  return;
}
 
void add_spell(string spell, int lev) {
  if(lev > 6) lev = 6;
  spells[spell] = lev;
  return;
}
 
void add_new_skill_bonus(string skill, int bonus) {
  sk_bonus[skill] = bonus;
 
  return;
}
 
void add_spell_bonus(string spell, int bonus) {
  sp_bonus[spell] = bonus;
  return;
}
 
string *query_all_skills() {
  string *res;
 
  res = (string *)next_shadow()->query_all_skills();
  if(!res) res = ({});
  return res + keys(skills);
}
 
string *query_all_spells() {
  string *res;
 
  res = (string *)next_shadow()->query_all_spells();
 
  if(!res) res = ({});
  return res + keys(spells);
}
 
int query_skill(string skill) {
  int res;
 
  res = (int)next_shadow()->query_skill(skill);
  if(skills[skill] && skills[skill] > res) res = skills[skill];
  if(sk_bonus[skill]) res += sk_bonus[skill];
  return res;
}
 
int query_spell_level(string spell) {
  int res;
 
  res = (int)next_shadow()->query_spell_level(spell);
  if(spells[spell] && spells[spell] > res) res = spells[spell];
  if(sp_bonus[spell]) res += sp_bonus[spell];
  if(res < 0) res = 0;
 
  else if(res > 6) res = 6;
  return res;
}
 
void expire_skill(object me) {
  if(me != this_object()) {
    next_shadow()->expire_skill(me);
    return;
  }
  if(exp_mesg) message("info", exp_mesg, who_shadowed);
  remove();
  return;
}
