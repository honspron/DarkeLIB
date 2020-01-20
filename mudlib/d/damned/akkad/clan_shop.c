/*
 * The Clan Registry, where dudes register their clans and buy modifications for
 * strongholds...
 *
 * Diewarzau 10/10/96
 * DarkeLIB 1.0
 */

#include <security.h>
#include <rooms.h>
#include <daemons.h>
#define MAX_SOUTH 79
#define MAX_EAST 39
#define DOORS ([ "wood door" : 40000, "iron door" : 102000, "steel door" : 280000, \
        "reinforced door" : 720000, "vault door" : 1500000 ])
#define FEATURES ([ "no scry" : 940000, "no teleport" : 560000, \
        "no summon" : 740000, "healing room" : 180000, \
        "special exits" : 100000 ])

inherit "/std/room";

int pay(object tp, int plat);
void read_sign();
void read_coming_soon();
void read_clans();

int pay(object tp, int plat) {
  plat = to_int(to_float(plat) * currency_rate("mithril"));
  if((int)tp->query_money("mithril") < plat) {
    message("info", "You do not have enough mithril for that.",
          tp);
    return 0;
  }
  tp->add_money("mithril", -1*plat);
  return 1;
}

void reset() {
  ::reset();
  if(!present("key rack"))
    new("/d/damned/akkad/obj/misc/clan_key_rack")->move(this_object());
  if(!present("kohr amaz"))
    new("/d/damned/akkad/obj/mon/kohr_amaz")->move(this_object());
}

void create() {
  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
  set_short("The Clan Registry");
  add_exit("/d/damned/akkad/ak_tavern1", "east");
  set("long",
  "This is the Clan Registry.\n"
  "Here clan-masters-to-be may register their new clans, and clan "
  "members may buy upgrades and enhancements for their clan strongholds.\n"
  "There are three signs on the back wall.");
  add_item("sign", (: call_other, this_object(), "la_signs" :));
  add_item("signs", (: call_other, this_object(), "la_signs" :));
  return;
}

int la_signs() {
  write("There are three signs on the wall, one entitled 'registry', one entitled "
    "'coming soon', and one entitled 'clans'.  Perhaps you could read them?");
  return 1;
}

void read_sign() {
  string tmp;

  tmp =
"Welcome to the Clan Registry!\n"
"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-\n"
"Here you may register your new clan and buy items and upgrades for an existing clan.  "
"Only the clan leader can buy 'teaching room upgrade' or 'clan room'; all members may buy "
"any of the other items in order to customize their rooms.  In order to start a new "
"clan, 'buy clan registry'.  You will be prompted for a clan name.  You must be "
"above level 25, not a member of any other clan, and not a guild master.  You will also "
"be prompted for the location (in standard south/east coordinates) of your new clan "
"stronghold.  The stronghold includes protective walls, a draw bridge, "
"two guards that will attack non-members on sight, a basic teaching room, and an inner-sanctum "
"with one room, which may be expanded to 40 rooms.\n"
"Below are the items which may be bought for the stronghold.  Buy them by typing "
"'buy <item>'.\n\n"+
sprintf("clan registry              %d mithril (see above)\n", to_int(13000000.0*currency_rate("mithril")))+
sprintf("clan room                  %d mithril\n", to_int(700000.0*currency_rate("mithril")))+
sprintf("teaching room upgrade      %d mithril\n", to_int(8500000.0*currency_rate("mithril")))+
sprintf("wood door                  %d mithril\n", to_int(40000.0*currency_rate("mithril")))+
sprintf("iron door                  %d mithril\n", to_int(102000.0*currency_rate("mithril")))+
sprintf("steel door                 %d mithril\n", to_int(280000.0*currency_rate("mithril")))+
sprintf("reinforced door            %d mithril\n", to_int(720000.0*currency_rate("mithril")))+
sprintf("vault door                 %d mithril\n", to_int(1500000.0*currency_rate("mithril")))+
"\n"
"Castle special features (good for one room only!):\n"
"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
sprintf("no scry                    %d mithril\n", to_int(940000.0*currency_rate("mithril")))+
"  ^ You cannot be scried in that room\n"+
sprintf("no teleport                %d mithril\n", to_int(560000.0*currency_rate("mithril")))+
"  ^ No one can teleport to that room.\n"+
sprintf("no summon                  %d mithril\n", to_int(740000.0*currency_rate("mithril")))+
"  ^ No one can be summoned from that room.\n"+
sprintf("healing room               %d mithril\n", to_int(180000.0*currency_rate("mithril")))+
"  ^ Any PLAYER in the room heals mp and hp at double rate.\n"+
sprintf("special exits              %d mithril\n", to_int(100000.0*currency_rate("mithril")))+
"  ^ Teleport exits to various useful places (church, shop, etc.)\n"
"\n"
"Clan Upgrades\n"
"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
sprintf("upgrade guard              %d mithril\n", to_int(1100000.0*currency_rate("mithril")))+
"  ^ Replaces a clan guard with a knight.  Knights are tougher, cast spells,\n"
"    and shout to the clan hall when the clan is under attack.\n"+
"\n"
"Buy any item with 'buy <item>'\n";
  this_player()->more(explode(wrap(tmp, (int)this_player()->getenv("SCREEN")), "\n"));
  return;
}

