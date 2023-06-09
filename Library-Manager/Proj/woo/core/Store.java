package woo.core;

//FIXME import classes (cannot import from pt.tecnico or woo.app)
import java.io.Serializable;
import java.io.IOException;

import java.util.*;

import woo.core.exception.*;
import woo.core.enumeration.*;

/**
 * Class Store implements a store.
 */
public class Store implements Serializable {

	/** Serial number for serialization. */
	private static final long serialVersionUID = 202009192006L;

	private static final int MINLEN = 1;

	private Map<String, Client> _clients;
	private Map<String, Supplier> _suppliers;
	private Map<String, Product> _products;
	private Map<Integer, Sale> _sales;
	private Map<Integer, Order> _orders;
	private Map<String, Notification> _notifications;


	public Store(){
		_clients = new TreeMap<>();
		_suppliers = new TreeMap<>();
		_products = new TreeMap<>();
		_sales = new TreeMap<>();
		_orders = new TreeMap<>();
		_notifications = new TreeMap<>();
	}


	protected void setProductPrice(String productID, int newPrice)
			throws UnknownProductKeyException{

		Product product = searchProduct(productID);
		if(product == null){
			throw new UnknownProductKeyException(productID);
		}

		if(newPrice < 0){
			return;
		}

		int currentPrice = product.getPrice();
		if(newPrice < currentPrice) {
			Notification notification = new Notification(product, NotificationDescription.BARGAIN);
			product.notifyObservers(notification);
			_notifications.put(product.getID(), notification);
		}

		product.setPrice(newPrice);

	}

	private Product searchProduct(String productID){

		for(Map.Entry<String, Product> entry : _products.entrySet()){
			if(entry.getKey().equalsIgnoreCase(productID)){
				return entry.getValue();
			}
		}

		return null;
	}

	private Client searchClient(String clientID){

		for(Map.Entry<String, Client> entry : _clients.entrySet()){
			if(entry.getKey().equalsIgnoreCase(clientID)){
				return entry.getValue();
			}
		}

		return null;
	}

	private Supplier searchSupplier(String supplierID){

		for(Map.Entry<String, Supplier> entry : _suppliers.entrySet()){
			if(entry.getKey().equalsIgnoreCase(supplierID)){
				return entry.getValue();
			}
		}

		return null;
	}

	public boolean toggleTransactions(String supplierID)
			throws UnknownSupplierKeyException {

		Supplier supplier = searchSupplier(supplierID);
		if(supplier == null){
			throw new UnknownSupplierKeyException(supplierID);
		}

		if(supplier.isActive()) {
			supplier.setActivity(false);
			return false;
		}else {
			supplier.setActivity(true);
			return true;
		}
	}

	public void registerSale(String clientID, int paymentDeadline, String productID, int quantity, int currentDate)
			throws UnavailableProductException, UnknownProductKeyException, UnknownClientKeyException{


		Client client = searchClient(clientID);
		if(client == null){
			throw new UnknownClientKeyException(clientID);
		}

		Product product = searchProduct(productID);
		if(product == null){
			throw new UnknownProductKeyException(productID);
		}

		int stock = product.getStock();
		if(quantity > stock){
			throw new UnavailableProductException(productID, quantity, stock);
		}


		Sale newSale = new Sale(client, currentDate + paymentDeadline, product, quantity);
		client.addPurchase(newSale);
		_sales.put(newSale.getID(), newSale);
		product.setStock(-quantity);

	}

	protected void checkRequest(String supplierID, String productID, int quantity)
			throws UnknownProductKeyException, UnauthorizedSupplierException,
			WrongSupplierException{

		Supplier supplier = searchSupplier(supplierID);

		if(!supplier.isActive()) {
			throw new UnauthorizedSupplierException(supplierID);
		}

		Product product = searchProduct(productID);
		if(product == null){
			throw new UnknownProductKeyException(productID);
		}

		if(!supplier.suppliesProduct(product)) {
			throw new WrongSupplierException(supplierID, productID);
		}

	}

	public List<Transaction> getSupplierTransactions(String supplierID)
			throws UnknownSupplierKeyException {

		Supplier supplier = searchSupplier(supplierID);
		if(supplier == null){
			throw new UnknownSupplierKeyException(supplierID);
		}

		return supplier.getOrders();

	}

	public List<Sale> getClientPurchases(String clientID)
			throws UnknownClientKeyException {

		Client client = searchClient(clientID);
		if(client == null){
			throw new UnknownClientKeyException(clientID);
		}

		return client.getPurchases();
	}

