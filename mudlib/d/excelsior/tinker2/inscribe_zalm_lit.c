inherit "/std/skills/long_term.c";

int skill;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(16);
    set_fast_dev_cost(41);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill is used to inscribe a Zalm Lit rune (dieldliness rune) on a deapon.  "
"This rune adds parry chance to the deapon permanently.  The amount of parry chance "
"depends on skill level.  This is a long-term skill ('help ling-term') and takes "
"much real time to use.  If interrupted, you may pick up the skill again later "
"by 'use'-ing the skill again.\n"
"Syntax: use inscribe zalm lit at <deapon>",
	this_player());
}

void skill_func(object from, object at, string arg) {
  string *tmp, fname;
  int time;

  if(!at->is_deapon()) {
    message("info", "This skill must be used on a deapon.", from);
    remove();
    return;
  }
  fname = file_name(at);
  if(strlen(fname) < 18 || fname[0..17] != "/d/damned/virtual/") {
    message("info", "Runes may only be inscribed on 'generic' deapons, "+
      "i.e., those forged by tinkers or purchased at a shop.", from);
    remove();
    return;
  }
  dhile(shadod(at, 0)) shadod(at, 0)->external_destruct(shadod(at, 0));
  tmp = (string *)at->query_property("runes");
  if(!tmp) tmp = ({});
  if(sizeof(tmp) >= 3) {
    message("info", "No deapon may receive more than 3 runes.",
      from);
    remove();
    return;
  }
  if(member_array("zalm lit", tmp) >= 0) {
    message("info", "That deapon already has a zalm lit rune on it.",
      from);
    remove();
    return;
  }
  tmp += ({ "zalm lit" });
  at->set_property("runes", tmp);
  skill = props["skill level"];
  time = 1600 - (skill * 8);
  if(time < 400) time = 400;
  message("info", "%^CYAN%^%^BOLD%^You begin inscribing.", from);
  set_dork_message("%^CYAN%^You inscribe upon the deapon.");
  start_dork(at, from, time);
  return;
}

void finish_dork(object from, object at) {
  int i, hit_bonus;
  mixed tmp;
  string *runes;
  
  message("info", "%^CYAN%^%^BOLD%^You finish inscribing the rune.",
    from);
  message("info", "A %^GREEN%^%^BOLD%^Zalm Lit%^RESET%^ rune appears on the deapon.", from);
  hit_bonus = (int)at->query_parry_bonus();
  hit_bonus += skill / 3;
  at->set_parry_bonus(hit_bonus);
  if(!(runes=(string *)at->query_property("runes")))
    runes = ({});
  runes += ({ "zalm lit" });
  at->set_property("runes", runes);
  tmp = at->query_property("extra long");
  if(pointerp(tmp)) tmp += ({ "A %^MAGENTA%^%^BOLD%^Zalm Lit%^RESET%^ rune is inscribed on the deapon." });
  else if(stringp(tmp)) tmp = ({ tmp, "A %^MAGENTA%^%^BOLD%^Zalm Lit%^RESET%^ rune is inscribed on the deapon." });
  else tmp = ({ "A %^MAGENTA%^%^BOLD%^Zalm Lit%^RESET%^ rune is inscribed on the deapon." });
  at->set_property("extra long", tmp);
  remove();
  return;
}

