******************************************************************************
    �ȈՃV�F���E�T���v���v���O����
    
    Copyright (c) 2014, eForce Co., Ltd. All rights reserved.
    
    2014-04-16: Created.
******************************************************************************

�� �͂��߂�

�@�ȈՃV�F���E�T���v���v���O����(�ȉ����A�ȈՃV�F��)�̎g�p���@��������܂��B


�� �@�\�T�v

�@�{�T���v���v���O�����͕��В񋟂�Telnet�T�[�o�[�A�v���A�����UART�h���C�o��
�����Ďg�p����ȈՃV�F���ł��B�ȉ��̋@�\������܂��B

�@�E���O�C���v�����v�g
�@�E�ȈՃq�X�g���@�\
�@�E���[�U�[�R�}���h�̎��s (�\�[�X�ύX�K�v)


�� �t�@�C���\��

�@�{�T���v���v���O�����A����ъ֘A����t�@�C���͎��̂悤�ɂȂ�܂��B
    
   uC3Std
    ����Driver
    ��  ����inc.............................�h���C�o�̃w�b�_�t�@�C��
    ��  ����src.............................�h���C�o�̃\�[�X�t�@�C��
    ��       ����DDR_COM.c......................�W��COM�|�[�g
    ��       ����DDR_TI_AM335xUART.c............UART
    ����Network
    ��  ����NetApp..........................�T���v���v���O����
    ��       ����telnet_server.c...............Telnet�T�[�o�[
    ����Sample
        ����NET.............................���ʃT���v���v���O����
        ��   ����shell.c........................�ȈՃV�F��(�{��)
        ����EVMAM3358.NETPRO................�T���v���v���O����
             ����DDR_TI_AM335xUART_cfg.h........UART�̐ݒ�
             ����shell_cfg.c/h..................�V�F���ݒ�p�t�@�C��
             ����telnet_server_cfg.h............Telnet�T�[�o�[�̐ݒ�

�@�ȈՃV�F���{�̂� shell.c �A�ȈՃV�F���̐ݒ�� shell_cfg.c/h �ōs���܂��B


�� �V�F���^�X�N�̗p��

�@�ȈՃV�F���͐ڑ����Ƀ^�X�N��1�K�v�Ƃ��܂��B�ȉ��ɃT���v������̃\�[�X����
�������܂��B

    --------------------------------------------
    �y�\�[�X��z
    /* �^�X�N�̐ݒ�l */
    static const T_CTSK net_ctsk_telnets = {
        TA_HLNG, (VP_INT)0, (FP)net_telnets_tsk, 6, 0x400, 0, "TelnetServer"
    };
    static const T_CTSK net_ctsk_shell = {
        TA_HLNG, (VP_INT)0, (FP)net_shell_tsk, 6, 0x400, 0, "Shell"
    };
    static const T_CTSK net_ctsk_console = {
        TA_HLNG, (VP_INT)0, (FP)net_console_tsk, 6, 0x400, 0, "Shell(UART)"
    };
    
    /* Control Block */
    static T_TELNET_SERVER net_ctl_telnets;     /* Telnet�T�[�o�[����p */
    static T_SHELL_CTL net_ctl_shell;           /* �ȈՃV�F������p(Telnet�T�[�o�[) */
    static T_SHELL_CTL net_ctl_console;         /* �ȈՃV�F������p(UART) */

    /*******************************
        Telnet Server Task
     *******************************/
    void net_telnets_tsk(VP_INT exinf)
    {
        net_ctl_telnets.dev_num = ID_NET_DEV;
        net_ctl_telnets.port = INADDR_ANY;
        net_ctl_telnets.shell_tid = net_id_tsk_shell;   /* Telnet�T�[�o�[�Ɗ֘A�t�����ꂽ
                                                           �V�F���̃^�X�NID���w�� */

        telnet_server(&net_ctl_telnets);
    }

    /***********************************
        Shell Task for Telnet Server
     ***********************************/
    void net_shell_tsk(VP_INT exinf)
    {
        net_memset(&net_ctl_shell, 0, sizeof(T_SHELL_CTL));

        net_ctl_shell.typ = TYP_TELNET;         /* �V�F���^�C�v�� Telnet ���w�� */
        net_ctl_shell.pcb = &net_ctl_telnets;   /* Telnet�T�[�o�[�Ƃ��������邽�߂�
                                                   Telnet�T�[�o����p�\���̂��Z�b�g���Ă��� */

        shell_sta(&net_ctl_shell);
    }
    
    /*********************************************
        Shell Task for UART Terminal Console
     *********************************************/
    void net_console_tsk(VP_INT exinf)
    {
        net_memset(&net_ctl_console, 0, sizeof(T_SHELL_CTL));

        net_ctl_console.typ = TYP_COM;          /* �V�F���^�C�v�� UART ���w�� */
        net_ctl_console.com_id = ID_UART;       /* �V�F���Ŏg�p����UART�ԍ����w�� */

        shell_sta(&net_ctl_console);
    }
    
    --------------------------------------------

���ӓ_�Ƃ��āATelet�T�[�o�[�^�X�N�Ɋ֘A�t������V�F���^�X�N��TA_STA������
�t�^���Ȃ��ŉ������B(Telnet�T�[�o�[�ɃN���C�A���g�ڑ����A�V�F���^�X�N���N
�������܂�) �܂��A�V�F���^�X�N�̃X�^�b�N�T�C�Y�̓V�F����œ��삷�郆�[�U�[
�A�v���ő�������̂œK�X���Ȃ��l��ݒ肵�Ă��������B


�� ���O�C�����[�U�[���E�p�X���[�h�̕ύX

���[�U�[���E�p�X���[�h�̕ύX���s���ꍇ�Ashell_cfg.c �� shell_usr_tbl �\��
�̔z��̒l��ύX���Ă��������B�ȉ��ɃT���v������̃\�[�X�����������܂��B

    --------------------------------------------
    �y�\�[�X��z
    /* Login user table (Max. 256 users) */
    const T_SHELL_USR_TBL shell_usr_tbl[] = {
        {"", ""},               /* Login: (��), Password: (��)*/
        {"User", "Password"},   /* Login: User, Password: Password */
        
        {0x00, 0x00}    /* Terminate mark (Do not change) */
    };
    --------------------------------------------


�� ���[�U�[�R�}���h�̕ύX

���[�U�[�R�}���h�̕ύX���s���ꍇ�Ashell_cfg.c �� shell_cmd_tbl �\���̔z��
�̃^�C��ύX���Ă��������B�ȉ��ɃT���v������̃\�[�X�����������܂��B

    --------------------------------------------
    �y�\�[�X��z
    /* Command functions (User commands) */
    /* EXT_FUNC(usr_cmd); */
    EXT_FUNC(shell_usr_cmd_ping);              /* �ǉ��������R�}���h�̌��֐� */

    /* Command table  (Max. 256 commands) */
    const T_SHELL_CMD_TBL shell_cmd_tbl[]  = {
        /* Include command */
        /* func,        cmd_name,  descr,                       usage,  arg_num */
        {shell_cmd_ip,    "ip",    "Display IP Address",        "",           0},
        {shell_cmd_quit,  "quit",  "Disconnect Telnet server",  "",           0},
        {shell_cmd_help,  "help",  "Help",                      "",           0},
        {shell_cmd_help,  "?",     "Help",                      "",           0},
        
        /* User command */
        /* {usr_cmd,      "user",  "Description",               "",           0}, */
        {shell_usr_cmd_ping,  "ping",     "Ping Request",     	"<remote ip> [length]", 1},
        
        {0x00, 0x00, 0x00, 0x00, 0}    /* Terminate mark (Do not change) */
    };
    --------------------------------------------

���[�U�[�R�}���h�p�̊֐������́uER user_cmd (VP ctrl, INT argc, VB *argv[]);�v
�ƂȂ�܂��Bargc �̓R�}���h�����̐��Aargv �̓R�}���h�����̕����񂪓���܂��B


�� ���[�U�[�R�}���h�p�̊֐����Ŏg�p�\�ȊȈՃV�F���pAPI

ER shell_puts(T_SHELL_CTL *sh, const VB *str)
    �ΏۃR���\�[���ւ̕����񑗐M�B��1�����̃p�����[�^�ɂ� VP ctrl ���w�肵�ĉ������B

ER shell_gets(T_SHELL_CTL *sh, VB *str, UH len)
    �ΏۃR���\�[������̕������M�B��1�����̃p�����[�^�ɂ� VP ctrl ���w�肵�ĉ������B



�� ���̑��ݒ�

�V�F���̃E�F���J�����b�Z�[�W�A���O�C���v�����v�g�̕\������ shell_cfg.h ��
�ҏW���邱�ƂŕύX�\�ł��B