	public void registerOrder(String supplierID, List<Request> requests, int payday) {

		double cost = 0;

		for(Request request : requests) {
			Product product = request.getProduct();
			int quantity = request.getQuantity();
			int currentProductStock = product.getStock();
			product.setStock(quantity);

			if(currentProductStock == 0 && quantity > 0) {
				Notification notification = new Notification(product, NotificationDescription.NEW);
				product.notifyObservers(notification);
				_notifications.put(product.getID(), notification);
			}

			cost += product.getPrice()*quantity;

		}

		Supplier supplier = searchSupplier(supplierID);

		Order newOrder = new Order(supplier, requests, payday);
		newOrder.setBaseValue(cost);
		_orders.put(newOrder.getID(), newOrder);

		supplier.addOrder(newOrder);
	}

	public void paySaleTransaction(int saleID, int payday)
			throws UnknownTransactionKeyException{

		if(_orders.containsKey(saleID)) {
			return;
		}

		Sale sale = _sales.get(saleID);
		if(sale == null) {
			throw new UnknownTransactionKeyException(saleID);
		}

		if(sale.isPaid()) {
			return;
		}

		sale.computeSalePeriodPrice(payday);
		sale.setPayDay(payday);
		Client client = sale.getClient();
		applyStatutePenalty(client, sale.getDeadLineShift());

		sale.setPaid();

		Period period = sale.getPeriod();
		double paidValue = sale.getPaidValue();
		if(period == Period.P1 || period == Period.P2) {
			client.setPoints((int) Math.round(10*paidValue));
			client.updateStatute();
		}

	}

	public List<Sale> getClientPaidPurchases(String clientID)
			throws UnknownClientKeyException{

		Client client = searchClient(clientID);
		if(client == null){
			throw new UnknownClientKeyException(clientID);
		}

		List<Sale> sales = new ArrayList<>();

		for(Sale sale : client.getPurchases()) {
			if(sale.isPaid()){
				sales.add(sale);
			}
		}

		return Collections.unmodifiableList(sales);
	}


	public List<Product> getProductsUnderTopPrice(int topPrice){
		List<Product> products = new ArrayList<>();

		for(Map.Entry<String, Product> entry : _products.entrySet()) {
			Product product = entry.getValue();
			if(product.getPrice() < topPrice) {
				products.add(product);
			}
		}

		return Collections.unmodifiableList(products);
	}


	protected void applyStatutePenalty(Client client, int daysPassed){

		Statute clientStatute = client.getStatute();

		if(daysPassed > 15){
			if(clientStatute == Statute.ELITE){
				client.setStatute(Statute.SELECTION);
				int pointsPenalty = (int) Math.round(client.getPoints()*0.75);
				client.setPoints(-pointsPenalty);
			}
		}else if(daysPassed > 2){
			if(clientStatute == Statute.SELECTION){
				client.setStatute(Statute.NORMAL);
				int pointsPenalty = (int) Math.round(client.getPoints()*0.9);
				client.setPoints(-pointsPenalty);
			}
		}
	}




	public Transaction getTransaction(int transactionID)
			throws UnknownTransactionKeyException{

		if(_sales.containsKey(transactionID)) {
			return _sales.get(transactionID);
		}else if(_orders.containsKey(transactionID)) {
			return _orders.get(transactionID);
		}else {
			throw new UnknownTransactionKeyException(transactionID);
		}
	}

	public int getAvailableBalance(){
		double availableBalance = 0;

		for(Map.Entry<Integer, Sale> entry : _sales.entrySet()){
			Sale sale = entry.getValue();
			if(sale.isPaid()) {
				availableBalance += sale.getPaidValue();
			}
		}

		for(Map.Entry<Integer, Order> entry : _orders.entrySet()){
			Order order = entry.getValue();
			availableBalance -= order.getBaseValue();
		}

		return (int) Math.round(availableBalance);
	}

	public int getAccountingBalance(int currentDate){
		double accountingBalance = 0;

		for(Map.Entry<Integer, Sale> entry : _sales.entrySet()){
			Sale sale = entry.getValue();
			sale.computeSalePeriodPrice(currentDate);
			accountingBalance += sale.getCurrentPaymentValue();
		}

		for(Map.Entry<Integer, Order> entry : _orders.entrySet()){
			Order order = entry.getValue();
			accountingBalance -= order.getBaseValue();
		}

		return (int) Math.round(accountingBalance);
	}