void read_coming_soon() {
  string tmp;

  tmp = "Coming soon to the Clan System...\n"
  "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n"
  "-*> More Guard Upgrades <*-\n"
  "     New and better guards to guard your stronghold are coming!  These have "
  "an important advantage over pets in that they are placed OUTSIDE "
  "of the inner sanctum and may thus block entry into the sanctum entirely.  "
  "Also, if killed, they come back at reboot, and do not need to be re-purchased.\n\n"
  "-*> Draw Bridge Upgrades <*-\n"
  "     Stronger draw bridges and even draw bridges with traps that hinder flying "
  "creatures attempting to ascend the raised bridge are coming.\n\n"
  "-*> Siege Engines <*-\n"
  "     You will not be able to buy these here, but tinkers will be able to construct "
  "them from appropriate amounts of wood and metal.  These may be used both to destroy "
  "draw bridges and harm guards and players inside the stronghold.  The types planned "
  "for release soon include: catapult (able to fire rocks or fireballs), ballista, and "
  "battering ram.\n\n"
  "-*> Counter-siege Ordinance <*-\n"
  "     Annoying battering ram knock-knock-knocking on your stronghold door?  Dump some "
  "molten lead on those bad boys with iron cauldrons.  Also archers can repel attackers, as "
  "can NPC clan wizards.  Both of these can fire their attacks OVER the stronghold walls to "
  "the outside, so only siege engines are capable of striking back.\n";
  this_player()->more(explode(wrap(tmp, (int)this_player()->getenv("SCREEN")), "\n"));
  return;
}

void read_clans() {
  string tmp, *clist;

  tmp = "Clans in the Realm of Darke\n"
  "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
  clist = map_array((string *)CLAN_D->all_clans(),
    (: sprintf($2, capitalize($1), capitalize((string)CLAN_D->clan_leader($1))) :),
    "Clan %-30s  Leader: %s");
  
  this_player()->more(explode(wrap(tmp, (int)this_player()->getenv("SCREEN")), "\n")+clist);
  return;
}

void init() {
  ::init();
  add_action("buy_item", "buy");
  add_action("check_read", "read");
  return;
}

int check_read(string what) {
  switch(what) {
  case "sign":
    write("There is a sign entitled 'registry' and a sign entitled "+
      "'coming soon'...which do you wish to read?");
    return 1;
  case "registry":
  case "registry sign":
  case "sign entitled registry":
    read_sign();
    return 1;
  case "coming soon":
  case "coming soon sign":
  case "sign entitled coming soon":
    read_coming_soon();
    return 1;
  case "clans":
  case "clans sign":
  case "sign entitled clans":
    read_clans();
    return 1;
  default:
    write("Read what?");
    return 1;
  }
  return 0;
}

