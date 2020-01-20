inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","ward entry");
    set_property("skill","clairvoyance");
    set_property("casting time",1);
    set_property("base mp cost",15);
    set_property("dev cost", 10);
    set_property("fast dev cost", 60);
    set_property("spell level", 3);
    set_property("moon","luna");
    set_property("caster message","You form a psychic link to $T's location.");
    set_property("target message","You feel the presence of another mind.");
    set_property("observer message","$C seems to concentrate intesely.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 0);
    return;
}

void info() {
message("help",@TEXT
This discipline will create a psychic link that will notify the target
of any entry into the room so warded.  The link between the entry ward
and the owner of the ward can be severed at any time by either the owner
or the caster in the room so warded (ie. <sever entry ward>).  Duration
is variable but higher levels of casting rank will dramatically increase
the lasting ability of the ward.  This is a deceptively powerful spell.
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
  int flag2;

  if(flag) {
    remove();
    return;
  }
  if((int)at->query_level() - (int)caster->query_level() > power) {
    message("info", "The power was insufficient for a target of that level.", caster);
    remove();
    return;
  }
  ob = new("/wizards/zortek/spells/entry_ward");
  ob->set_up(caster->query_true_name(), at->query_true_name(), power);
  ob->move(environment(at));
  remove();
  return;
}
