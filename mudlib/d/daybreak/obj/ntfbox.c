//    A specialized locker which may only contain money.
//    Only saves past reboots if it is in a locker_room.
//    This code has been modified from the Cleric Donation box.
//    DarkeLIB 0.1
//    -Diewarzau 7/29/95
//    Zortek
//    Modified by Traer 7/9/99

#include <std.h>
#include <move.h>
#include <daemons.h>
#include <dirs.h>

inherit BAG;
inherit "/std/money";
inherit "/std/locker_logic";

int max_items;
int closed_weight;
     
void set_max_items(int x) { max_items = x; }
     
status query_is_locker() { return 1; }

void create() {
  set_possible_to_close(1);
  is_closed = 1;
  seteuid(getuid());
  ::create();
  set_storage_key("locker");
  set_max_internal_encumbrance(50000);
  set_property("storage room", 1);
  set_max_items(10);
  set_name("box");
  set_id( ({ "box", "donation box" }) );
  set_short("A donation box");
  set_long("A small yellow sign reads, Donations for the poorest of thieves. Your generosity is greatly appreciated,\n -NTF\n");
  set_weight(100000);
  set_value(10000);
  set_closed_long("This is a donation box that is collected by the volunteers of the NTF. All donations are used to help feed, clothe and care for the neediest of thieves throughout the realms.\n");
  set_open_long("This is a donation box that is collected by the volunteers of the NTF. All donations are used to help feed, clothe and care for the neediest of thieves throughout the realms.\n");
}

status query_is_safe() { return 1; }

string query_long(string str) {
  string desc, *currs, *lines;
  int i;

  desc = ::query_long();
  lines = explode(desc, "\n");
  i = member_array("  It contains:", lines);
  if(i >=0 ) lines = exclude_array(lines, i, sizeof(lines) - 1);
  desc = implode(lines, "\n");
  desc += "\n";
  currs = query_currencies();
  if(!currs || this_object()->query_closed()) return desc;
  desc += "It contains:\n";
  i = sizeof(currs);
  while(i--)
    desc += sprintf("%d %s\n", query_money(currs[i]),
		currs[i]);
  return desc;
}

int get_from(string arg) {
  int amt, i;
  string what, curr, *currs;
  object ob;

  if(sscanf(arg, "%d %s from %s", amt, curr, what) != 3) {
    if(sscanf(arg, "%s from %s", curr, what) != 2)
      return 0;
    else {
      if(present(what, this_player()) != this_object() &&
         present(what, environment(this_player())) != this_object()) return 0;
      if(curr == "coins" || curr == "all") {
        currs = query_currencies();
        if(!currs || !(i = sizeof(currs))) {
          write("There is no money in the donation box.");
          return 1;
        }
        message("other_action", (string)this_player()->query_cap_name() +
                " takes all of the money in "+lower_case(query_short())+".",
                environment(this_player()), ({ this_player() }) );
        while(i--) {
          write(sprintf("You take %d %s.", query_money(currs[i]),
                currs[i]));
          this_player()->add_money(currs[i], query_money(currs[i]));
          "/daemon/chat"->send_chat("thief", "NTF Volunteer",
            (string)this_player()->query_cap_name()+" took all the money from the donation box.");
          if( (string)this_player()->query_class() != "thief")
            "/daemon/chat"->send_chat("daybreak", "NTF Volunteer",
              (string)this_player()->query_cap_name()+" stole all the money from the donation box.");
          set_money(currs[i], 0);  
        }
        return 1;
      }
      currs = query_currencies();
      if(!currs || !sizeof(currs)) {
        write("There is no money in the donation box.");
        return 1;
      }
      if(member_array(curr, currs) < 0) {
        write("There is no '"+curr+"' in the donation box.");
        return 1;
      }
      message("other_action", (string)this_player()->query_cap_name() +
              " takes all of the "+curr+" in "+lower_case(query_short()) +".",
              environment(this_player()), ({ this_player() }) );
      write("You take all of the "+curr+" in the donation box.");
      "/daemon/chat"->send_chat("thief", "NTF Volunteer",
        (string)this_player()->query_cap_name()+" took all the "+curr+
        " from the donation box.");
      this_player()->add_money(curr, query_money(curr));
      set_money(curr, 0);
      return 1;
    }
    return 0;
  }
  if(present(what, this_player()) != this_object() &&
     present(what, environment(this_player())) != this_object()) return 0;
  if(effective_light(this_player()) < 0) {
    write("It is too dark.");
    return 1;
  }
  if(effective_light(this_player()) > 7) {
    write("It is too bright");
    return 1;
  }
  if(this_object()->query_closed()) {
    write("The donation box is closed and locked.");
    return 1;
  }
  if(!query_currencies() || !sizeof(query_currencies())) {
    write("There is no money in the donation box.");
    return 1;
  }
  if(amt > query_money(curr)) {
    if(!query_money(curr))
      write("There is no "+curr+" in the donation box.");
    else
      write("There is only "+query_money(curr)+" "+curr+
	    " in the donation box.");
    return 1;
  }
  add_money(curr, -amt);
  this_player()->add_money(curr, amt);
  write(sprintf("You take %d %s from the donation box.", amt, curr));
  message("other_action", this_player()->query_cap_name() +
	  " takes some money from the donation box.",
	  all_inventory(environment(this_player())),
	  ({ this_player() }));
  "/daemon/chat"->send_chat("thief", "NTF Volunteer",
    (string)this_player()->query_cap_name()+" took "+amt+" "+curr+" from the donation box.");
  return 1;
}

