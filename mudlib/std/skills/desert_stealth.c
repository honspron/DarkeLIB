// Coder: %^YELLOW%^nEv!N%^RESET%^
// Darkemud
// Desert Stealth
// Modified from the woodland_stealth.c code

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(9);
    set_fast_dev_cost(25);
    set_property("no target", 1);
}

void info() {
message("help",
"This skill works just like the other 'stealth' skills except that it will "
"only work in the high desert.  When using this skill, the player will "
"attempt to hide behind sand dunes and use them to move unnoticed.  "
"Player and monsters with high perception skill will be able to see "
"your movements.\n\n"
"Usage: use desert stealth (toggles skill on and off)\n",
this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;

  if(ob = (object)from->query("desert shad")) {
    message("my_action", "You stop using desert stealth.", from);
    ob->external_destruct(ob);
    from->set("desert shad", 0);
    remove();
    return;
  }
  message("my_action", "You look for some sand dunes to hide behind.", 
	  from);
  seteuid(getuid());
  ob = new("/wizards/nevin/shadows/desert_shadow");
  from->set("desert shad", ob);
  ob->start_shadow(from);
  remove();
  return;
}
