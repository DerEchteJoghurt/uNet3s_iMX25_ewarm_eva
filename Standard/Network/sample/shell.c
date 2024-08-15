/***************************************************************************
    MICRO C CUBE / COMPACT, NETWORK Application
    Simple shell for Telnet Server or UART
    Copyright (c) 2014, eForce Co., Ltd. All rights reserved.

    Version Information
      2014.03.18: Created
      2014.08.05: Fixed bugs: When using UART, prompt chars delete BackSpace.
 ***************************************************************************/

#include "kernel.h"
#include "net_hdr.h"
#include "net_strlib.h"
#include "shell.h"

#if CFG_SH_USE_TELNET
#include "telnet_server.h"
#endif
#if CFG_SH_USE_COM
#include "DDR_COM.h"
#endif

extern const T_SHELL_USR_TBL shell_usr_tbl[];
extern const T_SHELL_CMD_TBL shell_cmd_tbl[];

#if !defined(NULL)
#define NULL    0
#endif

/* Default configuration */
#define SH_MAX_USR_LEN     CFG_SH_MAX_USR_LEN
#define SH_MAX_PWD_LEN     CFG_SH_MAX_PWD_LEN
#define SH_LOGIN_RETRY     CFG_SH_LOGIN_RETRY
#define SH_HISTORY_NUM     CFG_SH_HISTORY_NUM
#define SH_CMD_BUF_LEN     CFG_SH_CMD_BUF_LEN
#define SH_TMP_BUF_LEN     CFG_SH_TMP_BUF_LEN

/* Maximum number of users */
#if !defined(CFG_SH_MAX_USR_CNT)
#define MAX_USR_CNT       256
#else
#define MAX_USR_CNT       CFG_SH_MAX_USR_CNT
#endif

/* Maximum number of commands */
#if !defined(CFG_SH_MAX_CMD_CNT)
#define MAX_CMD_CNT       256
#else
#define MAX_CMD_CNT       CFG_SH_MAX_CMD_CNT
#endif

/* Messages */
#define MSG_WELCOME       CFG_SH_MSG_WELCOME
#define MSG_USR_PRMPT     CFG_SH_MSG_USR_PRMPT
#define MSG_PWD_PRMPT     CFG_SH_MSG_PWD_PRMPT
#define MSG_LOGIN_OK      CFG_SH_MSG_LOGIN_OK
#define MSG_LOGIN_NG      CFG_SH_MSG_LOGIN_NG
#define MSG_CMD_PRMPT     CFG_SH_MSG_CMD_PRMPT
#define MSG_CMD_LONG      CFG_SH_MSG_CMD_LONG

/* Conversion macros */
#define strlen    net_strlen
#define strcpy    net_strcpy
#define strcat    net_strcat
#define strcmp    net_strcmp

/* Error message */
typedef struct err_msg {
    ER ercd;
    VB *msg;
} T_ERR_MSG;

static void utl_add_spc(VB *buf, UB len)
{
    for (; *buf; ++buf) ;
    while (len--)   *(buf++) = ' ';
    *buf = '\0';
}

#if CFG_SH_ENA_ERCD
static int utl_ercd_str(ER ercd, char buf[32])
{
    const char *msg = " Unknown Error";
    const T_ERR_MSG err_msg[] = {
        { E_OK,       " E_OK (0)" },
        { E_SYS,      " E_SYS (-5)"},
        { E_NOSPT,    " E_NOSPT (-9)"},
        { E_PAR,      " E_PAR (-17)"},
        { E_ID,       " E_ID (-18) "},
        { E_NOMEM,    " E_NOMEM (-33)"},
        { E_OBJ,      " E_OBJ (-41)"},
        { E_NOEXS,    " E_NOEXS (-42)"},
        { E_QOVR,     " E_QOVR (-43)"},
        { E_RLWAI,    " E_RLWAI (-49)"},
        { E_TMOUT,    " E_TMOUT (-50)"},
        { E_DLT,      " E_DLT (-51)"},
        { E_CLS,      " E_CLS (-52)"},
        { E_WBLK,     " E_WBLK (-57)"},
        { E_BOVR,     " E_BOVR (-58)"}
    };
    UH i;

    net_memset(buf, ' ', 32);
    if(ercd > E_OK) {
        net_memcpy(buf, "ercd:", 5);
        i = 20;
        *(buf+i+1) = 0;
        while (ercd > 0) {
            *(buf+i) = '0'+ercd%10;
            ercd/=10;
            i--;
        }
        return 0;
    }

    for (i=0; i<(sizeof(err_msg)/sizeof(T_ERR_MSG)); i++) {
        if (err_msg[i].ercd == ercd) {
            return (buf - net_strcpy(buf, err_msg[i].msg));
        }
    }
    return (buf - net_strcpy(buf, msg));
}
#endif

