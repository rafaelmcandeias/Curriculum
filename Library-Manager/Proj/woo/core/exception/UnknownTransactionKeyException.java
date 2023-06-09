package woo.core.exception;

/** Exception for unknown transaction keys. */
public class UnknownTransactionKeyException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 2020091920081L;

  /** Unknown key. */
  private int _key;

  /** @param key Unknown key to report. */
  public UnknownTransactionKeyException(int key) {
    _key = key;
  }

  public int getKey() {
    return _key;
  }

}
