package woo.core;

import java.io.Serializable;

public abstract class Product extends Observable implements Serializable, Comparable<Product>{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 5201920206L;

	private String _id;
	private int _price;
	private int _criticalValue;
	private int _stock;
	private Supplier _supplier;
	private int _nDays;

	/**
	 * @param id - product id
	 * @param supplier - product supplier id
	 * @param price - product price
	 * @param criticalValue - product critical value
	 */
	public Product(String id, Supplier supplier, int price, int criticalValue, int nDays){
		_id = id;
		_supplier = supplier;
		_price = price;
		_criticalValue = criticalValue;
		_nDays = nDays;
	}

	/**
   * Function that returns the nDays atribute
   * @return _nDays
   */
	public int getNDays(){
		return _nDays;
	}

	/**
   * Function that returns the id atribute
   * @return _id
   */
	public String getID(){
		return _id;
	}

	/**
   * Function that returns the supplier atribute
   * @return _supplier
   */
	public Supplier getSupplier(){
		return _supplier;
	}

	/**
   * Function that changes the products price
   * @param newPrice
   */
	protected void setPrice(int newPrice){
		_price = newPrice;
	}

	/**
   * Function that returns the price atribute
   * @return _price
   */
	public int getPrice(){
		return _price;
	}

	/**
   * Function that returns the critical value atribute
   * @return _criticalValue
   */
	public int getCriticalValue(){
		return _criticalValue;
	}

	/**
   * Function that returns the stock atribute
   * @return _stock
   */
	public int getStock(){
		return _stock;
	}

	/**
   * Function that increases the amount of stock
   * @param quantity new stock quantity
   */
	protected void setStock(int quantity){
		_stock += quantity;
	}


	/**
   * Function that compares a product with this product
   * @param prod product object to compare
   * @return value of compare
   */
	public int compareTo(Product prod){
		return _id.toLowerCase().compareTo(prod.getID().toLowerCase());
	}

	/**
   * Function that returns the Product's description
   * @return iformation of Product
   */
	public abstract String showProductData();
}
