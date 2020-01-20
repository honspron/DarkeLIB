inherit "/std/armour";

void create() {
    ::create();
    set_name("shield");
    set("id", ({ "shield", "elven shield" }) );
    set("short", "An elven Shield");
    set("long",
	"This is a small wooden shield that is meant for warding "
	"off blows from those who might attack the bearer.");
    set_weight(150);
    set("value", 2000);
    set_type("shield");
   set_limbs( ({ ({ "right hand", "left hand", "first branch",
	"second branch", "third branch", "fourth branch" }) }) );
    set_ac(3);
}

