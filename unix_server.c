#include <stdlib.h>
#include <stdio.h>

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>

static void
die_if_fault_occurred(xmlrpc_env *const envP,
                      const char *const fun)
{
    if (envP->fault_occurred)
    {
        fprintf(stderr, "%s failed. %s (%d)\n",
                fun, envP->fault_string, envP->fault_code);
        exit(-1);
    }
}

// Server logic +++

static xmlrpc_value *
get_sum(xmlrpc_env *const envP,
        xmlrpc_value *const paramarrayP,
        void *const serverInfo,
        void *const channelInfo)
{
    xmlrpc_double sum = 0.0;

    xmlrpc_value *arrayP;
    xmlrpc_decompose_value(envP, paramarrayP, "(A)", &arrayP);
    die_if_fault_occurred(envP, "xmlrpc_decompose_value()");

    int len;
    len = xmlrpc_array_size(envP, arrayP);
    die_if_fault_occurred(envP, "xmlrpc_array_size()");

    for (int i = 0; i < len; i++)
    {
        xmlrpc_value *elemP;
        xmlrpc_double elem;

        xmlrpc_array_read_item(envP, arrayP, i, &elemP);
        die_if_fault_occurred(envP, "xmlrpc_array_read_item()");

        xmlrpc_read_double(envP, elemP, &elem);
        die_if_fault_occurred(envP, "xmlrpc_read_double()");

        sum += elem;

        xmlrpc_DECREF(elemP);
    }

    xmlrpc_DECREF(arrayP);

    return xmlrpc_build_value(envP, "d", sum);
}

// Server logic ---

int main(int argc, char **argv)
{
    struct xmlrpc_method_info3 const method_info =
        {
            // Server logic +++
            "get.sum",
            &get_sum,
            // Server logic ---
        };
    xmlrpc_server_abyss_parms server_param;
    xmlrpc_registry *registryP;
    xmlrpc_env env;

    if (argc - 1 != 1)
    {
        fprintf(stderr, "You must specify the only argument - the TCP port\n");
        exit(-1);
    }

    xmlrpc_env_init(&env);

    registryP = xmlrpc_registry_new(&env);
    die_if_fault_occurred(&env, "xmlrpc_registry_new()");

    xmlrpc_registry_add_method3(&env, registryP, &method_info);
    die_if_fault_occurred(&env, "xmlrpc_registry_add_method3()");

    server_param.config_file_name = NULL;
    server_param.registryP = registryP;
    server_param.port_number = atoi(argv[1]);
    server_param.log_file_name = "xmlrpc_log";

    xmlrpc_server_abyss(&env, &server_param, XMLRPC_APSIZE(log_file_name));
    die_if_fault_occurred(&env, "xmlrpc_server_abyss()");

    return 0;
}