#if (0 < SH_HISTORY_NUM)
#if (0 != (SH_HISTORY_NUM & (SH_HISTORY_NUM - 1)))
  #error "SH_HISTORY_NUM must be designated a power of 2."
#endif

/* Initialization of history for variable */
static void utl_his_ini(T_SHELL_HIS *hist)
{
    net_memset(hist, 0, sizeof(*hist));
}

static void utl_his_enable(T_SHELL_HIS *hist, UB ena)
{
    hist->ena = ena;
}

/* Replace the current buffer and history next */
static UH utl_his_next(T_SHELL_HIS *hist, VB *str, UB prev)
{
    VB tmp[SH_CMD_BUF_LEN];
    UW len;
    
    if (!hist->ena) {
        return net_strlen(str);
    }
    
    if (prev) {
        --hist->ncnt;
    }
    else {
        ++hist->ncnt;
    }
    hist->ncnt &= (SH_HISTORY_NUM - 1);
    
    len = net_strlen(str);
    if (sizeof(hist->buf[0]) <= len) {
        len = sizeof(hist->buf[0]) - 1;
        str[len] = '\0';      
    }
    
    net_strcpy(tmp, str);
    net_strcpy(str, hist->buf[hist->ncnt]);
    net_strcpy(hist->buf[hist->ncnt], tmp);
    
    return net_strlen(str);
}

/* Store current buffer to history */
static void utl_his_store(T_SHELL_HIS *hist, VB *str)
{
    UW len;
    
    if (!hist->ena) {
        return;
    }
    
    len = net_strlen(str);
    if (sizeof(hist->buf[0]) <= len) {
        len = sizeof(hist->buf[0]) - 1;
        str[len] = '\0';      
    }
    
    if (len) {
        net_strcpy(hist->buf[hist->scnt & (SH_HISTORY_NUM - 1)], str);
        ++hist->ncnt;
        ++hist->scnt;
    }
}
#endif

#if CFG_SH_USE_COM
static ER uart_puts(T_SHELL_CTL *sh, const VB *str)
{
    UINT cnt;
    
    cnt = strlen(str);
    puts_com(sh->com_id, (VB*)str, &cnt, TMO_FEVR);
    
    return E_OK;
}

static ER uart_gets(T_SHELL_CTL *sh, VB *buf, UH len, UB echo)
{
    ER ercd;
    INT i;
    INT j;
    INT esc_cnt;
    VB esc;
    UB pre;
    
    esc_cnt = 0;
    ercd = E_OK;
    
    for (i = 0; i < (INT)len; i++) {
        /* Wait for user command */
        ercd = getc_com(sh->com_id, &buf[i], NULL, TMO_FEVR);
        if (ercd != E_OK || buf[i] == '\n') {    /* LF */
            i = -1;
            continue;
        }
        if (buf[i] == 0x1B) {    /* Escape sequence */
            esc_cnt = 1;
            continue;
        }
        if (esc_cnt != 0) {
            esc = buf[i];
            if (esc_cnt == 2) {
                i -= esc_cnt;
                /* Up or down key */
                if (esc == 'A' || esc == 'B') {
                    if (i > 0) {
                        /* Delete right of a string */
                        j = i;
                        while (j > 0) {
                            putc_com(sh->com_id, '\b', TMO_FEVR);
                            j--;
                        }
                        uart_puts(sh, "\033[0K");    /* ESC [ K */
                    }
                    buf[i] = '\0';
                    pre = (esc == 'A') ? 1 : 0;
                    i = utl_his_next(&sh->hist, buf, pre);
                    if (i > 0) {
                        uart_puts(sh, buf);
                    }
                }
                i--;
            }
            esc_cnt = (esc_cnt >= 2) ? 0 : esc_cnt + 1;
            continue;
        }
        
        if (buf[i] == '\r') {    /* CR */
            buf[i] = '\0';
#if (0 < SH_HISTORY_NUM)
            if (i != 0) {
                utl_his_store(&sh->hist, buf);
            }
#endif
            break;
        } else if (buf[i] == '\b') {    /* BS */
            if (i > 0) {
                i -= 2;
                ercd = 3;
                puts_com(sh->com_id, "\b \b", (UINT*)&ercd, TMO_FEVR);
            } else {
                i--;
            }
        } else if (echo != 0) {
            putc_com(sh->com_id, buf[i], TMO_FEVR);    /* Echo */
        }
    }
    
    if (i >= (INT)len) {
        /* Command is too long */
        uart_puts(sh, MSG_CMD_LONG);
        return E_BOVR;
    }
    
    return E_OK;
}


