%%
%% ibt_client ≤‚ ‘
%%
loadlibrary('libibt_client_ex.dll','ibt_client.h');
[a1] = calllib('libibt_client_ex','ibt_send_order',2,0,0,1);
unloadlibrary('libibt_client_ex');
