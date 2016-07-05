// 编码方式 ISO-8859-1
/*  范例名称：生产者--消费者问题
 *  源文件名称：ProducerConsumer.java
 *  要  点：
 *      1. 共享数据的不一致性/临界资源的保护
 *      2. Java对象锁的概念
 *      3. synchronized关键字/wait()及notify()方法
 */
public class ProducerConsumer {
    public static void main(String[] args) {
        SyncStack ss = new SyncStack();
        Producer p = new Producer(ss);
        Consumer c = new Consumer(ss);
        new Thread(p).start();
//        new Thread(p).start();
//        new Thread(p).start();
        new Thread(c).start();
    }
}
class WoTou {
    int id;
    WoTou(int id) {
        this.id = id;
    }
    public String toString() {
        return "WoTou : " + id;
    }
}
class SyncStack {
    int index = 0;
    WoTou[] arrWT = new WoTou[3];
    public synchronized void push(WoTou wt) {
        while(index == arrWT.length) {
            try {
                this.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        this.notifyAll();
        arrWT[index] = wt;
        index ++;
    }
    public synchronized WoTou pop() {
        while(index == 0) {
            try {
                this.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        this.notifyAll();
        index--;
        return arrWT[index];
    }
}
class Producer implements Runnable {
    public static int len1 = 0;//留给图形化界面用
    SyncStack ss = null;
    Producer(SyncStack ss) {
        this.ss = ss;
    }
    public void run() {
        for(int i = 0; i < 100; i++) {
            WoTou wt = new WoTou(i);
            ss.push(wt);


            len1 += 1;
            if(len1 > 100) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("len1 = " + len1);
            System.out.println("生产了: " + wt);
            try {
                Thread.sleep((int)(Math.random() * 200));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
class Consumer implements Runnable {
    public static int len2 = 0;//留给图形化界面用
    SyncStack ss = null;
    Consumer(SyncStack ss) {
        this.ss = ss;
    }
    public void run() {
        for(int i = 0; i < 100; i++) {
            WoTou wt = ss.pop();
            len2 += 1;
            if(len2 > 100) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("len2 = " + len2);
            System.out.println("消费了: " + wt);
            try {
                Thread.sleep((int)(Math.random() * 1000));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