/* Execute command at local task */
static ER local_exec_cmd(UB cmd)
{
    ER ercd;
    ID tid;

    if (cmd & SHELL_CMD_QUIT) {
        ercd = get_tid(&tid);
        if (E_OK == ercd) {
            ercd = act_tsk(tid);
        }
    }
    else {
        ercd = E_NOSPT;
    }

    return ercd;
}
#endif

#if CFG_SH_USE_TELNET
/*-- Following function is used if parent is Telnet server. --*/
#define VTE_NONE        0
#define VTE_UP_KEY      1
#define VTE_DOWN_KEY    2
#define VTE_RIGHT_KEY   3
#define VTE_LEFT_KEY    4

/* Recognize the escape sequence of VT100 */
static UB telnet_esc(VB *str, UB len, UB *pe)
{
    VB *c = str;
    UB event;
    UB nx;
    
    if (*c != 0x1B)     return 0;
    
    event = VTE_NONE;
    
    switch (*(++c)) {
    case '7':   case '8':   case '=':   case '>':
    case 'D':   case 'E':   case 'H':   case 'M':    case 'Z':   case 'c':
        break;
        
    case '#':   case '(':   case ')':
        ++c;
        break;
        
    case '[':
        switch (*(++c)) {
        case 'A':   event = VTE_UP_KEY;     break;
        case 'B':   event = VTE_DOWN_KEY;   break;
        case 'C':   event = VTE_RIGHT_KEY;  break;
        case 'D':   event = VTE_LEFT_KEY;   break;
            
        default:
            for (nx = 0;; ++nx, ++c) {
                if (nx & 0x01) {
                    if (';' != *c)  break;
                }
            }
            break;
        }
        break;
        
    default:
        --c;
        break;
    }
    
    if (pe) {
        *pe = event;
    }
    nx = c - str;
    
    return (nx > len) ? len : nx ;
}

/* Data is transmitted to Telnet server */
static ER telnet_snd(T_TELNET_SERVER *telnet, const VB *buf, UH len)
{
    return snd_soc(telnet->sid, (VP)buf, len);
}

/* Receive data from Telnet server */
static ER telnet_rcv(T_TELNET_SERVER *telnet, VB *buf, UH len)
{
    ER ercd;
    T_SHELL_BLK *sblk;
    
    ercd = rcv_mbx(telnet->mbx_id, (T_MSG **)&sblk);
    
    if (E_OK == ercd) {
        len = (len < sblk->len) ? len : sblk->len;
        net_memcpy(buf, sblk->buf, len);
        rel_mpf(telnet->mpf_id, sblk);
    }
    
    return (0 > ercd) ? ercd : len ;
}

/* String is transmitted to Telnet server */
static ER telnet_puts(T_SHELL_CTL *sh, const VB *str)
{
    T_TELNET_SERVER *telnet = sh->pcb;
        
    return telnet_snd(telnet, str, net_strlen(str));
}

