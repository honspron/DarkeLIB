// /d/nfd/rooms/shops/dippy

inherit "/std/npc_shop";

void create() {
        object ob;
	::create();
	set_name("dippy");
	set("id",({"dippy","shopkeeper","man"}) );
	set_level( 20 );
	set("short","Dippy the shopkeeper");
	set("long","This is Dippy the shopkeeper. He has spent his life collecting "+
		"oddities and magical items. He would be happy to sell them to you at "+
		"a slight profit. 'say dippy, help' for some assistance." );
	set("race","dwarf");
	set_gender( "male" );
	set_body_type("human");
        set_overall_ac(120);
	set_skill( "attack",150);
	set_skill("dodge",100 );
	set_skill("prayer",100);
	set_skill("melee",130);
	set_skill("parry",200);
	set_skill("conjuration",105);
	set_combat_chance(80);
	add_spell("ice dagger","$A");
	add_spell("heal","$ME");
	set_spell_level("ice dagger",6);
	set_spell_level("heal",6);
	set_money("platinum",800);
	set_languages( ({"dwarvish","elvish","treefolk","serra","yin","common",
		"middle-english","gods-tongue"}) );
	set("storage room","/d/nfd/rooms/shops/dippy_storage");
	set("markup",1);
	set("no sell",1);
        ob = new("wizards/excelsior/rooms/shops/mshirt");
        ob->move(this_object());
	force_me("wear shirt");
        return;
}
