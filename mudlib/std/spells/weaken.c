// Weaken spell. Threlvar@Darkemud, 1995

inherit "/std/spells/spell";

void create() {
     ::create();
 set_property("name","weaken");
 set_property("skill","conjuration");
 set_property("casting time",4);
 set_property("base mp cost",20);
    set_property("dev cost", 30);
    set_property("fast dev cost", 75);
 set_property("spell level",7);
 set_property("moon","warzau");
 set_property("caster message","You drain strength from $T!");
 set_property("target message","$C twiddles his fingers, and you feel weaker!");
 set_property("observer message","$C twiddles his fingers, and $T looks weaker!");
 set_property("combat spell",1);
 set_property("can resist",1);
 set_property("duration",300);
 set_property("fumble message","$C fails at casting his spell!");
 set_property("stats",({"strength"}) );
 set_property("stat dice","-1D3");
}
