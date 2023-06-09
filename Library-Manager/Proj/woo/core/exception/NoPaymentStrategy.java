package woo.core.exception;

public class NoPaymentStrategy extends Exception {
	  /** Class serial number. */
	  private static final long serialVersionUID = 20140930104811L;

	  public NoPaymentStrategy() {
	    super("No payment strategy for the payment interval");
	  }

}
