package woo.core;

import java.io.Serializable;

import java.util.*;

public class Supplier implements Serializable, Comparable<Supplier>{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 5201920208L;

	private String _id;
	private String _name;
	private String _address;
	private boolean _activity;
	private List<Product> _products;
	private Map<Integer, Transaction> _transactions;

	/**
	 * @param id supplier id
	 * @param name supplier name
	 * @param address supplier address
	 */
	public Supplier(String id, String name, String address){
		_id = id;
		_name = name;
		_address = address;
		_activity = true;
		_products = new ArrayList<>();
		_transactions = new TreeMap<>();
	}

	public String getID(){
		return _id;
	}

	public String getName(){
		return _name;
	}

	public String getAddress(){
		return _address;
	}

	public boolean isActive(){
		return _activity;
	}


	/**
	 * @param state true to set supplier to active else will be inactive
	 */
	protected void setActivity(boolean state){
		_activity = state;
	}

	protected void addProduct(Product product) {
		_products.add(product);
	}

	protected void addOrder(Transaction order) {
		_transactions.put(order.getID(), order);
	}
	/**
	 * @param productID - the product to verify if the supplier supplies
	 */
	public boolean suppliesProduct(Product product) {
		return _products.contains(product);
	}

	public Product getProduct(String productID) {
		for(Product product : _products) {
			if(product.getID().equalsIgnoreCase(productID)) {
				return product;
			}
		}

		return null;

	}

	public List<Product> getProducts(){
		return Collections.unmodifiableList(_products);
	}

	public List<Transaction> getOrders(){
		return Collections.unmodifiableList(new ArrayList<Transaction>(_transactions.values()));
	}

	public String showSupplierData(String activity){
		return _id + "|" + _name + "|" + _address + "|" + activity;
	}


	/**
	 * @param supplier supplier object to compare to
	 */
	public int compareTo(Supplier supplier){
		return _id.toLowerCase().compareTo(supplier.getID().toLowerCase());
	}

}
