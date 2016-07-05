#!/usr/bin/python
#coding=utf-8
import curses
from os import system

def main(stdscreen):
    curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK) # 分别是前景色和后景色
    curses.init_pair(2, curses.COLOR_BLUE, curses.COLOR_BLACK) # 背景色为黑，表示用原来的背景色
    curses.init_pair(3, curses.COLOR_MAGENTA,curses.COLOR_BLACK)
    curses.init_pair(4, curses.COLOR_CYAN, curses.COLOR_BLACK)
    curses.init_pair(5, curses.COLOR_YELLOW, curses.COLOR_BLACK)
    stdscreen.clear()
    stdscreen.border(0)
    stdscreen.addstr(6, 20, "1. fork", curses.color_pair(1))
    stdscreen.addstr(8, 20, "2. signal", curses.color_pair(2))
    stdscreen.addstr(10, 20, "3. pipe", curses.color_pair(3))
    stdscreen.addstr(12, 20, "4. popen", curses.color_pair(4))
    stdscreen.addstr(14, 20, "5. fifo", curses.color_pair(5))
    stdscreen.addstr(16, 20, "6. clean", curses.color_pair(1))
    stdscreen.addstr(18, 20, "9. exit", curses.color_pair(2))
    stdscreen.refresh()
    x = stdscreen.getch()
    if x == ord('1'):
        curses.endwin()
        system("make -C ./process fork")
        stdscreen.getch() # 让程序等一会,否则看不见结果,就会回到菜单界面
        curses.wrapper(main)
        pass
    if x == ord('2'):
        curses.endwin()
        system("make -C ./process signal")
        stdscreen.getch()
        curses.wrapper(main)
    if x == ord('3'):
        curses.endwin()
        system("make -C ./process pipe")
        stdscreen.getch()
        curses.wrapper(main)
        pass
    if x == ord('4'):
        curses.endwin()
        system("make -C ./process popen")
        stdscreen.getch()
        curses.wrapper(main)
        pass
    if x == ord('5'):
        curses.endwin()
        system("make -C ./process fifo")
        stdscreen.getch()
        curses.wrapper(main)
        pass
    if x == ord('6'):
        curses.endwin()
        system("make -C ./process clean")
        stdscreen.getch()
        curses.wrapper(main)
        pass
    if x == ord('9'):
        curses.endwin()
        pass
    pass
if __name__ == '__main__':
    curses.wrapper(main)
