// This is not Nightmare's basic homeroom for new immortals.
// This is Excelsiors super charged workroom for the modern wizard.
// Contains a basic program for Excelsior's DarkeMUD viewing aparatus.
// Do _NOT_ inherit or #include this.  That may come later.
// DO copy this program for your own veiwing apparatus.

#include <std.h>
#include <daemons.h>
#include <socket.h>

#define FORGE_MATERIALS ({ "/metal/iron", "/metal/steel","/default" })

inherit VAULT;

string name,type,what;
object board;
mapping props;

int cmd_finger(string str);

void init()
{
   object money;
    if (!present("mover") ) {
	new("/wizards/excelsior/mover")->move(this_object());
	}
   if (!present("coins")){
      money = new("/std/obj/coins");
      money-> set_money("gold",3000);
      money->move(this_object());
   }
   add_action("tool","tool");
   ::init();
   add_action("test_thing","test");
   add_action("loc_player","view");
   add_action("tongues","tong");
   add_action("forge","forge");
}
void create() {
   ::create();
   set_property("light", 1);
   set_property("indoors", 1);
   set("short", "In a forest by a desk");
   set("creator", "Excelsior");
   set("long","Excelsiors workroom consists of a desk in the middle "+
    "of a beautiful forest. The grass grows high around the desk and "+
    "you feel very peaceful. On the desk is a Mac Performa 636CD computer "+
    "used to control the world with.");
 set_exits( (["church":"/d/standard/square","hall":"/d/standard/adv_main",
	"tink":"/d/damned/guilds/tinker/train_room",
	"arch":"/d/damned/guilds/sword-mage/train_room",
		"square":"/d/damned/akkad/ak_center",
	"city":"/d/nfd/rooms/faeriedust","stage":"/d/nfd/rooms/center_stage"]) );
   set_item_descriptions( ({ "sign" , "computer" }),  ({ "If" +
            " you so desire,  this computer will allow you to 'view <player>'", "Quite "+
            "a nice computer.  Hmmm." }) );
    set_smell("default","You smell the fact that 'tool' will produce a useful tool.");
   set_listen("default", "You hear the sounds of code creation.");
}


int loc_player(string str) 
{
string stri;
   object per,env;  //per is person peered,  env is room he is in.
   if ( !str )
      {
      write( "You tell the viewer to view nothing,  and only see the inside\n" +
         "of your head.\n" );
      return 1;
   }
   if ( !find_player(str) )
      {
      write( "Try viewing somebody who actually exists next time." );
      return 1;
   }
   env = environment( find_player(str) );
   sscanf( getuid( env ) , "%sobj", stri );
 if (!stri) stri = "<On Main>";
else stri = capitalize( stri );
   write( "A crisp,  clear image appears on the screen depicting\n" +
      capitalize(str) + " at: " + env->query_short() + ",  a room created by\n" +
      stri +"." );
   return 1;
}


int tool() {
	new("/wizards/excelsior/mover")->move( this_object() );
	write( "Enjoy my tool. It is on the floor. 'go <x,y>' is the command." );
   return 1;
}

int filter_weapon(object item, string type) {
  if(!item->id("board")) return 0;
  if(!item->query_property("progress "+name)) return 0;
  if((string)item->query_property("progress "+name) != type) return 0;
  return 1;
}

void finish_work(object from, object at) {
  int val,hit_bonus,wc_bonus;
  seteuid(getuid());
  message("info", "%^CYAN%^You are finished balancing the weapon!", from);
  if(at->query_wield()) at->__ActuallyUnwield();
  hit_bonus = (props["skill level"]*8)/(int)at->query_weight();
  wc_bonus = (props["skill level"]/6) + random(10);
  val = (int)at->query_value();
  at->set_value(val - 2*wc_bonus - hit_bonus);
  if((int)at->query_value() <= 0) at->set_value(1);
	val = (int)at->query_decay_rate();
  at->set_decay_rate(val - wc_bonus - hit_bonus);
  if((int)at->query_decay_rate() <= 0) at->set_decay_rate(1);
  at->set_property("balanced",name);
  at->set_property("balanced hit bonus",hit_bonus);
  at->set_property("balanced wc bonus",wc_bonus);
  return;
}


void skill_func(object from, object at) {
  int time, mod;
  seteuid(getuid());
  name = (string)from->query_name();
  if(!at->is_weapon()) {
    message("info", "You must use this skill on a weapon.", from);
    return;
  }
  if(!present("greater forge", environment(from)) && member_array(
  		(string)at->query_material(),FORGE_MATERIALS) == -1) {
    message("info", "You must be in a room with a greater forge to use this skill "+
    	"on weapons of such materials!",from);
    return;
  }
  else {
  	if(!present("forge") && member_array(
  		(string)at->query_material(),FORGE_MATERIALS) > -1) {
  		message("info", "You must be in a room with a forge to use this skill.",
  			from);
    	return;
    }
  }
  if(at->query_wield()) {
  	message("info","You must unwield that weapon to work on it.",from);
  	return;
  }
  mod = props["skill level"];
  if(!mod) mod = 1;
  time = (725 + (int)at->prop("hardness")) / mod;
  at->set_property("progress "+name, 1);
  write("%^CYAN%^You pound on the weapon.");
  finish_work(from,at);
  return;
}



int forge(string str) {
	object ob;
	ob = new("/wizards/excelsior/max_hp_shadow");
	ob->start_shadow( this_player(), -500, 10 );
	return 1;
}
	

string query_terrain() { return "W"; }

int test_thing(string str) {
		object ob;
		ob = new("/wizards/excelsior/crits/environment_shadow");
		ob->start_shadow( this_object(), ({this_player()}) );
		return 1;
	}