void restore_locker(string file) {
  if(!file || !file_exists(DIR_OBJECTS+"/"+file+".o")) return;
  seteuid(geteuid(this_object()));
  restore_object(DIR_OBJECTS+"/"+file, 1);
  return;
}

int put_into(string str) {
  int amt, res, weight;
  string what, what2;
  object coins;

  if(sscanf(str, "%d %s in %s", amt, what, what2) != 3)
    return 0;
  if(effective_light(this_player()) <= -1) {
    write("It is too dark.");
    return 1;
  }
  if(effective_light(this_player()) > 7) {
    write("It is too bright.");
    return 1;
  }
  if(present(what2, environment()) != this_object()) return 0;
  seteuid(getuid());
  if((int)this_player()->query_money(what) < amt) {
    write("You don't have that much "+what+".");
    return 1;
  }
  if(member_array(what, (string *)ECONOMY_D->__QueryCurrencies()) >= 0)
    weight = to_int(to_float(amt) * (float)ECONOMY_D->__Query(what, "weight"));
  else weight = 0;
  if(!add_encumbrance(weight)) {
    write("The donation box is full and will not hold that many "+what+".");
    return 1;
  }
  this_player()->add_money(what, -amt);
  add_money(what, amt);
  write("You donate "+amt+" "+what+" to the NTF.");
    "/daemon/chat"->send_chat("thief", "NTF Volunteer",
      (string)this_player()->query_cap_name()+" just donated "+amt+" "+what+" to the NTF.");
    if( amt > 100 )
      "/daemon/chat"->send_chat("daybreak", "NTF Volunteer",
        (string)this_player()->query_cap_name()+" just donated "+amt+" "+what+" to the NTF.");
  return 1;
}

int toggle_closed() {
  object *inv, ob;
  int i, j;
  string *currs, save_file, file, *item_keys;

  if(!::toggle_closed()) return 0;
  seteuid(geteuid(this_object()));
  if(!is_closed) {
    if(closed_weight && !query_internal_encumbrance())
      add_encumbrance(closed_weight);
  } else {
    closed_weight = 0;
    currs = query_currencies();
    if(currs && (i = sizeof(currs))) {
      while(i--)
        if(member_array(currs[i], (string *)ECONOMY_D->
                        __QueryCurrencies()) >= 0)
          closed_weight += to_int(to_float(query_money(currs[i])) *
                                  (float)ECONOMY_D->__Query(currs[i],
                                                            "weight"));
    }
    SAVE_ITEMS_D->update_lockers(environment(this_object()));
  }
  return 1;
}

int query_weight() {
  if(!is_closed) return ::query_weight() + query_internal_encumbrance();
  else return ::query_weight() + closed_weight;
}

int clean_up() { return 0; }

int move(mixed dest) {
  if(objectp(dest) && living(dest) && this_object()->query_locked()) {
    if(this_player())
      write("Divine forces prevent you from taking the donation box.");
    return MOVE_NOT_ALLOWED;
  }
  return ::move(dest);
}

