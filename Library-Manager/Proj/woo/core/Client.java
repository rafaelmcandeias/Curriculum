package woo.core;

import java.util.*;

import woo.core.enumeration.Statute;

public class Client implements Comparable<Client>, IObserver{

	/** Serial number for serialization. */
	private static final long serialVersionUID = 5201920203L;

	private String _id;
	private String _name;
	private String _address;
	private int _points;
	private Statute _statute;
	/** stores all client's purchases */
	private Map<Integer, Sale> _purchases;
	/** stores all client's notifications */
	private List<Notification> _notifications;


	/**
	 * @param id client id
	 * @param name client name
	 * @param address client address
	 */
	public Client(String id, String name, String address){
		_id = id;
		_name = name;
		_address = address;
		_purchases = new TreeMap<>();
		_notifications = new ArrayList<>();
		updateStatute();
	}

	/**
  * Function that returns the id attribute
  * @return _id
  */
	public String getID(){
		return _id;
	}

	/**
  * Function that returns the name attribute
  * @return _name
  */
	public String getName(){
		return _name;
	}

	/**
  * Function that returns the address attribute
  * @return _address
  */
	public String getAddress(){
		return _address;
	}

	/**
  * Function that returns the points attribute
  * @return _points
  */
	public int getPoints(){
		return _points;
	}

	/**
  * Function that adds a purchase to the purchases attribute
  * @param sale
  */
	protected void addPurchase(Sale sale) {
		_purchases.put(sale.getID(), sale);
	}

	/**
  * Function that returns all client's purchases
  * @return list of transactions
  */
	public List<Sale> getPurchases(){
		return Collections.unmodifiableList(new ArrayList<>(_purchases.values()));
	}

	public List<Notification> getNotifications(){
		return Collections.unmodifiableList(_notifications);
	}

	protected void clearNotifications(){
		_notifications.clear();
	}

	/**
  	* Function that increases the points attribute
  	* @param points - points to add
  	*/
	protected void setPoints(int points){
		_points+= points;
	}

	/**
  	* Function that changes the client's status
  	*/
	protected void updateStatute(){
		/** if has more than 25000 points, turns into elite */
		if(_points > 25000){
			_statute = Statute.ELITE;
		}
		/** if has more than 2000 points, turns into selection */
		else if(_points > 2000){
			_statute = Statute.SELECTION;
		}
		/** if has less or equal to 2000, turns into normal */
		else {
			_statute = Statute.NORMAL;
		}
	}

	/**
  	* Function that returns the statute attribute
  	* @return _statute
  	*/
	public Statute getStatute(){
		return _statute;
	}

	/**
  * Function that returns the statute attribute
  * @param statute
  */
	protected void setStatute(Statute statute){
		_statute = statute;
	}

	public int getPurchasesValue() {
		double cost = 0.0;
		ArrayList<Sale> sales = new ArrayList<>(_purchases.values());
		Iterator<Sale> itr = sales.iterator();

		while(itr.hasNext()) {
			Sale sale = itr.next();
			cost+= sale.getBaseValue();
		}

		return (int) Math.round(cost);
	}

	public int getPaidPurchasesValue() {
		double paidValue = 0;

		ArrayList<Sale> purchases = new ArrayList<>(_purchases.values());
		Iterator<Sale> itr = purchases.iterator();

		while(itr.hasNext()) {
			Sale sale = itr.next();
			if(sale.isPaid()){
					paidValue += sale.getPaidValue();
			}

		}

		return (int) Math.round(paidValue);
	}

	/**
  	* Function that returns the client's data
  	* @return client's information
  	*/
	public String showClientData(){
		return _id + "|" + _name + "|" + _address + "|" + _statute.name() + "|" + getPurchasesValue() + "|" + getPaidPurchasesValue();
	}

	/**
  	* Function that compares a client with this client
  	* @param client client object
  	* @return compare value
  	*/
	public int compareTo(Client client){
		return _id.toLowerCase().compareTo(client.getID().toLowerCase());
	}

	public String showBoughtProducts() {
		HashMap<Product, Integer> boughProducts = new HashMap<>();
		for (Sale sale : _purchases.values()) {
			Product product = sale.getProduct();
			if (boughProducts.containsKey(product)){
				int n = boughProducts.get(product);
				n += 1;
				boughProducts.replace(product, n);
			}else{
				boughProducts.put(product, 1);
			}
		}

		String lines = null;
		for (Map.Entry<Product, Integer> entry : boughProducts.entrySet()) {
			Product product = entry.getKey();
			String productName = "livro";

			if (product instanceof Container){
				productName = "contentor";
			}
			else if (product instanceof Box){
				productName = "caixa";
			}
			
			lines += "Comprou " + boughProducts.get(product) + " quantidades de " + productName + " fornecido por " + product.getSupplier() + ".\n";
		}

		return lines;
	}
	
	@Override
	public void update(Notification notification) {
		_notifications.add(notification);
	}
}
