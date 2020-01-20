//    A replacement for call_out.  Uses a single daemon
//    to manage delayed function calls.  Hopefully will
//    reduce overhead for some applications.

#define DELAY_D "/adm/daemon/delayed_function_d"

void remove_delayed_call(string func) {
  object caller;

  caller = previous_object();
  if(!caller) return;
  DELAY_D->remove_delayed_call(caller, func);
  return;
}

