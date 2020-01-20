// /d/nfd/weapon/galran_staff





inherit "/std/weapon";



void create() {

	::create();

	set_name("staff");

	set("id",({"staff","galran staff","galran's staff","Galran's staff"}));

	set("short","Galran's magical staff");

	set("long","This staff looks to have magical properties.");

	set_weight(130);

	set_value(3000);

	set_ac(3);

	set_wc(6,"crushing");

	set_wc(16,"fire");

	set_material("/wood/oak");

	set_type("two handed staff");

	set_quality(6);

}



void init() {

	::init();

		add_action("do_help","help");

}





int do_help(string str) {

		if(!id(str)) {

	notify_fail("What do you want help on?\n");

		return 0;

	}

if((int)this_player()->query_skill("detect magic") < random(100)) {

		write("You detect no magical properties or enchantments on the staff...");

		return 1;

	}

	write("You since the staff to have a high fire enchantment.");

	return 1;

}

