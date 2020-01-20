// a navigation tool for the lost and the damned domain

inherit "std/Object";
void reset() {
	::reset();
	if ( !wizardp(environment(this_object()))) {
	this_object()->remove();
}

}

void init() {
	::init();
	add_action("move_me","go");
	if ( environment()->is_player() && !wizardp(environment(this_object()))) {
	this_object()->remove();
}

}

void create() {
	::create();
	set_name("mover");
	set_id( ({"mover"}));
	set_short("Excelsior's Wizard Mover");
	set_long("This is a handy device that allows Wizards to move anywhere "+
	"in the Lost and The damned domain simply by typing 'go x,y' where "+
	"x is the x coordidnate you want to move to and y is the y- wow. "+
	"Cheers.");
	set_value( 5000 );
	set_weight( 1 );
}
int move_me(string str) {
	int x,y;
if ( sscanf( str,"%d,%d",x,y) != 2 ) {
	write("Syntax: go <x>,<y>");
	return 1;
}
if ( x > 39 || x < 1 || y > 39 || y < 1 ) {
	write("Coordinates out of range.");
	return 1;
}
if ( !wizardp(this_player())) {
	write("Only wizards are allowed to use this item.");
	return 1;
}
write("You give the mover your instructions and appear elsewhere with a wizardly feeling.");
this_player()->move_player("/d/damned/virtual/room_"+x+"_"+y+".world");
tell_room( environment(this_player()),this_player()->query_cap_name()+" appears in the room wizardly. Wow." , this_player() );
return 1;
}
