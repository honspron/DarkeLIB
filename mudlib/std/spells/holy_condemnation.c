inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","holy condemnation");
    set_property("skill","prayer");
    set_property("casting time", 4);
    set_property("base mp cost", 90);
    set_property("dev cost",80);
    set_property("fast dev cost",240);
    set_property("spell level", 25);
    set_property("moon","warzau");
    set_property("caster message","The Angel of Judgement responds to your call for Holy Condemnation!");
    set_property("target message","The Angel of Judgement responds to $C's call for Holy Condemnation!");
    set_property("observer message","The Angel of Judgement responds to $C'scall for Holy Condemnation!");
    set_property("spell type",({ "area damage" }));
    set_property("damage types", ([ "holy" : 25, "holy #2" : 25, "holy #3" : 25, "holy #4" : 25]));
    set_property("damage multiplier", 15);
    set_property("combat spell", 1);
    set_property("must be present", 1);
    set_property("can resist", 1);
    set_property("no target", 1);
    set_property("prereq", "bolt of righteousness");
    return;
}

void info() {
message("help",
"This is clearly the most destructive 'Act of God' that a cleric can call down upon "
"all enemies present.  When called the Angel of Judgement arrives to punish ALL present, friend and foe alike!",
this_player());
}