int buy_item(string str) {
  string *strp;
  string join_room;
  string clan;
  int tlevel, idx;
  object *inv, ob, troom;

  if(!this_player()->is_player()) return 0;
  seteuid(getuid());
  str = lower_case(str);
  if(str == "clan registry") {
    if(wizardp(this_player())) {
      write("Wizards cannot purchase clans....sorry.");
      return 1;
    }
    if(this_player()->query_guild() && (string)this_player()->query_guild() != "none") {
      write("You already belong to a clan.");
      return 1;
    }
    if((string)this_player()->query_class() != "child") {
      join_room = sprintf("/d/damned/guilds/join_rooms/%s_join",
        (string)this_player()->query_class());
      if(file_exists(join_room+".c") && (string)join_room->query_master() ==
        (string)this_player()->query_name()) {
        write("You may not start a clan if you are a guild master.");
        return 1;
      }
    }
    if((int)this_player()->query_level() < 20) {
      write("You must be of higher than level 20 or higher to start a clan.");
      return 1;
    }
    write("Please choose name for the clan.\n"
      "It may consist only of alphabetic characters and dashes (-).  "
      "No numbers, spaces, or special characters.  "
      "Any capitalization other than the first letter will be ignored.  "
      "Clan members will have access to a chat channel with the same name as "
      "the clan.");
    printf("Clan Name> ");
    input_to("pick_name", 0, this_player());
    return 1;
  }
  if(str == "clan room") {
    clan = (string)this_player()->query_guild();
    if(!clan || (string)this_player()->query_name() != (string)CLAN_D->
      clan_leader(clan)) {
      write("Only clan leaders may buy rooms for the stronghold.");
      return 1;
    }
    if((int)CLAN_D->query_num_rooms(clan) >= 40) {
      write("The stronghold of you clan already has the maximum number of rooms (40).");
      return 1;
    }
    if(!pay(this_player(), 700000)) return 1;
    write("You purchase an extra room for the stronghold.");
    CLAN_D->add_room(clan);
    return 1;
  }
  if(str == "teaching room upgrade") {
    clan = (string)this_player()->query_guild();
    if(!clan || (string)this_player()->query_name() != (string)CLAN_D->
      clan_leader(clan)) {
      write("Only clan leaders may upgrade the teaching room.");
      return 1;
    }
    if(!pay(this_player(), 8500000)) return 1;
    troom = load_object(sprintf("/d/damned/virtual/teach:%s_1.clan", clan));
    tlevel = (int)troom->query_room_info("teach room");
    if(tlevel >= 3) {
      write("The teaching room of your clan has been upgraded to the maximum.");
      return 1;
    }
    troom->set_room_info("teach room", tlevel + 1);
    inv = all_inventory(troom);
    foreach(ob in inv) if(ob) ob->move(ROOM_VOID);
    seteuid(UID_ROOT);
    destruct(troom);
    seteuid(getuid());
    foreach(ob in inv) if(ob) ob->move(sprintf("/d/damned/virtual/teach:%s_1.clan", clan));
    write("Teaching room upgraded.");
    return 1;
  }
  if(str == "upgrade guard") {
    if(!this_player()->query_guild() || (string)this_player()->query_guild() == "none") {
      write("You must be a member of a clan to buy that.");
      return 1;
    }
    troom = load_object(sprintf("/d/damned/virtual/courtyard:%s_1.clan",
        (string)this_player()->query_guild()));
    strp = (string *)call_other(troom, "query_room_info", "guards");
 idx = member_array("/std/diewarzau/obj/mon/clan_guard1", strp);
    if(idx == -1) {
      write("You have no guards to upgrade.");
      return 1;
    }
 strp[idx] = "/std/diewarzau/obj/mon/clan_guard2";
    troom->set_room_info("guards", strp);
    ob = present("guard of "+(string)this_player()->query_guild(), troom);
    if(ob) {
      ob->remove();
 ob = new("/std/diewarzau/obj/mon/clan_guard2");
      ob->setup((string)this_player()->query_guild());
      ob->move(troom);
      message("info", "A dwarven armourer appears seemingly out of nowhere and clads "
        "one of the guards in the attire of a knight!", troom);
    }
    return 1;
  }
  if(member_array(str, keys(DOORS)) >= 0) {
    if(!this_player()->query_guild() || (string)this_player()->query_guild() == "none") {
      write("You must be a member of a clan to buy that.");
      return 1;
    }
    if(!pay(this_player(), DOORS[str])) return 1;
    strp = (string *)this_player()->query_property("clan doors");
    if(!strp) strp = ({});
    strp += ({ str });
    this_player()->set_property("clan doors", strp);
    write("You have purchased a "+str+" for your clan's stronghold.");
    return 1;
  }
  if(member_array(str, keys(FEATURES)) >= 0) {
    if(!this_player()->query_guild() || (string)this_player()->query_guild() == "none") {
      write("You must be a member of a clan to buy that.");
      return 1;
    }
    if(!pay(this_player(), FEATURES[str])) return 1;
    strp = (string *)this_player()->query_property("clan features");
    if(!strp) strp = ({});
    strp += ({ str });
    this_player()->set_property("clan features", strp);
    write("You have purchased the feature: "+str+".");
    return 1;
  }
  notify_fail("Look at the sign for a list of inventory.\n");
  return 0;
}

