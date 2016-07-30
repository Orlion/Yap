static YAP_Interpreter *st_current_interpreter;

void crb_set_current_interpreter(YAP_Interpreter *inter)
{
    st_current_interpreter = inter;
}
