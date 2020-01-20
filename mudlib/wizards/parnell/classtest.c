#include <driver/runtime_config.h>;

inherit "/adm/obj/master.c";

class test_class {
    string thing;
}

/* master overrides for testing */
void ERROR(string msg) {
    write(sprintf("%s [%s] - %s",ctime(time()),"ERROR",msg));
}
void WARN(string msg) {
    write(sprintf("%s [%s] - %s",ctime(time()),"WARN",msg));
}
void INFO(string msg) {
    write(sprintf("%s [%s] - %s",ctime(time()),"INFO",msg));
}
void TRACE(string msg) {
    write(sprintf("%s [%s] - %s",ctime(time()),"TRACE",msg));
}
/* end of overrides */

void test_epilog() {
    string * results;
    results = epilog(1);
    for(int x=0;x<sizeof(results);x++) {
        write(x);
        write(results[x]);
    }
}

void create()
{
    class test_class one;
        
    //Master.c tests
    flag("test");
    
    test_epilog();

    call_out("destroy", 5);
}

void destroy() {
    destruct(this_object());
}