	/**
	 * @param id - client id
	 * @param name - client name
	 * @param address - client address
	 * @throws DuplicateClientKeyException
	 */
	public void registerClient(String id, String name, String address)
			throws DuplicateClientKeyException{

		if(searchClient(id) != null){
			throw new DuplicateClientKeyException(id);
		}

		if(!checkEntity(id, name, address)) {
			return;
		}

		Client client = new Client(id, name, address);
		_clients.put(id, client);
		addObserver(client);
	}

	/**
	 * @param id - supplier id
	 * @param name - supplier name
	 * @param address - supplier address
	 * @throws DuplicateSupplierKeyException
	 */
	public void registerSupplier(String id, String name, String address)
			throws DuplicateSupplierKeyException{

		if(searchSupplier(id) != null){
			throw new DuplicateSupplierKeyException(id);
		}


		if(!checkEntity(id, name, address)) {
			return;
		}

		_suppliers.put(id, new Supplier(id, name, address));
	}

	private boolean checkEntity(String id, String name, String address) {
		if(id.length() < MINLEN || name.length() < MINLEN || address.length() < MINLEN) {
			return false;
		}

		return true;
	}

	private boolean checkBook(String id, int price, int criticalValue, String title, String author, String isbn) {

		if(id.length() < MINLEN || title.length() < MINLEN || author.length() < MINLEN || isbn.length() < MINLEN ) {
			return false;
		}

		if(price < 0 || criticalValue < 0) {
			return false;
		}

		return true;
	}

	/**
	 * @param id - book id
	 * @param supplierID - book id
	 * @param price - book price
	 * @param criticalValue - book critical value
	 * @param title - book title
	 * @param author - book author
	 * @param isbn - book isbn
	 * @throws DuplicateProductKeyException
	 */
	public void registerBook(String id, String supplierID, int price, int criticalValue, String title, String author, String isbn)
			throws DuplicateProductKeyException, UnknownSupplierKeyException{

		if(searchProduct(id) != null){
			throw new DuplicateProductKeyException(id);
		}

		Supplier supplier = searchSupplier(supplierID);
		if(supplier == null){
			throw new UnknownSupplierKeyException(supplierID);
		}

		if(!checkBook(id, price, criticalValue, title, author, isbn)) {
			return;
		}

		Product book = new Book(id, supplier, price, criticalValue, title, author, isbn);
		_products.put(id, book);
		supplier.addProduct(book);
		addObservers(book);
	}

	public boolean toggleProductNotifications(String clientID, String productID)
			throws UnknownClientKeyException, UnknownProductKeyException{

		Client client = searchClient(clientID);
		if(client == null) {
			throw new UnknownClientKeyException(clientID);
		}

		Product product = searchProduct(productID);
		if(product == null) {
			throw new UnknownProductKeyException(productID);
		}


		if(product.containsObserver(client)) {
			product.removeObserver(client);
			return false;
		}else {
			product.registerObserver(client);
			return true;
		}
	}

	protected void addObservers(Product product) {
		for(Map.Entry<String,Client> entry : _clients.entrySet()) {
			product.registerObserver(entry.getValue());
		}
	}
	protected void addObserver(Client client){
		for(Map.Entry<String,Product> entry : _products.entrySet()) {
			entry.getValue().registerObserver(client);
		}
	}

	/**
	 * @param id - container id
	 * @param supplierID - container supplier id
	 * @param price - container price
	 * @param criticalValue - container critical value
	 * @param serviceType - service type (NORMAL, AIR, PERSONAL, EXPRESS)
	 * @param serviceLevel - container quality of service (B4, C4, C5, DL)
	 * @throws UnknownServiceLevelException
	 * @throws DuplicateProductKeyException
	 * @throws UnknownServiceTypeException
	 */
	public void registerContainer(String id, String supplierID, int price, int criticalValue, String serviceType, String serviceLevel)
			throws DuplicateProductKeyException, UnknownServiceLevelException,
			UnknownServiceTypeException, UnknownSupplierKeyException{

		if(searchProduct(id) != null){
			throw new DuplicateProductKeyException(id);
		}

		Supplier supplier = searchSupplier(supplierID);
		if(supplier == null){
			throw new UnknownSupplierKeyException(supplierID);
		}

		try{
			ServiceType.valueOf(serviceType.toUpperCase());
		}catch(IllegalArgumentException | NullPointerException enumEx){
			throw new UnknownServiceTypeException(serviceType);
		}

		try{
			ServiceLevel.valueOf(serviceLevel.toUpperCase());
		}catch(IllegalArgumentException | NullPointerException enumEx){
			throw new UnknownServiceLevelException(serviceLevel);
		}

		if(!checkContainer(id, price, criticalValue)) {
			return;
		}

		Product container = new Container(id, supplier, price, criticalValue,
				ServiceType.valueOf(serviceType.toUpperCase()),
				ServiceLevel.valueOf(serviceLevel.toUpperCase()));

		_products.put(id, container);
		supplier.addProduct(container);
		addObservers(container);
	}

