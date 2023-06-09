package woo.core.exception;

/** Exception for unknown product keys. */
public class UnknownProductKeyException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 2020091923351L;

  /** Unknown key. */
  String _key;

  /** @param key Unknown key to report. */
  public UnknownProductKeyException(String key) {
    _key = key;
  }

  public String getKey() {
    return _key;
  }

}
