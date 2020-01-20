#define SKILLS_AFFECTED ([ "perception" : 4, "conjuration" : 3, "elementalism" : 3, \
    "illusionism" : 3, "body alteration" : 3, "prayer" : 4, "magery" : 3, \
    "spell sense" : 3, "fast casting" : 3, "focus casting" : 3, "concentrate" : 3, \
    "consider" : 3, "animal empathy" : 3, "sorcery" : 2, "focus of elements" : 3, \
    "trade lore" : 3 ])

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","blessing of knowledge");
    set_property("skill","prayer");
    set_property("casting time",5);
    set_property("base mp cost",25);
    set_property("dev cost", 30);
    set_property("fast dev cost", 75);
    set_property("spell level", 4);
    set_property("moon","ankh");
    set_property("caster message","You pray for a blessing of knowledge for $T.");
    set_property("target message","$C prays for a blessing of knowledge for you.");
    set_property("observer message","$C appears to pray for $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "2D6");
    set_property("stats", ({ "intelligence", "wisdom", "charisma" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 160);
    return;
}

int res_spell() { return 1; }

void info() {
message("help",@TEXT
This spell gives a general short-term bonus in skills and stats which
may be useful in a variety of situations.  A target may have up to 2 blessings
of knowlede at a time.  Skills affected are basic skills which employ mental
faculties, and are not used for unholy pursuits (such as picking locks or
controlling demons).
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
//  object ob;
  mapping sk_aff = SKILLS_AFFECTED;

  seteuid(getuid());
  if ((int)at->query("k bless num") >= 2) {
    message("info", (string)at->query_cap_name() +
	    " can receive no additional blessings of knowledge.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) message("info", "The spell's effects are reversed!", caster);
  map_mapping(sk_aff, (: call_other($3, $4, $1, $2 * $5) :),
    at, "add_skill_bonus", ((flag)?-1:1) * power);
  at->set("k bless num", (int)at->query("k bless num") + 1);
  delayed_call("remove_spell", props["duration"], power, at, flag);
  ::spell_func(caster, at, power, args, flag);
  return;
}

void remove_spell(int power, object at, int flag) {
  mapping sk_aff = SKILLS_AFFECTED;
  
  if(!at) {
    remove();
    return;
  }
  message("info", "%^CYAN%^A blessing of knowledge expires.", at);
  map_mapping(sk_aff, (: call_other($3, $4, $1, $2 * $5) :),
    at, "add_skill_bonus", ((flag)?1:-1) * power);
  at->set("k bless num", (int)at->query("k bless num") - 1);
  remove();
  return;
}
