static YAP_String *alloc_yap_string(YAP_Interpreter *inter, char *str, YAP_Boolean is_literal)
{
	YAP_String *ret;

	ret = MEM_malloc(sizeof(YAP_String));
	ret->ref_count = 0;
	ret->is_literal = is_literal;
	ret->string = str;

	return ret;
}

YAP_String *yap_literal_to_yap_string(YAP_Interpreter *inter, char *str)
{
	YAP_String *ret;

	ret = alloc_yap_string(inter, str, YAP_TRUE);
	ret->ref_count = 1;

	return ret;
}

void yap_refer_string(YAP_String *str)
{
	str->ref_count++;
}

void
crb_release_string(CRB_String *str)
{
    str->ref_count--;

    DBG_assert(str->ref_count >= 0, ("str->ref_count..%d\n",
                                     str->ref_count));
    if (str->ref_count == 0) {
        if (!str->is_literal) {
            MEM_free(str->string);
        }
        MEM_free(str);
    }
}

void yap_release_string(YAP_String *str)
{
	str->ref_count--;

	if (str->ref_count == 0) {
		if (!str->is_literal) {
			MEM_free(str->string);
		}
		MEM_free(str);
	}
}