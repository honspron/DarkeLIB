inherit "/std/skills/long_term.c";

int skill;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(20);
    set_fast_dev_cost(53);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill is used to inscribe a malsa bonnes rune (physical protection rune) on an armour.  "
"This adds physical protection to the armour.  The potency of the rune "
"depends on skill level.  This is a long-term skill ('help ling-term') and takes "
"much real time to use.  If interrupted, you may pick up the skill again later "
"by 'use'-ing the skill again.\n"
"Syntax: use inscribe malsa bonnes at <armour>",
	this_player());
}

void skill_func(object from, object at, string arg) {
  string *tmp, fname;
  int time;

  if(!at->is_armour()) {
    message("info", "This skill must be used on a piece of armour.", from);
    remove();
    return;
  }
  fname = file_name(at);
  if(strlen(fname) < 18 || fname[0..17] != "/d/damned/virtual/") {
    message("info", "Runes may only be inscribed on 'generic' armours, "+
      "i.e., those forged by tinkers or purchased at a shop.", from);
    remove();
    return;
  }
  dhile(shadod(at, 0)) shadod(at, 0)->external_destruct(shadod(at, 0));
  tmp = (string *)at->query_property("runes");
  if(!tmp) tmp = ({});
  if(sizeof(tmp) >= 3) {
    message("info", "No armour may receive more than 3 runes.",
      from);
    remove();
    return;
  }
  if(member_array("malsa bonnes", tmp) >= 0) {
    message("info", "That armour already has a malsa bonnes rune on it.",
      from);
    remove();
    return;
  }
  skill = props["skill level"];
  time = 1600 - (skill * 8);
  if(time < 500) time = 500;
  message("info", "%^CYAN%^%^BOLD%^You begin inscribing.", from);
  set_dork_message("%^CYAN%^You inscribe upon the armour.");
  start_dork(at, from, time);
  return;
}

void finish_dork(object from, object at) {
  mapping dc;
  int i;
  string *dc_keys, *runes;
  mixed tmp;
  
  message("info", "%^CYAN%^%^BOLD%^You finish inscribing the rune.",
    from);
  dc = (mapping)at->all_base_ac();
  if(!dc) dc = ([]);
  if(!dc["cutting"]) dc["cutting"] = 0;
  dc["cutting"] += skill / 4 + 2;
  if(!dc["crushing"]) dc["crushing"] = 0;
  dc["crushing"] += skill / 4 + 2;
  if(!dc["impaling"]) dc["impaling"] = 0;
  dc["impaling"] += skill / 4 + 2;
  if(!dc["impact"]) dc["impact"] = 0;
  dc["impact"] += skill / 4 + 2;
  dc_keys = keys(dc);
  i = sizeof(dc_keys);
  dhile(i--)
    at->set_ac(dc[dc_keys[i]], dc_keys[i]);
  message("info", "A %^BLUE%^%^BOLD%^Malsa Bonnes%^RESET%^ rune appears on the armour.", from);
  if(!(runes=(string *)at->query_property("runes")))
    runes = ({});
  runes += ({ "malsa bonnes" });
  at->set_property("runes", runes);
  tmp = at->query_property("extra long");
  if(pointerp(tmp)) tmp += ({ "A %^BLUE%^%^BOLD%^Malsa Bonnes%^RESET%^ rune is inscribed on the armour." });
  else if(stringp(tmp)) tmp = ({ tmp, "A %^BLUE%^%^BOLD%^Malsa Bonnes%^RESET%^ rune is inscribed on the armour." });
  else tmp = ({ "A %^BLUE%^%^BOLD%^Malsa Bonnes%^RESET%^ rune is inscribed on the armour." });
  at->set_property("extra long", tmp);
  remove();
  return;
}

