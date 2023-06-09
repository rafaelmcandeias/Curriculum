package woo.core.exception;

/** Exception for unknown service levels. */
public class UnknownServiceLevelException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 2020091923351L;

  /** Unknown level. */
  private String _level;

  /** @param level Unknown level to report. */
  public UnknownServiceLevelException(String level) {
    _level = level;
  }

  public String getServiceLevel() {
    return _level;
  }

}
