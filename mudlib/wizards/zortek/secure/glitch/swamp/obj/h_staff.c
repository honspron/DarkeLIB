//	Wizard:  Glitch
//	hermits Staff - troll quest
//	h_staff.c

inherit "/std/weapon";

create() {
	::create();
	set_ac(10);
	set_name("oak staff");
	set("id", ({ "oak staff", "staff" }));
	set("short", "heavy oak staff");
	set("long","A heavy staff made from hard oak and polished to a sheen");
	set_type("two handed staff");
	set_quality(6);
	set_wc(20, "crushing");
	set_verb("bash");
	set_parry_bonus(15);
	set_weight(325);
	set_value(2500);
}
