/* Multi-Call Binary for vlmcs and vlmcsd */

#define _CRT_SECURE_NO_WARNINGS

#include "config.h"

#ifndef MULTI_CALL_BINARY
#error "Please define MULTI_CALL_BINARY when compiling this file."
#endif

#include <stdio.h>
#include <libgen.h>

#include "vlmcs.h"
#include "vlmcsd.h"
#include "types.h"
#include "shared_globals.h"
#include "output.h"

/**
 * Multi Entry
 */
int main(int argc, CARGV argv)
{
	multi_argv = argv;
	multi_argc = argc;

	if (!strcmp(basename((char*)*argv), "vlmcsd"))
		return server_main(argc, argv);

	if (!strcmp(basename((char*)*argv), "vlmcs"))
		return client_main(argc, argv);


	if (argc > 1)
	{
		if (!strcmp((char*)argv[1], "vlmcsd"))
			return server_main(argc - 1, argv + 1);

		if (!strcmp((char*)argv[1], "vlmcs"))
			return client_main(argc - 1, argv + 1);
	}

	errorout(
		"vlmcsdmulti %s\n\n"
		"Usage:\n"
		"\t%s vlmcsd [<vlmcsd command line>]\n"
		"\t%s vlmcs [<vlmcs command line>]\n\n",
		Version, *argv, *argv
	);

	return VLMCSD_EINVAL;
}

