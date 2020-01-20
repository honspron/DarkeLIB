#include <std.h>

inherit DAEMON;

int cmd_peer(string str) {
    string *dirlist, *destlist;
    string ret, tmp, l, dest;
    object who, test;
    int i, x;

    if(!str) {
        message("my_action", "You peer around the room.", this_player());
        message("other_action", sprintf("%s peers around the room",
          this_player()->query_cap_name()), environment(this_player()),
          ({ this_player() }));
        return 1;
    }
    if((x=effective_light(this_player())) > 15)
        return notify_fail("It is much too bright.\n");
    if(x < 0) return notify_fail("It is too dark.\n");
    if(who = present(str, environment(this_player()))) {
        message("my_action", "You peer at "+(string)who->query_cap_name()+".",
          this_player());
        message("other_action", (string)this_player()->query_cap_name()+
          " peers at "+(string)who->query_cap_name()+".", 
          environment(this_player()), ({ this_player(), who }));
        message("other_action", (string)this_player()->query_cap_name()+
          " peers at you.", who);
        return 1;
    }
    if(!sizeof(dirlist= (string *)environment(this_player())->query_exits()))
      return notify_fail("There appears to be no way out of here.\n");
    if((i=member_array(str, dirlist)) == -1)
      str = (string)environment(this_player())->query_full_direction(str);
    if(i== -1 && (i=member_array(str,dirlist)) == -1)
      return notify_fail("You cannot see far in that direction.\n");
    if(!(dest = (string)environment(this_player())->query_exit(dirlist[i])))
      return notify_fail("You cannot see much in that direction.\n");
    if(tmp = (string)environment(this_player())->query_door(dirlist[i]) &&
      !environment(this_player())->query_open(tmp))
      return notify_fail("The "+tmp+" blocks your view.\n");
    dest = replace_string(dest, ".c", ""); //Kalinash 1-14-94
    test = find_object_or_load(dest);
    if(!test)
      return notify_fail("You cannot see much in that direction.\n");
    if(dest->query_light() < 0) 
      message("my_action", "It is too dark.", this_player());
    else if(dest->query_light() > 6)
      message("my_action", "It is too bright that way.", this_player());
    else {
      message("room_description", (string)dest->query_long(0), this_player());
      message("room_exits", (string)dest->query_long_exits(), this_player());
      message("living_item", (string)dest->describe_living_contents(({})),
        this_player());
        message("inanimate_item", (string)dest->describe_item_contents(({})),
        this_player());
    }
    message("other_action", this_player()->query_cap_name()+
      " peers "+dirlist[i]+".", environment(this_player()), ({this_player()}));
    return 1;
}

int help() {
  message("help",
  "You may use this command to peer into adjacent rooms.\n"
  "Example:\n"
  "    peer south",
  this_player());
  return 1;
}
