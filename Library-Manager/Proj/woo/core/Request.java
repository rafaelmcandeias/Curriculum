package woo.core;

import java.io.Serializable;

public class Request implements Serializable {
	/** Serial number for serialization. */
	private static final long serialVersionUID = 52019202015L;

	private Product _product;
	private int _quantity;

	/**
   * @param product
   * @param quantity
   */
	public Request(Product product, int quantity) {
		_product = product;
		_quantity = quantity;
	}

	/**
   * Function that returns the product atribute
   * @return _product
   */
	public Product getProduct() {
		return _product;
	}

	/**
   * Function that returns the quantity atribute
   * @return _quantity
   */
	public int getQuantity() {
		return _quantity;
	}
}
