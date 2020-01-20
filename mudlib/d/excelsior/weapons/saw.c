// /wizards/excelsior/weapons/saw
// a amputation tool

inherit "std/weapon";
	
void create() {
	::create();	
	set("id",({"saw","doctor's saw"}));
	set_name("saw");
	set("short","doctor's amputation saw");
	set("long","This is a saw that is used to amputate unnecessary "+
		"limbs. It could serve as a weapon too.");
	set_weight( 111 );
	set_value( 12 );
	set_ac( 2 );
	set_wc( 2, "cutting" );
	set_type("blade");
	set_quality(1);
}