	private boolean checkContainer(String id, int price, int criticalValue) {

		if(id.length() < MINLEN) {
			return false;
		}

		if(price < 0 || criticalValue < 0) {
			return false;
		}

		return true;
	}

	/**
	 * @param id - box id
	 * @param supplierID - supplier id
	 * @param price - box price
	 * @param criticalValue - box critical value
	 * @param serviceType - box service type (NORMAL, AIR, PERSONAL, EXPRESS)
	 * @throws UnknownServiceLevelException
	 * @throws DuplicateProductKeyException
	 */
	public void registerBox(String id, String supplierID, int price, int criticalValue, String serviceType)
			throws UnknownServiceTypeException, DuplicateProductKeyException,
			UnknownSupplierKeyException {

		if(searchProduct(id) != null){
			throw new DuplicateProductKeyException(id);
		}

		Supplier supplier = searchSupplier(supplierID);
		if(supplier == null){
			throw new UnknownSupplierKeyException(supplierID);
		}

		try{
			ServiceType.valueOf(serviceType.toUpperCase());
		}catch(IllegalArgumentException | NullPointerException enumEx){
			throw new UnknownServiceTypeException(serviceType);
		}

		if(!checkContainer(id, price, criticalValue)) {
			return;
		}

		Product box = new Box(id, supplier, price, criticalValue, ServiceType.valueOf(serviceType.toUpperCase()));
		_products.put(id, box);
		supplier.addProduct(box);
		addObservers(box);
	}

	public List<Client> getClients(){
		ArrayList<Client> sortedClients = new ArrayList<>(_clients.values());
		Collections.sort(sortedClients);
		return Collections.unmodifiableList(sortedClients);
	}


	public List<Product> getProducts(){
		ArrayList<Product> sortedProducts = new ArrayList<>(_products.values());
		Collections.sort(sortedProducts);
		return Collections.unmodifiableList(sortedProducts);
	}

	public Product getProduct(String productID)
			throws UnknownProductKeyException{

		Product product = searchProduct(productID);
		if(product == null){
			throw new UnknownProductKeyException(productID);
		}

		return product;
	}

	/**
	 * @param clientID - client id
	 * @throws UnknownClientKeyException
	 */
	public Client getClient(String clientID)
			throws UnknownClientKeyException{

		Client client = searchClient(clientID);
		if(client == null){
			throw new UnknownClientKeyException(clientID);
		}

		return client;

	}



	public void checkSupplier(String supplierID)
			throws UnknownSupplierKeyException{

		Supplier supplier = searchSupplier(supplierID);
		if(supplier == null){
			throw new UnknownSupplierKeyException(supplierID);
		}
	}


	public List<Supplier> getSuppliers(){
		ArrayList<Supplier> sortedSuppliers = new ArrayList<>(_suppliers.values());
		Collections.sort(sortedSuppliers);

		return Collections.unmodifiableList(sortedSuppliers);
	}


	/**
	 * @param txtfile filename to be loaded.
	 * @throws IOException
	 * @throws BadEntryException
	 * @throws DuplicateSupplierKeyException
	 * @throws DuplicateClientKeyException
	 * @throws DuplicateProductKeyException
	 * @throws UnknownServiceLevelException
	 * @throws UnknownServiceTypeException
	 * @throws NumberFormatException
	 */
	void importFile(String txtfile) throws IOException, BadEntryException,
	DuplicateSupplierKeyException, DuplicateClientKeyException,DuplicateProductKeyException,
	UnknownServiceLevelException, UnknownServiceTypeException, NumberFormatException,
	UnknownSupplierKeyException, UnknownProductKeyException{

		MyParser parser = new MyParser(this);

		parser.parseFile(txtfile);
	}

}
