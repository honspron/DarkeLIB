#define CASTING_SKILLS ({ "conjuration", "prayer", "sorcery", "illusionism", \
        "magery", "necromancy", "elementalism", "body alteration", "concentrate" })
#define COMBAT_SKILLS ({ "attack", "dodge", "parry", "block", "melee", \
        "dual attack", "offhand training" })

inherit "/std/skills/skill.c";

string result(int res);

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(12);
    set_fast_dev_cost(37);
    set_property("target type", "living");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill may be used to consider potential opponents.  It will provide "
"a guess as to how well you would fare against the opponent in combat based "
"on several factors.  The higher your skill, the more accurate the estimate.\n"
"Usage: use consider at <target>",
	this_player());
}

void skill_func(object from, object at, string arg) {
  int lev, hp, mp, casting_skill, combat_skill, i, m_damage, *dmg;
  mapping tmp;

  lev = -1*(int)at->query_level() + (int)from->query_level();
  message("info", "You consider "+(string)at->query_short()+".", from);
  message("info", "Overall, compared to "+objective(at)+", you seem: "+
        result(lev), from);
  if(props["skill level"] <= 30) {
    remove();
    return;
  }
  message("info", "\nIn the following areas, compared to "+
        objective(at)+", you seem:\n", from);
  hp = -1*(int)at->query_max_hp()/150 + (int)from->query_max_hp()/50;
  mp = -1*(int)at->query_max_mp()/150 + (int)from->query_max_mp()/40;
  message("info", "Hit points: "+result(hp)+"\nMagic points: "+result(mp),
    from);
  if(props["skill level"] <= 50) {
    remove();
    return;
  }
  tmp = (mapping)at->query_property("melee damage");
  if(!tmp) m_damage = 0;
  else {
    dmg = values(tmp);
    i = sizeof(dmg);
    while(i--) m_damage -= dmg[i];
  }
  tmp = (mapping)from->query_property("melee damage");
  if(!tmp) m_damage += 0;
  else {
    dmg = values(tmp);
    i = sizeof(dmg);
    while(i--) m_damage += dmg[i];
  }
  m_damage /= 6;
  message("info", "Bare-handed damage: "+result(m_damage), from);
  if(props["skill level"] <= 75) {
    remove();
    return;
  }
  i = sizeof(COMBAT_SKILLS);
  combat_skill = 0;
  while(i--) combat_skill -= (int)at->query_skill(COMBAT_SKILLS[i]) -
        (int)from->query_skill(COMBAT_SKILLS[i]);
  i = sizeof(CASTING_SKILLS);
  casting_skill = 0;
  while(i--) casting_skill -= (int)at->query_skill(CASTING_SKILLS[i]) -
        (int)from->query_skill(CASTING_SKILLS[i]);
  combat_skill /= 30;
  casting_skill /= 30;
  message("info", "Combat skills: "+result(combat_skill) +
      "\nCasting skills: "+result(casting_skill), from);
  remove();
  return;
}

string result(int res) {
  switch(res) {
  case -10000..-20:
    return "Don't even THINK about it!";
  case -19..-17:
    return "extremely poor";
  case -16..-13:
    return "poor";
  case -12..-6:
    return "noticably lacking";
  case -5..-4:
    return "below average";
  case -3..-1:
    return "slightly worse";
  case 0..2:
    return "about even";
  case 3..4:
    return "slightly better";
  case 5..7:
    return "noticably better";
  case 8..11:
    return "quite a bit better";
  case 12..15:
    return "substantially better";
  case 16..17:
    return "A WHOLE lot better";
  case 19..10000:
    return "You will effortlessly kick ass here.";
  default:
    return "About even...";
  }
}

    
