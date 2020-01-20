inherit "std/quest_ob";



void create() {

    set_name("emerald");

    set_id( ({ "emerald", "quest_object", "emerald quest" }) );

    set("short", "%^GREEN%^%^BOLD%^The quest for the Emerald of the Mushroom Gnomes%^RESET%^");

    set_long(

	"Years ago the evil scorceror Mordor plundered the land in search "

	"of the enchanted %^GREEN%^%^BOLD%^Emerald of the Mushroom Gnomes"

	"%^RESET%^. This emerald gave a very select race of gnomes a power "

	"beyond what is known as magic today. The evil sorceror killed all "

	"the Gnomes the he met because if the emerald that he stole were ever "

	"to be returned to the Gnomes, his powers would be no longer.\n"

	"Find the emerald and return it to the Mushroom Gnomes if there "

     "are any left...\n\n"

       "Quest rating: Difficult\n"

    );

    set_quest_points(24);

}