/* Receive string from Telnet server */
static ER telnet_gets(T_SHELL_CTL *sh, VB *str, UH len)
{
    T_TELNET_SERVER *telnet = sh->pcb;
    ER ercd;
    VB *c;
    UH nx;
    UB event;
    VB tmp[SH_TMP_BUF_LEN];  
    
    UB for_brk;
    UB n;
    UB i, s;
    
    for (i = s = 0;; ) {
        ercd = telnet_rcv(telnet, tmp, len);
        if (0 > ercd) {
            break;
        }
        
        for (nx = 0, s = 0, for_brk = 0; (nx < ercd) && (0 == for_brk); ++nx) {
            /* ignore escape sequence */
            if (s) {
                s--;
                continue;
            }
            
            c = &tmp[nx];
            switch (*c) {
            case '\r':  /* CR or LF is end of text */
            case '\n':
                str[i] = '\0';
#if (0 < SH_HISTORY_NUM)                
                utl_his_store(&sh->hist, str);
#endif
                goto _exit_gets;
                
            case 0x7F:  /* delete */
            case '\b':  /* back space */
                if (i > 0) {
                    i--;
                    if (telnet->opt.st_will & TOBIT_ECHO) {
                        telnet_snd(telnet, "\b \b", 3);
                    }
                }
                continue;
                
            case 0x1B:  /* Escape sequence */
                s = telnet_esc(c, ercd - nx, &event);
#if (0 < SH_HISTORY_NUM)
                if (event & (VTE_UP_KEY | VTE_DOWN_KEY)) {
                    str[i] = '\0';
                    n = utl_his_next(&sh->hist, str, (event & VTE_UP_KEY));
                    
                    if (telnet->opt.st_will & TOBIT_ECHO) {
                        /* Escape sequence to remove line of current */
                        if (i) {
                            for (s = 0; s < i; ++s) tmp[s] = '\b';
                            tmp[s++] = 0x1B;
                            tmp[s++] = 0x5B;
                            tmp[s++] = 0x4B;
                            telnet_snd(telnet, tmp, s);
                            s = 0;
                        }
                        telnet_snd(telnet, str, n);
                    }
                    i = n;
                    for_brk = 1;
                }
#endif                
                continue;
                
            default:
                if (*c < 0x20 || *c > 0x7e) {    /* Invisible character */
                    continue;
                }                
                break;
            }
            
            if (i >= len - 1) {    /* Maximum buffer */
                continue;
            }
            
            if (telnet->opt.st_will & TOBIT_ECHO) {
                telnet_snd(telnet, c, 1);
            }            
            str[i++] = *c;
        }
    }
    
_exit_gets:
    return (0 > ercd) ? ercd : E_OK;
}

/* Send command to Telnet server */
static ER telnet_snd_cmd(T_TELNET_SERVER *telnet, UB cmd)
{
    UH tcmd;
    
    tcmd = 0;
    if (cmd & SHELL_CMD_ECHO_ON)   tcmd |= SFC_ECHO_ON;
    if (cmd & SHELL_CMD_ECHO_OFF)  tcmd |= SFC_ECHO_OFF;
    if (cmd & SHELL_CMD_FECHO_ON)  tcmd |= SFC_FECHO_ON;
    if (cmd & SHELL_CMD_FECHO_OFF) tcmd |= SFC_FECHO_OFF;
    if (cmd & SHELL_CMD_QUIT)      tcmd |= SFC_SHELL_QUIT;
    
    set_flg(telnet->flg_id, tcmd);
    set_flg(telnet->flg_id, SF_COMMAND);
    dly_tsk(10);
    
    return E_OK;
}
#endif


/* Command input processing */
static void shell_input(T_SHELL_CTL *sh, char *s)
{
    char *argv[16];
    ER ercd;
    int argc;
    int i;
#if CFG_SH_ENA_ERCD
    char err_msg[32] = {0};
#endif
    
    /* Parse command */
    argv[0] = "";
    for (argc = 0; argc < sizeof argv / sizeof (char *); argc++)
    {   while (' ' == *s)
            s++;
        if ('\0' == *s)
            break;
        argv[argc] = s;
        s = net_strchr(s, ' ');
        if (s == NULL)
            break;
        *s++ = '\0';
    }
    if(0 == net_strcmp(argv[0], "")) {
        return;
    }
    argc++;
    
    /* Command decision */
    ercd = E_OBJ;
    for (i = 0; i < MAX_CMD_CNT; i++) {
        if (shell_cmd_tbl[i].func == 0x00) {
            break;
        }
        if (net_strcmp(argv[0], shell_cmd_tbl[i].cmd_name) == 0) {
            ercd = E_OK;
            break;
        }
    }
    
    if (ercd != E_OK) {    /* Unsupported */
        shell_puts(sh, CFG_SH_LF " no command ");
        shell_puts(sh, argv[0]);
    }
    else if (argc < shell_cmd_tbl[i].arg_num + 1) {    /* Argument abnormal */
        shell_puts(sh, CFG_SH_LF);
        shell_puts(sh, argv[0]);
        shell_puts(sh, " ");
        shell_puts(sh, shell_cmd_tbl[i].usage);
    }
    else {
        ercd = shell_cmd_tbl[i].func(sh, argc, argv);
#if CFG_SH_ENA_ERCD
        utl_ercd_str(ercd, err_msg);
        shell_puts(sh, CFG_SH_LF);
        shell_puts(sh, err_msg);
#endif
    }
    
    shell_puts(sh, CFG_SH_LF);
}

