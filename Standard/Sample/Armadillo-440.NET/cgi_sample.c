/************************************************************************
    CGI Script
    
    Copyright (c) 2012-2015 eForce Co., Ltd. All rights reserved.
    
    2012-08-06: Created.
    2015-08-18: Deprecated dbg_console_puts function.
 ************************************************************************/

#include "kernel.h"
#include "net_hdr.h"
#include "http_server.h"
#include "net_strlib.h"

extern void puts_com_opt(VB *msg);  /* from main.c */

/* Response page  */
const char cgi_okay[] =
    "<html>\
    <title> ::: uNet3 HTTP Server ::: </title>\
    <body>\
    <br>\
    <center>\
    <table border=2 width=75%><tr><th><bold>uNet3 HTTP Server</bold></th></tr></table>\
    <br>\
    <p>Setup completed</p>\
    <a href=/>[Return]<a>\
    </center>\
    <hr>\
    <br><br><div align=\"right\"><font size=3>Powered by uC3, eForce Co.,Ltd.</font></div>\
    </body>\
    </html>";

/*******************************
    CGI Script
 *******************************/
INT cgi_val = 0;

void CgiScript(T_HTTP_SERVER *http)
{
    char *cgi_name[2];
    char *cgi_value[2];
    int  cgi_cnt;
    T_HTTP_HEADER *env = &http->hdr;
    VB buf[32];

    /* Parse the query string to argument list */
    CgiGetParam(env->Content, env->ContentLen, cgi_name, cgi_value, &cgi_cnt);

    /* Get cgi_val */
    if (cgi_cnt && net_strcmp(cgi_name[0], "cgi_val") == 0) {
        cgi_val = net_atoi(cgi_value[0]);
        puts_com_opt("\r\nCGI: cgi_val set to ");
        puts_com_opt(net_itoa(cgi_val, buf, 10));
        puts_com_opt("\r\n");
    }

    /* Response page */
    HttpSendText(http, (char *)cgi_okay, sizeof(cgi_okay));

    return;
}

