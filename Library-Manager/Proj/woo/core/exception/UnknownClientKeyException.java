package woo.core.exception;

/** Exception for unknown client keys. */
public class UnknownClientKeyException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 2020091923351L;

  /** Unknown key. */
  private String _key;

  /** @param key Unknown key to report. */
  public UnknownClientKeyException(String key) {
    _key = key;
  }

  public String getKey() {
    return _key;
  }

}
