#include <stdlib.h>
#include <stdio.h>

#define STR_LEN_DEF 256

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#define NAME "XML-RPC xmlrpc-c get_sum client"
#define VERSION "1.0"

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

int main(int argc, char **argv)
{
    xmlrpc_env env;
    xmlrpc_value *resultP;
    char server_url[STR_LEN_DEF];
    const char *const method_name = "get.sum"; // Client logic

    if (argc - 1 != 2)
    {
        fprintf(stderr, "You must specify two arguments - "
                        "the server ip addres and the server port\n");
        exit(-1);
    }

    sprintf(server_url, "http://%s:%s/RPC2", argv[1], argv[2]);

    xmlrpc_env_init(&env);

    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    die_if_fault_occurred(&env, "xmlrpc_client_init2()");

    // Client logic +++

    xmlrpc_value *arrayP = xmlrpc_array_new(&env);
    die_if_fault_occurred(&env, "xmlrpc_array_new()");

    size_t len;
    printf("Amount of numbers = ");
    scanf("%zd", &len);

    printf("Numbers:\n");
    for (size_t i = 0; i < len; i++)
    {
        double elem;
        scanf("%lf", &elem);

        xmlrpc_value *elemP;
        elemP = xmlrpc_double_new(&env, elem);
        die_if_fault_occurred(&env, "xmlrpc_double_new()");

        xmlrpc_array_append_item(&env, arrayP, elemP);
        die_if_fault_occurred(&env, "xmlrpc_array_append_item()");

        xmlrpc_DECREF(elemP);
    }

    resultP = xmlrpc_client_call(&env, server_url, method_name, "(A)", arrayP);
    die_if_fault_occurred(&env, "xmlrpc_client_call()");

    xmlrpc_double sum;
    xmlrpc_read_double(&env, resultP, &sum);
    die_if_fault_occurred(&env, "xmlrpc_read_double()");

    printf("Sum = %lf\n", sum);

    xmlrpc_DECREF(arrayP);

    // Client logic ---

    xmlrpc_DECREF(resultP);

    xmlrpc_env_clean(&env);

    xmlrpc_client_cleanup();

    return 0;
}
