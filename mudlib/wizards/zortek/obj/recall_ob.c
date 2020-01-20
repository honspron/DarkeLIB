#define LOCATIONS ({"/d/damned/join_rooms/cleric_join",})
inherit "/std/Object";
 
int success, recall_time;
string creator, recall_dest;
 
create()
{
  set_id( ({ "wafer","holy wafer", }) );
  set_name("wafer");
  set_short("Holy Wafer");
  set_weight(50);
  set_value(0);
}
void init()
{
  add_action("recall", "recall");
}
set_success(int x)
{
  success = x;
}
set_rtime(int rtime)
{
  recall_time = rtime;
}
set_dest(string where)
{
  recall_dest = where;
}
set_creator(string who)
{
  creator = who;
}
int recall(string str)
{
  int x;
  string go_where;
  if(time() > recall_time) {
    write("The Holy Wafer crumbles to dust.");
    say(this_player()->query_cap_name()+" mumbles something and "+
      this_player()->query_possessive()+" Holy Wafer crumbles to dust.");
    this_object()->remove();
    return 1;
  }
  if(success < random(30)) {
    x = random(sizeof(LOCATIONS));
    if(LOCATIONS[random(sizeof(LOCATIONS))] != "")
      go_where = LOCATIONS[x];
    else
      go_where = "/d/damned/akkad/ak_center";
  }
  else
    go_where = recall_dest;
  write("You invoke the Word of Recall cast by "+creator+" and are transported.");
  say(this_player()->query_cap_name() +" utters a Word of Recall and vanishes.");
  this_player()->move_player(recall_dest);
  say(this_player()->query_cap_name() +" materializes before you.");
  this_player()->set_hp(1);
  this_player()->set_mp(1);
  this_object()->remove();
  return 1;
}
