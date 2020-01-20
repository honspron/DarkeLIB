inherit "/std/weapon";

create() {
    ::create();
    set_ac(10);
    set("id", ({ "hammer", "warhammer", "war hammer" }) );
    set_short("A huge jeweled warhammer");
    set_long("It looks very heavy.\n");
    set_type("two handed blunt");
    set_quality(6);
    set_property("no decay",1);
    set_property("no add quality",1);
    set_wc(45,"crushing");
    set_wc(20,"fire");
    set_verb("pulverize");
    set_parry_bonus(5);
    set_property("enchantment",30);
    set_enh_critical(4);
    return;
}
