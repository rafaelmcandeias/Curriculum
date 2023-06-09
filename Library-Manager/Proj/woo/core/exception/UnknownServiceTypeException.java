package woo.core.exception;

/** Exception for unknown service types. */
public class UnknownServiceTypeException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 2020091923351L;

  /** Unknown type. */
  private String _type;

  /** @param type Unknown type to report. */
  public UnknownServiceTypeException(String type) {
    _type = type;
  }

  public String getServiceType() {
    return _type;
  }

}
