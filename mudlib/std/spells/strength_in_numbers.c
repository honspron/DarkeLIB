inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","strength in numbers");
    set_property("skill","illusionism");
    set_property("casting time",11);
    set_property("base mp cost",41);
    set_property("dev cost", 60);
    set_property("fast dev cost", 140);
    set_property("spell level", 10);
    set_property("moon","warzau");
    set_property("caster message","You call upon strength in numbers for
$T.");
    set_property("target message","$C calls upon strength in numbers for
you.");
    set_property("observer message","$C call upon strength in numbers for
$T.");
    set_property("spell type",({  }));
    set_property("target type", "living");
    set_property("must be present", 1);
    set_property("duration", 40);
    return;
}

void info() {
message("help",
"This spell summons several illusionary copies of the target (equal to "
"2 + power) which will sometimes be mistaken for the target in combat.  The
"
"illusions can only take a few hits before they disappear however.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  object ob;
  int i;

  for(i=1; i <= power+2; i++) {
    ob = new("/wizards/diewarzau/obj/misc/image");
    ob->set_up(at, props["duration"], power);
    ob->move(environment(at));
    if(flag) {
      ob->set_fumble();
      ob->kill_ob(at);
    }
  }
  message("info", "%^BOLD%^%^GREEN%^"+capitalize(consolidate(power +2, "mirror image of "+(string)at->query_cap_name()))+
                  " appear.", environment(at));
  if(flag)
    message("info", "%^BOLD%^%^RED%^The mirror images attack "+(string)at->query_cap_name()+"!", environment(at));
  remove();
  return;
}
