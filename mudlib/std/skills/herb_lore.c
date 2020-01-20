#include "/adm/include/clock.h"

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(11);
    set_fast_dev_cost(30);
    set_property("no target", 1);
}

void info() {
message("help",
        "The resin of the dark purple grass on the Darkemud plains is a "
	"powerful neurotropic which allows magi and the like to regain "
	"magic strength faster than usual.  This skill allows the selection "
	"of the good blades for pressing into a potion.  You will need an "
	"herb press and a vial to receive the tincture.  Note that the "
	"resin also is a very potent narcotic and can interfere with spell "
	"casting.  The use of the darke grass resin for recreational "
	"purposes is *strictly* discouraged.\n"
	"\nCLERIC GENERAL'S WARNING: Consuming darke grass resin can "
        "lead to increased incidence of spell failure.  Do not operate "
	"heavy two-handed swords after consuming this narcotic.\n",
	this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;

  if(!environment(from)->query_terrain() || capitalize((string)
     environment(from)->query_terrain()) != "P") {
    message("info", "You have to be in the plains to use this skill.",
	from);
    return;
  }
  if((time() - (int)from->query_last_use("herb lore")) / MINUTE < 2)
    {
    message("info", "You must wait a little longer before using this skill."
	, from);
    return;
  }
  from->set_last_use("herb lore");
  seteuid(geteuid(this_object()));
  ob = new("/std/Object");
  ob->set_name("grass");
  ob->set_id(({ "grass", "weed", "smoke", "mary jane", "shit",
	"green buddha", "wacky tabackey" }));
  ob->set_short("A small bundle of dark purple grass");
  ob->set_long("This is a bundle of hand selected Darke grass, "+
	"fabelled for its extreme potency.  It is used by magi and "+
	"wizards the world over.");
  ob->set_weight(3);
  message("info", "You pick some grass.", from);
  message("info", capitalize((string)from->query_name()) +
          " picks some grass.", all_inventory(environment(from)),
	  ({ from }));
  switch(props["skill level"] - random(55)) {
  case 99..1000:
    ob->set_property("quality", 10);
    message("info", "Upon inspecting it you exclaim: "+
	    "Dude!  This is the CHRONIC shit!", from);
    message("info", capitalize((string)from->query_name()) + 
	    " exclaims: Dude!  This is the CHRONIC shit!",
	    all_inventory(environment(from)), ({ from }));
    break;
  case 90..98:
    ob->set_property("quality", 9);
    message("info", "Upon inspection, you say: " +
	"This is some potent stuff!", from);
    message("info", capitalize((string)from->query_name()) +
	" says: This is some potent stuff!",
	all_inventory(environment(from)), ({ from }));
    break;
  case 80..89:
    ob->set_property("quality", 8);
    message("info", "Upon inspecting it, you think, 'This is the"+
	    " straight stuff.'", from);
    break;
  case 70..79:
    ob->set_property("quality", 7);
    message("info", "Upon inspecting it, you think, 'This'll make some "+
	"good resin'.", from);
    break;
  case 60..69:
    ob->set_property("quality", 6);
    message("info", "Upon inspecting it, you think, 'Well, it could be "+
	"better, but it'd be a waste not to use the sum bitch.", from);
    break;
  case 50..59:
    ob->set_property("quality", 5);
    message("info", "Upon inspecting it, you are slightly disappointed.",
	from);
    break;
  case 40..49:
    ob->set_property("quality", 4);
    message("info", "Upon inspecting it, you wish you had picked a better "+
	"location.", from);
    break;
  case 20..39:
    ob->set_property("quality", 3);
    message("info", "Upon inspecting it, you decide to save this stuff "+
	"for when your good stuff runs out.", from);
    break;
  case 0..19:
    ob->set_property("quality", 2);
    message("info", "Upon inspecting it, you try to pass it off on your "+
	"friend but he knows better.", from);
    message("info", capitalize((string)from->query_name()) + " tries to "+
	"pass off some really bad grass on you, but you refuse.",
	all_inventory(environment(from)), ({ from }));
    break;
  case -10..-1:
    ob->set_property("quality", 1);
    message("info", "Upon inspecting it, you entertain the idea of throwing "+
	"it away, but then think, 'stuff worth picking is stuff worth "+
	"using.'", from);
    break;
  default:
    message("info", "You think, 'Man this stuff isn't even worth the "+
	"ground it's growing in!' and throw it back.", from);
    message("info", capitalize((string)from->query_name()) +
	" looks at it in disgust and throws it back.",
	all_inventory(environment(from)), ({ from }));
    ob->remove();
  }
  if(objectp(ob))
  ob->move(from);
  remove();
  return;
}

