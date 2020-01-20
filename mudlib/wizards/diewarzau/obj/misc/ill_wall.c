//  An illusionary wall.

inherit "/wizards/diewarzau/obj/misc/wall";

void create() {
  ::create();
  set_function("do_illusion");
  set_short("A big ass brick wall");
  set_id(({ "wall", "big wall", "brick wall", "big ass brick wall" ,
      "illusionary wall" }));
  set_long("It looks like there is no getting around it.");
  return;
}

int do_illusion(object who) {
  string query_str;

  query_str = sprintf("ill fooled:%s", file_name(this_object()));
  if((who->query(query_str) && time() - (int)who->query(query_str) < 30) ||
    skill_contest(60 + 10*query_power(), (int)who->query_stats("intelligence"), 1) != 2) {
    message("info", "You bump into a big ass brick wall.", who);
    message("info", (string)who->query_cap_name()+ " bumps into a "+
      "big ass brick wall.", environment(who), ({ who }));
    who->set(query_str, time());
    return 1;
  }
  else
    return 0;
}

    
