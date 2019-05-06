# 可下载至arm开发板运行的音乐播放器软件

main.c 负责参数的输入以及触摸控制，argv[0]:运行文件名,argv[2]:mp3文件目录名，argv[2]：背景图名

bmp.c bmp.h 负责背景图在开发板上的显示方式

lcd.c lcd.h 负责将背景图显示以及对屏幕的操作

linklist.c linklist.h 创建链表来保存从目录中读出的mp3文件

Makefile 自动编译并将可运行文件拷贝到tftp目录下用tftp协议下载至开发板


