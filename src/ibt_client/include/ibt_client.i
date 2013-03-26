 %module ibt_client
 %{
 /* Includes the header in the wrapper code */
 #include "ibt_client.h"
 %}
 
 /* Parse the header file to generate wrappers */
 #define LIBIBT_CLIENT_STATIC_EXPORTS
 %include "ibt_client.h"
 