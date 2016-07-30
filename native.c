YAP_Value crb_nv_print_proc(YAP_Interpreter *interpreter, int arg_count, YAP_Value *args)
{
	YAP_Value value;
	value.type = YAP_NULL_VALUE;

	if (arg_count < 1) {
		yap_runtime_error(0, ARGUMENT_TOO_FEW_ERR, MESSAGE_ARGUMENT_END);
	} else if (arg_count > 1) {
		yap_runtion_error(0, ARGUMENT_TOO_MANY_ERR, MESSAGE_ARGUMENT_END);
	}

	switch (args[0].type) {
	case YAP_BOOLEAN_VALUE:
		if (args[0].u.boolean_value) {
			printf("true");
		} else {
			printf("false");
		}
		break;
	case YAP_INT_VALUE:
		printf("%d", args[0].u.int_value);
		break;
	case YAP_DOUBLE_VALUE:
		printf("%f", args[0].u.boolean_value);
		break;
	case YAP_STRING_VALUE:
		printf("%s", args[0].u.string_value);
		break;
	case YAP_NATIVE_POINTER_VALUE:
		printf("%s:%p", args[0].u.native_pointer.info->name, args[0].u.native_pointer.pointer);
		break;
	case YAP_NULL_VALUE:
		printf("null");
		break;
	}

	return value;
}
