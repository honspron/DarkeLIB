// /wizards/excelsior/cape/mon/bob
// a money changer, similiar to akkad's silas
// Excelsior
// 9-26-96

#include <daemons.h>
#define CURRS ({ "mithril", "platinum", "gold", "silver", "electrum", "copper" })

inherit "/std/monster";

void create() {
    object ob;

    ::create();
    set_name("bob");
    set("id", ({"bob", "moneychanger", "money changer"}));
    set_stats("strength", 300);
    add_money("gold", 1000);
    set_level(50);
    set_property("enhance criticals", -10);
    set_hp(2000000);
    set_max_hp(2000000);
    set_exp(2000000);
    set("short","Bob the entrepreneur");
    set("long",
"Bob is a nice looking Gerudan out to make an honest buck. He will exchange any "+
"money you may have if you ask him nicely. For more information type 'help money'");
    set_gender("male");
    set_body_type("human");
    set("race", "gerudan");
    set_property("melee damage", ([ "crushing" : 99]));
    set_skill("conjuration", 170);
    set_skill("elementalism", 175);
    set_spell_level("elemental storm", 6);
    add_spell("elemental storm", "");
    set_combat_chance(80);
    set_skill("dodge", 80);
    set_skill("parry", 80);
    set_skill("martial arts", 200);
    set_skill("perception", 95);
    set_languages(({"common", "stormspeak", "elvish", "serra", "yin", "dwarvish",
      "drow", "pix", "treefolk", "vr'krr", "middle-english",
      "catfolk", "ogryn" }));
}

void init() {
    ::init();
    add_action("money_help", "help");
    add_action("exchange", "exchange");
    return;
}

int money_help(string str) {
    if(str != "money") return 0;
    write("To exchange currencies, use the following format:");
    write("      exchange <how-much> <what> for <what>");
    write("   Ex: exchange 350 gold for mithril");
    write("\nThat will give you an amount of mithril equal to "
      "350 gold.");
    return 1;
}

int exchange(string str) {
    float rate;
    string what1, what2;
    int amt;

    if(sscanf(str, "%d %s for %s", amt, what1, what2) != 3) {
	write("Usage: exchange <amount> <what> for <what>");
	return 1;
    }
    if((int)this_player()->query_money(what1) < amt) {
	write("You do not have "+amt+" "+what1+"!");
	return 1;
    }

    if(what1 == "platinum") {
        write("Due to the recent market crash, platinum is no longer "+
        "available..");
        return 1;
    }

    if(what2 == "platinum") {
      write("Bob will not except your worthless platinum.");
      return 1;
    }
    if(member_array(what2, CURRS) < 0) {
	write("I do not have any '"+what2+"'.  I only carry:\n");
	write(format_page(CURRS, 2));
	return 1;
    }
    if(member_array(what1, (string *)ECONOMY_D->__QueryCurrencies()) < 0) {
      write("As far as Bob is concerned, "+what1+" isn't worth a thing!");
      return 1;
    }
    rate = to_float(amt) * (float)ECONOMY_D->__Query(what2, "rate") /
    (float)ECONOMY_D->__Query(what1, "rate");
    if(amt <= 0) {
	write("Uh, nice try...");
	return 1;
    }
    if(!to_int(rate)) {
	write("%^RED%^Bob apologizes: %^RESET%^I'm sorry, but "+amt+" "+what1+" is worth less than a "+
	  "single "+what2+".");
	return 1;
    }
    this_player()->add_money(what1, -1 * amt);
    this_player()->add_money(what2, to_int(rate));
    write("%^RED%^Bob smiles: %^RESET%^Your exchange is worth "+to_int(rate)+" "+what2+".\n"+
      "Here you go.");
    return 1;
}

int query_num_rounds() { return 3; }

string query_element() { return "aether"; }

