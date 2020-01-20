#include <std.h>
#include <security.h>
#include "banker.h"

inherit MONSTER;

int is_full(string playername);

void init()
{
::init();
add_action("do_store", "store");
add_action("list_items", "list");
add_action("do_retrieve", "restore");
add_action("backup", "backup");
return;
}
int backup(string args)
{
object ob;
if(!archp(this_player()))
{
return 0;
}
ob = new(replace_string(read_file(BBDIR+args, 1, 1), "#", ""));
seteuid(geteuid());
ob->restore_object(BBDIR+args);
ob->set_short((string)ob->query_property("new desc"));
ob->move(this_player());
return 1;
}

int do_retrieve(string item)
{
object ob;
string file;
	if(!item) 
	{
	write("Syntax: retrieve <keyword>");
	return 1;
	}
	if(this_player()->query_ghost())
	{
	force_me("say You're dead, nice try.");
	return 1;
	}
file = this_player()->query_true_name()+"_"+item;
seteuid(geteuid());
cp(BDIR+file+".o",
		BBDIR+file+".o");
if(archp(this_player())){message("info", "File copied", this_player());}
ob = new(replace_string(read_file(BDIR+file, 1, 1), "#", ""));
ob->restore_object(BDIR+this_player()->query_true_name()+"_"+item);
ob->set_short((string)ob->query_property("new desc"));
ob->move(this_player());

force_me("say Here you go.");
return 1;
}
int list_items()
{
string name;
mapping *files;
name = this_player()->query_true_name();
files = get_dir(BDIR+name+"*");
//no files?	
if(!files)
	{
	message("bank", "You have no items stored here.", this_player());
	return 1;
	};
//listem
	for(int i = 0;i < sizeof(files);i++)
	{
		message("bank", replace_string(files[i], name+"_", "")+"\n", this_player());
	}
return 1;
}

int do_store(string args)
{
object item;
string itemname, keyword, name;

name = this_player()->query_true_name();
if(sscanf(args, "%s %s", itemname, keyword) !=2)
{
write("You must use syntax: store <item> <keyword>");
}
   item = present(itemname, this_player());
	if(item->is_living() || is_full(name))
	{
	force_me("say You can't store that.");
	return 1;
	}
seteuid(geteuid());
item->save_object(BDIR+name+"_"+keyword);
rm(BBDIR+name+"*");
seteuid(geteuid());
item->move(this_object());
item->remove();
force_me("say Thank you, "+ capitalize(name) + ".");
return 1;
}

int is_full(string playername)
{if(sizeof(get_dir(BDIR+ playername + "*")) >= 5) return 1;
return 0;
}

create() {
  object ob;
  
  ::create();
    set_name("foz");
    set_id( ({ "banker", "Foz" }) );
    set_short("Foz the banker");
    set("race", "high-elf");
    set_long(
    "Raz is a busy elf that stores your goods.");
    set_body_type("human");
    set_hp(200000);
    set_max_hp(200000);
   set_property("enhance criticals", -10);
    set_level(20);
    set_exp(100);
    set_property("melee damage", ([ "crushing" : 99]));
    set_skill("melee", 260);
    set_skill("elementalism", 175);
    set_spell_level("elemental storm", 6);
    add_spell("elemental storm", "");
    set_combat_chance(80);
    set_skill("dodge", 70);
    set_skill("parry", 20);
    set_stats("dexterity", 130);
}
int query_num_rounds() { return 3; }

string query_element() { return "vacid"; }

