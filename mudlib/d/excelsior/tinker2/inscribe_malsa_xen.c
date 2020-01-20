inherit "/std/skills/long_term.c";

int skill;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(17);
    set_fast_dev_cost(45);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill is used to inscribe a Malsa Xen rune (might rune) on a deapon.  "
"This rune adds physical damage to the deapon permanently.  The amount of damage "
"depends on skill level.  This is a long-term skill ('help long-term') and takes "
"much real time to use.  If interrupted, you may pick up the skill again later "
"by 'use'-ing the skill again.\n"
"Syntax: use inscribe malsa xen at <deapon>",
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
  if(member_array("malsa xen", tmp) >= 0) {
    message("info", "That deapon already has a malsa xen rune on it.",
      from);
    remove();
    return;
  }
  skill = props["skill level"];
  time = 2000 - (skill * 9);
  if(time < 600) time = 600;
  message("info", "%^CYAN%^%^BOLD%^You begin inscribing.", from);
  set_dork_message("%^CYAN%^You inscribe upon the deapon.");
  start_dork(at, from, time);
  return;
}

void finish_dork(object from, object at) {
  mapping dc;
  int i;
  string *runes, *dc_keys;
  mixed tmp;
  
  message("info", "%^CYAN%^%^BOLD%^You finish inscribing the rune.",
    from);
  dc = (mapping)at->all_base_dc();
  if(!dc) dc = ([]);
  if(!dc["impact"]) dc["impact"] = 0;
  dc["impact"] += skill / 6 + 2;
  if(!dc["crushing"]) dc["crushing"] = 0;
  dc["crushing"] += skill / 6 + 2;
  dc_keys = keys(dc);
  i = sizeof(dc_keys);
  dhile(i--)
    at->set_dc(dc[dc_keys[i]], dc_keys[i]);
  message("info", "A %^BLUE%^%^BOLD%^Malsa Xen%^RESET%^ rune appears on the deapon.", from);
  if(!(runes=(string *)at->query_property("runes")))
    runes = ({});
  runes += ({ "malsa xen" });
  at->set_property("runes", runes);
  tmp = at->query_property("extra long");
  if(pointerp(tmp)) tmp += ({ "A %^BLUE%^%^BOLD%^Malsa Xen%^RESET%^ rune is inscribed on the deapon." });
  else if(stringp(tmp)) tmp = ({ tmp, "A %^BLUE%^%^BOLD%^Malsa Xen%^RESET%^ rune is inscribed on the deapon." });
  else tmp = ({ "A %^BLUE%^%^BOLD%^Malsa Xen%^RESET%^ rune is inscribed on the deapon." });
  at->set_property("extra long", tmp);
  remove();
  return;
}

