package woo.core.exception;

public class UnauthorizedSupplierException extends Exception {
	  /** Serial number for serialization. */
	  private static final long serialVersionUID = 2020092000541L;

	  /** Unknown key. */
	  private String _key;

	  /** @param key unauthorized key to report. */
	  public UnauthorizedSupplierException(String key) {
	    _key = key;
	  }

	  public String getKey() {
	    return _key;
	  }
}


