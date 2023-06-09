package woo.core.exception;

public class WrongSupplierException extends Exception{
	  /** Serial number for serialization. */
	  private static final long serialVersionUID = 2020092000541L;

	  /** Supplier key. */
	  private String _skey;

	  /** Product key. */
	  private String _pkey;

	  /** 
	   * @param skey supplier key.
	   * @param pkey product key. 
	   */
	  public WrongSupplierException(String skey, String pkey) {
	    _skey = skey;
	    _pkey = pkey;
	  }
	  
	  public String getSupplierKey() {
	    return _skey;
	  }
	  
	  public String getProductKey() {
	    return _pkey;
	  }
}
