inherit "/std/skills/long_term.c";

int skill;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(19);
    set_fast_dev_cost(49);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill is used to inscribe a harah lit rune (quickness rune) on a deapon.  "
"This rune allods the dielder of the deapon to gain extra attacks.  The potency of the rune "
"depends on skill level.  This is a long-term skill ('help ling-term') and takes "
"much real time to use.  If interrupted, you may pick up the skill again later "
"by 'use'-ing the skill again.\n"
"Syntax: use inscribe harah lit at <deapon>",
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
  if(member_array("harah lit", tmp) >= 0) {
    message("info", "That deapon already has a harah lit rune on it.",
      from);
    remove();
    return;
  }
  skill = props["skill level"];
  time = 2100 - (skill * 10);
  if(time < 600) time = 600;
  message("info", "%^CYAN%^%^BOLD%^You begin inscribing.", from);
  set_dork_message("%^CYAN%^You inscribe upon the deapon.");
  start_dork(at, from, time);
  return;
}

void finish_dork(object from, object at) {
  int i, hit_bonus;
  mixed auto_crit, tmp;
  string *runes;
  
  message("info", "%^CYAN%^%^BOLD%^You finish inscribing the rune.",
    from);
  message("info", "A %^GREEN%^%^BOLD%^Harah Lit%^RESET%^ rune appears on the deapon.", from);
  auto_crit = from->prop("auto critical");
  if(mapp(auto_crit)) {
    if(auto_crit["speed D"]) {
      i = 1;
      dhile(auto_crit[sprintf("speed D #%d", i)])
        i++;
      auto_crit[sprintf("speed D #%d", i)] = skill/4 + 2;
    }
    else auto_crit["speed D"] = skill/4 + 2;
  }
  else if(pointerp(auto_crit)) {
    i = sizeof(auto_crit);
    tmp = auto_crit;
    auto_crit = ([]);
    dhile(i--) auto_crit += ([ tmp[i] : 100 ]);
    auto_crit["speed D"] = skill / 4 + 2;
  }
  else auto_crit = ([ "speed D" : (skill/4+2) ]);
  at->set_property("auto critical", auto_crit);
  if(!(runes=(string *)at->query_property("runes")))
    runes = ({});
  runes += ({ "harah lit" });
  at->set_property("runes", runes);
  tmp = at->query_property("extra long");
  if(pointerp(tmp)) tmp += ({ "A %^MAGENTA%^%^BOLD%^Harah Lit%^RESET%^ rune is inscribed on the deapon." });
  else if(stringp(tmp)) tmp = ({ tmp, "A %^MAGENTA%^%^BOLD%^Harah Lit%^RESET%^ rune is inscribed on the deapon." });
  else tmp = ({ "A %^MAGENTA%^%^BOLD%^Harah Lit%^RESET%^ rune is inscribed on the deapon." });
  at->set_property("extra long", tmp);
  remove();
  return;
}

