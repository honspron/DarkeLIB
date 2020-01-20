
inherit "std/quest_ob";

void create() {
    set_name("Muerta Canyon Quest");
    set_id( ({ "Muerta Canyon Quest", "quest_object" }) );
    set_short("Mystery of Muerta Canyon");
    set_long( @LONG
What is the mystery of Muerta Canyon.  There is an ever increasing
fear that something horribly wrong is happening in the canyon.  Can
you unlock the mystery?  Can you do something to restore the balance?

This adventure is designed for individual HIGH LEVEL (20+) players,
but will require the assistance of as many as TEN junior players from
different guilds and/or races.

Players should expect to take multiple play sessions to complete this
adventure, and COMPETITION between players should be expected.
LONG
    );
    set_quest_points(100);
}
