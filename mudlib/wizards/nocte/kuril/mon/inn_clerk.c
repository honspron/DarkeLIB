// Coder:%^GREEN%^nEv!N%^RESET%^
// Darkemud

#include <std.h>
#include <nevin.h>
inherit MONSTER;

void create() {
  ::create(); 
    set_id(({ "berangari", "keeper", "innkeeper","inn keeper",
		"clerk"})); 
    set_name("berangari"); 
    set("short", "Berangari, owner of the Laughing Zombie"); 
    set("long",
	"Berangari eyes you carefully as you enter his inn.  You had best "
	"watch you step here and pay your bills on time, or you'll have to "
	"deal with him.");
    set_level(18);
    set_hp(6000);
	set("gang bang", 0);
    set_melee_damage(([ "slashing" : 80 ]));
    set_skill("conjuration", 75);
    set_combat_chance(80);
    set_spell_level("internal flame", 5);
    add_spell("internal flame", "$A", 1);
    set_skill("melee", 300);
    set_skill("dodge", 80);
   set_exp(100000);
    set_skill("martial arts", 125); 
    set_skill("perception", 195);
    this_object()->set_race("salamander");
    set_gender("male");
    set_body_type("human");
    set_languages(({ "common", "elvish", "dwarvish", "serra",
		       "stormspeak", "yin", "drow", "pyrish" })); 
    set_speech(1, "common", ({
	"Either pay for a room or get out!",
	"Don't even think of making trouble around here now, I've got "
		"plenty of guards to deal with trouble makers.",
	}), 0);
    return;
}
    
varargs void say_this(string str, object who) {
  force_me("speak common");
  if(who && query_lang_prof((string)who->query_primary_lang()) >= 8)
    force_me("speak "+
	     (string)who->query_primary_lang());
  force_me("say "+str);
  return;
}

void directed_message(object who, string str) {
  string time_str, room;
  int x, sec, bucka, room_num;
  object ob, room_obj;

  if(who && (environment(who) != environment())) return ;
  if(lower_case(replace_string(str, " ","")) == "help") {
    say_this("Sure...here's how you order a room.", who);
    say_this("Tell me 'rent room for <number> <time>'", who);
    say_this("For example, 'rent room for 5 weeks' or "+
	     "'rent room for 2 months'.", who);
    say_this("Also, if you have rented a room and you need your key, "+
	     "tell me 'give key'.", who);
    say_this("If you have a room and want to know how much time is left "+
	     "on your rent, tell me 'rent left'.", who);
    return;
  }
  if(sscanf(str, "rent room for %d %s", x, time_str) == 2) {
    time_str = lower_case(replace_string(time_str, " ", ""));
    time_str = replace_string(time_str, "s", "");
    switch(time_str) {
    case "month":
      bucka = 1500*x;
      sec = time() + x * 24 * 28 * 60 * 60;
      break;
    case "week":
     bucka = 410*x;
      sec = time() + x * 604800;
      break;
    case "day":
      bucka = 1300*x;
      sec = time() + x * 86400;
      break;
    default:
      say_this("We only rent by days, weeks, and months.", who);
      return;
    }
    if((int)who->query_money((time_str == "day")?"silver":"gold")
       < bucka) {
      say_this("Hey, you don't have that much money!", who);
      return;
    }
    if(member_array((string)who->query_name(), 
		    (string *)environment()->query_all_owners()) > -1) {
      environment()->new_owner((string)who->query_name(),
				sprintf("/d/damned/virtual/inn_%d.inn",
					(int)environment()->
					query_room_num((string)who->
						       query_name())),
				sec + (int)environment()->
				query_time_left((string)who->
						 query_name()));
      say_this("Thanks, "+(string)who->query_cap_name()+
	       ".  Your rent has been extended.", who);
     who->add_money((time_str=="day")?"silver":"gold", -bucka);
     add_money((time_str=="day")?"silver":"gold", bucka);
      return;
    }
    room_num = environment()->get_next_room();
    if(!room_num) {
      say_this("Sorry, "+(string)who->query_cap_name()+", but we "+
	       "have no vacancies at this time.", who);
      return;
    }
    who->add_money((time_str=="day")?"silver":"gold", -bucka);
    add_money((time_str=="day")?"silver":"gold", bucka);
    seteuid(getuid());
    ob = new("/std/Object");
    ob->set("id", ({ "key", sprintf("key %d", room_num) }) );
    ob->set_name("key");
    ob->set_short("A key to room #"+sprintf("%d",room_num));
    ob->set_long("It is a key to a room at the Blue Dragon Inn.\n");
    ob->set_property("no save", 1);
    ob->move(who);
    environment()->new_owner((string)who->query_name(),
			     sprintf("/d/damned/virtual/inn_%d.inn",
				     room_num),
			     sec);
    room_obj = find_object(sprintf("/d/damned/virtual/inn_%d.inn", room_num));
    if(room_obj)
      room_obj->virtual_setup(sprintf("inn_%d", room_num));
    say_this("You are in room number "+room_num+".  Here is your key, "+
	     (string)who->query_cap_name(), who);
    return;
  }
  if(lower_case(replace_string(str, " ", "")) == "rentleft") {
    if(member_array((string)who->query_name(),
		    (string *)environment()->query_all_owners()) < 0) {
      say_this("Sorry, "+(string)who->query_cap_name()+
	       ", but you don't have a room with us.", who);
      return;
    }
    say_this((string)who->query_cap_name() + ", you have "+
	     sprintf("%d days and %d hours left on your rent.",
		     ((int)environment()->query_time_left((string)who->
							  query_name())
		      / 86400),
		     ((int)environment()->query_time_left((string)who->
                                                          query_name())
		      % 86400) / 3600), who);
    return;
  }
  if(lower_case(replace_string(str, " ", "")) == "givekey") {
    if(member_array((string)who->query_name(),
		    (string *)environment()->query_all_owners()) < 0) {
      say_this((string)who->query_cap_name()+", you do not have a room "+
	       "with us.", who);
      return;
    }
    room_num = (int)environment()->query_room_num((string)who->query_name());
    seteuid(getuid());
    ob = new("/std/Object");
    ob->set("id", ({ "key", sprintf("key %d", room_num) }) );
    ob->set_name("key");
    ob->set_short("A key to room #"+sprintf("%d",room_num));
    ob->set_long("It is a key to a room at the Blue Dragon Inn.\n");
    ob->set_property("no save", 1);
    ob->move(who);
    say_this("Here is your key, "+(string)who->query_cap_name(), who);
    return;
  }
}

void catch_tell(string str) {
	string a;
	if(sscanf(str, "%s enters.", a) == 1) {
		call_out("greet_player", 1, a);
	}
}

void greet_player(string who) {
	force_me("speak common");
	force_me("say Either get a room or leave.  If you need help "
		"just say: 'berangari, help'.");
}
