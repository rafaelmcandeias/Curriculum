package woo.core;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Order extends Transaction {
	/** Serial number for serialization. */
	private static final long serialVersionUID = 52019202013L;

	Supplier _supplier;
	/** list of requests ordered to the supplier */
	List<Request> _requests;

	/**
	 * @param supplier - supplier
	 * @param requests - list of requests to be ordered
	 * @param payday - date of payment
	 */
	public Order(Supplier supplier, List<Request> requests, int payday) {
		super(payday);
		_supplier = supplier;
		_requests = requests;
	}

	/**
	 * Function that shows the Transaction's description
	 * @return String of information
	 */
	public String showTransaction(int currentDate) {
		String format = "";
		format += getID() + "|" + _supplier.getID() + "|" + (int) Math.round(getBaseValue()) + "|" + currentDate + "\n" ;

		for(Request request : _requests) {
			format += request.getProduct().getID() + "|" + request.getQuantity() + "\n";
		}

		return format;
	}

	/**
	 * Function that returns the supplier associated to this order
	 * @return _supplier
	 */
	public Supplier getSupplier() {
		return _supplier;
	}

	/**
	 * Function that returns all products in the order
	 * @return list of products
	 */
	public List<Product> getProducts(){
		List<Product> products = new ArrayList<>();
		for(Request request : _requests) {
			products.add(request.getProduct());
		}
		return Collections.unmodifiableList(products);
	}

	/**
	 * Function that returns the base value spent on the order
	 * @return value of purchase
	 */
	public double getTotalCost() {
		return getBaseValue();
	}
}
