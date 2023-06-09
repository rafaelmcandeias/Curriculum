package woo.core.exception;

/** Exception for unknown supplier keys. */
public class UnknownSupplierKeyException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 2020092000541L;

  /** Unknown key. */
  private String _key;

  /** @param key Unknown key to report. */
  public UnknownSupplierKeyException(String id) {
    _key = id;
  }

  public String getKey() {
    return _key;
  }

}
