inherit "/std/skills/long_term";

string name, key_id;
object blank;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(33);
    set_fast_dev_cost(102);
    set_property("no target", 1);
    set_property("prereq", "pick locks");
}

void info() {
message("help",
"This is a more useful version of the pick locks skill.  See "
"'help skill pick locks'.  It allows you to actually fashion a key to fit "
"a particular lock, which may be kept for later use.  This is a long-term "
"skill, which may be interrupted and picked up with a partially worked "
"key blank at a later time...see 'help long-term'.\n"
"Examples:\n"
"    use lock smithing at iron door\n"
"    use lock smithing at chest 2\n"
"NOTE: They key is made of soft metal, and will wear out after some time.",
this_player());
}

void skill_func(object from, object at, string arg) {
  int lock_lev, time, i;
  object *blanks;
  object ob, ob2;

  ob = present(arg, environment(from));
  if(!ob && !environment(from)->query_locked(arg)) {
    message("info", 
	    "There is no locked door or object of that description here.",
	    from);
    remove();
    return;
  }
  if(!present("key blank", from)) {
    message("info", "You need a key blank to do that.", from);
    remove();
    return;
  }
  if(from->query("lock picking")) {
    message("info", "You may not do this while you are working on another lock"
	, from);
    remove();
    return;
  }
  if(ob) {
    if(member_array("std/bag_logic.c", deep_inherit_list(this_object()))
       < 0) {
      message("info", "That doesn't have a lock.", from);
      remove();
      return;
    }
    if(!ob->query_locked()) {
      message("info", "It is not locked!", from);
      remove();
      return;
    }
    lock_lev = (int)ob->query_lock_level();
    name = lower_case((string)ob->query_short());
    key_id = ob->query_key();
  } else {
    lock_lev = environment(from)->query_lock_level(arg);
    key_id = environment(from)->query_key(arg);
    name = arg;
  }
  time = lock_lev*3 - (props["skill level"] / 10);
  if(time < 1) time = 1;
  blanks = filter_array(all_inventory(from), "is_key_blank", this_object());
  i = 0;
  if(!sizeof(blanks)) {
    message("info", "BUG, key blank not found....report immediately.", from);
    remove();
    return;
  }
  ob2 = 0;
  while(i < sizeof(blanks))
  {
    if((!ob2 && !blanks[i]->query_property("smithing prog")) ||
       blanks[i]->query_property("progress key:"+key_id))
      ob2 = blanks[i];
    i++;
  }
  if(!ob2) {
    message("info", "You must have a key blank that you have not already "+
	    "used to work on another lock.", from);
    remove();
    return;
  }
  from->set("lock picking", 1);
  props["skill level"] -= lock_lev;
  ob2->set_property("progress key:"+key_id, 1);
  ob2->set_property("smithing prog", 1);
  ob2->set_short("A partial key blank for "+name);
  blank = ob2;
  set_work_message("%^CYAN%^You carefully shape the key blank.");
  start_work(ob2, from, time * 60);
  return;
}

void inc_work_time() {
  if(random(100) < 1) {
    message("info", "Your key blank broke!", environment(blank));
    blank->remove();
    environment(blank)->set("lock picking", 0);
    remove();
    return;
  }
  ::inc_work_time();
}

void move_me(object who) {
  who->set("lock picking", 0);
  ::move_me(who);
  return;
}

void finish_work(object from, object key) {
  object ob;

  message("info", "You have successfully constructed a key for "+
	  name+"!", from);
  key->remove();
  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/misc/temp_key");
  from->set("lock picking", 0);
  ob->move(from);
  ob->set_key_id(key_id);
  remove();
  return;
}

int is_key_blank(object item) {
  if(item->id("key blank")) return 1;
  return 0;
}

