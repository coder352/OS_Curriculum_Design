#!/usr/bin/python
#coding=utf-8
# Queue封装了Condition的行为，如wait()，notify()，acquire()
# Python 中的是 synchronized queue 同步队列
# 好神奇... 这都可以
# 这个队列有一个condition，它有自己的lock。如果你使用Queue，你不需要为condition和lock而烦恼
from threading import Thread, Condition
from os import system
import curses
import time
import random
from Queue import Queue
# 警察和小偷， 100m 跑道，两人中间3m长的绳子，可以随时跑，到终点停止
# ... 好奇葩的规定...
queue = Queue(6)
queue.put(0)
queue.put(1)
queue.put(2) # 对应于警察和小偷的绳子是3米
length = 100;
condition = Condition() # print 的锁

class ProducerThread(Thread):
    i = 0;
    def getscreen(self, screen):
        self.screen = screen
    def run(self): # 重写Thread的run()方法
        nums = range(6)
        global queue
        while True:
            if(self.i == length):
                break # join 要在当前线程 运行结束以后才可以
                # th.join() # 加上 break 以后就不用 join 了
            num = random.choice(nums)
            queue.put(num) # put()在插入数据前有一个获取lock的逻辑
            self.i += 1
            # 同时，put()也会检查队列是否已满。如果已满，它会在内部调用wait()，生产者开始等待
            # print "Produced", num
            condition.acquire()
            updateframe(self.screen)
            # print "Pol: ", self.i
            condition.release()
            time.sleep(random.random() / 3)

class ConsumerThread(Thread):
    i = 0
    def getscreen(self, screen):
        self.screen = screen
    def run(self):
        global queue
        while True:
            if(self.i == length):
                break
                # po.join()
            num = queue.get() # get()从队列中移出数据前会获取lock
            # get()会检查队列是否为空，如果为空，消费者进入等待状态
            # get()和put()都有适当的notify()。现在就去看Queue的源码吧。
            self.i += 1
            queue.task_done()
            # task_done 在多线程中告诉queue上面的get()完成了
            # print "Consumed", num
            condition.acquire()
            # print "Thi: ", self.i
            updateframe(self.screen)
            condition.release()
            time.sleep(random.random() / 3)
            pass
        pass
    pass
def updateframe(screen):
    screen.clear()
    for i in range(5, 105):
        screen.addstr(10, i, "_")
        pass
    screen.addstr(8, th.i, "T: %d" % th.i)
    screen.addstr(12, po.i, "P: %d" % po.i)
    screen.refresh()
    # screen.getch()

    pass
def main(stdscreen):
    th.getscreen(stdscreen)
    po.getscreen(stdscreen)
    curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK) # 分别是前景色和后景色
    curses.init_pair(2, curses.COLOR_BLUE, curses.COLOR_BLACK) # 背景色为黑，表示用原来的背景色
    curses.init_pair(3, curses.COLOR_MAGENTA,curses.COLOR_BLACK)
    curses.init_pair(4, curses.COLOR_CYAN, curses.COLOR_BLACK)
    curses.init_pair(5, curses.COLOR_YELLOW, curses.COLOR_BLACK)
    stdscreen.clear()
    stdscreen.border(0)
    stdscreen.addstr(10, 20, "1. Police and Thief 1 curses", curses.color_pair(1))
    stdscreen.addstr(12, 20, "2. Police and Thief 2", curses.color_pair(2))
    stdscreen.addstr(14, 20, "3. Philosopher Dinner", curses.color_pair(3))
    stdscreen.refresh()
    x = stdscreen.getch()
    if x == ord('1'):
        th.start()
        po.start()
        updateframe(stdscreen)
        pass
    if x == ord('2'):
        curses.endwin()
        system("make pt")
        curses.wrapper(main)
    if x == ord('3'):
        curses.endwin()
        system("make philosopher")
        curses.wrapper(main)
        pass

th = ProducerThread()
po = ConsumerThread()
if __name__ == '__main__':
    curses.wrapper(main)
    # th.start()
    # po.start()

