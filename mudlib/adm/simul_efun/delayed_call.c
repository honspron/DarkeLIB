//    A replacement for call_out.  Uses a single daemon
//    to manage delayed function calls.  Hopefully will
//    reduce overhead for some applications.

#define DELAY_D "/adm/daemon/delayed_function_d"

varargs void delayed_call(string func, int dly, mixed arg1, mixed arg2, mixed arg3, mixed arg4) {
  object caller;

  caller = previous_object();
  if(!caller) return;
  DELAY_D->add_function(caller, func, dly, arg1, arg2, arg3, arg4);
  return;
}

