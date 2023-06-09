package woo.core;

import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;

import woo.core.exception.*;


public class MyParser {
	private Store _store;  // ou outra entidade

	MyParser(Store s) {
		_store = s;
	}

	/**
	 * Function that reads all lines from input file and parses them
	 * @param fileName name of the file to be imported
	 * @throws IOException
	 * @throws BadEntryException
	 * @throws DuplicateSupplierKeyException
	 * @throws DuplicateClientKeyException
	 * @throws DuplicateProductKeyException
	 * @throws UnknownServiceLevelException
	 * @throws UnknownServiceTypeException
	 * @throws NumberFormatException
	 * @throws UnknownSupplierKeyException
	 */
	void parseFile(String fileName) throws IOException, BadEntryException,
	DuplicateSupplierKeyException, DuplicateClientKeyException,DuplicateProductKeyException,
	UnknownServiceLevelException, UnknownServiceTypeException, NumberFormatException,
	UnknownSupplierKeyException, UnknownProductKeyException{

		try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
			String line;

			while ((line = reader.readLine()) != null){
				parseLine(line);
			}
		}
	}


	/**
	 * Function that parses the line
	 * @param line a line in the file imported
	 * @throws IOException
	 * @throws BadEntryException
	 * @throws DuplicateSupplierKeyException
	 * @throws DuplicateClientKeyException
	 * @throws DuplicateProductKeyException
	 * @throws UnknownServiceLevelException
	 * @throws UnknownServiceTypeException
	 * @throws NumberFormatException
	 */
	private void parseLine(String line) throws IOException, BadEntryException,
	DuplicateSupplierKeyException, DuplicateClientKeyException,DuplicateProductKeyException,
	UnknownServiceLevelException, UnknownServiceTypeException, NumberFormatException,
	UnknownSupplierKeyException, UnknownSupplierKeyException, UnknownProductKeyException{
		String[] components = line.split("\\|");

		switch(components[0]) {
		case "SUPPLIER":
			parseSupplier(line, components);
			break;

		case "CLIENT":
			parseClient(line, components);
			break;

		case "BOX":
			parseBox(line, components);
			break;

		case "CONTAINER":
			parseContainer(line, components);
			break;

		case "BOOK":
			parseBook(line, components);
			break;

		default:
			throw new BadEntryException("Type of line not supported: " + line);
		}
	}

	// Format: SUPPLIER|id|nome|endereço
	/**
	 * Function that parses the supplier
	 * @param line a line in the file imported
	 * @param components supplier object data (fields)
	 * @throws BadEntryException
	 * @throws DuplicateSupplierKeyException
	 * @throws UnknownSupplierKeyException
	 */
	private void parseSupplier(String line, String[] components)  throws BadEntryException, DuplicateSupplierKeyException, UnknownSupplierKeyException {
		if (components.length != 4)
			throw new BadEntryException("Invalid number of fields in supplier description (4) " + line);

		String id = components[1];
		String name = components[2];
		String address = components[3];

		_store.registerSupplier(id, name, address);
	}

	// Format: CLIENT|id|nome|endereço
	/**
	 * Function that parses the client
	 * @param line a line in the file imported
	 * @param components client object data (fields)
	 * @throws BadEntryException
	 * @throws DuplicateClientKeyException
	 */
	private void parseClient(String line, String[] components) throws BadEntryException, DuplicateClientKeyException {
		if (components.length != 4)
			throw new BadEntryException("Invalid number of fields (4) in client description: " + line);

		String id = components[1];
		String name = components[2];
		String address = components[3];

		_store.registerClient(id, name, address);
	}

	// Format: BOX|id|nivel-de-serviço|id-fornecedor|preço|valor-crítico|exemplares
	/**
	 * Function that parses the box
	 * @param line a line in the file imported
	 * @param components box object data (fields)
	 * @throws BadEntryException
	 * @throws NumberFormatException
	 * @throws UnknownServiceLevelException
	 * @throws DuplicateProductKeyException
	 *
	 */
	private void parseBox(String line, String[] components) throws BadEntryException,
	NumberFormatException, UnknownServiceTypeException, DuplicateProductKeyException,
	UnknownSupplierKeyException, UnknownProductKeyException {
		if (components.length != 7)
			throw new BadEntryException("wrong number of fields in box description  (7) " + line);

		String id = components[1];
		String serviceLevel = components[2];
		String supplierID = components[3];
		int price;
		int criticalValue;
		int stock;

		try{
			stock = Integer.parseInt(components[6]);
			price = Integer.parseInt(components[4]);
			criticalValue = Integer.parseInt(components[5]);
		} catch(NumberFormatException nfe){
			throw nfe;
		}

		// add code here
		_store.registerBox(id, supplierID, price, criticalValue, serviceLevel);
		_store.getProduct(id).setStock(stock);
	}

	// Format: BOOK|id|título|autor|isbn|id-fornecedor|preço|valor-crítico|exemplares
	/**
	 * Function that parses the book
	 * @param line a line in the file imported
	 * @param components book object data (fields)
	 * @throws BadEntryException
	 * @throws NumberFormatException
	 * @throws DuplicateProductKeyException
	 */
	private void parseBook(String line, String[] components) throws BadEntryException,
	DuplicateProductKeyException, UnknownSupplierKeyException,
	UnknownProductKeyException{
		if (components.length != 9)
			throw new BadEntryException("Invalid number of fields (9) in box description: " + line);

		String id = components[1];
		String title = components[2];
		String author = components[3];
		String isbn = components[4];
		String supplierID = components[5];
		int price;
		int criticalValue;
		int stock;

		try{
			price = Integer.parseInt(components[6]);
			criticalValue = Integer.parseInt(components[7]);
			stock = Integer.parseInt(components[8]);
		} catch(NumberFormatException nfe){
			throw nfe;
		}

		// add code here
		_store.registerBook(id, supplierID, price, criticalValue, title, author, isbn);
		_store.getProduct(id).setStock(stock);
	}

	// Format: CONTAINER|id|nivel-de-serviço|tipo-de-serviço|id-fornecedor|preço|valor-crítico|exemplares
	/**
	 * Function that parses the container
	 * @param line a line in the file imported
	 * @param components container object data (fields)
	 * @throws BadEntryException
	 * @throws UnknownServiceTypeException
	 * @throws UnknownServiceLevelException
	 * @throws DuplicateProductKeyException
	 */
	private void parseContainer(String line, String[] components) throws BadEntryException,
	DuplicateProductKeyException, UnknownServiceLevelException,
	UnknownServiceTypeException, UnknownSupplierKeyException,
	UnknownProductKeyException{
		if (components.length != 8)
			throw new BadEntryException("Invalid number of fields (8) in container description: " + line);

		String id = components[1];
		String serviceLevel = components[2];
		String serviceQuality = components[3];
		String supplierID = components[4];
		int price;
		int criticalValue;
		int stock;

		// add code here
		try{
			price = Integer.parseInt(components[5]);
			criticalValue = Integer.parseInt(components[6]);
			stock = Integer.parseInt(components[7]);
		} catch(NumberFormatException nfe){
			throw nfe;
		}

		_store.registerContainer(id, supplierID, price, criticalValue, serviceLevel, serviceQuality);
		_store.getProduct(id).setStock(stock);
	}

}
