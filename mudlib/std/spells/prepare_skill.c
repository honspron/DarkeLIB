inherit "/std/spells/spell";

object me;
string skill;
string lender;
int spell_pow;

void create() {
    ::create();
    set_property("name","prepare skill");
    set_property("skill","enchantment");
    set_property("casting time",9);
    set_property("base mp cost",41);
    set_property("dev cost", 82);
    set_property("fast dev cost", 250);
    set_property("spell level", 16);
    set_property("moon","luna");
    set_property("caster message","You cast prepare skill at $T.");
    set_property("target message","$C casts prepare skill at you.");
    set_property("observer message","$C casts prepare skill at $T.");
    set_property("spell type",({ }));
    set_property("target type", "player");
    set_property("must be present", 1);
    set_property("duration", "until quit");
    return;
}

void info() {
message("help",
"This spell is necessary to use in conjunction with the "
"'imbue skill' spell if you wish to imbue a skill which you "
"do not have.  It allows you to 'borrow' a skill from a player (players only) "
"for the sole purpose of casting imbue skill.  The skill borrowed will be at full level ONLY "
"if the spell is cast at level 6, otherwise it will be reduced.  Once the spell is cast "
"on a player, he/she must type 'allow <caster>' (<caster> is you) in 60 seconds or "
"the spell will fail.\n"
"Syntax: cast *3 prepare skill at <player> with <skill>\n"
"NOTE: You can only borrow one skill at a time.  The last one borrowed "
"will take precedence.  This spell may ONLY be cast on players your level or "
"lower.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
  
  if(!args) {
    message("info", "See 'help spell prepare skill' for syntax.",
        caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  me = caster;
  skill = lower_case(args);
  if(flag) {
    if(!at->query_skill(skill)) {
      message("info", "The spell merely fails.", caster);
      remove();
      return;
    }
    message("info", "You accidentally rob "+
      (string)at->query_cap_name()+" of part of the skill temporarily.",
      caster);
    at->add_skill_bonus(skill, -1 * power * random(10));
    remove();
    return;
  }
  if(!at->query_skill(skill)) {
    message("info", "That palyer does not have the skill: '"+skill+
          ".", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!at->skill_exists(skill)) {
    message("info", "You cannot borrow a skill that a player received "+
      "through magic items or other bonuses, only through training.",
      caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if((int)at->query_level() > (int)caster->query_level()) {
    message("info", "That player is higher level than you.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  seteuid(getuid());
  ob = present("borrow soul", at);
  if(ob) ob->remove();
  ob = new("/wizards/diewarzau/obj/misc/borrow_soul");
  ob->set_allow(caster, this_object());
  ob->move(at);
  message("info", "You have 60 seconds to type 'allow "+
    (string)caster->query_name()+"' to lend your "+
    skill+" skill.", at);
  spell_pow = power;
  lender = (string)at->query_cap_name();
  call_out("expire_time", 60);
  return;
}

void expire_time() {
  if(!me) {
    remove();
    return;
  }
  message("info", lender+" has not responded.  Your spell fails.",
    me);
  remove();
  return;
}

void allowed(object who) {
  int skill_lev;
  
  if(!me) return;
  skill_lev = (int)who->query_base_skill(skill);
  skill_lev = skill_lev * spell_pow /6;
  message("info", "Skill: "+skill+" prepared at level "+
    skill_lev+"%.", me);
  me->set("borrowed skill", skill);
  me->set("b skill lev", skill_lev);
  return;
}

