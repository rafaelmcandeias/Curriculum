package woo.core;

/**
 * @author Regino MBonge-ist96991 e Rafael Candeias-ist93748
 * @version final
 */

import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.List;

import woo.core.exception.*;

/**
 * StoreManager: façade for the core classes.
 */
public class StoreManager{

	/** Current filename. */
	private String _filename = "";

	/** The actual store. */
	private Store _store = new Store();

	/** System time */
	private Time _time = new Time();

	public String getFile(){
		return _filename;
	}

	public int getAvailableBalance(){
		return _store.getAvailableBalance();
	}

	public int getAccountingBalance(){
		return _store.getAccountingBalance(getCurrentDate());
	}

	public int getCurrentDate(){
		return _time.getCurrentDate();
	}

	public void setProductPrice(String productID, int newPrice) throws UnknownProductKeyException{
		_store.setProductPrice(productID, newPrice);
	}

	public List<Sale> getClientPaidPurchases(String clientID)
		throws UnknownClientKeyException{
		return _store.getClientPaidPurchases(clientID);
	}

	public List<Product> getProductsUnderTopPrice(int topPrice){
		return _store.getProductsUnderTopPrice(topPrice);
	}

	public boolean toggleTransactions(String supplierID) throws UnknownSupplierKeyException {
		return  _store.toggleTransactions(supplierID);
	}

	public boolean toggleProductNotifications(String clientID, String productID)
			throws UnknownClientKeyException, UnknownProductKeyException{
		return _store.toggleProductNotifications(clientID, productID);
	}

	/**
	 * @param numberOfDays - number of days to advance
	 * @throws InvalidDateException
	 */
	public void advanceDate(int numberOfDays) throws InvalidDateException{
		if(numberOfDays < 0){
			throw new InvalidDateException(numberOfDays);
		}
		_time.advanceDate(numberOfDays);
	}

	public void clearNotifications(Client client){
		client.clearNotifications();
	}



	/**
	 * @param id - client id
	 * @param name - client name
	 * @param address - client address
	 * @throws DuplicateClientKeyException
	 */
	public void registerClient(String id, String name, String address)
			throws DuplicateClientKeyException{
		_store.registerClient(id, name, address);
	}


	/**
	 * @param id - supplier id
	 * @param name - supplier name
	 * @param address - supplier address
	 * @throws DuplicateSupplierKeyException
	 * @throws UnknownSupplierKeyException
	 */
	public void registerSupplier(String id, String name, String address)
			throws DuplicateSupplierKeyException, UnknownSupplierKeyException{
		_store.registerSupplier(id, name, address);
	}


	/**
	 * @param id - book id
	 * @param supplierID - book supplier id
	 * @param price - book price
	 * @param criticalValue - book critical value
	 * @param title - book title
	 * @param author - book author
	 * @param isbn - book isbn
	 * @throws DuplicateProductKeyException
	 */
	public void registerBook(String id, String supplierID, int price, int criticalValue, String title, String author, String isbn)
			throws DuplicateProductKeyException, UnknownSupplierKeyException{
		_store.registerBook(id, supplierID, price, criticalValue, title, author, isbn);
	}


	/**
	 * @param id - container id
	 * @param supplierID - container id
	 * @param price - container price
	 * @param criticalValue - container critical value
	 * @param serviceLevel - level of service (NORMAL, AIR, PERSONAL, EXPRESS)
	 * @param serviceQuality - quality of service (B4, C4, C5, DL)
	 * @throws UnknownServiceLevelException
	 * @throws DuplicateProductKeyException
	 * @throws UnknownServiceTypeException
	 */
	public void registerContainer(String id, String supplierID, int price, int criticalValue, String serviceLevel, String serviceQuality)
			throws DuplicateProductKeyException, UnknownServiceLevelException,
			UnknownServiceTypeException, UnknownSupplierKeyException {
		_store.registerContainer(id, supplierID, price, criticalValue, serviceLevel, serviceQuality);
	}


	/**
	 * @param id - box id
	 * @param supplierID - supplier id
	 * @param price - box price
	 * @param criticalValue - box critical value
	 * @param serviceLevel - level of service (NORMAL, AIR, PERSONAL, EXPRESS)
	 * @throws UnknownServiceLevelException
	 * @throws DuplicateProductKeyException
	 */
	public void registerBox(String id, String supplierID, int price, int criticalValue, String serviceLevel)
			throws DuplicateProductKeyException, UnknownServiceTypeException,
			UnknownSupplierKeyException{
		_store.registerBox(id, supplierID, price, criticalValue, serviceLevel);
	}


