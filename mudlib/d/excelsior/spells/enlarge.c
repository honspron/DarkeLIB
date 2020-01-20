// Improved by Excelsior
// 6-9-96

#include <spell.h>

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","enlarge");
    set_property("skill","magery");
    set_property("casting time",8);
    set_property("base mp cost",72);
    set_property("dev cost", 43);
    set_property("fast dev cost", 100);
    set_property("spell level", 9);
    set_property("moon","ankh");
    set_property("caster message","You cast enlarge.");
    set_property("target message","$C casts enlarge.");
    set_property("observer message","$C casts enlarge.");
    set_property("spell type",({ "stat mod" }));
    set_property("target type", "living");
    set_property("must be present",1);
    return;
}

int can_exceed_max_hp() { return 1; }

void info() {
message("help",
"This spell increases your strength and hit points.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int roll, i;
  string wow;
  object ob;
  seteuid(getuid());
  if(flag) {
    message("info", "Instead of charging for battle, you are reduced to "+
      "10 hit points! (oops)", at);
    message("info", (string)at->query_cap_name() +
      " doesn't look too good.", EC, ({ at }));
    at->add_hp(-1 * ((int)at->query_hp() - 10));
    remove();
    return;
  }
  if(caster->query_current_attacker()) {
    message("info", "This spell may not be cast while you are "+
      "in combat.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  
  roll = 0;
  for(i=1;i<5;i++) roll += random(10) + power;
  roll *= power;
  caster->add_hp(roll);
   message("info", (string)at->query_cap_name()+" starts to grow!",
   	environment(caster),({at}));
  message("info","%^BLUE%^Your size increases.",at);
  message("info", "You have been granted "+roll+" extra hp over your max "+
    "for a total of "+(int)at->query_hp()+"!", at);
  i = (random(6) + 1) * power - random(5) + random(5);
  seteuid(getuid());
  ob = new("/std/spells/shadows/stat_shadow");
  ob->set_stat("strength");
  ob->set_mod(i);
  ob->start_shadow(at,300,"%^BLUE%^You shrink down to your normal size.");
  switch(i) {
  	case 0..7:
  		wow = "slightly bigger";
  		break;
  	case 8..14:
  		wow = "dwarfing";
  		break;
  	case 15..20:
  		wow = "enormous";
  		break;
  	case 21..25:
  		wow = "gigantic"; break;
  	case 26..31:
  		wow = "juggernaut"; break;
  	case 32..35:
  		wow = "absolutely humungous"; break;
  	case 36..10000:
  		wow = "unstoppable behemoth"; break;
  }
  message("info","Size: %^RED%^"+wow,at);
  remove();
  return;
}

