COMMAND     PID   USER   FD   TYPE             DEVICE SIZE/OFF    NODE NAME
minishell 40455 gevorg  cwd    DIR              259,6     4096 3706863 /home/gevorg/Desktop/Minishell
minishell 40455 gevorg  rtd    DIR              259,6     4096       2 /
minishell 40455 gevorg  txt    REG              259,6   377112 3708495 /home/gevorg/Desktop/Minishell/minishell
minishell 40455 gevorg  mem    REG              259,6  5717136 1706128 /usr/lib/locale/locale-archive
minishell 40455 gevorg  mem    REG              259,6   200136 1705128 /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
minishell 40455 gevorg  mem    REG              259,6  2220400 1705254 /usr/lib/x86_64-linux-gnu/libc.so.6
minishell 40455 gevorg  mem    REG              259,6   335936 1712720 /usr/lib/x86_64-linux-gnu/libreadline.so.8.1
minishell 40455 gevorg  mem    REG              259,6    27002 2541090 /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache
minishell 40455 gevorg  mem    REG              259,6   240936 1704706 /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
minishell 40455 gevorg    0u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    1u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    2u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    3u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    4u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    5u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    6w   REG              259,5        0      65 /tmp/.heredoc
minishell 40455 gevorg   37w   REG              259,6      487 3713834 /home/gevorg/.config/Code/logs/20240211T204825/ptyhost.log
minishell 40455 gevorg   38u  unix 0x0000000000000000      0t0   28336 type=STREAM
minishell 40455 gevorg   39r   REG              259,6 12177191 2108675 /usr/share/code/resources/app/node_modules.asar
minishell 40455 gevorg  103r   REG              259,6   626509 2108845 /usr/share/code/v8_context_snapshot.bin







gevorg@Legion-5-15IAH7:~/Desktop/Minishell$ lsof -p 40455
COMMAND     PID   USER   FD   TYPE             DEVICE SIZE/OFF    NODE NAME
minishell 40455 gevorg  cwd    DIR              259,6     4096 3706863 /home/gevorg/Desktop/Minishell
minishell 40455 gevorg  rtd    DIR              259,6     4096       2 /
minishell 40455 gevorg  txt    REG              259,6   377112 3708495 /home/gevorg/Desktop/Minishell/minishell
minishell 40455 gevorg  mem    REG              259,6  5717136 1706128 /usr/lib/locale/locale-archive
minishell 40455 gevorg  mem    REG              259,6   200136 1705128 /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
minishell 40455 gevorg  mem    REG              259,6  2220400 1705254 /usr/lib/x86_64-linux-gnu/libc.so.6
minishell 40455 gevorg  mem    REG              259,6   335936 1712720 /usr/lib/x86_64-linux-gnu/libreadline.so.8.1
minishell 40455 gevorg  mem    REG              259,6    27002 2541090 /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache
minishell 40455 gevorg  mem    REG              259,6   240936 1704706 /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
minishell 40455 gevorg    0u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    1u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    2u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    3u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    4u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg    5u   CHR              136,0      0t0       3 /dev/pts/0
minishell 40455 gevorg   37w   REG              259,6      487 3713834 /home/gevorg/.config/Code/logs/20240211T204825/ptyhost.log
minishell 40455 gevorg   38u  unix 0x0000000000000000      0t0   28336 type=STREAM
minishell 40455 gevorg   39r   REG              259,6 12177191 2108675 /usr/share/code/resources/app/node_modules.asar
minishell 40455 gevorg  103r   REG              259,6   626509 2108845 /usr/share/code/v8_context_snapshot.bin