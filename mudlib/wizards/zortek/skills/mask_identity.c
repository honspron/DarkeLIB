inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(20);
    set_fast_dev_cost(50);
    set_property("no target", 1);
}

void info() {
message("help",@TEXT
This discipline allows the caster to project an alternate identity of
himself into the minds of those around him (effectively masking his
true identity).
Syntax:  use mask identity at <player>    Mask your identity as <player>
         use mask identity                Stop projecting your mask
TEXT
,this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;
  object pl;

  if(ob = (object)from->query("mask shad")) {
    message("my_action", "You stop projecting your mask.", from);
    ob->external_destruct(ob);
    message("other_action", (string)from->query_cap_name()+
	    " suddenly looks like someone else.",
	    environment(from), ({ from }));
    from->set("mask shad", 0);
    if(!arg || !strlen(arg)) {
      remove();
      return;
    }
  }
  if(!arg) {
    message("info", "You do not have your identity masked at the moment.", from);
    remove();
    return;
  }
  if(!pl = find_player(lower_case(arg))) {
    message("info", "That player cannot be located, thus without an idenity pattern your attempt at this discipline fails.", from);
    remove();
    return;
  }
  if(wizardp(pl)) {
    message("info", "Wizard identities are not valid options to use with mask identity.", from);
    remove();
    return;
  }
  message("my_action", "You begin masking your identity as "+
    (string)pl->query_cap_name()+".",from);
  seteuid(getuid());
  ob = new("/std/spells/shadows/mask_shad");
  from->set("mask shad", ob);
  ob->set_my_skill(props["skill level"]+
    ((int)from->query_level()*2));
  ob->set_new_short((string)pl->query_short());
  ob->set_new_cap_name((string)pl->query_cap_name());
  ob->start_shadow(from);
  remove();
  return;
}
