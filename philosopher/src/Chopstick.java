import java.awt.*;

public class Chopstick {
    int x1, y1, x2, y2;
    private volatile boolean available = true;
    private int id;
    boolean used = false;
    public void draw(Graphics g) {
        if(!used) {
            g.setColor(Color.black);
            g.drawLine(x1, y1, x2, y2);
        }
    }
    public Chopstick(int id, int x1, int y1, int x2, int y2) {
        this.id = id;
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
    }
    public boolean isAvailable() {
        return available;
    }
    public void setAvailable(boolean available) {
        this.available = available;
    }
    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }
    @Override
    public String toString() {
        return "Пъзг" + id;
    }
}