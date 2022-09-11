#pragma once

typedef struct exception_cause {
	//exception code
	unsigned int code;
	//interrupt or error/exception
	char interrupt;
} exception_cause;

exception_cause get_mcause();
