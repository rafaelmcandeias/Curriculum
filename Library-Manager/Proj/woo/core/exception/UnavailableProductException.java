package woo.core.exception;

/** Exception thrown when a client key is duplicated. */
public class UnavailableProductException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 2017090213241L;

  /** Product key. */
  private String _key;

  /** Requested amount. */
  private int _requested;

  /** Available amount. */
  private int _available;

  /**
   * @param key the requested key
   * @param requested
   * @param avaliable
   */
  public UnavailableProductException(String key, int requested, int available) {
    _key = key;
    _available = available;
    _requested = requested;
  }

  public String getKey() {
    return _key;
  }

  public int getRequested() {
    return _requested;
  }

  public int getAvailable() {
    return _available;
  }

}