#if CFG_SH_ENA_LOGIN
/* Judgment of a valid user and password */
static ER shell_auth_db(const VB *usr, const VB *pwd)
{
    ER ercd;
    INT i;
    
    ercd = E_OBJ;
    for (i = 0; i < MAX_USR_CNT; i++) {
        if (shell_usr_tbl[i].usr == 0x00) {
            break;
        }
        if (net_strcmp(shell_usr_tbl[i].usr, usr) == 0 &&
            net_strcmp(shell_usr_tbl[i].pwd, pwd) == 0) {
                ercd = E_OK;
                break;
        }
    }
    
    return ercd;
}

/* Show Login prompt */
static ER shell_auth(T_SHELL_CTL *sh)
{
    ER ercd;
    UB retry;
    VB usr[SH_MAX_USR_LEN + 1], pwd[SH_MAX_PWD_LEN + 1];
    
    shell_cmd(sh, SHELL_CMD_ECHO_ON);    /* Echo on */
    
    ercd = E_PAR;
    for (retry = 0; retry < SH_LOGIN_RETRY; ++retry) {
        ercd = shell_puts(sh, MSG_USR_PRMPT);
        ercd = shell_gets(sh, usr, sizeof(usr));
        if (ercd == E_OK) {
            shell_cmd(sh, SHELL_CMD_FECHO_OFF);   /* Echo off */
            ercd = shell_puts(sh, MSG_PWD_PRMPT);
            ercd = shell_gets(sh, pwd, sizeof(pwd));
            shell_cmd(sh, SHELL_CMD_FECHO_ON);    /* Echo on */
        }
        if (ercd == E_OK) {
            ercd = shell_auth_db(usr, pwd);
            if (E_OK == ercd) {
                shell_puts(sh, MSG_LOGIN_OK);
                net_strcpy(sh->usr_name, usr);
                break;
            } else {
                shell_puts(sh, MSG_LOGIN_NG);
                ercd = E_OK;
            }
        }
        if (ercd != E_OK && ercd != E_BOVR) {
            ercd = E_OBJ;
            break;
        }
    }
    
    return ercd;
}
#endif

static ER shell_ini(T_SHELL_CTL *sh)
{
    ER ercd;
    
    if (!sh) {
        return E_PAR;
    }
    
    switch (sh->typ) {  
    case SHELL_TYP_TELNET:
        ercd = (sh->pcb == NULL) ? E_PAR : E_OK;
        break;
        
    case SHELL_TYP_COM:
        ercd = (sh->com_id == 0) ? E_PAR : E_OK;
        break;
        
    default:
        ercd = E_PAR;
        break;
    }
    
    return ercd;
}

ER shell_cmd_ip(VP ctrl, INT argc, VB *argv[])
{
    T_NET_ADR adr;
    ER ercd;
    VB ebuf[SH_TMP_BUF_LEN];

    ercd = net_ref(0, NET_IP4_CFG, (VP)&adr);
    if (E_OK != ercd) {
        return ercd;
    }
    
    ebuf[0] = '\0';
    
    net_strcat(ebuf, CFG_SH_LF " IP Address  : ");
    ercd = net_strlen(ebuf);
    ip_ntoa(&ebuf[ercd], adr.ipaddr);
    
    net_strcat(ebuf, CFG_SH_LF " Subnet Mask : ");
    ercd = net_strlen(ebuf);
    ip_ntoa(&ebuf[ercd], adr.mask);
    
    net_strcat(ebuf, CFG_SH_LF " Gateway     : ");
    ercd = net_strlen(ebuf);
    ip_ntoa(&ebuf[ercd], adr.gateway);
    
    shell_puts(ctrl, ebuf);
    
    return E_OK;
}

