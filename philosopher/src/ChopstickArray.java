public class ChopstickArray {
    Chopstick[] chopsticks;
    int x1, y1, x2, y2;
    public ChopstickArray(int size) {
        chopsticks = new Chopstick[size];//从正下方顺时针排序
        x1 = 400;
        y1 = 485;
        x2 = 400;
        y2 = 435;
        chopsticks[0] = new Chopstick(0, x1, y1, x2, y2);
        x1 = (int) (400 - 185 * Math.sin(72.0 / 180 * 3.1415926));
        y1 = (int) (300 + 185 * Math.cos(72.0 / 180 * 3.1415926));
        x2 = (int) (400 - 135 * Math.sin(72.0 / 180 * 3.1415926));
        y2 = (int) (300 + 135 * Math.cos(72.0 / 180 * 3.1415926));
        chopsticks[1] = new Chopstick(1, x1, y1, x2, y2);
        x1 = (int)(400 - 185 * Math.sin(36.0 / 180 * 3.1415926));
        y1 = (int)(300 - 185 * Math.cos(36.0 / 180 * 3.1415926));
        x2 = (int)(400 - 135 * Math.sin(36.0 / 180 * 3.1415926));
        y2 = (int)(300 - 135 * Math.cos(36.0 / 180 * 3.1415926));
        chopsticks[2] = new Chopstick(2, x1, y1, x2, y2);
        x1 = (int)(400 + 185 * Math.sin(36.0 / 180 * 3.1415926));
        y1 = (int)(300 - 185 * Math.cos(36.0 / 180 * 3.1415926));
        x2 = (int)(400 + 135 * Math.sin(36.0 / 180 * 3.1415926));
        y2 = (int)(300 - 135 * Math.cos(36.0 / 180 * 3.1415926));
        chopsticks[3] = new Chopstick(3, x1, y1, x2, y2);
        x1 = (int)(400 + 185 * Math.sin(72.0 / 180 * 3.1415926));
        y1 = (int)(300 + 185 * Math.cos(72.0 / 180 * 3.1415926));
        x2 = (int)(400 + 135 * Math.sin(72.0 / 180 * 3.1415926));
        y2 = (int)(300 + 135 * Math.cos(72.0 / 180 * 3.1415926));
        chopsticks[4] = new Chopstick(4, x1, y1, x2, y2);
    }
    public Chopstick getById(int id) {
        return chopsticks[id];
    }
    public Chopstick getLast(int id) {
        if (id == 0) {
            return chopsticks[chopsticks.length - 1];
        } else {
            return chopsticks[id - 1];
        }
    }
}