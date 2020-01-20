inherit "/std/spells/shadows/shadow";

private object player;

string query_cap_name();

void sh_init( object ob )
{
    if( query_shadowing( ob ) )
    {
	tell_object( ob, "You are already shadowed by this." );
	call_out( "remove", 1 );
	return;
    } else tell_object( ob, "Now shadowing." );
    begin_shadow( ob );
    player = ob;
}

void remove_me()
{
    stop_shadow();
    remove();
}

void setenv( string s, mixed value )
{
    if( s == "TITLE" ) 
    {
	tell_object( player, this_player()->query_cap_name() +
	  " tried to change your title to " + value + "." );
	return;
    }
    return( player->setenv( s, value ) );
}

string query_title()
{
    string tmp;

    switch( random( 10 ) )
    {
    case 0: tmp = "-> We've changed a lot and then some - some"; break;
    case 1: tmp = "-> You know that we have always been down - down"; break;
    case 2: tmp = "-> And if I ever don't thank you - you";break; 
    case 3: tmp = "-> Then just let me do it now"; break;
    case 4: tmp = "-> Keep my feet on the ground";break;
    case 5: tmp = "-> Keep my head in the clouds";break;    
    case 6: tmp = "-> Electrified by the sound";break;
    default: tmp = "-> Comes from the down - and";break;
    }
    return( query_cap_name() + " " + tmp );
}

string query_cap_name()
{
    string name, tmp;
    
    if(this_player())
    {
      name = this_player()->query_cap_name() + " oohh great one";
    } else {
    name = "Someone";
    }
    
    switch( random( 3 ) )
    {
    case 0: tmp = "DrIzZt"; break;
    default: tmp = "Drizz't Do'Urden"; break;
    }
    return tmp;
}

