// wizards/excelsior/armor/mask
// whee-hee-hee-hee

inherit "std/armour";

void create() {
	::create();
	set_name("mask");
	set("id", ({"mask","phantom mask","mask of the phantasm","opera mask"}) );
	set("short","The mask of the phantasm [tm]");
	set("long","This is a mask similiar to that worn by a mentally insane "+
		"psychopath who doesn't care about people laughing at him. If you "+
		"don't mind being made fun of, this is the mask for you!");
	set_type("helmet");
	set_ac(5);
	set_limbs( ({"head"}) );
	set_weight(121);
	set("value",500);
	set_wear("You feel silly as you put on a mask.");
	set_value(500);
	set_remove("You don't feel so silly anymore.");
}