	public void registerSale(String clientID, int paymentDeadline, String productID, int quantity)
			throws UnavailableProductException, UnknownProductKeyException, UnknownClientKeyException {
			try{
				_store.registerSale(clientID, paymentDeadline, productID, quantity, getCurrentDate());

			}catch(NullPointerException e){
				System.out.println("AQUIIIIIIIIIIII");
			}
	}

	public void checkRequest(String supplierID, String productID, int quantity)
			throws UnknownProductKeyException, UnauthorizedSupplierException,
			WrongSupplierException{
		_store.checkRequest(supplierID, productID, quantity);
	}

	public void registerOrder(String supplierID, List<Request> requestsWrapper) {
		_store.registerOrder(supplierID, requestsWrapper, getCurrentDate());
	}

	public Transaction getTransaction(int transactionID)
			throws UnknownTransactionKeyException{
		return _store.getTransaction(transactionID);
	}

	public List<Transaction> getSupplierTransactions(String supplierID)
			throws UnknownSupplierKeyException {
		return _store.getSupplierTransactions(supplierID);
	}

	public List<Sale> getClientPurchases(String clientID)
			throws UnknownClientKeyException {
		return _store.getClientPurchases(clientID);
	}

	public void pay(int saleID)
			throws UnknownTransactionKeyException, NoPaymentStrategy{
		_store.paySaleTransaction(saleID, getCurrentDate());
	}


	public List<Client> getClients(){
		return _store.getClients();
	}

	public List<Product>  getProducts(){
		return _store.getProducts();
	}

	public List<Supplier> getSuppliers(){
		return _store.getSuppliers();
	}

	/**
	 * @param clientID
	 * @return client object
	 * @throws UnknownClientKeyException
	 */
	public Client getClient(String clientID)
			throws UnknownClientKeyException{
		return _store.getClient(clientID);
	}

	/**
	 * @param productID
	 * @return product object
	 * @throws UnknownProductKeyException
	 */
	public Product getProduct(String productID)
			throws UnknownProductKeyException{
		return _store.getProduct(productID);
	}

	/**
	 * @param supplier
	 * @throws UnknownSupplierKeyException
	 */
	public void checkSupplier(String supplierID)
			throws UnknownSupplierKeyException{
		_store.checkSupplier(supplierID);
	}


	/**
	 * @throws IOException
	 * @throws FileNotFoundException
	 * @throws MissingFileAssociationException
	 */
	public void save() throws IOException, FileNotFoundException, MissingFileAssociationException {

		if("".equals(_filename)){
			throw new MissingFileAssociationException();
		}

		try (ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream(_filename));){
			outputStream.writeObject(_store);
			outputStream.writeObject(_time);
			outputStream.writeObject(_filename);
		} catch(FileNotFoundException ex){
			throw ex;
		} catch(IOException ioe){
			throw ioe;
		}
	}

	/**
	 * @param filename
	 * @throws MissingFileAssociationException
	 * @throws IOException
	 * @throws FileNotFoundException
	 */
	public void saveAs(String filename) throws MissingFileAssociationException, FileNotFoundException, IOException {
		_filename = filename;
		save();
	}

	/**
	 * @param filename
	 * @throws UnavailableFileException
	 */
	public void load(String filename) throws UnavailableFileException {
		try(ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(filename))){
			_store = (Store) inputStream.readObject();
			_time = (Time) inputStream.readObject();
			_filename = filename;
		} catch (IOException | ClassNotFoundException ex){
			throw new UnavailableFileException(filename);
		}

	}

	/**
	 * @param textfile
	 * @throws ImportFileException
	 */
	public void importFile(String textfile) throws ImportFileException {
		try {
			_store.importFile(textfile);
		} catch (IOException | BadEntryException | NumberFormatException
				| DuplicateSupplierKeyException | DuplicateClientKeyException
				| DuplicateProductKeyException | UnknownServiceLevelException
				| UnknownServiceTypeException | UnknownSupplierKeyException
				| UnknownProductKeyException e) {

			e.printStackTrace();
			throw new ImportFileException(textfile);
		}
	}


}
