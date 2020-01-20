//    A generic transportation object, can be used to take
//    players places.
//    -Diewarzau 1/29/96
//    DarkeLIB 1.0
inherit "/std/Object";

mapping dests;
string arrival_mesg;
string my_mesg;
string leave_mesg;

void set_arrival_mesg(string str);
void set_leave_mesg(string str);
void set_my_mesg(string str);
void add_destination(string file, string item, string desc, int cost);
void remove_destination(string item);

void set_arrival_mesg(string str) { arrival_mesg = str; }

void set_leave_mesg(string str) { leave_mesg = str; }

void set_my_mesg(string str) { my_mesg = str; }

void add_destination(string file, string item, string desc, int cost) {
  item = lower_case(item);
  if(!dests) dests = ([]);
  dests[item] = ([]);
  dests[item]["file"] = file;
  dests[item]["desc"] = desc;
  dests[item]["cost"] = cost;
  return;
}

void remove_destination(string item) {
  if(!dests) return;
  map_delete(dests, item);
  return;
}

string query_long(string str) {
  string ret;
  int i;
  string *d_keys;

  ret = ::query_long(str);
  ret +=
  "The following destinations are available:\n"
  "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
  d_keys = keys(dests);
  i = sizeof(d_keys);
  ret += sprintf("%-15s%-35s %-5s\n", "Destination:", "Description:", "Cost:")+
  "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n";
  while(i--)
    ret += sprintf("%-'.'15s%-35s %d gold\n", d_keys[i], dests[d_keys[i]]["desc"],
          to_int(to_float(dests[d_keys[i]]["cost"])*currency_rate("gold")));
  ret += "\nType 'travel dest' to travel to the destination.";
  return ret;
}

void init() {
  ::init();
  add_action("travel", "travel");
  return;
}

int travel(string str) {
  int gold;

  str = lower_case(str);
  if(member_array(str, keys(dests)) < 0) {
    notify_fail("That destination is not available.\n");
    return 0;
  }
  gold = to_int(to_float(dests[str]["cost"])*currency_rate("gold"));
  if((int)this_player()->query_money("gold") < gold) {
    write("You do not have enough gold for that.");
    return 1;
  }
  if(catch(call_other(dests[str]["file"], "???"))) {
    write("There is a bug with that destination.  Report to an arch.");
    return 1;
  }
  this_player()->add_money("gold", -1*gold);
  message("info", my_mesg, this_player());
  message("info", (string)this_player()->query_cap_name() +
    " "+leave_mesg, environment(this_player()), ({ this_player() }));
  this_player()->move(dests[str]["file"]);
  message("info", (string)this_player()->query_cap_name() +
    " "+arrival_mesg, environment(this_player()), ({ this_player() }));
  return 1;
}

