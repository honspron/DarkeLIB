inherit "/std/Object";

void whee(string who) {
	object ob;
	string stuff,level,finger;
	ob = find_living(who);
	stuff = ob->query_position();
	switch(stuff) {
      case "superuser": level = "%^BOLD%^RED%^God Wizard%^RESET%^RESET%^"; break;
      case "assist":    level = "%^BOLD%^YELLOW%^Head Arch Wizard%^RESET%^"; break;
      case "mentor":    level = "%^BOLD%^PURPLE%^Arch Wizard%^RESET%^"; break;
      case "elder":     level = "%^BOLD%^GREEN%^Elder Wizard%^RESET%^"; break;
      case "wizard":    level = "%^BOLD%^BLUE%^Wizard%^RESET%^"; break;
      case "player":    level = "Mortal"; break;
      default:          level = "Unknown";
    }
    if(archp(this_player()) && !wizardp(ob))
      level = sprintf("%d", ob->query_level());
    finger = "%^BOLD%^CYAN%^Darke Position:\t\t%^RESET%^"+level+"\n";
    write(finger);
}

void init() {
	::init();
	add_action("whee","whee");
}

void create()  {
	::create();
	set("short","stuff");
	set("id",({"stuff"}));
}
