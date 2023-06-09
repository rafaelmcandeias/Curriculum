package woo.core.exception;

/** Exception thrown when a supplier key is duplicated. */
public class DuplicateSupplierKeyException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 2017090213241L;

  /** Supplier key. */
  private String _key;

  /** @param key the duplicated key */
  public DuplicateSupplierKeyException(String key) {
    _key = key;
  }

  public String getKey() {
    return _key;
  }

}
