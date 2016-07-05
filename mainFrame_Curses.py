#!/usr/bin/env python
#coding=utf-8
from os import system
# from Consumer_Producer_Queue_Curses import main
import Consumer_Producer_Queue_Curses
import process_curses
import curses
import locale
locale.setlocale(locale.LC_ALL, '')
encoding = locale.getpreferredencoding()
def get_param(prompt_string):
    screen.clear()
    screen.border(0)
    screen.addstr(2, 2, prompt_string)
    screen.refresh()
    input = screen.getstr(10, 10, 60)
    return input
def execute_cmd(cmd_string):
    system("clear")
    a = system(cmd_string)
    print ""
    if a == 0:
        print "Command executed correctly"
    else:
        print "Command terminated with error"
    raw_input("Press enter")
    print ""
x = 0
screen = curses.initscr() # 申请一次就够了，endwin之后变量依然保存着窗口
curses.start_color() # 告知系统准备在程序中使用颜色了
curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK) # 分别是前景色和后景色
curses.init_pair(2, curses.COLOR_BLUE, curses.COLOR_BLACK) # 背景色为黑，表示用原来的背景色
curses.init_pair(3, curses.COLOR_MAGENTA,curses.COLOR_BLACK)
curses.init_pair(4, curses.COLOR_CYAN, curses.COLOR_BLACK)
curses.init_pair(5, curses.COLOR_YELLOW, curses.COLOR_BLACK)
curses.curs_set(0)
while x != ord('9'):
    screen.clear()
    screen.border(0) # 每次clear之后都要再写一次，花布周围画上边框。
    # 这虽然不是必须的，但有了之后却可以让我们的窗口看起来更漂亮
    # 每次使用边界时都会消耗掉一个可用的字符位置
    # 行和字符位置都是从0开始的。这就意味着屏幕的第一行是0，最后一行是终端最底部，超出会报错
    rows, columns = screen.getmaxyx()
    bottom_menu = u"(↓) Next line | (↑) Previous line | (→) Next page | (←) Previous page | (q) Quit".encode(encoding).center(columns - 4) # center(len) len指定了总长度,在其中间显示字符串
    screen.addstr(rows - 1, 2, bottom_menu, curses.A_REVERSE)

    screen.addstr(3, 2, "Please enter a number...")
    screen.addstr(6, 4, "1 - Add a user", curses.color_pair(1))
    screen.addstr(7, 4, "2 - MultiThread", curses.color_pair(2))
    screen.addstr(8, 4, "3 - Show disk space", curses.color_pair(3))
    screen.addstr(9, 4, "4 - Spiral Rectangle", curses.color_pair(4))
    screen.addstr(10, 4, "5 - Process", curses.color_pair(1))
    screen.addstr(11, 4, "6 - jshell", curses.color_pair(2))
    screen.addstr(12, 4, "9 - Exit", curses.color_pair(5))
    screen.refresh() # 当调用一个方法去显示或者擦除文本时，效果不会立即显示。为了减少屏幕重绘的时间，
    # curses就先累积这些操作，用一种更有效的方式去显示。
    # 就比如说你的程序先在窗口显示了几个字符，然后就清除屏幕，那就没必要发送初始字符了，因为它们不会被显示。
    # 因此，curses需要你使用refresh()函数明确指出重绘窗口
    x = screen.getch()
    if x == ord('1'):
        username = get_param("Enter the username")
        homedir = get_param("Enter the home directory, eg /home/nate")
        groups = get_param("Enter comma-separated groups, eg adm,dialout,cdrom")
        shell = get_param("Enter the shell, eg /bin/bash:")
        screen.clear()
        screen.border(0) # border(0)比较好看，clear以后原来的border也会消失
        screen.addstr(10, 10, "useradd -d " + homedir + " -g 1000 -G " + groups + " -m -s " + shell + " " + username)
        screen.getch() # 这里是让程序停在那里，直到输入任意字符才离开
        # curses.endwin() # 因为下面要执行终端的命令，所以要结束curses，返回终端模式
        # execute_cmd("useradd -d " + homedir + " -g 1000 -G " + groups + " -m -s " + shell + " " + username)
    if x == ord('2'):
        curses.endwin()
        curses.wrapper(Consumer_Producer_Queue_Curses.main)
        curses.cbreak() # 不加这句话,如果切换了其它的 curses 界面,再回来就会回显自己的输入,并且要按回车
        # curses.noecho() # 不显示自己输入的字符
        # execute_cmd("apachectl restart")
    if x == ord('3'):
        curses.endwin()
        execute_cmd("df -h") # 执行终端命令以前一定要endwin
        pass
    if x == ord('4'):
        curses.endwin()
        # system("vim lx.cpp")
        execute_cmd("g++ -o JD lx.cpp && ./JD && rm JD")
    if x == ord('5'):
        curses.endwin()
        curses.wrapper(process_curses.main)
        curses.cbreak()
    if x == ord('6'):
        curses.endwin()
        system("./Jshell")
        curses.cbreak()
        pass
curses.endwin() # 在程序运行结束后，返回终端的默认模式，避免终端混乱，所以这句话在每个判断分支都要有或者最后
# 有时候会用try ... finally 的方式确保 endwin 最后会被执行
