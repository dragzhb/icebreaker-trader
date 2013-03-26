 %module ibt_asset
 %{
 /* Includes the header in the wrapper code */
 #include "ibt_asset_cxx.h"
 %}
 
 /* Parse the header file to generate wrappers */
 #define LIBIBT_ASSET_STATIC_EXPORTS
 %include "ibt_asset_cxx.h"
 