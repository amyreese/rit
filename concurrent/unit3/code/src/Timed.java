
public interface Timed {
  void pretick() throws TimeStop;
  void tick();
}