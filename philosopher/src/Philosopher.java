import java.awt.Color;
import java.awt.Graphics;
import java.util.Random;
public class Philosopher implements Runnable {
    int sleepTime = 3000;
    int x, y;
    int x1, y1, x2, y2;
    private int id;
    private boolean state; //false停止思考，等待筷子。  true思考
    MainFrame mf;
    boolean eat = false;
    public Philosopher(int id, MainFrame mf, int x1, int y1, int x2, int y2, int x, int y) {
        this.id = id;
        this.mf = mf;
        this.x1 = x1;
        this.x2 = x2;
        this.y1 = y1;
        this.y2 = y2;
        this.x = x;
        this.y = y;
    }

    public void draw(Graphics g) {
        g.setColor(Color.blue);
        g.fillOval(x, y, 100, 100);
        g.setColor(Color.white);
        if(state == true) {
            g.drawString("thinking", x + 40, y + 40);
        } else if(eat == true) {
            g.drawString("eating", x + 40, y + 40);
        } else {
            g.drawString("waiting", x + 40, y + 40);
        }
        if(eat) {
            g.setColor(Color.ORANGE);
            g.drawLine(x1, y1, x2, y2);
            mf.chopstickArray.chopsticks[id].used = true;
            mf.chopstickArray.chopsticks[(id + 5 - 1) % 5].used = true;
        }
    }
    public synchronized void thinking() {
        if (state) { // 如果在思考,说明这个哲学家两面的筷子没用
            mf.chopstickArray.getById(id).setAvailable(true);
            mf.chopstickArray.getLast(id).setAvailable(true);
            eat = false;
//            mf.repaint();

            try {
                Thread.sleep(sleepTime);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        state = false;//要吃饭了
    }
    public synchronized void eating() {
        if (!state) { // 等待,要吃饭了
            if (mf.chopstickArray.getById(id).isAvailable()) { // 如果哲学家右手边的筷子可用
                if (mf.chopstickArray.getLast(id).isAvailable()) { // 如果左手边的筷子也可用
                    // 然后将这个能吃饭的哲学家两侧的筷子都设置为不可用
                    mf.chopstickArray.getById(id).setAvailable(false);
                    mf.chopstickArray.getLast(id).setAvailable(false);
                    eat = true;
                    mf.repaint();


                    try {
                        Thread.sleep(sleepTime);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                } else {
                    // 右手边的筷子可用，但是左手边的不可用
                    try {
                        wait(new Random().nextInt(100));
//                        wait(sleepTime);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            } else {
                // 如果哲学家右手边的筷子不可用则等待
                try {
                    wait(new Random().nextInt(100));
//                    wait(sleepTime);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        state = true;
        eat = false;
    }
    @Override
    public void run() {
        for (int i = 0; i < 10; ++i) {
            thinking();
            eating();
        }
    }
    @Override
    public String toString() {
        return " 哲学家 " + id;
    }
}
