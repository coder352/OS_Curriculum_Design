// 编码方式 ISO-8859-1
import java.awt.*;
import java.awt.event.*;
public class MainFrame extends Frame{
    private static Toolkit tk = Toolkit.getDefaultToolkit();
    private static boolean init = false;
    SyncStack ss;
    Producer p;
    Consumer c;
    private static Image[] imgs = {
            tk.getImage(MainFrame.class.getClassLoader().getResource("images/0.jpg")),
            tk.getImage(MainFrame.class.getClassLoader().getResource("images/1.jpg")),
    };
    public static final int REC_WIDTH = 600;
    public static final int REC_HEIGH = 15;
    public static final int REC1_X = 100;
    public static final int REC1_Y = 300;
    public static final int REC2_X = 100;
    public static final int REC2_Y = 500;
    BloodBar bar1 = new BloodBar(REC1_X, REC1_Y, REC_WIDTH, REC_HEIGH, 0);
    BloodBar bar2 = new BloodBar(REC2_X, REC2_Y, REC_WIDTH, REC_HEIGH, 1);
    public void paint(Graphics g) {
        bar1.draw(g);
        bar2.draw(g);
    }
    public void launchFrame() {
        setLocation(100, 100);
        setSize(800, 600);
        setResizable(false);
        setBackground(Color.green);
        setTitle("Police_Thief");
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
        addKeyListener(new KeyMonitor());
        setVisible(true);
        new Thread(new PaintThread()).start();
    }
    public static void main(String[] args) {
        new MainFrame().launchFrame();
    }
    private class KeyMonitor extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            int key = e.getKeyCode();
            if(key == KeyEvent.VK_CONTROL) {
                ss = new SyncStack();
                p = new Producer(ss);
                c = new Consumer(ss);
                new Thread(p).start();
                new Thread(c).start();
            }
        }

    }
    private class PaintThread implements Runnable {
        public void run() {
            while(true) {//这里注意一下
                repaint();
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    private class BloodBar {//画警察和小偷血条的类
        int x, y, width, heigh, id;
        public BloodBar(int x, int y, int width, int heigh, int id) {
            this.x = x;
            this.y = y;
            this.width = width;
            this.heigh = heigh;
            this.id = id;
        }
        public void draw(Graphics g) {
            if(!init) {//这样做是为了解决2.8_2第一次花爆炸画不出来
                for (int i = 0; i < imgs.length; i++) {
                    g.drawImage(imgs[i], -100, -100, null);
                }
                init = true;
            }
            Color color = g.getColor();
            g.setColor(Color.RED);
            g.drawRect(x, y, width, heigh);
            int w;
            if(id == 0)
                w = p.len1;
            else
                w = c.len2;
            int ww = w * (REC_WIDTH / 100);//将血条的长度设置成100
            g.fillRect(x, y, ww, heigh);
            g.setColor(color);
            g.drawImage(imgs[id], x + ww, y - 100, null);
            g.drawString(w + "", x + ww, y + 30);
        }
    }
}