void pick_name(string cname, object tp) {
  string res;

  if(!cname || cname == "") {
    write("Clan Registry aborted.  Better luck next time.");
    return;
  }
  res = (string)CLAN_D->new_clan(cname, (string)tp->query_name());
  if(res) {
    write(res+"\nRegistry failed.");
    return;
  }
  write("Pick a plot for the Stronghold of Clan "+capitalize(lower_case(cname))+
        ".\nInput it in standard <south>, <east> coordinates.\n"
        "Example: 13,21 (enter to abort)");
  printf("coordinates> ");
  input_to("pick_plot", 0, tp, lower_case(cname));
  return;
}
  

void pick_plot(string coords, object tp, string cname) {
  int south, east;
  object room, *inv, ob;
  string name;
  int i;

  if(!coords || coords == "") {
    write("Clan registry aborted.  Better luck next time...");
    CLAN_D->remove_clan(cname);
    return;
  }
  if(sscanf(coords, "%d,%d", south, east) != 2) {
    message("info", "Please input in the form <south>, <east>.", tp);
    printf("coordinates> ");
    input_to("pick_plot", 0, tp, cname);
    return;
  }
  if(east > MAX_EAST || south > MAX_SOUTH) {
    message("info", "Those coordinates are off the map!", tp);
    printf("coordinates> ");
    input_to("pick_plot", 0, tp, cname);
    return;
  }
  room = find_object_or_load(sprintf("/d/damned/virtual/room_%d_%d.world", east, south));
  if(!room) {
    message("info", "Those coordinates are off the map!", tp);
    printf("coordinates> ");
    input_to("pick_plot", 0, tp, cname);
    return;
  }
  if(lower_case((string)room->query_terrain()) == "w") {
    message("info", "That is in the middle of the water!", tp);
    printf("coordinates> ");
    input_to("pick_plot", 0, tp, cname);
    return;
  }
  if(member_array("clan", (string *)room->query_exits()) >= 0) {
    message("info", "There is already a Clan Stronghold there.", tp);
    printf("coordinates> ");
    input_to("pick_plot", 0, tp, cname);
    return;
  }
  if(!pay(tp, 13000000)) return;
  seteuid(UID_DAMNED_DATA);
  write_file("/d/damned/data/world_items.db",
      sprintf("%d_%d:/d/damned/virtual/outer:%s_7.clan:clan:The Stronghold of Clan %s\n",
          east, south, cname,
          capitalize(cname)));
  inv = all_inventory(room);
  message("info", "With blinding speed, a gang of dwarves assemble a Clan Stronghold here!",
      room);
  i = sizeof(inv);
  while(i--) if(inv[i]) inv[i]->move(ROOM_VOID);
  name = base_name(room);
  seteuid(UID_ROOT);
  destruct(room);
  seteuid(getuid());
  i = sizeof(inv);
  while(i--) if(inv[i]) inv[i]->move(name);
  tp->set_guild(cname);
  room = load_object(sprintf("/d/damned/virtual/outer:%s_7.clan", cname));
  call_other(room,
	  "add_exit", sprintf("/d/damned/virtual/room_%d_%d.world", east, south),
	  "south");
  call_other(room,
	  "set_room_info", "extra exits", ([ "south" : sprintf("/d/damned/virtual/room_%d_%d.world", east, south) ]));
	room = load_object(sprintf("/d/damned/virtual/%s_hall_1.clan_strong", cname));
	room->add_exit(sprintf("/d/damned/virtual/courtyard:%s_1.clan", cname), "out");
	room->rewrite_castle();
	ob = new("/std/diewarzau/obj/misc/clan_master_ob");
	ob->set_clan_name(cname);
	ob->set_leader((string)tp->query_name());
	ob->move(tp);
	tp->save_player((string)tp->query_name());
	CLAN_D->set_clan_location(cname, south, east);
  message("info", "Your Clan Stronghold has been built.", tp);
  message("shout", "The DemiUrge shouts: Let it be known!  A new Clan has been "
      "formed in our realm.  It shall be known as Clan "+capitalize(cname)+" under the "
      "leadership of "+
      capitalize((string)tp->query_name())+"!", users());
  message("info", "Type 'help clan leader' for help.", tp);
  return;
}
