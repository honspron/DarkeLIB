//  A saving key rack!
//  -Diewarzau 1/30/96
//  DarkeLIB 1.0
#include <security.h>
#include <move.h>
#define SAVE_FILE "/d/damned/data/castle_rack"

inherit "/std/Object";

mapping allowed;

void save_this();

void save_this() {
  seteuid(UID_DAMNED_DATA);
  save_object(SAVE_FILE);
  seteuid(getuid());
  return;
}

int move(mixed dest) {
  if(objectp(dest) && living(dest)) return MOVE_NOT_ALLOWED;
  else return ::move(dest);
}

void create() {
  ::create();
  allowed = ([]);
  set_name("key rack");
  set_id(({ "rack", "key rack" }));
  set_short("A key rack");
  set_long(
  "This key rack contains various castle keys.\n"
  "You may get your key with 'take key'\n"
  "You may allow another player to get your key with 'allow key <player>'\n"
  "You may disallow a player after you have allowed him/her by typing 'unallow key <player>'\n"
  "You may get another player's key (must be allowed) by typing 'take <player> key'\n"
  "To see who is allowed to get your key, type 'allow list'.\n"
  "Taking any key costs 2 gold.\n");
  seteuid(UID_DAMNED_DATA);
  if(file_exists(SAVE_FILE+".o"))
    restore_object(SAVE_FILE);
  seteuid(getuid());
  return;
}

void init() {
  ::init();
  add_action("take_key", "take");
  add_action("allow_player", "allow");
  add_action("unallow_player", "unallow");
  return;
}

int take_key(string str) {
  object ob;
  string plyr;

  if(lower_case(str) == "key") plyr = (string)this_player()->query_name();
  else if(sscanf(str, "%s key", plyr) != 1)
    return notify_fail("Syntax: 'take key' or 'take <player> key'\n");
  else {
    if(present((lower_case(plyr)+" castle key"), this_player())) {
      write("You already have that key.");
      return 1;
    }
    if((int)this_player()->query_money("gold") < 2) {
      write("You must pay a fee of 2 gold to take the key.");
      return 1;
    }
    this_player()->add_money("gold", -2);
    plyr = lower_case(replace_string(plyr, "'s", ""));
    if(plyr != (string)this_player()->query_name() &&
      (!allowed[plyr] || member_array((string)this_player()->query_name(),
          allowed[plyr]) < 0))
    {
      write("You are not allowed to get "+capitalize(plyr)+"'s key.");
      return 1;
    }
  }
  ob = new("/std/Object");
  ob->set_property("no save", 1);
  ob->set_weight(4);
  ob->set_value(0);
  ob->set_short("A key to "+capitalize(plyr)+"'s Castle");
  ob->set_id(({ "key", "castle key", plyr+" castle key" }));
  ob->set_long(
  "This key will open any doors (but not chests) in "+capitalize(plyr)+"'s castle.");
  if((int)ob->move(this_player()) != MOVE_OK) {
    write("Amazingly, the key is too heavy, and you drop it.");
    ob->move(environment(this_player()));
    message("info", "HEY EVERYONE! "+(string)this_player()->query_cap_name() +
        " just dropped a castle key!  Get it quick and run!",
        environment(this_player()), ({ this_player() }));
  }
  return 1;
} 

int unallow_player(string str) {
  string plyr, me;
  int i;

  me = (string)this_player()->query_name();
  if(sscanf(str, "key %s", plyr)) {
    plyr = lower_case(plyr);
    if(!allowed[me]) allowed[me] = ({});
    else if(member_array(plyr, allowed[me]) < 0) {
      write("That player is already not allowed to get your key.");
      return 1;
    }
    allowed[me] -= ({ plyr });
    write(capitalize(plyr) + " is not allowed to get your key anymore.");
    save_this();
    return 1;
  }
  notify_fail("Syntax: 'unallow key <player>'\n");
  return 0;
}

int allow_player(string str) {
  string plyr, me;
  int i;

  me = (string)this_player()->query_name();
  if(sscanf(str, "key %s", plyr)) {
    plyr = lower_case(plyr);
    if(!allowed[me]) allowed[me] = ({});
    else if(member_array(plyr, allowed[me]) >= 0) {
      write("That player is already allowed to get your key.");
      return 1;
    }
    allowed[me] = distinct_array(allowed[me] + ({ plyr }));
    write(capitalize(plyr) + " is now allowed to get your key.");
    save_this();
    return 1;
  }
  if(str == "list") {
    if(!allowed[me]) {
      write("No one except you can get your key.");
      return 1;
    }
    write("Players allowed to get your key:\n\n"+format_page(allowed[me], 2));
    return 1;
  }
  notify_fail("Syntax: 'allow key <player>' or 'allow list'\n");
  return 0;
}

