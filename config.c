#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


static const char *init_mode_str[] = {
	[CFG_DEFAULT] = "default",
	[CFG_GLIDER]  = "glider",
	[CFG_RANDOM]  = "random",
};

static const struct option long_options[] =
{
	{"help",  no_argument,       0, 'h'},
	{"nrows", required_argument, 0, 'R'},
	{"ncols", required_argument, 0, 'C'},
	{"init",  required_argument, 0, 'i'},
	{0, 0, 0, 0}
};

static bool check_config(const struct config *config);
static enum cfg_init_mode str2init_mode(const char *opt);

int config_parse_argv(struct config *config, int argc, char *argv[])
{
	int option_index = 0;
	int c;

	// Default values
	config->show_help = false;
	config->nrows     = 20;
	config->ncols     = 20;
	config->init_mode = CFG_DEFAULT;

	while ((c = getopt_long(argc, argv, "hR:C:i:", long_options,
				&option_index)) != -1) {
		switch (c) {
		case 'h':
			config->show_help = true;
			config_print_usage(argv[0]);
			break;
		case 'R':
			config->nrows = strtol(optarg, NULL, 0);
			break;
		case 'C':
			config->ncols = strtol(optarg, NULL, 0);
			break;
		case 'i':
			config->init_mode = str2init_mode(optarg);
		case '?':
			printf("\nERROR: unknown option %s \n", optopt);
		}
	}
	return check_config(config);
}


static bool check_config(const struct config *config)
{
	bool correct = true;

	if (config->show_help)
		return true;

	correct &= config->nrows > 0;
	correct &= config->ncols > 0;
	correct &= config->init_mode > -1;

	return correct;
}

static enum cfg_init_mode str2init_mode(const char *opt)
{
	int i;
	for (i = 0; i < CFG_N_INIT_MODES; i++)
		if ( !strcmp(opt, init_mode_str[i]) )
			break;
	return i == CFG_N_INIT_MODES ? CFG_NOT_DEF : i;
}

void config_print_usage(const char *arg0)
{
	printf("Usage: %s\n"
		"\t[-h|--help]\n"
		"\t[-R|--nrows <positive integer>]\n"
		"\t[-C|--ncols <positive integer>]\n"
		"\t[-i|--init <init_mode>]\n"
		, arg0);

	// Print all initialization modes
	printf("\ninit_mode: ");
	for (int i = 0; i < CFG_N_INIT_MODES + 1; i++)
		printf(" '%s'", init_mode_str[i]);
	printf("\n\n");
}

void config_print(const struct config *config)
{
	printf("config {\n");
	printf("\tshow help = %s\n", config->show_help ? "YES" : "NO");
	printf("\tsize_x    = %d\n", config->nrows);
	printf("\tsize_y    = %d\n", config->ncols);
	printf("\tinit_mode = %d(%s)\n",
		config->init_mode, init_mode_str[config->init_mode]);
	printf("}\n");
}