ER shell_cmd_help(VP ctrl, INT argc, VB *argv[])
{
    VB ebuf[SH_TMP_BUF_LEN];
    UH i;
    UB len, spc;
    
    
    /* Calculate the number of spaces between command and description */
    spc = 0;
    for(i = 0; i < MAX_CMD_CNT; i++) {
        if (shell_cmd_tbl[i].func == 0x00) {
            break;
        }
        len = net_strlen(shell_cmd_tbl[i].cmd_name);
        if (len > spc) {
            spc = len;
        }
    }
    spc = (spc + (4-1)) & (~(4 - 1));   /* space width 4x */
    
    /* Show command and command description */
    for(i = 0; i < MAX_CMD_CNT; i++) {
        if (shell_cmd_tbl[i].func == 0x00) {
            break;
        }
        ebuf[0] = '\0';
        net_strcat(ebuf, CFG_SH_LF " ");
        net_strcat(ebuf, shell_cmd_tbl[i].cmd_name);
        
        len = spc - net_strlen(shell_cmd_tbl[i].cmd_name);
        utl_add_spc(ebuf, len);
        net_strcat(ebuf, " -> ");
        
        net_strcat(ebuf, shell_cmd_tbl[i].descr);
        shell_puts(ctrl, ebuf);
    }
    return E_OK;
}

ER shell_cmd_quit(VP ctrl, INT argc, VB *argv[])
{
    shell_puts(ctrl, CFG_SH_LF CFG_SH_LF);
    shell_cmd(ctrl, SHELL_CMD_QUIT);
    ext_tsk();
    
    return E_OK;
}

ER shell_sta(T_SHELL_CTL *sh)
{
    ER ercd;
    VB buf[SH_CMD_BUF_LEN];
    
    ercd = shell_ini(sh);
    if (E_OK != ercd) {
        return ercd;
    }
    
#if CFG_SH_ENA_WELLCOME
    /* Welcome Message */
    shell_puts(sh, MSG_WELCOME);
#endif
#if CFG_SH_ENA_LOGIN
    /* Login Prompt */
    ercd = shell_auth(sh);
    if (E_OK != ercd) {
        shell_cmd(sh, SHELL_CMD_QUIT);
        ext_tsk();
    }
#endif
    
#if (0 < SH_HISTORY_NUM)
    /* history clear */
    utl_his_ini(&sh->hist);
#endif
    
    for (;;) {
        ercd = shell_puts(sh, MSG_CMD_PRMPT);
        utl_his_enable(&sh->hist, 1);
        ercd = shell_gets(sh, (VB *)buf, sizeof(buf));
        utl_his_enable(&sh->hist, 0);
        
        if (0 <= ercd) {
            if ('\0' != buf[0]) {
                shell_input(sh, (VB *)buf);
            }
        }
    }
}

/* String is transmitted */
ER shell_puts(T_SHELL_CTL *sh, const VB *str)
{
    ER ercd;
    
    if (!sh) {
        return E_PAR;
    }
    
    switch (sh->typ) {
#if CFG_SH_USE_TELNET
    case SHELL_TYP_TELNET:
        ercd = telnet_puts(sh, str);
        break;
#endif
#if CFG_SH_USE_COM
    case SHELL_TYP_COM:
        ercd = uart_puts(sh, str);
        break;
#endif

    default:
        ercd = E_NOSPT;
        break;
    }
    
    return ercd;
}

/* Receive string */
ER shell_gets(T_SHELL_CTL *sh, VB *str, UH len)
{
    ER ercd;
    
    if (!sh) {
        return E_PAR;
    }
    
    switch (sh->typ) {
#if CFG_SH_USE_TELNET
    case SHELL_TYP_TELNET:
        ercd = telnet_gets(sh, str, len);
        break;
#endif
#if CFG_SH_USE_COM
    case SHELL_TYP_COM:
        ercd = uart_gets(sh, str, len, 1 /* Echo */);
        break;
#endif
        
    default:
        ercd = E_NOSPT;
        break;
    }
    
    return ercd;
}

/* Send command */
ER shell_cmd(T_SHELL_CTL *sh, UB cmd)
{
    ER ercd;
    
    if (!sh) {
        return E_PAR;
    }
    if (0 != (cmd & ~SHELL_CMD_ALL)) {
        return E_NOSPT;
    }
    
    switch (sh->typ) {
#if CFG_SH_USE_TELNET
    case SHELL_TYP_TELNET:
        ercd = telnet_snd_cmd(sh->pcb, cmd);
        break;
#endif
#if CFG_SH_USE_COM
    case SHELL_TYP_COM:
        ercd = local_exec_cmd(cmd);
        break;
#endif

    default:
        ercd = E_NOSPT;
        break;
    }
    
    return ercd;
}

