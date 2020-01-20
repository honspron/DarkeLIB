// /d/nfd/weapons/fencing_sword

// this shouldn't be here. sigh.



inherit "std/weapon";



void create() {

	object weapon;

	::create();

	weapon = this_object();

	weapon->set_name("sword");

	weapon->set_id( ({"sword","fencing sword"}) );

	weapon->set("short","Renaissance fencing sword");

	weapon->set("long","This is a fine light sword built for fencing.");

	weapon->set_weight(81);

	weapon->set("value",25);

	weapon->set_ac(4);

	weapon->set_wc(3, "piercing");

	weapon->set_type("blade");

	weapon->set_quality(2);

	weapon->set_hit_bonus(30);

	weapon->set_parry_bonus(50);

	set_value(25);

}

