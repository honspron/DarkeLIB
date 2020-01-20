// Curtain of Holiness
  
inherit "/wizards/diewarzau/obj/misc/rune";

void create() {
  ::create();
  set_id(({ "curtain of holiness", "curtain" }));
  set_short("%^WHITE%^%^BOLD%^A curtain of holiness%^RESET%^%^MAGENTA%^%^BOLD%^");
  set_long("It shimmers about you with a holy light.");
  set("function", (: call_other, this_object(), "do_explosion" :));
  return;
}

void do_explosion(object who) {
  int dmg, i;
  if( (who->query_race() == "undead") || (who->query_class() ==
	"chaotic-lord") ) {
  dmg = 0;
  for(i=1; i<=10; i++) dmg += 1+random(10);
  dmg *= query_level();
  message("info", "%^WHITE%^%^BOLD%^A curtain of holiness burns away at your "
	"skin!");
  who->do_damage((string)who->return_target_limb(), dmg);
  do_critical(this_object(), who, "holy B", 0);
  return;
  }
  return;
}
