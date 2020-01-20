// /d/damned/quest/mae-tagg_quest



inherit "std/quest_ob";



void create() {

	set_name("mae-tagg");

	set_id(({"mae-tagg","mae-tagg quest","quest_object","the quest to rescur mae-tagg"}));

	set("short","%^BLUE%^%^BOLD%^The quest to rescue Mae-tagg%^RESET%^");

	set("long","The city of New Faerie Dust was not always a cess pool of crime "+

		"and poverty. This poverty was brought on with the new mayor and his "+

		"dictatorship. Legend tells of the heroics of Toastmaster and his "+

		"side kick Mae-tagg. However, recently the government captured Mae-tagg "+

		"and Toastmaster had to hide in the sewer system. This brings us "+

		"to %^BLUE%^%^BOLD%^the quest to rescue mae-tagg.%^RESET%^ Find him and "+

		"bring him to toastmaster.\n\n"+

		"Quest rating: %^GREEN%^mid-level");

	set_quest_points(21);

}

