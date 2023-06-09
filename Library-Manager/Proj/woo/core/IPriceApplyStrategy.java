package woo.core;

import java.io.Serializable;

public interface IPriceApplyStrategy extends Serializable {
  /**
  * @param apply the discount or penalty to the price
  */
  void apply(Sale sale);
}
