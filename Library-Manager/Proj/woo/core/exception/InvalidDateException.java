package woo.core.exception;

/** Exception for date-related problems. */
public class InvalidDateException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 2020091923351L;

  /** Bad date. */
  private int _date;

  /** @param date bad date to report. */
  public InvalidDateException(int date) {
    _date = date;
  }

  public int getDate() {
    return _date;
  }

}
